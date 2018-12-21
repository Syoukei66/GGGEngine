#pragma once

#include <Core/Application/Platform/API/_Resource/APIResourceObject.h>

/*!
 * @brief テクスチャのリソースデータ
 */
struct TextureResourceData
{

};

class rcTextureResource : public GGAPIResourceObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT(rcTextureResource);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  //static UniqueRef<rcRenderState> Create(const RenderStateData& data);

  // =================================================================
  // Method 
  // =================================================================
public:
  virtual void SetResource(T_UINT32 index) const = 0;

};