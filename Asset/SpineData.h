#pragma once

#include <spine\spine.h>

//TODO:�A�Z�b�g�Ǘ��̕ύX�ɍ��킹�Ă����C������
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