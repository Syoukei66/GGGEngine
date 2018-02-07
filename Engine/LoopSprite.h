//#pragma once
//
//#include "Sprite.h"
//#include "LoopTextureRegion.h"
//
//class LoopSprite : public Sprite
//{
//  // =================================================================
//  // Factory Method
//  // =================================================================
//public:
//  static LoopSprite* Create();
//  static LoopSprite* CreateWithTextureRegion(LoopTextureRegion* region);
//  static LoopSprite* CreateWithMaterial(Material* material);
//  static LoopSprite* CreateWithTexture(const Texture& texture);
//
//  // =================================================================
//  // Methods for/from SuperClass/Interfaces
//  // =================================================================
//public:
//  virtual void OnVertexCoordChanged();
//
//  // =================================================================
//  // Setter / Getter
//  // =================================================================
//public:
//  inline LoopTextureRegion* GetLoopTextureRegion()
//  {
//    return (LoopTextureRegion*)this->GetTextureRegion();
//  }
//};
