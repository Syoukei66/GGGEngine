#ifndef HAL_ENGINE_ENTITY_ENTITY_H_
#define HAL_ENGINE_ENTITY_ENTITY_H_

#include "NativeType.h"
#include "GameComponent.h"
#include "Material.h"

#include "Renderer.h"
#include "AnimatedSpriteRenderer.h"
#include "MeshRenderer.h"
#include "SpriteRenderer.h"

#include "Transform.h"

class GameObjectRenderState;

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
  virtual void Init();

  virtual void ManagedPreUpdate() = 0;
  virtual void ManagedUpdate() = 0;
  virtual void ManagedPostUpdate() = 0;

  virtual void ManagedDraw(GameObjectRenderState* state);
  
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

  inline void SetRenderer(Renderer* renderer)
  {
    this->renderer_ = renderer;
  }
  inline Renderer* GetRenderer() const
  {
    return this->renderer_;
  }

  // =================================================================
  // delegate to Transform
  // =================================================================
  inline const INativeMatrix& GetMatrix() const
  {
    return this->transform_->GetMatrix();
  }

  inline const INativeMatrix& GetTranslateMatrix() const
  {
    return this->transform_->GetTranslateMatrix();
  }

  inline const INativeMatrix& GetRotationMatrix() const
  {
    return this->transform_->GetRotationMatrix();
  }

  inline const INativeMatrix& GetScaleMatrix() const
  {
    return this->transform_->GetScaleMatrix();
  }

  inline const INativeMatrix& GetWorldMatrix() const
  {
    return this->transform_->GetWorldMatrix();
  }

  // =================================================================
  // delegate to Renderer
  // =================================================================
  inline void UniqueMaterial()
  {
    this->renderer_->UniqueMaterial();
  }
  inline void SetLayerId(T_UINT8 layer_id)
  {
    this->renderer_->SetLayerId(layer_id);
  }
  inline T_UINT8 GetLayerId() const
  {
    this->renderer_->GetLayerId();
  }
  inline void AddMaterial(Material& material)
  {
    this->renderer_->AddMaterial(material);
  }
  inline void SetMaterial(Material& material)
  {
    this->renderer_->SetMaterial(material);
  }
  inline void SetMaterial(T_UINT16 index, Material& material)
  {
    this->renderer_->SetMaterial(index, material);
  }
  inline Material* GetMaterial(T_UINT16 index = 0) const
  {
    return this->renderer_->GetMaterial(index);
  }
  inline T_UINT16 GetMaterialCount()
  {
    return this->renderer_->GetMaterialCount();
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  Transform* transform_;

private:
	bool visible_;
  Renderer* renderer_;
};

#endif//HAL_ENGINE_ENTITY_ENTITY_H_
