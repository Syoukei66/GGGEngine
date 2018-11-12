#pragma once

/*!
* @brief アセットの先頭で定義するマクロ
* GG_OBJECTとGG_LOAD_FUNCの組み合わせ
*/
#define GG_ASSET(Type, Data)  GG_OBJECT(Type);\
public:\
  static GG_INLINE UniqueRef<Type> CreateFromFile(const char* path)\
  {\
    Data data;\
    CerealIO::Binary::Import<Data>(path, &data);\
    return Create(data);\
  }\
  GG_CREATE_FUNC_1(Type, const Data&)
