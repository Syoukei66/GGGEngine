#include "EntryPoint.h"

// =================================================================
// Methods
// =================================================================
void EntryPoint::Run(IEngineBehavior* behavior)
{
  Engine engine = Engine(behavior);
  Application::Run(&engine, *this);
}
