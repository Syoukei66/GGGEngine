#ifndef HAL_ENGINE_ENTITY_ENTITY_H_
#define HAL_ENGINE_ENTITY_ENTITY_H_

#include "NativeType.h"
#include "BlendFunction.h"
#include "GameComponent.h"
#include "GameObjectRenderState.h"

class GameObject : public GameComponent
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GameObject();
  virtual ~GameObject();

  // =================================================================
  // Method
  // =================================================================
public:
  //GameObject�̍��W�Ȃǂ̏������ł�
  //�ێ����Ă���I�u�W�F�N�g���������鎖�͂���܂���B
  //TODO:����ǂ̃����o������������A�ǂ̃����o������������Ȃ��̂����s���ĂȂ̂�
  //     �f�[�^�����o�̈ꕔ���N���X�����āA(Transform��)
  //     ���̃C���X�^���X�ɑ΂��鏉�����Ƃ����`�ł̎����Ƃ��Ă͂ǂ����낤��
  virtual void Init();

  //TODO: ���}���u�B
  void ApplyMaterial(GameObjectRenderState* state);

  virtual void ManagedPreUpdate() = 0;
  virtual void ManagedUpdate() = 0;
  virtual void ManagedPostUpdate() = 0;
  
  // =================================================================
  // Events
  // =================================================================
public:
  virtual void FireOnPositionChanged(GameObject* root) = 0;
  virtual void FireOnScaleChanged(GameObject* root) = 0;
  virtual void FireOnRotationChanged(GameObject* root) = 0;

protected:
  virtual void OnPositionChanged(GameObject* root) {}
  virtual void OnScaleChanged(GameObject* root) {}
  virtual void OnRotationChanged(GameObject* root) {}

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline void SetVisible(bool visible)
  {
    this->visible_ = visible;
  }
  inline bool IsVisible() const
  {
    return this->visible_;
  }

  inline void SetLayerId(T_UINT8 layer_id)
  {
    this->layer_id_ = layer_id;
  }
  inline T_UINT8 GetLayerId() const
  {
    return this->layer_id_;
  }

  inline void SetBlendFunction(BlendFunction::BlendMode src, BlendFunction::BlendMode dst)
  {
    this->blend_function_src_ = src;
    this->blend_function_dst_ = dst;
  }
  inline void SetBlendFunctionSource(BlendFunction::BlendMode src)
  {
    this->blend_function_src_ = src;
  }
  inline BlendFunction::BlendMode GetBlendFunctionSource() const
  {
    return this->blend_function_src_;
  }
  inline void SetBlendFunctionDestination(BlendFunction::BlendMode dst)
  {
    this->blend_function_dst_ = dst;
  }
  inline BlendFunction::BlendMode GetBlendFunctionDestination() const
  {
    return this->blend_function_dst_;
  }
  // =================================================================
  // Data Member
  // =================================================================
private:
	bool visible_;
  T_UINT8 layer_id_;

  BlendFunction::BlendMode blend_function_src_;
  BlendFunction::BlendMode blend_function_dst_;
};

#endif//HAL_ENGINE_ENTITY_ENTITY_H_
