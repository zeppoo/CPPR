#include "include/test.hpp"

int main()
{
  std::string names[4] = {"hi","Hello","y0","m8m"};

  MyStruct myStruct{3 , {4,2}, {&names[0], &names[1], &names[2], &names[3]}};

  myStruct.structDesc.To_Json("dump.txt", &myStruct);
  myStruct.structDesc.From_Json("dump.txt", &myStruct);
  return 0;
}