#pragma once

#include "GGRefSFINAE.h"

/*!
 * @brief GGGEngine�Ŏg�p����S�ẴI�u�W�F�N�g�̊��N���X
 * ���t�@�����X�J�E���^�������Ă���A�K�[�x�b�W�R���N�^�Ŏ�����������B
 * ���t�@�����X�J�E���^��Object���g�������Ă���̂́A
 * Ref�Ɏ��������ꍇ���ƃR�s�[�R�X�g����������ׁB
 */
class GGObject
{
  GG_NO_COPYABLE(GGObject);

  friend class GGObjectManager;
  template <class Obj_, GGIsObject<Obj_>>
  friend class GGRef;
  template <class Obj_>
  friend class SharedRef;
  template <class Obj_>
  friend class UniqueRef;

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  GGObject() = default;
  virtual ~GGObject() = default;

  // =================================================================
  // Methods
  // =================================================================
private:
  /*!
   * @brief ObjectManager�ɊǗ�����Ă��邩�̃t���O�𗧂Ă�
   * ��d�o�^�̖h�~�ȂǂɎg�p����
   */
  GG_INLINE void Managed() const
  {
    const_cast<GGObject*>(this)->managed_ = true;
  }

  /*!
   * @brief ObjectManager�ɊǗ�����Ă��邩
   */
  GG_INLINE bool IsManaged() const
  {
    return this->managed_;
  }

  /*!
   * @brief ���t�@�����X�J�E���^�̑���
   */
  GG_INLINE void Retain() const
  {
    ++const_cast<GGObject*>(this)->reference_count_;
  }

  /*!
   * @brief ���t�@�����X�J�E���^�̌���
   */
  GG_INLINE void Release() const
  {
    GG_ASSERT(this->reference_count_ > 0, "���t�@�����X�J�E���^��0�̎���Release���܂���");
    --const_cast<GGObject*>(this)->reference_count_;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:

  /*!
   * @brief �f�o�b�O���⃍�O��ŕ\�������I�u�W�F�N�g���B
   * ��`����ۂ�GG_OBJ_NAME�}�N�����g�p���鎖�𐄏�
   */
  virtual const char* GetObjectName() const = 0;

  /*!
   * @brief �f�o�b�O���⃍�O��ŕ\�������g�p�������T�C�Y�B
   * �h���N���X����override���Ȃ��ƃ������T�C�Y�Q�Ǝ��G���[���O���\�������B
   */
  virtual size_t GetMemorySize() const;

  /*!
   * @brief �f�o�b�O���⃍�O��ŕ\�������g�p�r�f�I�������T�C�Y�B
   * �h���N���X����override���Ȃ��ƃr�f�I�������T�C�Y�Q�Ǝ��G���[���O���\�������B
   */
  virtual size_t GetVideoMemorySize() const;

  GG_INLINE T_UINT32 GetReferenceCount() const
  {
    return this->reference_count_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  bool managed_;
  T_UINT32 reference_count_;

};