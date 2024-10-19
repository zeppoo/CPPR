# How to use

# Instructions for Using the Runtime C++ Reflector

## 1. Installation

- Download the reflector library from the official repository
- Include the library in your C++ project
- Ensure you have a C++17 compatible compiler

## 2. Setting Up Your Classes

- Add the REFLECT macro to the classes/structs you want to reflect

```cpp
struct MyStruct
{
	REFLECT();
  int number;
  std::vector<int> vector;
  std::string* namesPtr[4];
};
```

## 3. Generating Reflection Data

- Use the `REFLECT_STRUCT_BEGIN` macro with the typename( not an instance name! ) in your `main.cpp` or a separate source file( make sure the file has access to the struct ).
- Now for each field/member the struct has. Use `REFLECT_STRUCT_MEMBER` and the name of the field/member as parameter
- End it with a `REFLECT_STRUCT_END`

```cpp
REFLECT_STRUCT_BEGIN(MyStruct)
  REFLECT_STRUCT_MEMBER(number)
  REFLECT_STRUCT_MEMBER(vector)
  REFLECT_STRUCT_MEMBER(namesPtr)
REFLECT_STRUCT_END()
```

## 4. Using Reflection at Runtime

- Access type information by referencing `myStruct.structDesc`
- Serialize the struct by calling `myStruct.structDesc.To_Json("filePath", &myStruct);`
- Deserialize the struct by calling `myStruct.structDesc.From_Json("filePath", &myStruct);`

```
myStruct.structDesc.To_Json("config.json", &myStruct);
myStruct.structDesc.From_Json("config.json", &myStruct);
```

## 6. Best Practices

- Only reflect the necessary members to keep compilation times manageable
- Consider performance implications when using reflection in performance-critical code

## 7. Troubleshooting

- Check compiler errors for missing or incorrect macro usage
- Ensure all required headers are included
- Verify that the reflection generation step is properly integrated into your build process