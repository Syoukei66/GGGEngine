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

//エンジン側が使うリソース
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