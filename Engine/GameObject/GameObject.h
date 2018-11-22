#pragma once

#include <Engine/GameObject/Transform/Transform.h>

class GameComponent;
class GameObjectRenderState;

class GameObject : public GGObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
public:
  GG_INIT_FUNC(GameObject);

  // =================================================================
  // Methods
  // =================================================================
public:
  void AddChild(const SharedRef<GameObject>& child);
  void RemoveSelf();
  void ClearChildren();

  // =================================================================
  // Components
  // =================================================================
public:
  template <class T>
  GG_INLINE SharedRef<T> AddComponent() 
  {
    GG_ASSERT(!this->HasComponent<T>(), "コンポーネントが二重に登録されました");
    const SharedRef<T>& component = T::Create(this);
    this->components_.emplace(T::ID & GameComponent::COMPONENT_MASK, component);
    return component;
  }

  template <class T>
  GG_INLINE SharedRef<T> GetComponent()
  {
    GG_ASSERT(this->HasComponent<T>(), "セットされていないComponentを取得しようとしました");
    const auto& pair = this->components_.find(T::ID & GameComponent::COMPONENT_MASK);
    GG_ASSERT(
      ((T::ID & GameComponent::INHERITANCE_MASK) == (pair->second->GetComponentID() & GameComponent::INHERITANCE_MASK)) ||
      ((T::ID & GameComponent::INHERITANCE_MASK) == (pair->second->GetComponentID() & GameComponent::COMPONENT_MASK)),
      "継承関係にないComponentのキャストを行おうとしました");
    return SharedRef<T>::StaticCast(pair->second);
  }

  template <class T>
  GG_INLINE bool HasComponent()
  {
    return this->components_.find(T::ID & GameComponent::COMPONENT_MASK) != this->components_.end();
  }

  template <class T>
  GG_INLINE void RemoveComponent()
  {
    this->components_.erase(T::ID & GameComponent::COMPONENT_MASK);
  }

  // =================================================================
  // Events
  // =================================================================
public:
  void Draw(GameObjectRenderState* state);

  void ManagedPreUpdate();
  void ManagedUpdate();
  void ManagedPostUpdate();

  void FireOnPositionChanged();
  void FireOnScaleChanged();
  void FireOnRotationChanged();

protected:
  virtual void PreUpdate() {}
  virtual void Update() {}
  virtual void PostUpdate() {}

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE bool HasParent() const
  {
    return this->parent_ != nullptr;
  }
  GG_INLINE SharedRef<GameObject> GetParent() const
  {
    return SharedRef<GameObject>(this->parent_);
  }

  GG_INLINE void SetEnabled(bool enabled)
  {
    this->enabled_ = enabled;
  }
  GG_INLINE bool IsEnabled() const
  {
    return this->enabled_;
  }

  GG_INLINE Transform* GetTransform()
  {
    return this->transform_;
  }
  GG_INLINE const Transform* GetTransform() const
  {
    return this->transform_;
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  Transform* transform_;

private:
	bool enabled_;
  
  /*!
   * @brief 親GameObject,RefでのSFINAEで
   * 未解決のGameObjectに対する判定が行われる事でエラーが起きるので、
   * 例外的に生ポインタを扱う。振る舞いとしてはWeakRefと同様となるように
   * （リファレンスカウンタの操作を行わない）
   */
  GameObject* parent_;

  std::vector<SharedRef<GameObject>> children_;
  std::unordered_map<T_UINT32, SharedRef<GameComponent>> components_;

};
