#pragma once

#include <Engine/GameObject/GameObject.h>
#include "ComponentMacro.h"

/*!
 * @brief GameObjectにアタッチして使用するコンポーネント
 */
class GameComponent : public GGObject
{
protected:
  enum ComponentType
  {
    COMPONENT_TYPE_RENDERER,
    COMPONENT_TYPE_CAMERA,
    COMPONENT_TYPE_GIZMO_RENDERER,
  };

  static constexpr T_UINT32 COMPONENT_SHIFT = 8;
  static constexpr T_UINT32 INHERITANCE_SHIFT = 4;

  enum class ComponentID : T_UINT32
  {
    Renderer          = (1 << COMPONENT_TYPE_RENDERER) << COMPONENT_SHIFT,
    MeshRenderer,
    SpriteRenderer,
    Camera            = (1 << COMPONENT_TYPE_CAMERA) << COMPONENT_SHIFT,
    Camera2D          = Camera + (1 << INHERITANCE_SHIFT),
    Camera3D          = Camera + (2 << INHERITANCE_SHIFT),
    Camera3D_LookAt,
    GizmoRenderer     = (1 << COMPONENT_TYPE_GIZMO_RENDERER) << COMPONENT_SHIFT,
  };

public:
  static constexpr T_UINT32 COMPONENT_MASK   = 0xff00;
  static constexpr T_UINT32 INHERITANCE_MASK = 0xfff0;

  // =================================================================
  // GGG Statement
  // =================================================================
  GG_INIT_FUNC_1(GameComponent, GameObject*, obj);

  // =================================================================
  // Events
  // =================================================================
public:
  virtual void PreUpdate() {}
  virtual void Update() {}
  virtual void PostUpdate() {}

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  virtual T_UINT32 GetComponentID() const = 0;

  GG_INLINE void SetEnabled(bool enabled)
  {
    this->enabled_ = enabled;
  }
  GG_INLINE bool IsEnabled() const
  {
    return this->enabled_;
  }

  SharedRef<GameObject> GetObject()
  {
    return SharedRef<GameObject>(this->obj_);
  }

  SharedRef<const GameObject> GetObject() const
  {
    return SharedRef<const GameObject>(this->obj_);
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  bool enabled_;
  GameObject* obj_;

};
