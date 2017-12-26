#pragma once

#include "NativeType.h"
#include "Geometry.h"

//当たり判定の処理はパフォーマンスに大きく関わるので
//Engine側では管理/実装を行わない
//代わりに演算の為の関数とインターフェースを用意するので、
//これらを利用してゲーム毎に管理/実装しよう

class ICollider2D
{
public:
  //衝突判定に使用する座標情報やバウンディングボックスの
  //
  //この時点でfalseが帰ってきた場合、衝突判定計算を行わず、
  //判定の結果をfalseとする。
  virtual bool Prepare() = 0;

  //当たり判定処理を高速化する為に必要
  //複雑な当たり判定が必要な場合は、
  //あらかじめ円でのラフチェックを行う
  virtual T_FLOAT BoundX() = 0;
  virtual T_FLOAT BoundY() = 0;
  virtual T_FLOAT BoundRadius() = 0;
};

class IPointCollider2D : public virtual ICollider2D
{
public:
  virtual T_FLOAT GetX() const = 0;
  virtual T_FLOAT GetY() const = 0;
};

class ILineCollider2D : public virtual ICollider2D
{
public:
  virtual T_FLOAT GetX1() const = 0;
  virtual T_FLOAT GetY1() const = 0;
  virtual T_FLOAT GetX2() const = 0;
  virtual T_FLOAT GetY2() const = 0;
};

class ICircleCollider2D : public virtual ICollider2D
{
public:
  virtual T_FLOAT GetX() const = 0;
  virtual T_FLOAT GetY() const = 0;
  virtual T_FLOAT GetRadius() const = 0;
}; 

class IRectCollider2D : public virtual ICollider2D
{
public:
  virtual T_FLOAT GetX() const = 0;
  virtual T_FLOAT GetY() const = 0;
  virtual T_FLOAT GetWidth() const = 0;
  virtual T_FLOAT GetHeight() const = 0;
};

class IPolygonCollider2D : public virtual ICollider2D
{
public:
  virtual T_FLOAT GetOffsetX() const = 0;
  virtual T_FLOAT GetOffsetY() const = 0;
  virtual T_UINT16 GetVertexCount() const = 0;
  virtual const TVec2f* GetVertexes() const = 0;
};
