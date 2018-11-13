#pragma once

#include <Scene/ViewerScene.h>
#include <Entity/AssetEntity.h>
#include <Entity/AssetInfo.h>

/*!
 * @brief アセットビューワーの動作を定義するクラス
 */
class AssetViewerBehavior : public IViewerBehavior
{
  // =================================================================
  // Methods from IViewerBehavior
  // =================================================================
public:
  virtual void Start(Scene* scene) override
  {
    this->OnStart(scene);
    this->OnLoad(this->entity_->GetAssetInfo()->GetUniqueID());
  }
  virtual void End() override
  {
    this->OnUnload();
    this->OnEnd();
  }
  virtual void Update() override
  {
    this->OnUpdate();
  }

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual void OnStart(Scene* scene) = 0;
  virtual void OnEnd() = 0;
  virtual void OnLoad(T_UINT32 unique_id) = 0;
  virtual void OnUnload() = 0;
  virtual void OnUpdate() {};

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE void SetEntity(AssetEntity* entity)
  {
    this->entity_ = entity;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  AssetEntity* entity_;

};