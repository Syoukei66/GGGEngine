#pragma once

#include <spine\spine.h>

//TODO:アセット管理の変更に合わせていつか修正する
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