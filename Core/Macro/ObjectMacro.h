#pragma once

#include <Core/Macro/AssertMacro.h>

/*!
* @brief �R�s�[�֎~�̃N���X���ɋL�q���鎖��
* �f�t�H���g�̃R�s�[�R���X�g���N�^�⃀�[�u�R���X�g���N�^��
* ���������̂�h��
*/
#define GG_NO_COPYABLE(Type)private:\
  Type(const Type&) = delete;\
  Type& operator = (const Type&) = delete;\
  Type(Type&&) = delete;\
  Type& operator = (Type&&) = delete

/*!
* @brief �V���O���g���ɂ������N���X���ɋL�q����
* GGGEngine���̃V���O���g���N���X�����ʂ̃t�H�[�}�b�g��
* �L�q����̂��ړI�B
*/
#define GG_SINGLETON(Type) GG_NO_COPYABLE(Type);\
  static GG_INLINE Type& Instance()\
  {\
    static Type self;\
    return self;\
  }\
\
  Type() = default;\
  ~Type() = default

/*!
* @brief GGObject���p�������N���X���ɋL�q����K�v������B
* GetObjectName()��override���邾���ł��R���p�C���͒ʂ邪�A
* �c�[���̃T�|�[�g���󂯂����ꍇ�͂��̃}�N����ʂ��ċL�q���鎖�B
*/
#define GG_OBJECT_NAME(Name)public:\
  virtual GG_INLINE const char* GetObjectName() const override\
  {\
    return #Name;\
  }

/*!
* @brief �V���A���C�Y�\�ȃN���X���ɋL�q����
*/
#define GG_SERIALIZABLE(Type, ...)public:\
  template <class Archive>\
  void serialize(Archive& archive, Type& value)

/*!
 * @brief GGObject�̈��S��CreateMethod��񋟂���
 */
#define GG_CREATE_FUNC(Type)public:\
  static GG_INLINE UniqueRef<Type> Create()\
  {\
    Type* ret = new (std::nothrow) Type();\
    GG_ASSERT_IS_NULL(ret);\
    ret->Init();\
    return UniqueRef<Type>();\
  }\
\
protected:\
  void Init()

/*!
* @brief �f�[�^����ɓ��e������������N���X��CreateMethod��񋟂���B
* void Init(const Data& data)����������K�v������B
*/
#define GG_LOAD_FUNC(Type, Data)public:\
  static GG_INLINE UniqueRef<Type> Create(const Data& data)\
  {\
    Type* ret = new (std::nothrow) Type();\
    GG_ASSERT_IS_NULL(ret);\
    ret->Init(data);\
    return UniqueRef<Type>(ret);\
  }\
\
protected:\
  void Init(const Data& data)
