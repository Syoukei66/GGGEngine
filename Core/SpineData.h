#pragma once

#include "spine\spine.h"
#include "Resource.h"

class rcSpineData : public Resource
{
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueResource<rcSpineData> CreateFromFile(const char* path);
  static UniqueResource<rcSpineData> Create(spSkeletonData* skeleton_data, spAtlas* atlas);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcSpineData(spSkeletonData* skeleton_data, spAtlas* atlas);

  // =================================================================
  // Getter / Setter
  // =================================================================
public:
  inline virtual const char* GetResourceName() override
  {
    return "SpineData";
  }

  inline const spSkeletonData* GetSkeletonData() const
  {
    return this->skeleton_data_;
  }
  inline const spAtlas* GetAtlas() const
  {
    return this->atlas_;
  }

  // =================================================================
  // Data Members
  // =================================================================
protected:
  spSkeletonData* skeleton_data_;
  spAtlas* atlas_;

};