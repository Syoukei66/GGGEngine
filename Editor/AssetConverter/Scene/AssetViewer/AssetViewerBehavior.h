#pragma once

#include <Scene/ViewerScene.h>
#include <Entity/AssetEntity.h>
#include <Entity/AssetMetaData.h>

/*!
 * @brief アセットビューワーの動作を定義するクラス
 */
class AssetViewerBehavior : public IViewerBehavior
{
  // =================================================================
  // Methods from IViewerBehavior
  // =================================================================
public:
  virtual void Start(Scene* scene, AssetConverterContext* context) override;
  virtual void End() override;
  virtual void Update(AssetConverterContext* context) override;

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
  GG_INLINE void SetEntity(const SharedRef<AssetEntity>& entity)
  {
    this->entity_ = entity;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  SharedRef<AssetEntity> entity_;

};