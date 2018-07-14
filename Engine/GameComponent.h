#pragma once

class GameObject;

class GameComponent
{
protected:
  enum Type
  {
    RENDERER,
    CAMERA,
  };

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  void Release();

protected:
  GameComponent(GameObject* entity);
  virtual ~GameComponent();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline GameObject* GetGameObject()
  {
    return this->entity_;
  }

  inline const GameObject* GetGameObject() const 
  {
    return this->entity_;
  }

  inline void SetEnabled(bool enabled)
  {
    if (this->enabled_ == enabled)
    {
      return;
    }
    this->enabled_ = enabled;
  }
  inline bool IsEnabled() const
  {
    return this->enabled_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  GameObject* entity_;
  bool enabled_;

};
