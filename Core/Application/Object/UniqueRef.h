#pragma once

#include "Ref.h"

template <class Obj_>
class UniqueRef;
template <class Obj_>
class SharedRef;

/*!
* @brief GGObject��p��unique_ptr
*/
template <class Obj_>
class UniqueRef : public GGRef<Obj_>
{
  template <class OtherObj_>
  friend class UniqueRef;
  template <class OtherObj_>
  friend class SharedRef;

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  /*!
  * @brief �f�t�H���g�R���X�g���N�^�B
  * ���L���������Ȃ��A���UniqueRef���\�z����B
  */
  GG_INLINE constexpr UniqueRef() noexcept = default;

  /*!
  * @brief �f�t�H���g�f�X�g���N�^�B���L����j������B
  */
  GG_INLINE ~UniqueRef() = default;

  /*!
  * @brief ���|�C���^�̏��L�����󂯎��A
  * �I�u�W�F�N�g�Ǘ��N���X�֒ǉ��B
  */
  GG_INLINE explicit UniqueRef(Obj_* ptr) : GGRef<Obj_>(ptr) {}

  /*!
  * @brief ���L���������Ȃ����UniqueRef�̍쐬�B
  */
  GG_INLINE constexpr UniqueRef(nullptr_t p) : GGRef<Obj_>(p) {}

  /*!
  * @brief ���[�u�R���X�g���N�^�B
  * ���̕ϊ��\��UniqueRef���珊�L�����ړ�����B
  */
  template <class OtherObj_, GGRefConvertible<Obj_, OtherObj_> = nullptr>
  GG_INLINE UniqueRef(UniqueRef<OtherObj_>&& o) noexcept
  {
    this->ptr_ = o.ptr_;
    o.ptr_ = nullptr;
  }

  // =================================================================
  // operator
  // =================================================================
public:
  /*!
  * @brief ���g���ێ����Ă��郊�\�[�X���������B
  */
  GG_INLINE UniqueRef& operator = (nullptr_t p) noexcept
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
  * ���̕ϊ��\��UniqueRef�������L�����ړ�����B
  */
  template <class OtherObj_, GGRefConvertible<Obj_, OtherObj_> = nullptr>
  GG_INLINE UniqueRef& operator = (UniqueRef<OtherObj_>&& o) noexcept
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
