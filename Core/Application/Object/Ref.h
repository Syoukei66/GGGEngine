#pragma once

#include "ObjectManager.h"

class GGObject;

/*!
 * @brief SFINAE�ׂ̈Ƀ|�C���^�̌^�`�F�b�N�ɗp����
 */
template <class From_, class To_>
using GGRefConvertible = std::enable_if_t<
  std::is_same<From_, To_>::value ||
  std::is_base_of<To_, From_>::value ||
  std::is_convertible<From_, To_>::value,
  std::nullptr_t
>;

/*!
 * @brief SFINAE�ׂ̈Ƀ|�C���^�̌^�`�F�b�N�ɗp����
 */
template <class From_, class To_>
using GGRefStaticCastbale = std::enable_if_t<
  std::is_same<From_, To_>::value ||
  std::is_base_of<To_, From_>::value ||
  std::is_convertible<From_, To_>::value,
  std::nullptr_t
>;

/*!
 * @brief SFINAE�ׂ̈Ƀ|�C���^�̌^�`�F�b�N�ɗp����
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
   * @brief �f�t�H���g�R���X�g���N�^�B
   * ���L���������Ȃ��A���Ref���\�z����B
   */
  GG_INLINE constexpr GGRef() noexcept = default;

  /*!
   * @brief �f�X�g���N�^�B���L����j������B
   */
  GG_INLINE ~GGRef()
  {
    if (this->ptr_)
    {
      this->ptr_->Release();
    }
  }

  /*!
   * @brief ���|�C���^�̏��L�����󂯎��A
   * �I�u�W�F�N�g�Ǘ��N���X�֒ǉ��B
   */
  template <GGIsObject<Obj_> = nullptr>
  GG_INLINE explicit GGRef(Obj_* ptr)
  {
    ptr->Retain();
    GGObjectManager::Manage(ptr);
    this->ptr_ = ptr;
  }

  /*!
   * @brief ���L���������Ȃ����Ref�̍쐬�B
   */
  GG_INLINE constexpr GGRef(nullptr_t p)
    : ptr_()
  {}

  // =================================================================
  // operator
  // =================================================================
public:
  /*!
   * @brief �R�s�[����֎~�B
   */
  GG_INLINE GGRef& operator = (const GGRef&) = delete;

  /*!
   * @brief �����o�A�N�Z�X
   */
  GG_INLINE Obj_* operator -> () const noexcept
  {
    return this->ptr_;
  }

  /*!
   * @brief �ԐڎQ��
   */
  GG_INLINE Obj_& operator*() const noexcept
  {
    return *this->ptr_;
  }

  /*!
   * @brief �L���ȃ��\�[�X�����L���Ă��邩���肷��
   */
  GG_INLINE explicit operator bool() const noexcept
  {
    return this->ptr_ != nullptr;
  }

  /*!
   * @brief ���l��r
   */
  template <class Other_>
  GG_INLINE bool operator== (const GGRef<Other_>& o) const noexcept
  {
    return this->ptr_ == o.ptr_;
  }

  /*!
   * @brief nullptr���l��r
   */
  GG_INLINE bool operator== (nullptr_t o) const noexcept
  {
    return this->ptr_ == o;
  }

  /*!
   * @brief �񓙒l��r
   */
  template <class Other_>
  GG_INLINE bool operator!= (const GGRef<Other_>& o) const noexcept
  {
    return this->ptr_ != o.ptr_;
  }

  /*!
   * @brief nullptr�񓙒l��r
   */
  GG_INLINE bool operator!= (nullptr_t o) const noexcept
  {
    return this->ptr_ != o;
  }

  /*!
   * @brief <��r
   */
  template <class Other_>
  GG_INLINE bool operator< (const GGRef<Other_>& o) const noexcept
  {
    return this->ptr_ < o.ptr_;
  }

  /*!
   * @brief <=��r
   */
  template <class Other_>
  GG_INLINE bool operator<= (const GGRef<Other_>& o) const noexcept
  {
    return this->ptr_ <= o.ptr_;
  }

  /*!
   * @brief >��r
   */
  template <class Other_>
  GG_INLINE bool operator> (const GGRef<Other_>& o) const noexcept
  {
    return this->ptr_ > o.ptr_;
  }

  /*!
   * @brief >��r
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