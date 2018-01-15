#pragma once

#include <deque>
#include "Camera2D.h"
#include "UpdateEvent.h"

class GameObject2D;

class Camera2D_MultiTarget : public Camera2D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Camera2D_MultiTarget(T_FLOAT x, T_FLOAT y, T_FLOAT width, T_FLOAT height, T_FLOAT z_min, T_FLOAT z_max);
  Camera2D_MultiTarget();
  ~Camera2D_MultiTarget();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void Update() override;

  virtual INativeMatrix* GetViewMatrix() const override;

  // =================================================================
  // Method
  // =================================================================
public:
  void SetViewEntity(GameObject2D* view_);

protected:
  void OnUpdateZoom();

  // =================================================================
  // setter/getter
  // =================================================================
public:
  inline void AddTargetEntity(GameObject2D* target)
  {
    this->target_entities_.push_back(target);
  }
  inline void RemoveTargetEntity(GameObject2D* target)
  {
    for (std::deque<GameObject2D*>::iterator itr = this->target_entities_.begin(); itr != this->target_entities_.end(); ++itr)
    {
      if (target == (*itr))
      {
        this->target_entities_.erase(itr);
        return;
      }
    }
  }
  inline void ClearTargetEntity()
  {
    this->target_entities_.clear();
  }
  inline void SetZoom(T_FLOAT zoom)
  {
    this->next_zoom_ = zoom;
  }
  inline void SetPadding(T_FLOAT padding)
  {
    this->padding_ = padding;
  }
  inline const TVec2f& GetPosition() const
  {
    return this->position_;
  }
  inline T_FLOAT GetZoom() const
  {
    return this->zoom_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  GameObject2D* view_;
  std::deque<GameObject2D*> target_entities_;
  INativeMatrix* translate_;
  INativeMatrix* scale_;
  INativeMatrix* view_matrix_;
  TVec2f position_;
  T_FLOAT zoom_;
  T_FLOAT next_zoom_;
  T_FLOAT padding_;
};