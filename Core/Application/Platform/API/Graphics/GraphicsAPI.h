#pragma once

#include <Core/Application/Platform/API/APIObject.h>
#include <Core/Application/Platform/API/Graphics/TextureModule.h>

class Activity;
class rcIndexBuffer;

/*!
 * @brief 描画APIのベースクラス
 */
class GraphicsAPI : public GGAPIObject
{
  // =================================================================
  // Methods from GGAPIObject
  // =================================================================
public:
  virtual void SetupModules() override;

  // =================================================================
  // Methods
  // =================================================================
public:
  bool Draw(const SharedRef<Activity>& activity, const std::function<void()>& draw_method);
  
public:
  virtual void ViewportClear(const ActivityContext& context, const TColor& color) = 0;
  virtual void SetViewport(T_FLOAT x, T_FLOAT y, T_FLOAT w, T_FLOAT h, T_FLOAT minZ, T_FLOAT maxZ) = 0;
  virtual void PackColor4u8(T_FIXED_UINT32* color, T_UINT8 r, T_UINT8 g, T_UINT8 b, T_UINT8 a) = 0;
  virtual void UnpackColor4u8(T_FIXED_UINT32 color, T_UINT8* r, T_UINT8* g, T_UINT8* b, T_UINT8* a) = 0;
  virtual void SetRenderTarget(const SharedRef<Activity>& activity) = 0;
  //virtual void SetRenderTarget(const SharedRef<rcRenderBuffer>& color_buffer, const SharedRef<rcRenderBuffer>& depth_stencil_buffer, bool clear) = 0;
  virtual void ResetRenderTarget() = 0;

  virtual void DrawIndexedPrimitive(Vertex::PrimitiveType primitive_type, const SharedRef<const rcIndexBuffer>& index_buffer) = 0;
  
  virtual bool ImGuiNewFrame() = 0;

  virtual void CreateSubActivityResources(const SharedRef<Activity>& activity) = 0;

protected:
  virtual bool PreDraw(const SharedRef<Activity>& activity) = 0;
  virtual bool PostDraw(const SharedRef<Activity>& activity) = 0;

  virtual SharedRef<TextureModule> CreateTextureModule() const = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE SharedRef<TextureModule> GetTextureModule()
  {
    return this->texture_module_;
  }
  GG_INLINE const SharedRef<TextureModule> GetTextureModule() const
  {
    return this->texture_module_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
	SharedRef<TextureModule> texture_module_;

};
