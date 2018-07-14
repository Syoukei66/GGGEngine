#include "Camera2D.h"

// =================================================================
// Constructor / Destructor
// =================================================================
Camera2D::Camera2D(GameObject* entity)
  : Camera(entity)
{}

Camera2D::~Camera2D()
{}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
const Matrix4x4& Camera2D::GetViewMatrix() const
{
  return Matrix4x4::identity;
}

const Matrix4x4& Camera2D::GetProjectionMatrix() const
{
  //TODO:毎フレーム計算させるのは効率が悪い。
  //RenderState側に特化されたマトリックスを用意し、
  //そちら側でインターフェースやキャッシュを作成する方がいいかも
  const Viewport& viewport = this->GetRenderState()->GetViewport();
  return Matrix4x4::Ortho(
    viewport.size.width,
    viewport.size.height,
    0.0f,
    1000.0f
  );
}

