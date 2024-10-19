#pragma once
#include "descriptors.hpp"

#define REFLECT() \
  static reflect::StructDescriptor structDesc; \
  static void initReflection(reflect::StructDescriptor*); \

#define REFLECT_STRUCT_BEGIN(type) \
  reflect::StructDescriptor type::structDesc{type::initReflection}; \
  void type::initReflection(reflect::StructDescriptor* typeDesc) { \
    using T = type; \
    typeDesc->name = #type; \
    typeDesc->size = sizeof(T); \

#define REFLECT_STRUCT_MEMBER(name) \
    typeDesc->AddMember<decltype(T::name)>(#name, sizeof(T::name), offsetof(T, name)); \

#define REFLECT_STRUCT_END() \
  }