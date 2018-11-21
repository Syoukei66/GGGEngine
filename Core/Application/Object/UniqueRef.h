#pragma once

#include "Ref.h"

template <class Obj_>
class UniqueRef;
template <class Obj_>
class SharedRef;

/*!
* @brief GGObject専用のunique_ptr
*/
template <class Obj_>
class UniqueRef : public GGRef<Obj_>
{
  template <class OtherObj_>
  friend class UniqueRef;
  template <class OtherObj_>
  friend class SharedRef;

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  /*!
  * @brief デフォルトコンストラクタ。
  * 所有権を持たない、空のUniqueRefを構築する。
  */
  GG_INLINE constexpr UniqueRef() noexcept = default;

  /*!
  * @brief デフォルトデストラクタ。所有権を破棄する。
  */
  GG_INLINE ~UniqueRef() = default;

  /*!
  * @brief 生ポインタの所有権を受け取り、
  * オブジェクト管理クラスへ追加。
  */
  GG_INLINE explicit UniqueRef(Obj_* ptr) : GGRef<Obj_>(ptr) {}

  /*!
  * @brief 所有権を持たない空のUniqueRefの作成。
  */
  GG_INLINE constexpr UniqueRef(nullptr_t p) : GGRef<Obj_>(p) {}

  /*!
  * @brief ムーブコンストラクタ。
  * 他の変換可能なUniqueRefから所有権を移動する。
  */
  template <class OtherObj_, GGRefConvertible<Obj_, OtherObj_> = nullptr>
  GG_INLINE UniqueRef(UniqueRef<OtherObj_>&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  // =================================================================
  // operator
  // =================================================================
public:
  /*!
  * @brief 自身が保持しているリソースを解放する。
  */
  GG_INLINE UniqueRef& operator = (nullptr_t p) noexcept
  {
    if (this->ptr_)
    {
      this->ptr_->Release();
      this->ptr_ = p;
    }
    return *this;
  }

  /*!
  * @brief 自身が保持している所有権を放棄し、
  * 他の変換可能なUniqueRefが持つ所有権を移動する。
  */
  template <class OtherObj_, GGRefConvertible<Obj_, OtherObj_> = nullptr>
  GG_INLINE UniqueRef& operator = (UniqueRef<OtherObj_>&& o) noexcept
  {
    if (this->ptr_)
    {
      this->ptr_->Release();
    }
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
    return *this;
  }
  
};
