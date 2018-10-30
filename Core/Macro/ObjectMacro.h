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
* GGGEngine内のシングルトンクラスを共通のフォーマットで記述するのが目的。
* 基本的にGetInstance()->が邪魔なので、staticメソッドを使用。
* staticメンバは持たず、staticなインスタンスを提供するSelf()アクセサを使用してメンバへアクセスする。
* Self()メソッドは隠ぺいし、staticメソッドの内部でthisポインタの代わりに使用する
* Instance()メソッドはpublicだが、constな参照を返すので
* システム側ではキャストして使用し、使用側ではconstなインスタンスを使用するなど使い分ける
*/
#define GG_SINGLETON(Type) GG_NO_COPYABLE(Type);\
private:\
  static GG_INLINE Type& Self()\
  {\
    static Type self;\
    return self;\
  }\
public:\
  static GG_INLINE const Type& Instance()\
  {\
    return Self();\
  }\
private:\
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
  void serialize(Archive& archive)

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
