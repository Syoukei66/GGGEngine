#pragma once

#include "../Asset/StaticModelData.h"
#include "BaseConverterTest.h"

class StaticModelConverterTest : public BaseConverterTest
{
public:
  using BaseConverterTest::Compare;
  void Compare(const StaticModelData& a, const StaticModelData& b);

private:
  void Compare(const StaticModelTextureData& a, const StaticModelTextureData& b);
  void Compare(const StaticModelMaterialData& a, const StaticModelMaterialData& b);
};