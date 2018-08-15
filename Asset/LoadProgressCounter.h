#pragma once

#include <string>
#include <unordered_map>
#include "../Core/NativeType.h"
#include "AssetManager.h"

class ILoadingProgressCounterCallback
{
public:
  virtual void OnLoadingReserved(IAssetContainer* asset) = 0;
  virtual void OnLoadingStarted() = 0;
  virtual void OnLoadingProgressed(IAssetContainer* asset) = 0;
  virtual void OnLoadingFinished() = 0;
};

class LoadingProgressCounter : public IAssetLoadingListener
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  LoadingProgressCounter();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void OnLoadingInit() override;
  virtual void OnLoadingStarted() override;
  virtual void OnLoadingReserved(IAssetContainer* asset) override;
  virtual void OnLoadingProgressed(IAssetContainer* asset) override;
  virtual void OnLoadingFinished() override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline T_FLOAT GetTaskProgressRate()
  {
    return (T_FLOAT)this->task_sum_ / this->progressed_task_sum_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  //ロード処理の合計
  T_UINT64 task_sum_;

  //進行済みロード処理の合計
  T_UINT64 progressed_task_sum_;
};
