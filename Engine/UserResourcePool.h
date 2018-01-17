#pragma once
#include "ResourcePool.h"

//ユーザー側が使うリソース
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