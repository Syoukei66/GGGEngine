#pragma once

#include <list>
#include "GameObjectRenderState.h"
#include "Color.h"

class Camera2D;

class GameObject2DRenderState : public GameObjectRenderState
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GameObject2DRenderState(Camera2D* camera);
  ~GameObject2DRenderState();

  // =================================================================
  // Method
  // =================================================================
public:
  void Init() override;
  void PushColor(const Color& color);
  void PopColor();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline Camera2D* GetCamera() const
  {
    return this->camera_;
  }
  inline T_UINT32 GetWorldPackedColor()
  {
    Color color = Color::WHITE;
    for (std::list<Color>::iterator itr = this->color_stack_.begin(); itr != this->color_stack_.end(); ++itr)
    {
      color *= (*itr);
    }
    return color.GetPackedColor();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  Camera2D* const camera_;

  Color4F world_color_;
  std::list<Color> color_stack_;
};