//#include "LoopSprite.h"
//#include "EngineAsset.h"
//
//// =================================================================
//// Factory Method
//// =================================================================
//LoopSprite* LoopSprite::Create()
//{
//  LoopSprite* ret = new LoopSprite();
//  ret->Init();
//  return ret;
//}
//
//LoopSprite* LoopSprite::CreateWithTextureRegion(LoopTextureRegion* region)
//{
//  LoopSprite* ret = LoopSprite::Create();
//  ret->SetTextureRegion(region);
//  ret->FitToTexture();
//  return ret;
//}
//
//LoopSprite* LoopSprite::CreateWithMaterial(Material* material)
//{
//  LoopTextureRegion* region = LoopTextureRegion::CreateWithMaterial(material);
//  LoopSprite* ret = LoopSprite::CreateWithTextureRegion(region);
//  ret->SetMaterial(*material);
//  ret->delete_region_ = true;
//  return ret;
//}
//
//LoopSprite* LoopSprite::CreateWithTexture(const Texture& texture)
//{
//  Material* mat = EngineAsset::Material::SPRITE.Clone();
//  mat->SetMainTexture(texture);
//  return CreateWithMaterial(mat);
//}
//
//// =================================================================
//// Methods for/from SuperClass/Interfaces
//// =================================================================
//void LoopSprite::OnVertexCoordChanged()
//{
//  Shape::OnVertexCoordChanged();
//  LoopTextureRegion* region = this->GetLoopTextureRegion();
//  region->SetLoopSize(this->GetSize());
//}
