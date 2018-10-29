#pragma once

/*!
* @brief アセットの先頭で定義するマクロ
* GG_OBJECT_NAMEとGG_LOAD_FUNCの組み合わせ
*/
#define GG_ASSET(Type, Data)  GG_OBJECT_NAME(Type);\
  GG_LOAD_FUNC(Type, Data)
