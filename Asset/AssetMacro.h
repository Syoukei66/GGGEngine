#pragma once

/*!
* @brief �A�Z�b�g�̐擪�Œ�`����}�N��
* GG_OBJECT_NAME��GG_LOAD_FUNC�̑g�ݍ��킹
*/
#define GG_ASSET(Type, Data)  GG_OBJECT_NAME(Type);\
  GG_LOAD_FUNC(Type, Data)
