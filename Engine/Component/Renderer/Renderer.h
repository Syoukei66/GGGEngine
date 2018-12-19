#pragma once

#include <Engine/Component/GameComponent.h>

class GameObjectRenderState;

class Renderer : public GameComponent
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_COMPONENT(Renderer);
  GG_INIT_FUNC_1(Renderer, GameObject*);

  // =================================================================
  // Methods
  // =================================================================
public:
  void ReserveDraw(GameObjectRenderState* state);
  void Draw(GameObjectRenderState* state) const;

protected:
  virtual bool SetStreamSource() const = 0;
  virtual bool BeginPass(T_UINT8 pass, const SharedRef<rcShader>& shader) const = 0;
  virtual void DrawSubset(T_UINT8 submesh_index) const = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE void SetLayerId(T_UINT8 layer_id)
  {
    this->layer_id_ = layer_id;
  }
  GG_INLINE T_UINT8 GetLayerId() const
  {
    return this->layer_id_;
  }

  void SetMaterial(const SharedRef<rcMaterial>& material, T_UINT16 index = 0);
  GG_INLINE void SetSharedMaterial(const SharedRef<const rcMaterial>& material, T_UINT16 index = 0)
  {
    this->shared_materials_[index] = material;
  }

  SharedRef<rcMaterial> GetMaterial(T_UINT16 index = 0);
  SharedRef<const rcMaterial> GetMaterial(T_UINT16 index = 0) const;
  GG_INLINE SharedRef<const rcMaterial> GetSharedMaterial(T_UINT16 index = 0)
  {
    return this->shared_materials_.at(index);
  }

  GG_INLINE bool HasMaterial() const
  {
    return this->shared_materials_.size() > 0 || this->materials_.size() > 0;
  }

  GG_INLINE T_UINT8 GetMaterialCount() const
  {
    return (T_UINT8)this->shared_materials_.size();
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  T_UINT8 layer_id_;
  std::unordered_map<T_UINT32, SharedRef<const rcMaterial>> shared_materials_;
  std::unordered_map<T_UINT32, SharedRef<rcMaterial>> materials_;

  struct ShaderBuiltinData
  {
    Matrix4x4 mat_mvp;
    //Matrix4x4 mat_mv;
    //Matrix4x4 obj_to_world;
    //Matrix4x4 world_to_obj;

    //TVec4f time_;
    //TVec4f sin_time_;
    //TVec4f cos_time_;
  } builtin_variable_;
  SharedRef<rcConstantBuffer> builtin_variable_buffer_;

};