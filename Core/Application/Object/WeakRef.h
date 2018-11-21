#pragma once

#include "Ref.h"

#include "SharedRef.h"

template <class Obj_>
class WeakRef;

/*!
 * @brief GGObject専用のweak_ptr
 */
template <class Obj_>
class WeakRef : public GGRef<Obj_>
{
  template <class OtherObj_>
  friend class WeakRef;

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  /*!
   * @brief デフォルトコンストラクタ。
   * 監視対象を持たない、空のWeakRefを構築する。
   */
  GG_INLINE constexpr WeakRef() noexcept = default;

  /*!
   * @brief デストラクタ。
   * 監視しているオブジェクトに影響を与えないよう、
   * スーパークラスのデストラクタが起動する前にnullptrを代入しておく
   */
  GG_INLINE ~WeakRef()
  {
    this->ptr_ = nullptr;
  }

  /*!
   * @brief コピーコンストラクタ。
   * 他のWeakRefから監視対象をコピーする。
   */
  GG_INLINE WeakRef(const WeakRef& o) noexcept
  {
    this->ptr_ = o.ptr_;
  }

  /*!
   * @brief コピーコンストラクタ。
   * 他の変換可能なWeakRefから監視対象をコピーする。
   */
  template <class OtherObj_>
  GG_INLINE WeakRef(const WeakRef<OtherObj_>& o) noexcept
  {
    static_assert(std::is_base_of<Obj_, OtherObj_>::value, "type parameter of this class must derive from BaseClass");
    this->ptr_ = o.ptr_;
  }

  /*!
   * @brief コピーコンストラクタ
   * 他の変換可能なSharedRefが所有するオブジェクトを監視する。
   */
  template <class OtherObj_>
  GG_INLINE WeakRef(const SharedRef<OtherObj_>& o) noexcept
  {
    static_assert(std::is_base_of<Obj_, OtherObj_>::value, "type parameter of this class must derive from BaseClass");
    this->ptr_ = o.ptr_;
  }

  /*!
   * @brief ムーブコンストラクタ。
   * 他のWeakRefの監視対象を自身に移動する
   */
  GG_INLINE WeakRef(WeakRef&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  /*!
   * @brief ムーブコンストラクタ。
   * 他のWeakRefの変換可能な監視対象を自身に移動する
   */
  template <class OtherObj_>
  GG_INLINE WeakRef(WeakRef<OtherObj_>&& o) noexcept
  {
    static_assert(std::is_base_of<Obj_, OtherObj_>::value, "type parameter of this class must derive from BaseClass");
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  // =================================================================
  // operator
  // =================================================================
public:
  /*!
   * @brief 現在の監視を放棄し、新たな監視対象をセットする
   */
  GG_INLINE WeakRef& operator = (const WeakRef& o) noexcept
  {
    this->ptr_ = o.ptr_;
    return *this;
  }

  /*!
   * @brief 現在の監視を放棄し、変換可能な新たな監視対象をセットする
   */
  template <class OtherObj_>
  GG_INLINE WeakRef& operator = (const WeakRef<OtherObj_>& o) noexcept
  {
    this->ptr_ = o.ptr_;
    return *this;
  }

  /*!
   * @brief 自身が保持している所有権を放棄し、
   * 他のSharedRefが持つオブジェクトの監視を開始する。
   */
  template <class OtherObj_>
  GG_INLINE WeakRef& operator = (const SharedRef<OtherObj_>& o) noexcept
  {
    this->ptr_ = o.ptr_;
    return *this;
  }

  /*!
   * @brief 現在の監視を放棄し、新たな監視対象を移動する
   */
  GG_INLINE WeakRef& operator = (WeakRef&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
    return *this;
  }

  /*!
   * @brief 現在の監視を放棄し、変換可能な新たな監視対象を移動する
   */
  template <class OtherObj_>
  GG_INLINE WeakRef& operator = (WeakRef<OtherObj_>&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
    return *this;
  }

  // =================================================================
  // Method
  // =================================================================
public:
  GG_INLINE void Reset() const
  {
    const_cast<WeakRef<Obj_>*>(this)->ptr_ = nullptr;
  }

  GG_INLINE SharedRef<Obj_> Lock() const
  {
    if (this->ptr_)
    {
      return SharedRef<Obj_>(this->ptr_);
    }
    return nullptr;
  }

};
