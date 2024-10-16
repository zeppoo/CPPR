#include "../../../Crow-Engine/CrowEngine/libs/cppr/type_info.hpp"


TypeInfo::TypeInfo(const char* name, const primitive_type kind, size_t size) : name{name}, kind{kind}, size{size} {}

PrimitiveTypeInfo::PrimitiveTypeInfo(const char* name, const primitive_type kind, size_t size, bool isPtr) : TypeInfo(name, kind, size) {}

std::string PrimitiveTypeInfo::serialize(void* memberPtr) {
  types value = get_type(kind, memberPtr);
  return "\"" + std::string(name) + "\": " + toString(value) + "\n";
}

void PrimitiveTypeInfo::deserialize(std::string content, void* memberPtr)
{
  std::string json_value = extract_json_value(content, name);
  types value = get_type(kind, memberPtr);
  std::visit([&](auto&& arg) {
    using T = std::decay_t<decltype(arg)>;
    T* memberTypePtr;
    memberTypePtr = static_cast<T*>(memberPtr);
    *memberTypePtr = fromString<T>(json_value);
  }, value);
}

ArrayTypeInfo::ArrayTypeInfo(const char* name, size_t size, std::unique_ptr<TypeInfo> element_info)
    : TypeInfo(name, ARRAY, size), element_info(std::move(element_info)) {}

std::string ArrayTypeInfo::serialize(void* memberPtr) {
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
  ss << "]\n";
  return ss.str();
}

void ArrayTypeInfo::deserialize(std::string content, void* memberPtr) {
  std::vector<std::string> json_values = extract_json_values(content, name);
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

template<typename T>
struct is_std_vector : std::false_type {};

template<typename U, typename Alloc>
struct is_std_vector<std::vector<U, Alloc>> : std::true_type {
  using value_type = U;
};

template<typename T>
std::unique_ptr<TypeInfo> create_type_info(const char* name) {
  if constexpr (is_std_vector<T>::value) {
    using element_type = typename is_std_vector<T>::value_type;
    return std::make_unique<ArrayTypeInfo>(name, sizeof(T), create_type_info<element_type>("element"));
  } else {
    return std::make_unique<PrimitiveTypeInfo>(name, get_kind<T>(), sizeof(T), std::is_pointer<T>::value);
  }
}

types get_type(primitive_type typeKind, void* ptr) {
  types value;
  switch (typeKind) {
    case PTR: {
      void** voidPtr = toTypePtr<void*>(ptr);
      if (voidPtr) value = *voidPtr;
      break;
    }
    case BOOL: {
      bool* boolPtr = toTypePtr<bool>(ptr);
      if (boolPtr) value = *boolPtr;
      break;
    }
    case CHAR: {
      char* charPtr = toTypePtr<char>(ptr);
      if (charPtr) value = *charPtr;
      break;
    }
    case U_CHAR: {
      unsigned char* ucharPtr = toTypePtr<unsigned char>(ptr);
      if (ucharPtr) value = *ucharPtr;
      break;
    }
    case I_CHAR: {
      signed char* scharPtr = toTypePtr<signed char>(ptr);
      if (scharPtr) value = *scharPtr;
      break;
    }
    case U_SHORT: {
      unsigned short* ushortPtr = toTypePtr<unsigned short>(ptr);
      if (ushortPtr) value = *ushortPtr;
      break;
    }
    case I_SHORT: {
      short* shortPtr = toTypePtr<short>(ptr);
      if (shortPtr) value = *shortPtr;
      break;
    }
    case U_INT: {
      unsigned int* uintPtr = toTypePtr<unsigned int>(ptr);
      if (uintPtr) value = *uintPtr;
      break;
    }
    case I_INT: {
      int* intPtr = toTypePtr<int>(ptr);
      if (intPtr) value = *intPtr;
      break;
    }
    case U_LONG: {
      unsigned long* ulongPtr = toTypePtr<unsigned long>(ptr);
      if (ulongPtr) value = *ulongPtr;
      break;
    }
    case I_LONG: {
      long* longPtr = toTypePtr<long>(ptr);
      if (longPtr) value = *longPtr;
      break;
    }
    case U_LONG_LONG: {
      unsigned long long* ulonglongPtr = toTypePtr<unsigned long long>(ptr);
      if (ulonglongPtr) value = *ulonglongPtr;
      break;
    }
    case I_LONG_LONG: {
      long long* longlongPtr = toTypePtr<long long>(ptr);
      if (longlongPtr) value = *longlongPtr;
      break;
    }
    case FLOAT: {
      float* floatPtr = toTypePtr<float>(ptr);
      if (floatPtr) value = *floatPtr;
      break;
    }
    case DOUBLE: {
      double* doublePtr = toTypePtr<double>(ptr);
      if (doublePtr) value = *doublePtr;
      break;
    }
    case STRING: {
      std::string* stringPtr = toTypePtr<std::string>(ptr);
      if (stringPtr) value = *stringPtr;
      break;
    }
    default:
      throw std::runtime_error("Trying to return Unkown Type");
  }
  return value;
}