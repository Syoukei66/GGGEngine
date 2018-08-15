#include "LoadProgressCounter.h"

// =================================================================
// Constructor / Destructor
// =================================================================
LoadingProgressCounter::LoadingProgressCounter()
  : task_sum_(0)
  , progressed_task_sum_(0)
{
}

// =================================================================
// Method
// =================================================================
void LoadingProgressCounter::OnLoadingInit()
{
  this->task_sum_ = 0;
  this->progressed_task_sum_ = 0;
}

void LoadingProgressCounter::OnLoadingStarted()
{
}

void LoadingProgressCounter::OnLoadingReserved(IAssetContainer* asset)
{
  this->task_sum_ += asset->GetSize();
}

void LoadingProgressCounter::OnLoadingProgressed(IAssetContainer* asset)
{
  this->progressed_task_sum_ += asset->GetSize();
}

void LoadingProgressCounter::OnLoadingFinished()
{
}
