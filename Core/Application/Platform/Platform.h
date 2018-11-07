#pragma once

#include <Core/Application/Activity/Activity.h>
#include <Core/Application/Platform/API/Graphics/GraphicsAPI.h>
#include <Core/Application/Platform/API/Audio/AudioAPI.h>
#include <Core/Application/Platform/API/Input/InputAPI.h>

class Platform : public GGObject
{
  friend class Application;

  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT_NAME(Platform);
  GG_CREATE_FUNC(Platform) { return true; }

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE SharedRef<Activity> GetMainActivity()
  {
    return this->main_activity_;
  }

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
  SharedRef<Activity> main_activity_;
  SharedRef<GraphicsAPI> graphics_api_;
  SharedRef<AudioAPI> audio_api_;
  SharedRef<InputAPI> input_api_;

};