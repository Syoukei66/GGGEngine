#pragma once

#include "ObjectManager.h"

class GGObject;

/*!
 * @brief SFINAEの為にポインタの型チェックに用いる
 */
template <class From_, class To_>
using GGRefConvertible = std::enable_if_t<
  std::is_same<From_, To_>::value ||
  std::is_base_of<To_, From_>::value ||
  std::is_convertible<From_, To_>::value,
  std::nullptr_t
>;

/*!
 * @brief SFINAEの為にポインタの型チェックに用いる
 */
template <class From_, class To_>
using GGRefStaticCastbale = std::enable_if_t<
  std::is_same<From_, To_>::value ||
  std::is_base_of<To_, From_>::value ||
  std::is_convertible<From_, To_>::value,
  std::nullptr_t
>;

/*!
 * @brief SFINAEの為にポインタの型チェックに用いる
 */
template <class Obj_>
using GGIsObject = std::enable_if_t<
  std::is_same<Obj_, GGObject>::value ||
  std::is_base_of<GGObject, Obj_>::value ||
  std::is_convertible<Obj_, GGObject>::value,
  std::nullptr_t
>;

template <class Obj_>
class GGRef
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  /*!
   * @brief デフォルトコンストラクタ。
   * 所有権を持たない、空のRefを構築する。
   */
  GG_INLINE constexpr GGRef() noexcept = default;

  /*!
   * @brief デストラクタ。所有権を破棄する。
   */
  GG_INLINE ~GGRef()
  {
    if (this->ptr_)
    {
      this->ptr_->Release();
    }
  }

  /*!
   * @brief 生ポインタの所有権を受け取り、
   * オブジェクト管理クラスへ追加。
   */
  template <GGIsObject<Obj_> = nullptr>
  GG_INLINE explicit GGRef(Obj_* ptr)
  {
    ptr->Retain();
    GGObjectManager::Manage(ptr);
    this->ptr_ = ptr;
  }

  /*!
   * @brief 所有権を持たない空のRefの作成。
   */
  GG_INLINE constexpr GGRef(nullptr_t p)
    : ptr_()
  {}

  // =================================================================
  // operator
  // =================================================================
public:
  /*!
   * @brief コピー代入禁止。
   */
  GG_INLINE GGRef& operator = (const GGRef&) = delete;

  /*!
   * @brief メンバアクセス
   */
  GG_INLINE Obj_* operator -> () const noexcept
  {
    return this->ptr_;
  }

  /*!
   * @brief 間接参照
   */
  GG_INLINE Obj_& operator*() const noexcept
  {
    return *this->ptr_;
  }

  /*!
   * @brief 有効なリソースを所有しているか判定する
   */
  GG_INLINE explicit operator bool() const noexcept
  {
    return this->ptr_ != nullptr;
  }

  /*!
   * @brief 等値比較
   */
  template <class Other_>
  GG_INLINE bool operator== (const GGRef<Other_>& o) const noexcept
  {
    return this->ptr_ == o.ptr_;
  }

  /*!
   * @brief nullptr等値比較
   */
  GG_INLINE bool operator== (nullptr_t o) const noexcept
  {
    return this->ptr_ == o;
  }

  /*!
   * @brief 非等値比較
   */
  template <class Other_>
  GG_INLINE bool operator!= (const GGRef<Other_>& o) const noexcept
  {
    return this->ptr_ != o.ptr_;
  }

  /*!
   * @brief nullptr非等値比較
   */
  GG_INLINE bool operator!= (nullptr_t o) const noexcept
  {
    return this->ptr_ != o;
  }

  /*!
   * @brief <比較
   */
  template <class Other_>
  GG_INLINE bool operator< (const GGRef<Other_>& o) const noexcept
  {
    return this->ptr_ < o.ptr_;
  }

  /*!
   * @brief <=比較
   */
  template <class Other_>
  GG_INLINE bool operator<= (const GGRef<Other_>& o) const noexcept
  {
    return this->ptr_ <= o.ptr_;
  }

  /*!
   * @brief >比較
   */
  template <class Other_>
  GG_INLINE bool operator> (const GGRef<Other_>& o) const noexcept
  {
    return this->ptr_ > o.ptr_;
  }

  /*!
   * @brief >比較
   */
  template <class Other_>
  GG_INLINE bool operator>= (const GGRef<Other_>& o) const noexcept
  {
    return this->ptr_ >= o.ptr_;
  }


  // =================================================================
  // Data Members
  // =================================================================
protected:
  Obj_* ptr_;

};