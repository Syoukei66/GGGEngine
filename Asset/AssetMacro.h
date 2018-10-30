#pragma once

/*!
* @brief �A�Z�b�g�̐擪�Œ�`����}�N��
* GG_OBJECT_NAME��GG_LOAD_FUNC�̑g�ݍ��킹
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
