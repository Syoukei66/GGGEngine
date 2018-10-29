#pragma once

#include <Core/Macro/AssertMacro.h>

/*!
* @brief コピー禁止のクラス内に記述する事で
* デフォルトのコピーコンストラクタやムーブコンストラクタが
* 生成されるのを防ぐ
*/
#define GG_NO_COPYABLE(Type)private:\
  Type(const Type&) = delete;\
  Type& operator = (const Type&) = delete;\
  Type(Type&&) = delete;\
  Type& operator = (Type&&) = delete

/*!
* @brief シングルトンにしたいクラス内に記述する
* GGGEngine内のシングルトンクラスを共通のフォーマットで
* 記述するのが目的。
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
* @brief GGObjectを継承したクラス内に記述する必要がある。
* GetObjectName()をoverrideするだけでもコンパイルは通るが、
* ツールのサポートを受けたい場合はこのマクロを通して記述する事。
*/
#define GG_OBJECT_NAME(Name)public:\
  virtual GG_INLINE const char* GetObjectName() const override\
  {\
    return #Name;\
  }

/*!
* @brief シリアライズ可能なクラス内に記述する
*/
#define GG_SERIALIZABLE(Type, ...)public:\
  template <class Archive>\
  void serialize(Archive& archive, Type& value)

/*!
 * @brief GGObjectの安全なCreateMethodを提供する
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
* @brief データを基に内容を初期化するクラスのCreateMethodを提供する。
* void Init(const Data& data)を実装する必要がある。
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
