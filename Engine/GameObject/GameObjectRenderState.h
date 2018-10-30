#pragma once

#include "GameObjectRenderQueue.h"

class Camera;
class Renderer;

//TODO:ƒJƒƒ‰‚ÆØ‚è—£‚µ‚½•û‚ª‚¢‚¢
class GameObjectRenderState
{

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GameObjectRenderState(Camera* camera);
  virtual ~GameObjectRenderState();

  // =================================================================
  // Method
  // =================================================================
public:
  void Init();
  void Draw();
  void AddQueue(const Renderer* renderer);

  GG_INLINE void SetWorldMatrix(const Matrix4x4& model)
  {
    this->world_matrix_ = model;
  }
  GG_INLINE void PushWorldMatrix(const Matrix4x4& model)
  {
    this->world_matrix_ *= model;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE void AddTargetLayerId(T_UINT8 layer_id)
  {
    layer_state_ |= 1 << layer_id;
  }
  GG_INLINE void AddAllTargetLayerIds()
  {
    layer_state_ = 0xffffffff;
  }
  GG_INLINE void RemoveTargetLayerId(T_UINT8 layer_id)
  {
    layer_state_ &= ~(1 << layer_id);
  }
  GG_INLINE void ClearTargetLayerIds()
  {
    layer_state_ = 0x00000000;
  }
  GG_INLINE bool IsTargetedLayer(T_UINT8 layer_id)
  {
    return layer_state_ & (1 << layer_id);
  }
  GG_INLINE const Camera* GetCamera() const
  {
    return this->camera_;
  }
  GG_INLINE const Matrix4x4& GetViewProjMatrix() const
  {
    return this->view_proj_matrix_;
  }
  GG_INLINE const Matrix4x4& GetWorldMatrix() const
  {
    return this->world_matrix_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  Camera* camera_;
  T_UINT32 layer_state_;
  Matrix4x4 view_proj_matrix_;
  Matrix4x4 world_matrix_;

  GameObjectRenderQueue* queues_[Graphics::RQ_DATANUM];
};
