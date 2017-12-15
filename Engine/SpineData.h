#pragma once

#include <spine\spine.h>

class SpineData
{
public:
  static SpineData* CreateFromFile(const char* path);

private:
  SpineData();

public:
  spSkeletonData* skeleton_data;
  spAtlas* atlas;
};