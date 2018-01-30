#pragma once

#include <spine/spine.h>
#include <string>

#include "GameObject2D.h"
#include "AttachmentVertexes.h"
#include "SpineData.h"

class SkeletonAnimation : public GameObject2D
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static SkeletonAnimation* CreateWithData(const SpineData* data);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  SkeletonAnimation(spSkeletonData* data);
  ~SkeletonAnimation();
  
  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void ManagedDraw(GameObjectRenderState* state) override;
  virtual void Update() override;

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
