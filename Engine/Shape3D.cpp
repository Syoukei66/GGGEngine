#include "Shape3D.h"
#include "NativeMethod.h"
#include "IVertexBufferObject.h"
#include "GameObject3DRenderState.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Shape3D::Shape3D(IVertexBufferObject* vbo)
  : Primitive3D(vbo)
  , texture_(nullptr)
  , lighting_enabled_(true)
{
  this->material_ = new Material();
}

Shape3D::~Shape3D()
{
  delete this->material_;
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void Shape3D::NativeDraw(GameObject3DRenderState* state)
{
  const void* vertexes = this->vbo_->GetVertexes();
  T_UINT32 size = this->vbo_->GetVertexesCount();
  NativeMethod::Graphics().Graphics_SetTexture(this->texture_);
  this->material_->Apply();
  NativeMethod::Graphics().Graphics_SetMaterial(this->material_);
  NativeMethod::Graphics().Graphics_SetLightingEnabled(this->lighting_enabled_);
  NativeMethod::Graphics().Graphics_DrawIndexedVertexes(
    state,
    this->vbo_->GetPrimitiveType(),
    this->vbo_->GetVertexType(),
    vertexes,
    size,
    this->vbo_->GetIndexes()
  );
}
