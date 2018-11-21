#pragma once

#include "Ref.h"

#include "SharedRef.h"

template <class Obj_>
class WeakRef;

/*!
 * @brief GGObject��p��weak_ptr
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
   * @brief �f�t�H���g�R���X�g���N�^�B
   * �Ď��Ώۂ������Ȃ��A���WeakRef���\�z����B
   */
  GG_INLINE constexpr WeakRef() noexcept = default;

  /*!
   * @brief �f�X�g���N�^�B
   * �Ď����Ă���I�u�W�F�N�g�ɉe����^���Ȃ��悤�A
   * �X�[�p�[�N���X�̃f�X�g���N�^���N������O��nullptr�������Ă���
   */
  GG_INLINE ~WeakRef()
  {
    this->ptr_ = nullptr;
  }

  /*!
   * @brief �R�s�[�R���X�g���N�^�B
   * ����WeakRef����Ď��Ώۂ��R�s�[����B
   */
  GG_INLINE WeakRef(const WeakRef& o) noexcept
  {
    this->ptr_ = o.ptr_;
  }

  /*!
   * @brief �R�s�[�R���X�g���N�^�B
   * ���̕ϊ��\��WeakRef����Ď��Ώۂ��R�s�[����B
   */
  template <class OtherObj_>
  GG_INLINE WeakRef(const WeakRef<OtherObj_>& o) noexcept
  {
    static_assert(std::is_base_of<Obj_, OtherObj_>::value, "type parameter of this class must derive from BaseClass");
    this->ptr_ = o.ptr_;
  }

  /*!
   * @brief �R�s�[�R���X�g���N�^
   * ���̕ϊ��\��SharedRef�����L����I�u�W�F�N�g���Ď�����B
   */
  template <class OtherObj_>
  GG_INLINE WeakRef(const SharedRef<OtherObj_>& o) noexcept
  {
    static_assert(std::is_base_of<Obj_, OtherObj_>::value, "type parameter of this class must derive from BaseClass");
    this->ptr_ = o.ptr_;
  }

  /*!
   * @brief ���[�u�R���X�g���N�^�B
   * ����WeakRef�̊Ď��Ώۂ����g�Ɉړ�����
   */
  GG_INLINE WeakRef(WeakRef&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  /*!
   * @brief ���[�u�R���X�g���N�^�B
   * ����WeakRef�̕ϊ��\�ȊĎ��Ώۂ����g�Ɉړ�����
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
   * @brief ���݂̊Ď���������A�V���ȊĎ��Ώۂ��Z�b�g����
   */
  GG_INLINE WeakRef& operator = (const WeakRef& o) noexcept
  {
    this->ptr_ = o.ptr_;
    return *this;
  }

  /*!
   * @brief ���݂̊Ď���������A�ϊ��\�ȐV���ȊĎ��Ώۂ��Z�b�g����
   */
  template <class OtherObj_>
  GG_INLINE WeakRef& operator = (const WeakRef<OtherObj_>& o) noexcept
  {
    this->ptr_ = o.ptr_;
    return *this;
  }

  /*!
   * @brief ���g���ێ����Ă��鏊�L����������A
   * ����SharedRef�����I�u�W�F�N�g�̊Ď����J�n����B
   */
  template <class OtherObj_>
  GG_INLINE WeakRef& operator = (const SharedRef<OtherObj_>& o) noexcept
  {
    this->ptr_ = o.ptr_;
    return *this;
  }

  /*!
   * @brief ���݂̊Ď���������A�V���ȊĎ��Ώۂ��ړ�����
   */
  GG_INLINE WeakRef& operator = (WeakRef&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
    return *this;
  }

  /*!
   * @brief ���݂̊Ď���������A�ϊ��\�ȐV���ȊĎ��Ώۂ��ړ�����
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
