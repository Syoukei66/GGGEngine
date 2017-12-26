#ifndef HAL_ENGINE_ENTITY_SHAPE_SPRITE_H_
#define HAL_ENGINE_ENTITY_SHAPE_SPRITE_H_

#include "Shape.h"
#include "SpriteVertexBufferObject.h"
#include "ITextureRegion.h"

class Sprite : public Shape
{  
  // =================================================================
  // Factory Method
  // =================================================================
public:
  static Sprite* Create();

  //ITextureRegionをあらかじめセットした状態でSpriteを生成します。
  //Spriteのサイズ(width/height)はITextureRegionに準じたものとなります。
  //引数で渡したITextureRegionの解放はこのクラスでは行われません。
  static Sprite* CreateWithTextureRegion(ITextureRegion* region);

  //TextureからTextureRegionを作成し、
  //それをもとにSpriteを生成します。
  //Spriteのサイズ(width/height)はTextureに準じたものとなります、
  //Textureの解放はこのクラスでは行われませんが、
  //生成されたTextureRegionの解放はこのクラスでは行われます。
  static Sprite* CreateWithTexture(const ITexture* texture);

  //指定したパスから画像をTextureとしてロードし、
  //そのTextureからTextureRegionを作成し、
  //それをもとにSpriteを生成します。
  //Spriteのサイズ(width/height)は画像のサイズ(width/height)に準じたものとなります、
  //ロードされたTextureの解放はこのクラスでは行われませんが、
  //生成されたTextureRegionの解放はこのクラスでは行われます。
  static Sprite* CreateFromAsset(T_UINT8 palette_id, T_UINT16 texture_id);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  virtual ~Sprite();
protected:
  Sprite();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void Init() override;
  virtual void PreDraw(GameObject2DRenderState* state) override;
  virtual void NativeDraw(GameObject2DRenderState* state) override;
  virtual void PostDraw(GameObject2DRenderState* state) override;

  // =================================================================
  // Method
  // =================================================================
public:
  void OnTextureChanged();
  //Spriteのサイズ(width/height)をITextureRegionに準じたものに変更します。
  //ITextureRegionがNULLの場合、サイズは0*0になります。
  void FitToTexture();

  // =================================================================
  // setter/getter
  // =================================================================
public:
  virtual IVertexBufferObject* GetVbo() const override;
  void SetTextureRegion(ITextureRegion* itr);
  inline ITextureRegion* GetTextureRegion() const
  {
    return this->texture_region_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  SpriteVertexBufferObject* vbo_;
  ITextureRegion* texture_region_;

protected:
  //TODO:KEN,どうにかしろ
  bool delete_region_;
};

#endif//HAL_ENGINE_ENTITY_SHAPE_SPRITE_H_

