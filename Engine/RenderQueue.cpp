#include "RenderQueue.h"
#include <ppl.h>

/*
CommitChange,DrawPramをそれぞれ引数としたテンプレートを作成
Rendererはフレーム毎にEntityにどのような更新が行われたのかを記録しておく
アップデートスレッドの最後でQueueを回し、
Rendererの変化を受け取り、DrawParamに記録しておく
ここはDrawParam側のメソッドとして定義してもいいかも
あとDrawParamという名前なんか嫌なので
いい名前を考えておく

<typename DrawParam, typename Func = DrawParam>

*/

RenderQueue::RenderQueue()
{
}

RenderQueue::~RenderQueue()
{
}

void RenderQueue::Add(Renderer* renderer)
{
  const T_UINT8 material_count = renderer->GetMaterialCount();
  for (T_UINT8 i = 0; i < material_count; ++i)
  {
    Material* mat = renderer->GetMaterial(i);
    INativeVertexBuffer* vertex_buffer = rendere
    this->commands_.emplace_back();
  }
}

void RenderQueue::Remove(Renderer* renderer)
{
}

void RenderQueue::Clear()
{
}

//
//inline void RenderQueue::Update()
//{
//  for (Params& target : this->params_)
//  {
//    target.Update();
//  }
//}
//
//inline void RenderQueue::CommitChanges()
//{
//  StatesUpdate::Update();
//  const TVec3f& view_position = this->render_state_->GetViewMatrix().GetPosition3d();
//  const TVec3f& view_direction = this->render_state_->GetViewMatrix().GetDirection3d();
//  for (Params& target : this->params_)
//  {
//    TVec3f distance = target.renderer->GetGameObject()->GetWorldMatrix().GetPosition3d();
//    distance -= view_position;
//    target.distance = TVec3f::InnerProduct(distance, view_direction);
//  }
//  //不透明キュー
//  concurrency::parallel_sort(this->params_.begin(), this->params_.end(), [](const DrawParam& a, const DrawParam& b)
//  {
//    return a.distance < b.distance;
//  });
//  //透明キュー
//  concurrency::parallel_sort(this->params_.begin(), this->params_.end(), [](const DrawParam& a, const DrawParam& b)
//  {
//    return a.distance > b.distance;
//  });
//}
//
//inline void RenderQueue::Draw()
//{
//  for (const Params& target : this->params_)
//  {
//    target.renderer->ManagedDraw(this->render_state_);
//  }
//}
