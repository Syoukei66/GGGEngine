#pragma once

#include "Ref.h"

#include "UniqueRef.h"

template <class Obj_>
class SharedRef;

/*!
 * @brief GGObject専用のshared_ptr
 */
template <class Obj_>
class SharedRef : public GGRef<Obj_>
{
  template <class OtherObj_>
  friend class SharedRef;

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  /*!
   * @brief デフォルトコンストラクタ。
   * 所有権を持たない、空のSharedRefを構築する。
   */
  GG_INLINE constexpr SharedRef() noexcept = default;

  /*!
   * @brief デフォルトデストラクタ。所有権を破棄する。
   */
  GG_INLINE ~SharedRef() = default;

  /*!
   * @brief 生ポインタの所有権を受け取り、
   * オブジェクト管理クラスへ追加。
   */
  GG_INLINE explicit SharedRef(Obj_* ptr) : GGRef<Obj_>(ptr) {}

  /*!
   * @brief 所有権を持たない空のSharedRefの作成。
   */
  GG_INLINE constexpr SharedRef(nullptr_t p) : GGRef<Obj_>(p) {}

  /*!
   * @brief コピーコンストラクタ。
   * 他のSharedRefと所有権の共有。
   */
  GG_INLINE SharedRef(const SharedRef& o) noexcept
  {
    if (o.ptr_)
    {
      o.ptr_->Retain();
    }
    this->ptr_ = o.ptr_;
  }

  /*!
   * @brief コピーコンストラクタ。
   * 他の変換可能なSharedRefと所有権の共有。
   */
  template <class _OtherObj>
  GG_INLINE SharedRef(const SharedRef<_OtherObj>& o) noexcept
  {
    if (o.ptr_)
    {
      o.ptr_->Retain();
    }
    this->ptr_ = o.ptr_;
  }

  /*!
   * @brief ムーブコンストラクタ。
   * 他のSharedRefから所有権を移動する。
   */
  GG_INLINE SharedRef(SharedRef&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  /*!
   * @brief ムーブコンストラクタ。
   * 他の変換可能なSharedRefから所有権を移動する。
   */
  template <class _OtherObj>
  GG_INLINE SharedRef(SharedRef<_OtherObj>&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  /*!
   * @brief ムーブコンストラクタ。
   * 他の変換可能なUniqueRefから所有権を移動する。
   */
  template <class _OtherObj>
  GG_INLINE SharedRef(UniqueRef<_OtherObj>&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  /*!
   * @brief StaticCastを行ったSharedRefを返す。
   * 生ポインタを引数としたコンストラクタを起動してしまうと
   * ObjectManagerへ二重登録がされてしまう為避けている。
   */
  template <class OtherObj_>
  static GG_INLINE SharedRef<Obj_> StaticCast(const SharedRef<OtherObj_>& ref)
  {
    SharedRef<Obj_> ret;
    ret.ptr_ = static_cast<Obj_*>(ref.ptr_);
    return ret;
  }

  // =================================================================
  // operator
  // =================================================================
public:
  /*!
   * @brief 自身が保持しているリソースを解放する。
   */
  GG_INLINE SharedRef& operator = (nullptr_t p) noexcept
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
   * 他のSharedRefが持つ所有権を共有する。
   */
  GG_INLINE SharedRef& operator = (const SharedRef& o) noexcept
  {
    o.ptr_->Retain();
    if (this->ptr_)
    {
      this->ptr_->Release();
    }
    this->ptr_ = o.ptr_;
    return *this;
  }

  /*!
   * @brief 自身が保持している所有権を放棄し、
   * 他の変換可能なSharedRefが持つ所有権を共有する。
   */
  template <class OtherObj_>
  GG_INLINE SharedRef& operator = (const SharedRef<OtherObj_>& o) noexcept
  {
    o.ptr_->Retain();
    if (this->ptr_)
    {
      this->ptr_->Release();
    }
    this->ptr_ = o.ptr_;
    return *this;
  }

  /*!
   * @brief 自身が保持している所有権を放棄し、
   * 他のSharedRefが持つ所有権を移動する。
   */
  GG_INLINE SharedRef& operator = (SharedRef&& o) noexcept
  {
    if (this->ptr_)
    {
      this->ptr_->Release();
    }
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
    return *this;
  }

  /*!
   * @brief 自身が保持している所有権を放棄し、
   * 他の変換可能なSharedRefが持つ所有権を移動する。
   */
  template <class OtherObj_>
  GG_INLINE SharedRef& operator = (SharedRef<OtherObj_>&& o) noexcept
  {
    if (this->ptr_)
    {
      this->ptr_->Release();
    }
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
    return *this;
  }

  /*!
   * @brief 自身が保持している所有権を放棄し、
   * 他の変換可能なUniqueRefが持つ所有権を移動する。
   */
  template <class OtherObj_>
  GG_INLINE SharedRef& operator = (UniqueRef<OtherObj_>&& o) noexcept
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