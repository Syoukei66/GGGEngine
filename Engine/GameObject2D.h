#pragma once

#include <vector>
#include "GameObject.h"
#include "Color.h"
#include "Transform2D.h"

class EntityModifierRoot;
class GameObject2DRenderState;

class GameObject2D : public GameObject
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GameObject2D();
  virtual ~GameObject2D();
  
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
  void AddChild(GameObject2D* child);
  //�w�肵���qGameObject���q���X�g����폜���܂��B
  void RemoveChild(GameObject2D* child);
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
  virtual void Draw(GameObject2DRenderState* state);

  virtual void PreDraw(GameObject2DRenderState* state) {}
  virtual void NativeDraw(GameObject2DRenderState* state) {}
  virtual void PostDraw(GameObject2DRenderState* state) {}


private:
  void UpdateChildrenZIndex();

public:
  //���g���e�ƂȂ����ۂ̍��W�����[�J�����W�Ƃ��Ă��鎖�ɒ���
  //absolute��true�ɂ���ƁA�e��IsWorld�t���O�������Ă��悤��Scene�̐�΍��W�𓾂��
 
  //TODO:IsWorld�𕜊�������K�v���邩��
  void ConvertPositionLocalToWorld(const TVec2f* local, TVec2f* dest, GameObject2D* root = nullptr) const;
  void ConvertPositionLocalToWorld(T_FLOAT local_x, T_FLOAT local_y, TVec2f* dest, GameObject2D* root = nullptr) const;
  T_FLOAT ConvertXLocalToWorld(T_FLOAT local_x, GameObject2D* root = nullptr) const;
  T_FLOAT ConvertYLocalToWorld(T_FLOAT local_y, GameObject2D* root = nullptr) const;

  void RegisterEntityModifier(EntityModifierRoot* root);
  void UnregisterEntityModifier(EntityModifierRoot* root);
  void ClearEntityModifiers();

protected:
  virtual void PushMatrixStack(GameObject2DRenderState* state);
  virtual void PopMatrixStack(GameObject2DRenderState* state);

  // =================================================================
  // Events
  // =================================================================
public:
  virtual void FireOnPositionChanged(GameObject* root) override;
  virtual void FireOnScaleChanged(GameObject* root) override;
  virtual void FireOnRotationChanged(GameObject* root) override;

  virtual void OnChildrenZIndexChanged();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline Transform2D* GetTransform()
  {
    return this->transform_;
  }
  inline const Transform2D* GetTransform() const
  {
    return this->transform_;
  }
  inline void SetColor(const Color& color)
  {
    this->color_ = color;
  }
  inline void SetColor(T_UINT8 r, T_UINT8 g, T_UINT8 b)
  {
    this->color_.SetColor(r, g, b);
  }
  inline void SetColor(T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a)
  {
    this->color_.SetColor(r, g, b, a);
  }
  inline const Color& GetColor() const
  {
    return this->color_;
  }
  inline void SetRed(T_UINT8 r)
  {
    this->color_.SetRed(r);
  }
  inline T_UINT8 GetRed() const
  {
    return this->color_.GetRed();
  }
  inline void SetGreen(T_UINT8 g)
  {
    this->color_.SetGreen(g);
  }
  inline T_UINT8 GetGreen() const
  {
    return this->color_.GetGreen();
  }
  inline void SetBlue(T_UINT8 b)
  {
    this->color_.SetBlue(b);
  }
  inline T_UINT8 GetBlue() const
  {
    return this->color_.GetBlue();
  }
  inline void SetAlpha(T_UINT8 a)
  {
    this->color_.SetAlpha(a);
  }
  inline T_UINT8 GetAlpha() const
  {
    return this->color_.GetAlpha();
  }
  inline T_PACKED_COLOR_UINT32 GetPackedColor()
  {
    return this->color_.GetPackedColor();
  }
  inline void SetZIndex(T_INT8 zindex)
  {
    this->zindex_ = zindex;
    if (this->parent_)
    {
      this->parent_->OnChildrenZIndexChanged();
    }
  }
  inline T_INT8 GetZIndex() const
  {
    return this->zindex_;
  }
  
private:
  Transform2D* transform_;

  Color color_;

  GameObject2D* parent_;
  std::vector<GameObject2D*> children_;

  T_INT8 zindex_;
  bool children_zindex_dirty_;
};
