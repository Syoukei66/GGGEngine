#pragma once

#include <Core/Mesh.h>

#include "Renderer.h"

class MeshRenderer : public Renderer
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static MeshRenderer* Create(const SharedRef<const rcMesh>& mesh, GameObject* entity);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  MeshRenderer(GameObject* entity);
  virtual ~MeshRenderer();

  // =================================================================
  // Method
  // =================================================================
protected:
  virtual bool SetStreamSource() const override;
  virtual void SetProperties(const SharedRef<rcShader>& shader) const override;
  virtual void DrawSubset(T_UINT8 submesh_index) const override;

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline void SetMesh(const SharedRef<const rcMesh>& mesh)
  {
    this->mesh_ = mesh;
  }
  inline void SetSubmeshVisible(T_UINT32 submesh_index, bool visible)
  {
    this->submesh_visible_[submesh_index] = visible;
  }
  inline bool GetSubmeshVisible(T_UINT32 submesh_index)
  {
    return this->submesh_visible_[submesh_index];
  }
  inline bool GetSubmeshVisible(T_UINT32 submesh_index) const
  {
    const auto& itr = this->submesh_visible_.find(submesh_index);
    if (itr != this->submesh_visible_.end())
    {
      return itr->second;
    }
    return true;
  }
  inline void ClearSubmeshVisible()
  {
    this->submesh_visible_.clear();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  SharedRef<const rcMesh> mesh_;
  std::unordered_map<T_UINT8, bool> submesh_visible_;

};