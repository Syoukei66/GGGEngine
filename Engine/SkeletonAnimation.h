#pragma once

#include <spine/spine.h>
#include <string>

#include "GameObject2D.h"
#include "AttachmentVertexes.h"

class SkeletonAnimation : public GameObject2D
{

public:
  static SkeletonAnimation* CreateFromAsset(T_UINT8 spine_id);

public:
  SkeletonAnimation(spSkeletonData* data);
  ~SkeletonAnimation();
  
  virtual void PreDraw(GameObject2DRenderState* state) override;
  virtual void NativeDraw(GameObject2DRenderState* state) override;

  //=============================================================================
  // Animation
  //=============================================================================
  spTrackEntry* setAnimation(int trackIndex, const std::string& name, bool loop);
  spTrackEntry* getCurrent(int trackIndex = 0);

public:
  inline AttachmentVertexes* GetAttachmentVertexes(spRegionAttachment* attachment) const
  {
    return (AttachmentVertexes*)attachment->rendererObject;
  }

private:
  spSkeletonData* data_;
  spSkeleton* skeleton_;
  spAtlas* atlas_;
  spAnimationState* state_;

  spAttachmentLoader* attachment_loader_;
  float time_scale_;
};
