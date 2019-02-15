#pragma once

#include <Core/Macro/ObjectMacro.h>

/*!
 * @brief �A�Z�b�g�̐擪�Œ�`����}�N��
 * GG_OBJECT��GG_LOAD_FUNC�̑g�ݍ��킹
 */
#define GG_COMPONENT(Type)GG_OBJECT(Type);\
public:\
  static const T_UINT32 ID = static_cast<T_UINT32>(ComponentID::Type);\
  GG_INLINE virtual T_UINT32 GetComponentID() const override\
  {\
    return ID;\
  }
