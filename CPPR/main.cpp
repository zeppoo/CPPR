#include "../../Crow-Engine/CrowEngine/libs/cppr/cppr.hpp"

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

int main()
{
  std::string names[4] = {"hi","Hello","y0","m8m"};

  MyStruct myStruct{3 , {4,2}, {&names[0], &names[1], &names[2], &names[3]}};

  myStruct.structDesc.To_Json("dump.txt", &myStruct);
  myStruct.structDesc.From_Json("dump.txt", &myStruct);
  return 0;
}