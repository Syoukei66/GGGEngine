//#pragma once
//
//#include <spine/spine.h>
//#include <string>
//#include <Asset/Spine/AttachmentVertexes.h>
//#include <Asset/Spine/SpineData.h>
//
//#include <Engine/GameObject/GameObject2D.h>
//
//class SkeletonAnimation : public GameObject2D
//{
//  // =================================================================
//  // Factory Method
//  // =================================================================
//public:
//  static SkeletonAnimation* CreateWithData(const rcSpineData* data);
//
//  // =================================================================
//  // Constructor / Destructor
//  // =================================================================
//public:
//  SkeletonAnimation(const spSkeletonData* data);
//  ~SkeletonAnimation();
//  
//  // =================================================================
//  // Methods for/from SuperClass/Interfaces
//  // =================================================================
//public:
//  virtual void ManagedDraw(GameObjectRenderState* state) override;
//  virtual void Update() override;
//
//  //=============================================================================
//  // Animation
//  //=============================================================================
//  spTrackEntry* setAnimation(int trackIndex, const std::string& name, bool loop);
//  spTrackEntry* getCurrent(int trackIndex = 0);
//
//public:
//  GG_INLINE AttachmentVertexes* GetAttachmentVertexes(spRegionAttachment* attachment) const
//  {
//    return (AttachmentVertexes*)attachment->rendererObject;
//  }
//
//private:
//  const spSkeletonData* data_;
//  spSkeleton* skeleton_;
//  spAtlas* atlas_;
//  spAnimationState* state_;
//
//  spAttachmentLoader* attachment_loader_;
//  float time_scale_;
//};
