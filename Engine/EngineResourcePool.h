#pragma once
#include "ResourcePool.h"

//エンジン側が使うリソース
class EngineResourcePool : public ResourcePool
{
public:
  static EngineResourcePool& GetInstance()
  {
    static EngineResourcePool self = EngineResourcePool();
    return self;
  }

private:
  EngineResourcePool() {}

public:
  ~EngineResourcePool() {}

};