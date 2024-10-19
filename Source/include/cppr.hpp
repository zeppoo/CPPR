#pragma once
#include "descriptors.hpp"

#define REFLECT() \
  static inline void initReflection(reflect::StructDescriptor*); \
  static inline reflect::StructDescriptor structDesc{initReflection};

#define REFLECT_STRUCT_BEGIN(type) \
  inline void type::initReflection(reflect::StructDescriptor* typeDesc) { \
    using T = type; \
    typeDesc->name = #type; \
    typeDesc->size = sizeof(T);

#define REFLECT_STRUCT_MEMBER(name) \
    typeDesc->AddMember<decltype(T::name)>(#name, sizeof(T::name), offsetof(T, name)); \

#define REFLECT_STRUCT_END() \
  }

namespace getting_rid_of_annoying_warning {}