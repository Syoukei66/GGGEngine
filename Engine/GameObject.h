#ifndef HAL_ENGINE_ENTITY_ENTITY_H_
#define HAL_ENGINE_ENTITY_ENTITY_H_

#include "NativeType.h"
#include "GameComponent.h"
#include "Material.h"
#include "Renderer.h"

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
  // Data Member
  // =================================================================
private:
	bool visible_;
  Renderer* renderer_;
};

#endif//HAL_ENGINE_ENTITY_ENTITY_H_
