#pragma once

#include "Ref.h"

#include "UniqueRef.h"

template <class Obj_>
class SharedRef;

/*!
 * @brief GGObject��p��shared_ptr
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
   * @brief �f�t�H���g�R���X�g���N�^�B
   * ���L���������Ȃ��A���SharedRef���\�z����B
   */
  GG_INLINE constexpr SharedRef() noexcept = default;

  /*!
   * @brief �f�t�H���g�f�X�g���N�^�B���L����j������B
   */
  GG_INLINE ~SharedRef() = default;

  /*!
   * @brief ���|�C���^�̏��L�����󂯎��A
   * �I�u�W�F�N�g�Ǘ��N���X�֒ǉ��B
   */
  GG_INLINE explicit SharedRef(Obj_* ptr) : GGRef<Obj_>(ptr) {}

  /*!
   * @brief ���L���������Ȃ����SharedRef�̍쐬�B
   */
  GG_INLINE constexpr SharedRef(nullptr_t p) : GGRef<Obj_>(p) {}

  /*!
   * @brief �R�s�[�R���X�g���N�^�B
   * ����SharedRef�Ə��L���̋��L�B
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
   * @brief �R�s�[�R���X�g���N�^�B
   * ���̕ϊ��\��SharedRef�Ə��L���̋��L�B
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
   * @brief ���[�u�R���X�g���N�^�B
   * ����SharedRef���珊�L�����ړ�����B
   */
  GG_INLINE SharedRef(SharedRef&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  /*!
   * @brief ���[�u�R���X�g���N�^�B
   * ���̕ϊ��\��SharedRef���珊�L�����ړ�����B
   */
  template <class _OtherObj>
  GG_INLINE SharedRef(SharedRef<_OtherObj>&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  /*!
   * @brief ���[�u�R���X�g���N�^�B
   * ���̕ϊ��\��UniqueRef���珊�L�����ړ�����B
   */
  template <class _OtherObj>
  GG_INLINE SharedRef(UniqueRef<_OtherObj>&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  /*!
   * @brief StaticCast���s����SharedRef��Ԃ��B
   * ���|�C���^�������Ƃ����R���X�g���N�^���N�����Ă��܂���
   * ObjectManager�֓�d�o�^������Ă��܂��ה����Ă���B
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
   * @brief ���g���ێ����Ă��郊�\�[�X���������B
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
   * @brief ���g���ێ����Ă��鏊�L����������A
   * ����SharedRef�������L�������L����B
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
   * @brief ���g���ێ����Ă��鏊�L����������A
   * ���̕ϊ��\��SharedRef�������L�������L����B
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
   * @brief ���g���ێ����Ă��鏊�L����������A
   * ����SharedRef�������L�����ړ�����B
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
   * @brief ���g���ێ����Ă��鏊�L����������A
   * ���̕ϊ��\��SharedRef�������L�����ړ�����B
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
   * @brief ���g���ێ����Ă��鏊�L����������A
   * ���̕ϊ��\��UniqueRef�������L�����ړ�����B
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