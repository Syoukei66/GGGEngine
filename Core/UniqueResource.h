#pragma once

#include "Macro.h"

template <class Resource_> class SharedRef;

template <class Resource_>
class UniqueResource
{
  template <class Resource_>
  friend class SharedRef;

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  /*!
   * デフォルトコンストラクタ。所有権を持たない、空のUniqueResourceオブジェクトを構築する。
   */
  FORCE_INLINE constexpr UniqueResource() noexcept = default;

  /*!
   * 生ポインタの所有権を受け取る。
   * \param ptr 生ポインタ
   */
  FORCE_INLINE explicit UniqueResource(Resource_* ptr)
  {
    ptr->Retain();
    this->ptr_ = ptr;
  }

  /*!
   * ムーブコンストラクタ。他のSharedRefから所有権を移動する。
   * \param o 他のSharedRef
   */
  FORCE_INLINE UniqueResource(UniqueResource&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  /*!
   * ムーブコンストラクタ。他の変換可能なSharedRefから所有権を移動する。
   * \param o 他の変換可能なSharedRef
   */
  template <class _OtherResource>
  FORCE_INLINE UniqueResource(UniqueResource<_OtherResource>&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  /*!
   * デストラクタ。所有権を破棄する。
   */
  FORCE_INLINE ~UniqueResource()
  {
    if (this->ptr_)
    {
      this->ptr_->Release();
    }
  }

  // =================================================================
  // operator
  // =================================================================
public:
  /*!
   * コピー代入禁止。
   */
  FORCE_INLINE UniqueResource& operator = (const UniqueResource&) = delete;

  /*!
   * 自身が保持しているリソースを解放し、他のUniqueResourceから所有権を移動する。
   * \param o 他のUniqueResource
   */
  FORCE_INLINE UniqueResource& operator = (UniqueResource&& o) noexcept
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
   * 自身が保持しているリソースを解放し、他のUniqueResourceから所有権を移動する。
   * \param o 他のUniqueResource
   */
  template <class OtherResource_>
  FORCE_INLINE UniqueResource& operator = (UniqueResource<OtherResource_>&& o) noexcept
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
   * 自身が保持しているリソースを解放する。
   * \param p nullptr
   */
  FORCE_INLINE UniqueResource& operator = (nullptr_t p) noexcept
  {
    if (this->ptr_)
    {
      this->ptr_->Release();
      this->ptr_ = p;
    }
    return *this;
  }

  /*!
   * 間接参照
   */
  FORCE_INLINE Resource_& operator*() const noexcept
  {
    return *this->ptr_;
  }

  /*!
   * メンバアクセス
   */
  FORCE_INLINE Resource_* operator -> () const noexcept
  {
    return this->ptr_;
  }

  /*!
   * 有効なリソースを所有しているか判定する
   */
  FORCE_INLINE explicit operator bool() const noexcept
  {
    return this->ptr_ != nullptr;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  Resource_* ptr_;

};
