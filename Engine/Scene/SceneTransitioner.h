#pragma once

class Scene;

class ISceneShowListener
{
public:
  ISceneShowListener()
    : controled_(false)
  {}
  virtual ~ISceneShowListener() {}

public:
  virtual void OnShowFinish() = 0;

public:
  GG_INLINE void ControlShowFinish()
  {
    this->controled_ = true;
  }
  GG_INLINE bool IsShowFinishControlled()
  {
    return this->controled_;
  }

private:
  bool controled_;
};

class ISceneHideListener
{
public:
  ISceneHideListener()
    : controled_(false)
  {}
  virtual ~ISceneHideListener() {}

public:
  virtual void OnHideFinish() = 0;

public:
  GG_INLINE void ControlHideFinish()
  {
    this->controled_ = true;
  }
  GG_INLINE bool IsHideFinishControlled()
  {
    return this->controled_;
  }

private:
  bool controled_;
};

//TODO:ê›åvÇ™ãCéùÇøà´Ç¢ÇÃÇ≈å„Ç≈íºÇ∑
class SceneTransitioner : public ISceneShowListener, public ISceneHideListener
{
private:
  enum SceneTransitionState
  {
    SCENE_TRANSITION_NONE,
    SCENE_TRANSITION_ON_HIDE,
    SCENE_TRANSITION_HIDING,
    SCENE_TRANSITION_LOADING,
    SCENE_TRANSITION_ON_SHOW,
    SCENE_TRANSITION_SHOWING,
  };

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  SceneTransitioner();
  ~SceneTransitioner();

  // =================================================================
  // Methods
  // =================================================================
public:
  SharedRef<Scene> Transition();
 
  void OnShowFinish() override;
  void OnHideFinish() override;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  void SetNextScene(const SharedRef<Scene>& scene);

  bool IsDuringTransition()
  {
    return this->state_ != SCENE_TRANSITION_NONE;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  SharedRef<Scene> now_scene_;
  SharedRef<Scene> next_scene_;
  SceneTransitionState state_;
};