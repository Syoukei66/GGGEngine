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
   * DynamicCast���s����SharedRef��Ԃ��B
   */
  template <class OtherResource_>
  static FORCE_INLINE SharedRef<Resource_> DynamicCast(const SharedRef<OtherResource_>& ref)
  {
    return SharedRef<Resource_>((Resource_*)ref.ptr_);
  }

  /*!
   * �f�t�H���g�R���X�g���N�^�B���L���������Ȃ��A���SharedRef���\�z����B
   */
  FORCE_INLINE constexpr SharedRef() noexcept = default;

  /*!
   * ���|�C���^�̏��L�����󂯎��B
   * \param ptr ���|�C���^
   */
  FORCE_INLINE explicit SharedRef(Resource_* ptr)
  {
    ptr->Retain();
    this->ptr_ = ptr;
  }

  /*!
   * �R�s�[�R���X�g���N�^�Bo�Ə��L���̋��L�B
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
   * �R�s�[�R���X�g���N�^�B�ϊ��\��o�Ə��L���̋��L�B
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
   * ���[�u�R���X�g���N�^�Bo���珊�L�����ړ�����B
   */
  FORCE_INLINE SharedRef(SharedRef&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  /*!
   * ���[�u�R���X�g���N�^�B���̕ϊ��\��o���珊�L�����ړ�����B
   */
  template <class _OtherResource>
  FORCE_INLINE SharedRef(SharedRef<_OtherResource>&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  /*!
   * o���珊�L���̈ړ��B
   */
  template <class _OtherResource>
  FORCE_INLINE SharedRef(UniqueResource<_OtherResource>&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  /*!
   * ���L���������Ȃ����SharedRef�̍쐬�B
   * \param p nullptr
   */
  FORCE_INLINE constexpr SharedRef(nullptr_t p)
  {
    this->ptr_ = p;
  }

  /*!
   * �f�X�g���N�^�B���L����j������B
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
   * ���g���ێ����Ă��郊�\�[�X�̏��L����������Ao�������\�[�X�̏��L�������L����B
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
   * ���g���ێ����Ă��郊�\�[�X�̏��L����������A�ϊ��\��o�������\�[�X�̏��L�������L����B
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
   * ���g���ێ����Ă��郊�\�[�X�̏��L����������Ao�������\�[�X�̏��L�����ړ�����B
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
  * ���g���ێ����Ă��郊�\�[�X�̏��L����������Ao�������\�[�X�̏��L�����ړ�����B
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
   * ���g���ێ����Ă��郊�\�[�X�̏��L����������A�ϊ��\��o�������\�[�X�̏��L�����ړ�����B
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
   * ���g���ێ����Ă��郊�\�[�X�̏��L����������Ao�������\�[�X�̏��L�����ړ�����B
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
   * �����o�A�N�Z�X
   */
  FORCE_INLINE Resource_* operator -> () const noexcept
  {
    return this->ptr_;
  }

  /*!
   * �ԐڎQ��
   */
  FORCE_INLINE Resource_& operator*() const noexcept
  {
    return *this->ptr_;
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