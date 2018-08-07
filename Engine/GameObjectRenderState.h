#pragma once

#include "../Common/NativeType.h"
#include "../Common/BlendFunction.h"
#include "../Common/GraphicsConstants.h"
#include "../Common/Matrix4x4.h"

#include "GameObjectRenderQueue.h"

class Camera;
class Renderer;

//TODO:カメラと切り離した方がいい
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

  inline void SetWorldMatrix(const Matrix4x4& model)
  {
    this->world_matrix_ = model;
  }
  inline void PushWorldMatrix(const Matrix4x4& model)
  {
    this->world_matrix_ *= model;
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline void AddTargetLayerId(T_UINT8 layer_id)
  {
    layer_state_ |= 1 << layer_id;
  }
  inline void AddAllTargetLayerIds()
  {
    layer_state_ = 0xffffffff;
  }
  inline void RemoveTargetLayerId(T_UINT8 layer_id)
  {
    layer_state_ &= ~(1 << layer_id);
  }
  inline void ClearTargetLayerIds()
  {
    layer_state_ = 0x00000000;
  }
  inline bool IsTargetedLayer(T_UINT8 layer_id)
  {
    return layer_state_ & (1 << layer_id);
  }
  inline const Camera* GetCamera() const
  {
    return this->camera_;
  }
  inline const Matrix4x4& GetViewProjMatrix() const
  {
    return this->view_proj_matrix_;
  }
  inline const Matrix4x4& GetWorldMatrix() const
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
