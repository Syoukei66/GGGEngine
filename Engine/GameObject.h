#ifndef HAL_ENGINE_ENTITY_ENTITY_H_
#define HAL_ENGINE_ENTITY_ENTITY_H_

#include "NativeType.h"
#include "BlendFunction.h"
#include "GameComponent.h"
#include "GameObjectRenderState.h"
#include "Material.h"

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
  //GameObjectの座標などの初期化です
  //保持しているオブジェクトが解放される事はありません。
  //TODO:現状どのメンバが初期化され、どのメンバが初期化されないのかが不明瞭なので
  //     データメンバの一部をクラス化して、(Transform等)
  //     そのインスタンスに対する初期化という形での実装としてはどうだろうか
  virtual void Init();

  //TODO: 応急処置。
  void ApplyBlendMode(GameObjectRenderState* state);

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

  inline void SetMaterial(Material* material)
  {
    this->material_ = material;
  }
  inline Material* GetMaterial() const
  {
    return this->material_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
	bool visible_;
  T_UINT8 layer_id_;
  Material* material_;
  
};

#endif//HAL_ENGINE_ENTITY_ENTITY_H_
