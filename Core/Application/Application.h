#pragma once

#include "ApplicationOption.h"
#include <Core/Application/Platform/Platform.h>
#include <Core/Application/Activity/Activity.h>

class IApplicationBehavior;
class IApplicationSetting;

/*!
 * @brief アクティビティやプラットフォームを動作させるクラス
 * アクティビティの管理を行う
 */
class Application
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SINGLETON(Application);

  // =================================================================
  // Methods
  // =================================================================
public:
  static void Run(IApplicationBehavior* behavior, const SharedRef<Platform>& platform);

  static SharedRef<Activity> StartActivity(const SharedRef<Activity>& activity, const ActivityOption& ao);

  static bool IsActive();

private:
  static bool Init(const SharedRef<Platform>& platform, IApplicationBehavior* behavior, const ApplicationOption& option);
  static bool Uninit(IApplicationBehavior* behavior);
  static bool Update();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  static GG_INLINE const ApplicationOption& GetOption()
  {
    return Self().option_;
  }
  
  static GG_INLINE SharedRef<Platform> GetPlatform()
  {
    return Self().platform_;
  }

  static GG_INLINE SharedRef<Activity> GetMainActivity()
  {
    return Self().main_activity_;
  }

  static GG_INLINE const UpdateEventState& GetUpdateEventState()
  {
    return *(Self().update_event_state_);
  }

  // =================================================================
  // Data Members
  // =================================================================
private:
  IApplicationBehavior* behavior_;
  ApplicationOption option_;
  SharedRef<Platform> platform_;
  SharedRef<Activity> main_activity_;
  std::vector<SharedRef<Activity>> sub_activities_;
  UpdateEventState* update_event_state_;
};