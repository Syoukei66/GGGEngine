#include "SkeletonAnimation.h"

#include <spine/extension.h>

#include "NativeMethod.h"
#include "Director.h"

// =================================================================
// Factory Method
// =================================================================
SkeletonAnimation* SkeletonAnimation::CreateWithData(const SpineData* data)
{
  return new SkeletonAnimation(data->skeleton_data);
}

// =================================================================
// Constructor / Destructor
// =================================================================
SkeletonAnimation::SkeletonAnimation(spSkeletonData* data)
  : data_(data)
{
  this->time_scale_ = 1.0f;
  this->skeleton_ = spSkeleton_create(data);

  this->state_ = spAnimationState_create(spAnimationStateData_create(this->skeleton_->data));
  this->state_->rendererObject = this;
  
}

SkeletonAnimation::~SkeletonAnimation()
{
  spSkeleton_dispose(this->skeleton_);
  if (this->atlas_)
  {
    spAtlas_dispose(this->atlas_);
  }
  if (this->attachment_loader_)
  {
    spAttachmentLoader_dispose(this->attachment_loader_);
  }
  spAnimationState_dispose(this->state_);
}

// =================================================================
// Methods for/from SuperClass/Interfaces
// =================================================================
void SkeletonAnimation::ManagedDraw(GameObjectRenderState* state)
{
  Color4F nodeColor = this->GetRenderer()->GetMaterial()->GetDiffuse();

  AttachmentVertexes* attachment_vertexes = nullptr;
  Color4F color = Color4F();
  for (int i = 0, n = skeleton_->slotsCount; i < n; ++i)
  {
    spSlot* slot = skeleton_->drawOrder[i];

    if (slot->attachment->type != SP_ATTACHMENT_REGION)
    {
      //RegionAttachmentˆÈŠO‚Í–¢‘Î‰ž
      continue;
    }
    spRegionAttachment* attachment = (spRegionAttachment*)slot->attachment;

    color.SetRed(attachment->color.r);
    color.SetGreen(attachment->color.g);
    color.SetBlue(attachment->color.b);
    color.SetAlpha(attachment->color.a);
    color.SetAlpha(
      color.GetAlpha() *
      nodeColor.GetAlpha() *
      this->skeleton_->color.a *
      slot->color.a
    );
    // skip rendering if the color of this attachment is 0
    if (color.GetAlpha() == 0.0f) {
      continue;
    }

    //switch (slot->data->blendMode) {
    //case SP_BLEND_MODE_ADDITIVE:
    //  this->GetMaterial()->SetBlendFunction(BlendFunction::BLEND_ADD_SRC, BlendFunction::BLEND_ADD_DST);
    //  break;
    //case SP_BLEND_MODE_MULTIPLY:
    //  this->GetMaterial()->SetBlendFunction(BlendFunction::BLEND_MUL_SRC, BlendFunction::BLEND_MUL_DST);
    //  break;
    //case SP_BLEND_MODE_SCREEN:
    //  this->GetMaterial()->SetBlendFunction(BlendFunction::BLEND_SCREEN_SRC, BlendFunction::BLEND_SCREEN_DST);
    //  break;
    //default:
    //  this->GetMaterial()->SetBlendFunction(BlendFunction::BLEND_DEFAULT_SRC, BlendFunction::BLEND_DEFAULT_DST);
    //}

    attachment_vertexes = this->GetAttachmentVertexes(attachment);
    Vertex::VCT* vertexes = new Vertex::VCT[attachment_vertexes->size_]();
    for (int j = 0; j < attachment_vertexes->size_; ++j)
    {
      vertexes[j] = attachment_vertexes->vertexes_[j];
    }

    spRegionAttachment_computeWorldVertices(attachment, slot->bone, (float*)vertexes, 0, sizeof(Vertex::VCT) / sizeof(float));

    for (int j = 0; j < attachment_vertexes->size_; ++j)
    {
      NativeMethod::Graphics().Graphics_PackColor4u8(&vertexes[j].color, color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
    }

    //this->ApplyBlendMode(state);
    //NativeMethod::Graphics().Graphics_SetTexture(attachment_vertexes->texture_);
    NativeMethod::Graphics().Graphics_DrawSprite(state, INativeProcess_Graphics::PRIMITIVE_TRIANGLESTRIP, vertexes, attachment_vertexes->size_);

    delete[] vertexes;
  }
}

void SkeletonAnimation::Update()
{
  const T_FLOAT delta_time = 0.001f * Director::GetInstance()->GetEngineOption()->render_cycle * this->time_scale_;
  spSkeleton_update(this->skeleton_, delta_time);
  spAnimationState_update(this->state_, delta_time);
  spAnimationState_apply(this->state_, this->skeleton_);
  spSkeleton_updateWorldTransform(this->skeleton_);
}

//=============================================================================
// Animation
//=============================================================================
spTrackEntry* SkeletonAnimation::setAnimation(int trackIndex, const std::string& name, bool loop)
{
  spAnimation* animation = spSkeletonData_findAnimation(this->skeleton_->data, name.c_str());
  if (!animation) {
    return nullptr;
  }
  return spAnimationState_setAnimation(this->state_, trackIndex, animation, loop);
}

spTrackEntry* SkeletonAnimation::getCurrent(int trackIndex)
{
  return spAnimationState_getCurrent(this->state_, trackIndex);
}
