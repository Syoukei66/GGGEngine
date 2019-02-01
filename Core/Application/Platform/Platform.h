#pragma once

#include <Core/Application/Activity/ActivityContext.h>
#include <Core/Application/Platform/API/Graphics/GraphicsAPI.h>
#include <Core/Application/Platform/API/Audio/AudioAPI.h>
#include <Core/Application/Platform/API/Input/InputAPI.h>
#include <Core/Application/IApplicationBehavior.h>

class Platform : public GGObject
{
  friend class Application;

  // =================================================================
  // Methods
  // =================================================================
protected:
  /*!
   * @brief プラットフォームの初期化処理
   * @returns falseなら失敗
   */
  bool Init(const ApplicationOption& option);

  /*!
   * @brief プラットフォームの終了処理
   * @returns falseなら失敗
   */
  bool Uninit();

  /*!
   * @brief プラットフォームのアップデートが続くかどうかの判定
   * @return falseなら終了
   */
  virtual bool ContinueEnabled() = 0;

  /*!
   * @brief フレーム処理が有効かどうかの判定
   * @return falseならアップデート処理を行わず待機する
   */
  virtual bool FrameEnabled() = 0;

  virtual UniqueRef<GraphicsAPI> CreateGraphicsAPI(const ApplicationOption& op) const = 0;
  virtual UniqueRef<AudioAPI> CreateAudioAPI(const ApplicationOption& op) const = 0;
  virtual UniqueRef<InputAPI> CreateInputAPI(const ApplicationOption& op) const = 0;
  virtual UniqueRef<ActivityContext> CreateMainActivityContext() const = 0;
  virtual UniqueRef<ActivityContext> CreateActivityContext() const = 0;

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE SharedRef<GraphicsAPI> GetGraphicsAPI()
  {
    return this->graphics_api_;
  }

  GG_INLINE SharedRef<AudioAPI> GetAudioAPI()
  {
    return this->audio_api_;
  }

  GG_INLINE SharedRef<InputAPI> GetInputAPI()
  {
    return this->input_api_;
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  SharedRef<GraphicsAPI> graphics_api_;
  SharedRef<AudioAPI> audio_api_;
  SharedRef<InputAPI> input_api_;

};