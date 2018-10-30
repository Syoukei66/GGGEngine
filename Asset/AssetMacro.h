#pragma once

/*!
* @brief アセットの先頭で定義するマクロ
* GG_OBJECT_NAMEとGG_LOAD_FUNCの組み合わせ
*/
#define GG_ASSET(Type, Data)  GG_OBJECT_NAME(Type);\
public:\
  static GG_INLINE UniqueRef<Type> CreateFromFile(const char* path)\
  {\
    Data data;\
    CerealIO::Binary::Import<Data>(path, &data);\
    return Create(data);\
  }\
  GG_LOAD_FUNC(Type, Data)
