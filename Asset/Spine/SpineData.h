#pragma once

struct spSkeletonData;
struct spAtlas;

class rcSpineData : public GGAssetObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT_NAME(rcSpineData);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcSpineData> CreateFromFile(const char* path);
  static UniqueRef<rcSpineData> Create(spSkeletonData* skeleton_data, spAtlas* atlas);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcSpineData(spSkeletonData* skeleton_data, spAtlas* atlas);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE const spSkeletonData* GetSkeletonData() const
  {
    return this->skeleton_data_;
  }
  GG_INLINE const spAtlas* GetAtlas() const
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