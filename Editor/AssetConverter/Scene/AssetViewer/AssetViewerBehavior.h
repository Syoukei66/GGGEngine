#pragma once

#include <Scene/ViewerScene.h>
#include <Entity/AssetEntity.h>
#include <Entity/AssetMetaData.h>

/*!
 * @brief �A�Z�b�g�r���[���[�̓�����`����N���X
 */
class AssetViewerBehavior : public IViewerBehavior
{
  // =================================================================
  // Methods from IViewerBehavior
  // =================================================================
public:
  virtual void Start(Scene* scene, AssetConverterContext* context) override;
  virtual void End() override;
  virtual bool Update(const ActivityContext& activity_context, AssetConverterContext* context) override;

  // =================================================================
  // Methods
  // =================================================================
public:
  virtual void OnStart(Scene* scene) = 0;
  virtual void OnEnd() = 0;
  virtual void OnLoad(T_UINT32 unique_id) = 0;
  virtual void OnUnload() = 0;
  virtual void OnUpdate(const ActivityContext& activity_context, AssetConverterContext* context) {};

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE void SetEntity(const SharedRef<AssetEntity>& entity)
  {
    this->entity_ = entity;
  }
  GG_INLINE SharedRef<AssetEntity> GetEntity() const override
  {
    return this->entity_;
  }

  /*!
   * @brief �G�f�B�^���g�p���Ă���AssetEntity��ǉ�����
   */
  GG_INLINE void AddEditorUseEntity(const SharedRef<AssetEntity>& entity)
  {
    this->use_entities_.insert(entity);
  }
  /*!
   * @brief �G�f�B�^���g�p���Ă���AssetEntity��ǉ�����
   */
  GG_INLINE void RemoveEditorUseEntity(const SharedRef<AssetEntity>& entity)
  {
    this->use_entities_.erase(entity);
  }
  /*!
   * @brief �G�f�B�K�g�p���Ă���AssetEntity�̓o�^��S�ĉ�������
   */
  GG_INLINE void RemoveEditorUseEntity()
  {
    this->use_entities_.clear();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  SharedRef<AssetEntity> entity_;
  std::set<SharedRef<AssetEntity>> use_entities_;

};