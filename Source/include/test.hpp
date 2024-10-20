#pragma once
#include "cppr.hpp"

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

struct MyStruct2
{
  int number;
  std::vector<int> vector2;
  std::string* namesPtr2[4];
  REFLECT()
};

REFLECT_STRUCT_BEGIN(MyStruct2)
  REFLECT_STRUCT_MEMBER(number)
  REFLECT_STRUCT_MEMBER(vector2)
  REFLECT_STRUCT_MEMBER(namesPtr2)
REFLECT_STRUCT_END()

struct MyStruct3
{
  int number3;
  std::vector<int> vector3;
  std::string* namesPtr3[4];
  REFLECT()
};

REFLECT_STRUCT_BEGIN(MyStruct3)
  REFLECT_STRUCT_MEMBER(number3)
  REFLECT_STRUCT_MEMBER(vector3)
  REFLECT_STRUCT_MEMBER(namesPtr3)
REFLECT_STRUCT_END()