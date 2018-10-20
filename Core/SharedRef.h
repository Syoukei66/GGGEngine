#pragma once

#include "Macro.h"

template <class Resource_> class UniqueResource;

template <class Resource_>
class SharedRef
{
  template <class OtherResource_>
  friend class SharedRef;

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  /*!
   * DynamicCastを行ったSharedRefを返す。
   */
  template <class OtherResource_>
  static FORCE_INLINE SharedRef<Resource_> DynamicCast(const SharedRef<OtherResource_>& ref)
  {
    return SharedRef<Resource_>((Resource_*)ref.ptr_);
  }

  /*!
   * デフォルトコンストラクタ。所有権を持たない、空のSharedRefを構築する。
   */
  FORCE_INLINE constexpr SharedRef() noexcept = default;

  /*!
   * 生ポインタの所有権を受け取る。
   * \param ptr 生ポインタ
   */
  FORCE_INLINE explicit SharedRef(Resource_* ptr)
  {
    ptr->Retain();
    this->ptr_ = ptr;
  }

  /*!
   * コピーコンストラクタ。oと所有権の共有。
   */
  FORCE_INLINE SharedRef(const SharedRef& o) noexcept
  {
    if (o.ptr_)
    {
      o.ptr_->Retain();
    }
    this->ptr_ = o.ptr_;
  }

  /*!
   * コピーコンストラクタ。変換可能なoと所有権の共有。
   */
  template <class _OtherResource>
  FORCE_INLINE SharedRef(const SharedRef<_OtherResource>& o) noexcept
  {
    if (o.ptr_)
    {
      o.ptr_->Retain();
    }
    this->ptr_ = o.ptr_;
  }
  
  /*!
   * ムーブコンストラクタ。oから所有権を移動する。
   */
  FORCE_INLINE SharedRef(SharedRef&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  /*!
   * ムーブコンストラクタ。他の変換可能なoから所有権を移動する。
   */
  template <class _OtherResource>
  FORCE_INLINE SharedRef(SharedRef<_OtherResource>&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  /*!
   * oから所有権の移動。
   */
  template <class _OtherResource>
  FORCE_INLINE SharedRef(UniqueResource<_OtherResource>&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  /*!
   * 所有権を持たない空のSharedRefの作成。
   * \param p nullptr
   */
  FORCE_INLINE constexpr SharedRef(nullptr_t p)
  {
    this->ptr_ = p;
  }

  /*!
   * デストラクタ。所有権を破棄する。
   */
  FORCE_INLINE ~SharedRef()
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
   * 自身が保持しているリソースの所有権を放棄し、oが持つリソースの所有権を共有する。
   */
  FORCE_INLINE SharedRef& operator = (const SharedRef& o) noexcept
  {
    if (o.ptr_)
    {
      o.ptr_->Retain();
    }
    if (this->ptr_)
    {
      this->ptr_->Release();
    }
    this->ptr_ = o.ptr_;
    return *this;
  }

  /*!
   * 自身が保持しているリソースの所有権を放棄し、変換可能なoが持つリソースの所有権を共有する。
   */
  template <class OtherResource_>
  FORCE_INLINE SharedRef& operator = (const SharedRef<OtherResource_>& o) noexcept
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
   * 自身が保持しているリソースの所有権を放棄し、oが持つリソースの所有権を移動する。
   */
  FORCE_INLINE SharedRef& operator = (SharedRef&& o) noexcept
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
  * 自身が保持しているリソースの所有権を放棄し、oが持つリソースの所有権を移動する。
  */
  FORCE_INLINE SharedRef& operator = (nullptr_t o) noexcept
  {
    if (this->ptr_)
    {
      this->ptr_->Release();
    }
    this->ptr_ = nullptr;
    return *this;
  }

  /*!
   * 自身が保持しているリソースの所有権を放棄し、変換可能なoが持つリソースの所有権を移動する。
   */
  template <class OtherResource_>
  FORCE_INLINE SharedRef& operator = (SharedRef<OtherResource_>&& o) noexcept
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
   * 自身が保持しているリソースの所有権を放棄し、oが持つリソースの所有権を移動する。
   */
  template <class OtherResource_>
  FORCE_INLINE SharedRef& operator = (UniqueResource<OtherResource_>&& o) noexcept
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
   * メンバアクセス
   */
  FORCE_INLINE Resource_* operator -> () const noexcept
  {
    return this->ptr_;
  }

  /*!
   * 間接参照
   */
  FORCE_INLINE Resource_& operator*() const noexcept
  {
    return *this->ptr_;
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