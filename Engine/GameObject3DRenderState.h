#pragma once

#include <vector>
#include <map>
#include "GameObjectRenderState.h"

class Camera3D;
class GameObject3D;

class GameObject3DRenderState : public GameObjectRenderState
{
private:
  class PostDrawParam
  {
  public:
    GameObject3D* object;
    T_FLOAT distance;
  };

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GameObject3DRenderState(Camera3D* camera);
  ~GameObject3DRenderState();

  // =================================================================
  // Method
  // =================================================================
public:
  void Init() override;
  void AddZCheckOrder(T_UINT8 level, GameObject3D* object);
  void DrawZOrderedGameObject();

protected:
  virtual void SetupViewProjMatrix(INativeMatrix* view_proj_matrix) override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline Camera3D* GetCamera() const
  {
    return this->camera_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  Camera3D* const camera_;

  INativeMatrix* mat_;
  std::map<int, std::vector<PostDrawParam>> post_draw_map_;

};