#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "DirectXActivity.h"

class DirectXDirector
{
public:
  static DirectXDirector& GetInstance()
  {
    static DirectXDirector self;
    return self;
  }

private:
  DirectXDirector() {}

public:
  inline HWND GetHWnd() const
  {
    return this->activity_->GetHWnd();
  }

  inline void SetActivity(DirectXActivity* activity)
  {
    this->activity_ = activity;
  }

private:
  DirectXActivity* activity_;
};