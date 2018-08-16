#pragma once

#include <vector>
#include "../Core/NativeAssert.h"
#include "../Core/Shader.h"
#include "../Core/GraphicsConstants.h"

class Material
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Material(rcShader* shader, bool protect = false);
  virtual ~Material();

  // =================================================================
  // Methods
  // =================================================================
public:
  Material* Clone();
  Material* InitialClone();

protected:
  virtual Material* CreateClone(rcShader* shader);
  virtual void CopyPropertiesToClone(Material* clone);

public:
  T_UINT8 Begin();
  void BeginPass(T_UINT8 path_id);
  void CommitChanges();
  void EndPass();
  void End();

  virtual void SetProperties(rcShader* shader) {};

  // =================================================================
  // Getter / Setter
  // =================================================================
protected:
  inline void ProtectedAssertion() const
  {
    NATIVE_ASSERT(!this->protected_, "保護されたマテリアルを変更しようとしました");
  }

public:
  void SetShader(rcShader* shader);

  inline rcShader* GetShader()
  {
    return this->shader_;
  }

  inline void SetTechnique(const std::string& technique)
  {
    this->technique_ = technique;
  }
  inline const std::string& GetTechnique() const
  {
    return this->technique_;
  }

  inline void SetRenderQueue(Graphics::RenderQueue queue)
  {
    this->ProtectedAssertion();
    this->queue_ = queue;
  }
  inline Graphics::RenderQueue GetRenderQueue() const
  {
    return this->queue_;
  }

  inline void SetMainTexture(const rcTexture* texture)
  {
    this->ProtectedAssertion();
    this->texture_ = texture;
  }
  inline const rcTexture* GetMainTexture() const
  {
    return this->texture_;
  }

  inline void SetTiling(const TVec2f& tiling)
  {
    this->tiling_ = tiling;
  }
  inline const TVec2f& GetTiling() const
  {
    return this->tiling_;
  }

  inline void SetTilingOffset(const TVec2f& offset)
  {
    this->tiling_offset_ = offset;
  }
  inline const TVec2f& GetTilingOffset() const
  {
    return this->tiling_offset_;
  }

  inline void SetMainColor(const TColor& color)
  {
    this->ProtectedAssertion();
    this->color_ = color;
  }
  inline void SetMainColor(T_FLOAT r, T_FLOAT g, T_FLOAT b)
  {
    this->ProtectedAssertion();
    this->color_.r = r;
    this->color_.g = g;
    this->color_.b = b;
  }
  inline void SetMainColor(T_FLOAT r, T_FLOAT g, T_FLOAT b, T_FLOAT a)
  {
    this->ProtectedAssertion();
    this->color_.r = r;
    this->color_.g = g;
    this->color_.b = b;
    this->color_.a = a;
  }
  inline TColor& GetMainColor()
  {
    this->ProtectedAssertion();
    return this->color_;
  }
  inline const TColor& GetMainColor() const
  {
    return this->color_;
  }

  inline void SetBillboardingFlag(bool billboarding)
  {
    this->ProtectedAssertion();
    this->billbording_ = billboarding;
  }

  inline bool IsBillboard() const
  {
    return this->billbording_;
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  Graphics::RenderQueue queue_;
  const rcTexture* texture_;
  TVec2f tiling_;
  TVec2f tiling_offset_;
  TColor color_;
  bool billbording_;

private:
  const bool protected_;
  rcShader* shader_;
  std::string technique_;

  std::vector<Material*> clones_;
};