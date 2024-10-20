#include "../include/type_info.hpp"

namespace reflect
{
  TypeInfo::TypeInfo(const char* name, const primitive_type kind, size_t size) : name{name}, kind{kind}, size{size} {}

  TypeInfo::~TypeInfo() {}

  std::string TypeInfo::serialize(void* memberPtr) {return "0";}
  void TypeInfo::deserialize(std::string json, std::string parent, void* memberPtr) {}

  PrimitiveTypeInfo::PrimitiveTypeInfo(const char* name, const primitive_type kind, size_t size, bool isPtr) : TypeInfo(name, kind, size) {}

  std::string PrimitiveTypeInfo::serialize(void* memberPtr) {
    types value = get_type(kind, memberPtr);
    return "\"" + std::string(name) + "\": " + toString(value) + ",\n";
  }

  void PrimitiveTypeInfo::deserialize(std::string content, std::string parent, void* memberPtr)
  {
    std::string json_value = extract_json_value(content, name, parent);
    types value = get_type(kind, memberPtr);
    std::visit([&](auto&& arg) {
      using T = std::decay_t<decltype(arg)>;
      T* memberTypePtr;
      memberTypePtr = static_cast<T*>(memberPtr);
      *memberTypePtr = fromString<T>(json_value);
    }, value);
  }

  VectorTypeInfo::VectorTypeInfo(const char* name, size_t size, std::unique_ptr<TypeInfo> element_info)
      : TypeInfo(name, ARRAY, size), element_info(std::move(element_info)) {}

  std::string VectorTypeInfo::serialize(void* memberPtr) {
    std::vector<void*>* vec = static_cast<std::vector<void*>*>(memberPtr);  // Assuming dynamic array is stored in std::vector
    std::ostringstream ss;
    ss << "\"" << name << "\": [";
    size_t element_offset = &vec[0] - vec;
    element_offset *= element_info->size;
    char* element_ptr = reinterpret_cast<char*>(vec->data()) + element_offset;
    types element_value = get_type(element_info->kind, element_ptr);

    std::visit([&](auto&& arg) {
      using T = std::decay_t<decltype(arg)>;
      std::vector<T> list = toTypeVector<T>(vec);
      int i = 0;
      for (T element : list)
      {
        element_value = get_type(element_info->kind, &element);
        ss << toString(element_value);
        if(i++ < list.size() - 1) ss << ", ";
      }
    }, element_value);
    ss << "],\n";
    return ss.str();
  }

  void VectorTypeInfo::deserialize(std::string content, std::string parent, void* memberPtr) {
    std::vector<std::string> json_values = extract_json_values(content, name, parent);
    std::vector<void*>* vec = static_cast<std::vector<void*>*>(memberPtr); // member becomes vector holding empty data
    size_t element_offset = &vec[0] - vec; // calculate offset of the singular void* in the vector
    element_offset *= element_info->size; // get offset by size of the data
    char* element_ptr = reinterpret_cast<char*>(vec->data()) + element_offset; //reinterpret ptr as a char*
    types element_value = get_type(element_info->kind, element_ptr); // use char* and type kind to find data type
    std::visit([&](auto&& arg) { // for each type in the variant check if we can set data to the right type
      using T = std::decay_t<decltype(arg)>;
      std::vector<T*> list;
      int i = 0;
      for (T* element : list)
      {
        *element = fromString<T>(json_values[i++]);
      }
    }, element_value);
  }

  ArrayTypeInfo::ArrayTypeInfo(const char* name, size_t size, std::unique_ptr<TypeInfo> element_info)
      : TypeInfo(name, ARRAY, size), element_info(std::move(element_info)) {}

  std::string ArrayTypeInfo::serialize(void* memberPtr) {
    size_t arraySize = this->size / element_info->size;
    std::ostringstream ss;
    ss << "\"" << name << "\": [";

    // Use std::visit to handle the element type
    std::visit([&](auto&& arg) {
      using T = std::decay_t<decltype(arg)>;
      T* arrayPtr = static_cast<T*>(memberPtr);  // Cast memberPtr to the correct type

      // Serialize each element
      for (size_t i = 0; i < arraySize;) {
        ss << toString(arrayPtr[i]);  // Convert each element to a string
        if (++i < arraySize) ss << ", ";  // Add comma unless it's the last element
      }
    }, get_type(element_info->kind, memberPtr));  // Determine the element type

    ss << "],\n";  // Close the JSON array
    return ss.str();  // Return the serialized string
  }

  void ArrayTypeInfo::deserialize(const std::string content, std::string parent, void* memberPtr) {
    std::vector<std::string> json_values = extract_json_values(content, name, parent);
    size_t arraySize = this->size / element_info->size;

    if (json_values.size() != arraySize) {
      throw std::runtime_error("Mismatch between JSON values and array size");
    }

    // Use std::visit to handle the element type
    std::visit([&](auto&& arg) {
      using T = std::decay_t<decltype(arg)>;
      T* arrayPtr = static_cast<T*>(memberPtr);  // Cast memberPtr to the correct type

      // Deserialize each value from the JSON into the array
      for (size_t i = 0; i < std::min(arraySize, json_values.size()); ++i) {
        arrayPtr[i] = fromString<T>(json_values[i]);
      }
    }, get_type(element_info->kind, memberPtr));  // Determine the element type
  }

  types get_type(primitive_type typeKind, void* ptr) {
    if (!ptr) {
      throw std::runtime_error("Null pointer in get_type");
    }

    switch (typeKind) {
      case PTR: return cast_and_dereference<void*>(ptr);
      case BOOL: return cast_and_dereference<bool>(ptr);
      case CHAR: return cast_and_dereference<char>(ptr);
      case U_CHAR: return cast_and_dereference<unsigned char>(ptr);
      case I_CHAR: return cast_and_dereference<signed char>(ptr);
      case U_SHORT: return cast_and_dereference<unsigned short>(ptr);
      case I_SHORT: return cast_and_dereference<short>(ptr);
      case U_INT: return cast_and_dereference<unsigned int>(ptr);
      case I_INT: return cast_and_dereference<int>(ptr);
      case U_LONG: return cast_and_dereference<unsigned long>(ptr);
      case I_LONG: return cast_and_dereference<long>(ptr);
      case U_LONG_LONG: return cast_and_dereference<unsigned long long>(ptr);
      case I_LONG_LONG: return cast_and_dereference<long long>(ptr);
      case FLOAT: return cast_and_dereference<float>(ptr);
      case DOUBLE: return cast_and_dereference<double>(ptr);
      case STRING: return cast_and_dereference<std::string>(ptr);
      default:
        throw std::runtime_error("Unknown type in get_type");
    }
  }
}