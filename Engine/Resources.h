#pragma once

#include "ResourcePool.h"

//���[�U�[�����g�����\�[�X
class UserResourcePool : public ResourcePool
{
public:
  static UserResourcePool& GetInstance()
  {
    UserResourcePool self = UserResourcePool();
    return self;
  }

private:
  UserResourcePool() {}

public:
  ~UserResourcePool() {}

};

//�G���W�������g�����\�[�X
class EngineResourcePool : public ResourcePool
{
public:
  static EngineResourcePool& GetInstance()
  {
    EngineResourcePool self = EngineResourcePool();
    return self;
  }

private:
  EngineResourcePool() {}

public:
  ~EngineResourcePool() {}

};