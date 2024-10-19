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