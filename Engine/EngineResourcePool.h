#pragma once
#include "ResourcePool.h"

//�G���W�������g�����\�[�X
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