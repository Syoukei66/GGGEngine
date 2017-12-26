#include "LoadProgressCounter.h"

// =================================================================
// Constructor / Destructor
// =================================================================
LoadingProgressCounter::LoadingProgressCounter()
  : task_sum_(0)
  , category_task_sum_()
  , progressed_task_sum_(0)
  , category_progressed_task_sum_()
{
}

// =================================================================
// Method
// =================================================================
void LoadingProgressCounter::OnLoadingInit()
{
  this->category_task_sum_.clear();
  this->task_sum_ = 0;
  this->category_progressed_task_sum_.clear();
  this->progressed_task_sum_ = 0;
}

void LoadingProgressCounter::OnLoadingReserved(const std::string& category, T_UINT8 weight)
{
  this->category_task_sum_[category] += weight;
  this->task_sum_ += weight;
}

void LoadingProgressCounter::OnLoadingProgressed(const std::string& category, T_UINT8 weight)
{
  this->category_progressed_task_sum_[category] += weight;
  this->progressed_task_sum_ += weight;
}

void LoadingProgressCounter::OnLoadingFinished()
{
}
