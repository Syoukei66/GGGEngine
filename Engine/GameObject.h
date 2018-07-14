#pragma once

#include <unordered_map>

#include "Transform.h"
#include "Scene.h"

class GameComponent;

class GameObject
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GameObject();
  virtual ~GameObject();

  // =================================================================
  // Method
  // =================================================================
public:
  void AddChild(GameObject* child);
  void RemoveChild(GameObject* child);
  void RemoveSelf();
  void ClearChildren();

  template <class T>
  T* AddComponent()
  {
    T* component = T::Create(this);
    this->components_.emplace(T::ID, component);
    return component;
  }

  template <class T>
  inline T* GetComponent()
  {
    NATIVE_ASSERT(this->GetComponentCount() > 0, "存在しないComponentを取得しようとしました");
    return this->components_.find(T::ID)->second;
  }

  template <class T>
  inline T* SafeGetComponent()
  {
    auto itr = this->components_.find(T::ID);
    return itr != this->components_.end() ? itr->second : nullptr;
  }

  template <class T>
  inline T_UINT32 GetComponentCount()
  {
    return (T_UINT32)this->components_.count(T::ID);
  }

  template <class T>
  inline auto GetComponents()
  {
    return this->components_.equal_range(T::ID);
  }
  
  template <class T>
  inline void RemoveComponent(T* component)
  {
    auto range = this->components_.equal_range(T::ID);
    for (auto itr = range.first; itr != range.second; ++itr)
    {
      if (itr->second == component)
      { 
        m.erase(itr);
        return;
      }
    }
  }

  template <class T>
  inline void RemoveComponents()
  {
    this->components_.erase(T::ID);
  }

  // =================================================================
  // Events
  // =================================================================
public:
  //TODO:アップデート処理はタスクスレッドにタスクを渡す事で実現するように変更する
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
  // delegate to Transform
  // =================================================================
public:
  inline const Matrix4x4& GetMatrix() const
  {
    return this->transform_->GetMatrix();
  }

  inline const Matrix4x4& GetTranslateMatrix() const
  {
    return this->transform_->GetTranslateMatrix();
  }

  inline const Matrix4x4& GetRotationMatrix() const
  {
    return this->transform_->GetRotationMatrix();
  }

  inline const Matrix4x4& GetScaleMatrix() const
  {
    return this->transform_->GetScaleMatrix();
  }

  inline const Matrix4x4& GetWorldMatrix() const
  {
    return this->transform_->GetWorldMatrix();
  }

  // =================================================================
  // Setter / Getter
  // =================================================================
  inline Scene* GetScene()
  {
    return this->scene_;
  }
  inline const Scene* GetScene() const
  {
    return this->scene_;
  }
  inline bool HasParent() const
  {
    return this->parent_;
  }
  inline GameObject* GetParent() const
  {
    return this->parent_;
  }

  // =================================================================
  // Data Member
  // =================================================================
protected:
  Transform* transform_;

private:
  Scene* scene_;
  
  GameObject* parent_;
  std::vector<GameObject*> children_;

  std::unordered_multimap<T_UINT32, GameComponent*> components_;

};
