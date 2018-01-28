#pragma once

class GameComponent
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GameComponent();
  virtual ~GameComponent() {}

  // =================================================================
  // Events
  // =================================================================
public:
  virtual void PreUpdate() {}
  virtual void Update() {}
  virtual void PostUpdate() {}

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  void SetEnabled(bool enabled);

  inline bool IsEnabled() const
  {
    return this->enabled_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  bool enabled_;

};
