#include "MaterialAssetConverterSetting.h"

// =================================================================
// Methods from ConverterSetting
// =================================================================
bool MaterialAssetConverterSetting::EditWithImGuiProcess()
{
  return this->editor.EditWithImGui();
}
