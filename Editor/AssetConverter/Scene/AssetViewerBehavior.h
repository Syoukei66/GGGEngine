#pragma once

#include "ViewerScene.h"

/*!
 * @brief アセットビューワーの動作を定義するクラス
 */
template <typename Data_>
class AssetViewerBehavior : public IViewerBehavior
{
  // =================================================================
  // Methods from IViewerBehavior
  // =================================================================
public:
  virtual void Start(Scene* scene) override
  {
    this->OnStart(this->target_, scene);
  }
  virtual void End() override
  {
    this->OnEnd();
  }

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual void OnStart(const Data_* data, Scene* scene) = 0;
  virtual void OnEnd() = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE void SetTarget(Data_* data)
  {
    this->target_ = data;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  Data_* target_;

};