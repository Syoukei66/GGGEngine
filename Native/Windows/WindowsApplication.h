#pragma once

#include <Core/Application/Application.h>
#include "WindowsPlatform.h"

/*!
 * @brief Windows—p‚ÌApplication
 */
class WindowsApplication
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_SINGLETON(WindowsApplication);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  static GG_INLINE SharedRef<WindowsPlatform> GetPlatform()
  {
    return SharedRef<WindowsPlatform>::StaticCast(Application::GetPlatform());
  }

  static GG_INLINE SharedRef<WindowActivityContext> GetMainActivityContext()
  {
    return SharedRef<WindowActivityContext>::StaticCast(Application::GetMainActivity()->GetContext());
  }

};