#pragma once

/*!
* @brief アセットの先頭で定義するマクロ
* GG_OBJECTとGG_LOAD_FUNCの組み合わせ
*/
#define GG_ASSET(Type, Data)public:\
  static GG_INLINE UniqueRef<Type> CreateFromFile(const char* path)\
  {\
    Data data;\
    CerealIO::Binary::Import<Data>(path, &data);\
    return Create(data);\
  }\
  GG_CREATE_FUNC_1(Type, const Data&, data)

#define GG_ASSET_INIT(Type, Data)\
GG_CREATE_FUNC_IMPL_1(Type, const Data&, data)
