#pragma once

class GameComponent
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  GameComponent();

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
    return this->is_enabled_;
  }

private:
  bool is_enabled_;

};
