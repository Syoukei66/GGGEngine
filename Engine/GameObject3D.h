#pragma once

#include <vector>
#include "GameObject.h"
#include "Color.h"
#include "Transform3D.h"

class GameObject3DRenderState;

class GameObject3D : public GameObject
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GameObject3D();
  virtual ~GameObject3D();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void Init() override;

  virtual void ManagedPreUpdate() override;
  virtual void ManagedUpdate() override;
  virtual void ManagedPostUpdate() override;

  // =================================================================
  // Method
  // =================================================================
public:
  //�qGameObject��ǉ����܂��B
  //�ǉ����ꂽ�qGameObject��delete����@�\�͂���܂���
  void AddChild(GameObject3D* child);
  //�w�肵���qGameObject���q���X�g����폜���܂��B
  void RemoveChild(GameObject3D* child);
  //���g��eGameObject�̎q���X�g����폜���܂��B
  void RemoveSelf();
  //�S�Ă̎qGameObject���q���X�g����폜���܂��B
  void ClearChildren();

  //�`�惁�\�b�h�ł��B���g�Ǝ��g�̎q�̕`�揈�����s���܂��B
  //�����̃��\�b�h�̓G���W�����`��T�C�N���̒��ŌĂяo���ׁA
  //���[�U�[�����ڌĂяo���@��͂���܂���B
  //�`����s�������ꍇ��GameObject�����݂�Scene��root�Ƃ���
  //GameObject�̎qGameObject�ɒǉ����Ă��������B
  //Draw���\�b�h���ł͈ȉ��̏��Ԃŏ������s���܂��B
  //  0.VBO�X�V����
  //  1.PreDraw()
  //  2.ZIndex��0�����̎qGameObject��Draw()
  //  4.NativeDraw() //���g�̕`�揈��
  //  5.ZIndex��0�ȏ�̎qGameObject��Draw()
  //  6.PostDraw()
  virtual void Draw(GameObject3DRenderState* state);

  virtual void PreDraw(GameObject3DRenderState* state) {}
  virtual void NativeDraw(GameObject3DRenderState* state) {}
  virtual void PostDraw(GameObject3DRenderState* state) {}

protected:
  virtual void PushMatrixStack(GameObject3DRenderState* state);
  virtual void PopMatrixStack(GameObject3DRenderState* state);

  // =================================================================
  // Events
  // =================================================================
public:
  virtual void FireOnPositionChanged(GameObject* root) override;
  virtual void FireOnScaleChanged(GameObject* root) override;
  virtual void FireOnRotationChanged(GameObject* root) override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline bool HasParent() const
  {
    return this->parent_;
  }
  inline GameObject3D* GetParent() const
  {
    return this->parent_;
  }

  inline Transform3D* GetTransform()
  {
    return this->transform_;
  }

  inline const Transform3D* GetTransform() const
  {
    return this->transform_;
  }

  inline void SetZTestFlag(bool z_test)
  {
    this->z_test_ = z_test;
  }

  inline bool GetZTestFlag() const
  {
    return this->z_test_;
  }

  inline void SetBillboardingFlag(bool billboarding)
  {
    this->billbording_ = billboarding;
  }

  inline bool IsBillboard() const
  {
    return this->billbording_;
  }

private:
  Transform3D* transform_;
  GameObject3D* parent_;
  std::vector<GameObject3D*> children_;

  bool z_test_;
  bool billbording_;
};
