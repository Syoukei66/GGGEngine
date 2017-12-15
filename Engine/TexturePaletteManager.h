#pragma once

#include <string>
#include "NativeType.h"
#include "ResourcePool.h"
#include "ITexturePalette.h"
#include "TexturePalette.h"

class TexturePaletteManager : public ResourcePool<T_UINT8, ITexturePalette>
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  TexturePaletteManager();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
protected:
  virtual ITexturePalette* PreLoadProcess(const T_UINT8& key) override;
  virtual ITexturePalette* LoadProcess(const T_UINT8& key, ITexturePalette* value) override;
  virtual void PreUnloadProcess(const T_UINT8& key, ITexturePalette* value) override;
  virtual void UnloadProcess(const T_UINT8& key, ITexturePalette* value) override;

  // =================================================================
  // Methods
  // =================================================================
public:
  void RegisterPath(T_UINT8 id, const char* path);

  //動的ロードされたテクスチャは自動的に開放されないので
  //基本的に使わないこと
  //モデル等が使用する
  const Texture* DynamicLoad(const char* path);
  void DynamicUnload(const char* path);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  const Texture* GetDynamicTexture(const char* path) const;

  // =================================================================
  // Data Member
  // =================================================================
private:
  std::map<T_UINT8, std::string> paths_;
  TexturePalette* dynamic_texture_palette_;
};
