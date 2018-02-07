#pragma once
#include "ResourcePool.h"

//���[�U�[�����g�����\�[�X
class UserResourcePool : public ResourcePool
{
public:
  static UserResourcePool& GetInstance()
  {
    static UserResourcePool self = UserResourcePool();
    return self;
  }

private:
  UserResourcePool() {}

public:
  ~UserResourcePool() {}

};