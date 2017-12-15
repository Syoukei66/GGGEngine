#pragma once

#include <string>
#include <map>
#include "NativeType.h"
#include "ResourcePool.h"

class ILoadingProgressCounterCallback
{
public:
  virtual void OnLoadingReserved(const std::string& category, T_UINT8 weight);
  virtual void OnLoadingStarted();
  virtual void OnLoadingProgressed(const std::string& category, T_UINT8 weight);
  virtual void OnLoadingFinished();
};

class LoadingProgressCounter : public IResourceLoadingListener
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
  virtual void OnLoadingReserved(const std::string& category, T_UINT8 weight) override;
  virtual void OnLoadingProgressed(const std::string& category, T_UINT8 weight) override;
  virtual void OnLoadingFinished() override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline T_FLOAT GetTaskProgressRateForCategory(const std::string& category)
  {
    return this->category_task_sum_[category] / this->category_progressed_task_sum_[category];
  }
  inline T_FLOAT GetTaskProgressRate()
  {
    return this->task_sum_ / this->progressed_task_sum_;
  }
  inline std::map<std::string, T_UINT32>::iterator TaskIteratorBegin()
  {
    return this->category_task_sum_.begin();
  }
  inline std::map<std::string, T_UINT32>::iterator TaskIteratorEnd()
  {
    return this->category_task_sum_.end();
  }
  inline std::map<std::string, T_UINT32>::iterator ProgressedTaskIteratorBegin()
  {
    return this->category_progressed_task_sum_.begin();
  }
  inline std::map<std::string, T_UINT32>::iterator ProgressedTaskIteratorEnd()
  {
    return this->category_progressed_task_sum_.end();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  //ロード処理の合計
  T_UINT32 task_sum_;
  std::map<std::string, T_UINT32> category_task_sum_;

  //進行済みロード処理の合計
  T_UINT32 progressed_task_sum_;
  std::map<std::string, T_UINT32> category_progressed_task_sum_;
};
