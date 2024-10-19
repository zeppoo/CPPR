#include "../include/type_resolver.hpp"

namespace reflect
{
// Resolves the value at the ptr to a string
//
//
//
  std::string toString(void* value) {
    std::ostringstream oss;
    oss << std::hex << std::uppercase << value;
    return oss.str();
  }

  std::string toString(bool value) {
    return value ? "true" : "false";
  }

  std::string toString(char value) {
    return "\'"+std::string(1, value)+"\'";
  }

  std::string toString(unsigned char value) {
    return "\'"+std::to_string(value)+"\'";
  }

  std::string toString(unsigned short value) {
    return std::to_string(value);
  }

  std::string toString(unsigned int value) {
    return std::to_string(value);
  }

  std::string toString(unsigned long value) {
    return std::to_string(value);
  }

  std::string toString(unsigned long long value) {
    return std::to_string(value);
  }

  std::string toString(signed char value) {
    return "\'"+std::to_string(value)+"\'";
  }

  std::string toString(short value) {
    return std::to_string(value);
  }

  std::string toString(int value) {
    return std::to_string(value);
  }

  std::string toString(long value) {
    return std::to_string(value);
  }

  std::string toString(long long value) {
    return std::to_string(value);
  }

  std::string toString(float value) {
    return std::to_string(value);
  }

  std::string toString(double value) {
    return std::to_string(value);
  }

  std::string toString(const std::string& value) {
    return "\""+value+"\"";
  }

  std::string toString(types value) {
    std::string result = std::visit([](auto&& arg) {
      using T = std::decay_t<decltype(arg)>;
      return toString(arg);
    }, value);
    return result;
  }

  // Resolves the value of the string to the right type
//
//
//

  template <>
  void* fromString<void*>(const std::string& value) {
    unsigned long long addr = 0;
    std::stringstream ss;
    ss << std::hex << value;  // Interpret the string as hexadecimal
    ss >> addr;               // Convert to a number
    return reinterpret_cast<void*>(addr); // convert to void pointer
  }

  template <>
  int fromString<int>(const std::string& value) {
    return std::stoi(value);
  }

  template <>
  unsigned int fromString<unsigned int>(const std::string& value) {
    return static_cast<unsigned int>(std::stoul(value));  // Use std::stoul for unsigned
  }

  template <>
  float fromString<float>(const std::string& value) {
    return std::stof(value);
  }

  template <>
  double fromString<double>(const std::string& value) {
    return std::stod(value);
  }

  template <>
  long fromString<long>(const std::string& value) {
    return std::stol(value);
  }

  template <>
  unsigned long fromString<unsigned long>(const std::string& value) {
    return std::stoul(value);
  }

  template <>
  long long fromString<long long>(const std::string& value) {
    return std::stoll(value);
  }

  template <>
  unsigned long long fromString<unsigned long long>(const std::string& value) {
    return std::stoull(value);
  }

  template <>
  unsigned char fromString<unsigned char>(const std::string& value) {
    return static_cast<unsigned char>(std::stoul(value));
  }

  template <>
  unsigned short fromString<unsigned short>(const std::string& value) {
    return static_cast<unsigned short>(std::stoul(value));
  }

  template <>
  signed char fromString<signed char>(const std::string& value) {
    return static_cast<signed char>(std::stoi(value));
  }

  template <>
  short fromString<short>(const std::string& value) {
    return static_cast<short>(std::stoi(value));
  }

// Specialization for bool (handling common true/false string values)
  template <>
  bool fromString<bool>(const std::string& value) {
    if (value == "true" || value == "1") return true;
    if (value == "false" || value == "0") return false;
    return false;
  }

  template <>
  char fromString<char>(const std::string& value) {
    if (value.length() != 1) return '@';
    return value[0];
  }

  template <>
  std::string fromString<std::string>(const std::string& value) {
    return value;
  }

// Resolves the value at the ptr to the pointer of the right type
//
//
//


  template <>
  void* toTypePtr<void>(void* ptr) {
    return ptr;
  }

  template <>
  int* toTypePtr<int>(void* ptr) {
    return static_cast<int*>(ptr);
  }

  template <>
  unsigned int* toTypePtr<unsigned int>(void* ptr) {
    return static_cast<unsigned int*>(ptr);
  }

  template <>
  float* toTypePtr<float>(void* ptr) {
    return static_cast<float*>(ptr);
  }

  template <>
  double* toTypePtr<double>(void* ptr) {
    return static_cast<double*>(ptr);
  }

  template <>
  long* toTypePtr<long>(void* ptr) {
    return static_cast<long*>(ptr);
  }

  template <>
  unsigned long* toTypePtr<unsigned long>(void* ptr) {
    return static_cast<unsigned long*>(ptr);
  }

  template <>
  long long* toTypePtr<long long>(void* ptr) {
    return static_cast<long long*>(ptr);
  }

  template <>
  unsigned long long* toTypePtr<unsigned long long>(void* ptr) {
    return static_cast<unsigned long long*>(ptr);
  }

