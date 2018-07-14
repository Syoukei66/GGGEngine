#pragma once

#include "RenderCommand.h"
#include "MeshRenderer.h"

class RenderCommand_DrawMesh : public RenderCommand
{
public:
  static Create();

protected:
  RenderCommand_DrawMesh(CommandBuffer* buffer, MeshRenderer* mesh_renderer, T_UINT8 material_index)
    : RenderCommand(buffer)
    , mesh_renderer_(mesh_renderer)
    , material_index_(material_index)
  {}

public:
  inline const Matrix4x4& GetWorldMatrix() override
  {
    return this->mesh_renderer_->GetGameObject()->GetWorldMatrix();
  }
  inline T_UINT8 GetAttributeId() override
  {
    return this->mesh_renderer_->GetMaterial(this->material_index_)->GetRenderAttribute();
  }
  inline T_UINT8 GetLayerId() override
  {
    return this->mesh_renderer_->GetLayerId();
  }
  inline T_UINT8 GetIndexId() override
  {
    return this->mesh_renderer_->GetIndexId();
  }

  inline Material* GetMaterial() override
  {
    this->mesh_renderer_->GetMaterial(this->material_index_);
  }
  inline INativeVertexBuffer* GetVertexBuffer() override
  {
    this->mesh_renderer_->GetMesh()->GetVertexBuffer();
  }
  inline INativeIndexBuffer* GetIndexBuffer() override
  {
    this->mesh_renderer_->GetMesh()->GetIndexBuffer(this->material_index_);
  }

private:
  MeshRenderer* mesh_renderer_;
  T_UINT8 material_index_;

};