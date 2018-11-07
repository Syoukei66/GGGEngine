#pragma once

class Scene;
class SceneTransitioner;
class UpdateEventState;

class SceneManager
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  SceneManager();
  ~SceneManager();

  // =================================================================
  // Methods
  // =================================================================
public:
  void ChangeScene(Scene* next);

  void Update(const UpdateEventState& state);
  void Draw();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE Scene* GetNowScene()
  {
    return this->scene_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  T_UINT32 second_elapsed_from_last_render_; //ƒ~ƒŠ•b‚È‚Ì‚Åint

  Scene* scene_;
  SceneTransitioner* scene_transitioner_;
};
