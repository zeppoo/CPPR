# How it works

## 1. Metadata Registration

The system uses a macro-based approach to register metadata for each struct:

```cpp
struct MyStruct
{
  int number;
  std::vector<int> vector;
  std::string* namesPtr[4];
  REFLECT()
};

REFLECT_STRUCT_BEGIN(MyStruct)
  REFLECT_STRUCT_MEMBER(number)
  REFLECT_STRUCT_MEMBER(vector)
  REFLECT_STRUCT_MEMBER(namesPtr)
REFLECT_STRUCT_END()
```

This macro expands to generate metadata about the struct's fields, including their names and types before compile time.

```
#define REFLECT() \
    static reflect::StructDescriptor structDesc; \
    static void initReflection(reflect::StructDescriptor*);

#define REFLECT_STRUCT_BEGIN(type) \
    reflect::StructDescriptor type::structDesc{type::initReflection}; \
    void type::initReflection(reflect::StructDescriptor* typeDesc) { \
        using T = type; \
        typeDesc->name = #type; \
        typeDesc->size = sizeof(T);

#define REFLECT_STRUCT_MEMBER(name) \
    typeDesc->AddMember<decltype(T::name)>(#name, sizeof(T::name), offsetof(T, name));

#define REFLECT_STRUCT_END() \
    }
```

## 2. Reflection Registry

create_type_info detects if the given Type is a array or a primitive type

```cpp
template<typename T>
  struct is_std_vector : std::false_type {};

  template<typename U, typename Alloc>
  struct is_std_vector<std::vector<U, Alloc>> : std::true_type {
    using value_type = U;
  };

  template<typename T>
  std::unique_ptr<TypeInfo> create_type_info(const char* name) {
    if constexpr (std::is_array<T>::value) {
      using element_type = typename std::remove_extent<T>::type;
      return std::make_unique<ArrayTypeInfo>(name, sizeof(T), create_type_info<element_type>("element"));
    }
    else if constexpr (is_std_vector<T>::value) {
      using element_type = typename is_std_vector<T>::value_type;
      return std::make_unique<VectorTypeInfo>(name, sizeof(T), create_type_info<element_type>("element"));
    } else {
      return std::make_unique<PrimitiveTypeInfo>(name, get_kind<T>(), sizeof(T), std::is_pointer<T>::value);
    }
  }
```

## 3. Type Traits

Using Type Traits I’m able to identify the type and store it

```cpp
template <typename T>
  primitive_type get_kind() {
    if constexpr (std::is_pointer_v<T>) {
      return PTR;
    } else if constexpr (std::is_enum_v<T>) {
      return get_kind<typename std::underlying_type<T>::type>();
    } else if constexpr (std::is_void_v<T>) {
      return VOID;
    } else if constexpr (std::is_same_v<T, unsigned char>) {
      return U_CHAR;
    } else if constexpr (std::is_same_v<T, unsigned short>) {
      return U_SHORT;
    } else if constexpr (std::is_same_v<T, unsigned int>) {
      return U_INT;
    } else if constexpr (std::is_same_v<T, unsigned long>) {
      return U_LONG;
    } else if constexpr (std::is_same_v<T, unsigned long long>) {
      return U_LONG_LONG;
    } else if constexpr (std::is_same_v<T, signed char>) {
      return I_CHAR;
    } else if constexpr (std::is_same_v<T, short>) {
      return I_SHORT;
    } else if constexpr (std::is_same_v<T, int>) {
      return I_INT;
    } else if constexpr (std::is_same_v<T, long>) {
      return I_LONG;
    } else if constexpr (std::is_same_v<T, long long>) {
      return I_LONG_LONG;
    } else if constexpr (std::is_same_v<T, float>) {
      return FLOAT;
    } else if constexpr (std::is_same_v<T, double>) {
      return DOUBLE;
    } else if constexpr (std::is_same_v<T, bool>) {
      return BOOL;
    } else if constexpr (std::is_same_v<T, char>) {
      return CHAR;
    } else if constexpr (std::is_same_v<T, std::string>) {
      return STRING;
    } else if constexpr (std::is_integral_v<T>) {
      return I_INT;
    } else {
      throw std::runtime_error("This Type is not supported for reflection!");
      return UNKNOWN;
    }
  }
```

These traits define how to convert each supported type to and from JSON.

This reflection system significantly reduces boilerplate code and makes it easier to maintain serialization logic as your codebase evolve