  template <>
  bool* toTypePtr<bool>(void* ptr) {
    return static_cast<bool*>(ptr);
  }

  template <>
  char* toTypePtr<char>(void* ptr) {
    return static_cast<char*>(ptr);
  }

  template <>
  unsigned char* toTypePtr<unsigned char>(void* ptr) {
    return static_cast<unsigned char*>(ptr);
  }

  template <>
  unsigned short* toTypePtr<unsigned short>(void* ptr) {
    return static_cast<unsigned short*>(ptr);
  }

  template <>
  short* toTypePtr<short>(void* ptr) {
    return static_cast<short*>(ptr);
  }

  template <>
  signed char* toTypePtr<signed char>(void* ptr) {
    return static_cast<signed char*>(ptr);
  }

  template <>
  std::string* toTypePtr<std::string>(void* ptr) {
    return static_cast<std::string*>(ptr);
  }


// Resolves the value at the ptr to the vector of the right type
//
//
//
  template <>
  std::vector<void*>& toTypeVector<void*>(void* ptr) {
    std::vector<void*>* vectorPtr = reinterpret_cast<std::vector<void*>*>(ptr);
    return *vectorPtr;
  }

  template <>
  std::vector<bool>& toTypeVector<bool>(void* ptr) {
    std::vector<bool>* vectorPtr = reinterpret_cast<std::vector<bool>*>(ptr);
    return *vectorPtr;
  }

  template <>
  std::vector<char>& toTypeVector<char>(void* ptr) {
    std::vector<char>* vectorPtr = reinterpret_cast<std::vector<char>*>(ptr);
    return *vectorPtr;
  }

  template <>
  std::vector<signed char>& toTypeVector<signed char>(void* ptr) {
    std::vector<signed char>* vectorPtr = reinterpret_cast<std::vector<signed char>*>(ptr);
    return *vectorPtr;
  }

  template <>
  std::vector<unsigned char>& toTypeVector<unsigned char>(void* ptr) {
    std::vector<unsigned char>* vectorPtr = reinterpret_cast<std::vector<unsigned char>*>(ptr);
    return *vectorPtr;
  }

  template <>
  std::vector<short>& toTypeVector<short>(void* ptr) {
    std::vector<short>* vectorPtr = reinterpret_cast<std::vector<short>*>(ptr);
    return *vectorPtr;
  }

  template <>
  std::vector<unsigned short>& toTypeVector<unsigned short>(void* ptr) {
    std::vector<unsigned short>* vectorPtr = reinterpret_cast<std::vector<unsigned short>*>(ptr);
    return *vectorPtr;
  }

  template <>
  std::vector<int>& toTypeVector<int>(void* ptr) {
    std::vector<int>* vectorPtr = reinterpret_cast<std::vector<int>*>(ptr);
    return *vectorPtr;
  }

  template <>
  std::vector<unsigned int>& toTypeVector<unsigned int>(void* ptr) {
    std::vector<unsigned int>* vectorPtr = reinterpret_cast<std::vector<unsigned int>*>(ptr);
    return *vectorPtr;
  }

  template <>
  std::vector<long>& toTypeVector<long>(void* ptr) {
    std::vector<long>* vectorPtr = reinterpret_cast<std::vector<long>*>(ptr);
    return *vectorPtr;
  }

  template <>
  std::vector<unsigned long>& toTypeVector<unsigned long>(void* ptr) {
    std::vector<unsigned long>* vectorPtr = reinterpret_cast<std::vector<unsigned long>*>(ptr);
    return *vectorPtr;
  }

  template <>
  std::vector<long long>& toTypeVector<long long>(void* ptr) {
    std::vector<long long>* vectorPtr = reinterpret_cast<std::vector<long long>*>(ptr);
    return *vectorPtr;
  }

  template <>
  std::vector<unsigned long long>& toTypeVector<unsigned long long>(void* ptr) {
    std::vector<unsigned long long>* vectorPtr = reinterpret_cast<std::vector<unsigned long long>*>(ptr);
    return *vectorPtr;
  }

  template <>
  std::vector<float>& toTypeVector<float>(void* ptr) {
    std::vector<float>* vectorPtr = reinterpret_cast<std::vector<float>*>(ptr);
    return *vectorPtr;
  }

  template <>
  std::vector<double>& toTypeVector<double>(void* ptr) {
    std::vector<double>* vectorPtr = reinterpret_cast<std::vector<double>*>(ptr);
    return *vectorPtr;
  }

  template <>
  std::vector<long double>& toTypeVector<long double>(void* ptr) {
    std::vector<long double>* vectorPtr = reinterpret_cast<std::vector<long double>*>(ptr);
    return *vectorPtr;
  }

  template <>
  std::vector<std::string>& toTypeVector<std::string>(void* ptr) {
    std::vector<std::string>* vectorPtr = reinterpret_cast<std::vector<std::string>*>(ptr);
    return *vectorPtr;
  }
}
