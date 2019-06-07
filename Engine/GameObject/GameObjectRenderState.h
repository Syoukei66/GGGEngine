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
  // Methods
  // =================================================================
public:
  void Init();
  void Draw();
  void AddQueue(const Renderer* renderer);
  GG_INLINE void SetConstantBuffer()
  {
    this->builtin_variable_buffer_->SetBuffer();
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
    return this->builtin_variable_.mat_vp;
  }
  GG_INLINE const Matrix4x4& GetViewMatrix() const
  {
    return this->builtin_variable_.mat_v;
  }
  GG_INLINE const Matrix4x4& GetProjectionMatrix() const
  {
    return this->builtin_variable_.mat_p;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  Camera* camera_;
  T_UINT32 layer_state_;

  GameObjectRenderQueue* queues_[Graphics::RQ_DATANUM];

  struct ShaderBuiltinData
  {
    Matrix4x4 mat_v;
    Matrix4x4 mat_p;
    Matrix4x4 mat_vp;

    TVec4f world_space_camera_pos_;
    TVec4f projection_params_;
    TVec4f screen_params_;
    TVec4f z_buffer_params_;
    TVec4f ortho_params_;
  } builtin_variable_;
  SharedRef<rcConstantBuffer> builtin_variable_buffer_;

};
