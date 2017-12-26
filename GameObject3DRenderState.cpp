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
  this->mat_->Assign(this->GetMatrixStack()->GetTop());
  this->mat_->Multiple(*this->camera_->GetViewMatrix());
  this->mat_->Multiple(*this->camera_->GetProjectionMatrix());

  TVec4f pos = TVec4f(0.0f, 0.0f, 0.0f, 1.0f);
  this->mat_->Apply(&pos);

  PostDrawParam* param = new PostDrawParam();
  param->object = object;
  param->distance = pos.z / pos.w;
  this->post_draw_list_.push_back(param);
}

void GameObject3DRenderState::DrawZOrderedGameObject()
{
  this->camera_->GetDirection();
  std::sort(this->post_draw_list_.begin(), this->post_draw_list_.end(), [](PostDrawParam* a, PostDrawParam* b) {
    return a->distance > b->distance;
  });
  for (std::vector<PostDrawParam*>::iterator itr = this->post_draw_list_.begin(); itr != this->post_draw_list_.end();)
  {
    this->PushMatrix((*itr)->object->GetTransform()->GetWorldMatrix());
    (*itr)->object->ApplyBlendMode(this);
    (*itr)->object->NativeDraw(this);
    this->PopMatrix();
    delete (*itr);
    itr = this->post_draw_list_.erase(itr);
  }
}