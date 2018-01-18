#include "GameObject3DRenderState.h"
#include <algorithm>

#include "NativeMethod.h"
#include "GameObject3D.h"
#include "Camera3D.h"

GameObject3DRenderState::GameObject3DRenderState(Camera3D* camera)
  : camera_(camera)
  , post_draw_list_()
{
  this->mat_ = INativeMatrix::Create();
}

GameObject3DRenderState::~GameObject3DRenderState()
{
  delete this->mat_;
}

void GameObject3DRenderState::Init()
{
  GameObjectRenderState::Init();
}

void GameObject3DRenderState::AddZCheckOrder(GameObject3D* object)
{
  this->mat_->Assign(*object->GetTransform()->GetWorldMatrix());
  this->mat_->Multiple(*this->camera_->GetViewMatrix());
  this->mat_->Multiple(*this->camera_->GetProjectionMatrix());

  TVec4f pos = TVec4f(0.0f, 0.0f, 0.0f, 1.0f);
  this->mat_->Apply(&pos);

  PostDrawParam param = PostDrawParam();
  param.object = object;
  param.distance = pos.z / pos.w;
  this->post_draw_list_.push_back(param);
}

void GameObject3DRenderState::DrawZOrderedGameObject()
{
  this->camera_->GetDirection();
  std::sort(this->post_draw_list_.begin(), this->post_draw_list_.end(), [](const PostDrawParam& a, const PostDrawParam& b) {
    return a.distance > b.distance;
  });
  for (PostDrawParam param : this->post_draw_list_)
  {
    if (param.object->IsBillboard())
    {
      GameObject3D* p = param.object;
      this->mat_->Init();
      while (!p->IsBillboardingRoot())
      {
        this->mat_->MultipleReverse(*p->GetTransform()->GetMatrix());
        p = p->GetParent();
      }
      Material* const material = param.object->GetMaterial();
      if (material)
      {
        this->PushMatrix(p->GetTransform()->GetWorldMatrix());
        this->PushMatrix(this->camera_->GetBillboardingMatrix());
        this->PushMatrix(this->mat_);
        material->Begin();
        param.object->NativeDraw(this);
        material->End();
        this->PopMatrix();
        this->PopMatrix();
        this->PopMatrix();
      }
    }
    else
    {
      this->PushMatrix(param.object->GetTransform()->GetWorldMatrix());
      param.object->NativeDraw(this);
      this->PopMatrix();
    }
  }
  this->post_draw_list_.clear();
}
