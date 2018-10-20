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
   * �f�t�H���g�R���X�g���N�^�B���L���������Ȃ��A���UniqueResource�I�u�W�F�N�g���\�z����B
   */
  FORCE_INLINE constexpr UniqueResource() noexcept = default;

  /*!
   * ���|�C���^�̏��L�����󂯎��B
   * \param ptr ���|�C���^
   */
  FORCE_INLINE explicit UniqueResource(Resource_* ptr)
  {
    ptr->Retain();
    this->ptr_ = ptr;
  }

  /*!
   * ���[�u�R���X�g���N�^�B����SharedRef���珊�L�����ړ�����B
   * \param o ����SharedRef
   */
  FORCE_INLINE UniqueResource(UniqueResource&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  /*!
   * ���[�u�R���X�g���N�^�B���̕ϊ��\��SharedRef���珊�L�����ړ�����B
   * \param o ���̕ϊ��\��SharedRef
   */
  template <class _OtherResource>
  FORCE_INLINE UniqueResource(UniqueResource<_OtherResource>&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  /*!
   * �f�X�g���N�^�B���L����j������B
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
   * �R�s�[����֎~�B
   */
  FORCE_INLINE UniqueResource& operator = (const UniqueResource&) = delete;

  /*!
   * ���g���ێ����Ă��郊�\�[�X��������A����UniqueResource���珊�L�����ړ�����B
   * \param o ����UniqueResource
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
   * ���g���ێ����Ă��郊�\�[�X��������A����UniqueResource���珊�L�����ړ�����B
   * \param o ����UniqueResource
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
   * ���g���ێ����Ă��郊�\�[�X���������B
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
   * �ԐڎQ��
   */
  FORCE_INLINE Resource_& operator*() const noexcept
  {
    return *this->ptr_;
  }

  /*!
   * �����o�A�N�Z�X
   */
  FORCE_INLINE Resource_* operator -> () const noexcept
  {
    return this->ptr_;
  }

  /*!
   * �L���ȃ��\�[�X�����L���Ă��邩���肷��
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
