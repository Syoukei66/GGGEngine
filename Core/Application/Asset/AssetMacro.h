#pragma once

/*!
* @brief �A�Z�b�g�̐擪�Œ�`����}�N��
* GG_OBJECT��GG_LOAD_FUNC�̑g�ݍ��킹
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
