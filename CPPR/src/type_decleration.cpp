#include "../../../Crow-Engine/CrowEngine/libs/cppr/type_declaration.hpp"

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