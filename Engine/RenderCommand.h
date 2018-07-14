#pragma once

#include "Renderer.h"
#include "NativeVertexBuffer.h"
#include "NativeIndexBuffer.h"

class RenderState;
class CommandBuffer;

/*
    描画の最小単位
    RenderCommand１つが描画１つを表す。
    動的バッチングの為に
    同じ頂点バッファ、インデックスバッファ、マテリアルを使用している描画は
    極力まとめれるようにする
    また、CommandBuffer内の描画順ソートやフィルタリングなどの実行も最低限に抑えたいので、
    それぞれキャッシュを取るようにしていく。
*/

class RenderCommand
{
protected:
  RenderCommand(CommandBuffer* buffer);
  virtual ~RenderCommand();

public:
  void Release();

public:
  //描画の基準となるワールド行列
  virtual const Matrix4x4& GetWorldMatrix() = 0;
  //描画タイプ（透明/不透明/表面下拡散など）。パイプラインの選択やフィルタリングに使用。
  virtual T_UINT8 GetAttributeId() = 0;
  //フィルタリングに使用するパラメータ
  virtual T_UINT8 GetLayerId() = 0;
  //カリングに使用するパラメータ
  virtual T_UINT8 GetIndexId() = 0;

  virtual Material* GetMaterial() = 0;
  virtual INativeVertexBuffer* GetVertexBuffer() = 0;
  virtual INativeIndexBuffer* GetIndexBuffer() = 0;

private:
  CommandBuffer* buffer_;

};

