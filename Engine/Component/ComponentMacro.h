#pragma once

#include <Core/Macro/ObjectMacro.h>

/*!
 * @brief アセットの先頭で定義するマクロ
 * GG_OBJECTとGG_LOAD_FUNCの組み合わせ
 */
#define GG_COMPONENT(Type)GG_OBJECT(Type);\
public:\
  static const T_UINT32 ID = static_cast<T_UINT32>(ComponentID::Type);\
  GG_INLINE virtual T_UINT32 GetComponentID() const override\
  {\
    return ID;\
  }
