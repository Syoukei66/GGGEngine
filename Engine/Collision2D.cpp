#include "Collision2D.h"
#include "Collider2D.h"
#include "MathConstants.h"
#include <math.h>

namespace Collision
{

//汎用
static T_FLOAT Square(T_FLOAT v)
{
  return v * v;
}

static T_FLOAT InnerProduct(T_FLOAT ax, T_FLOAT ay, T_FLOAT bx, T_FLOAT by)
{
  return ax * bx + ay * by;
}

static T_FLOAT OuterProduct(T_FLOAT ax, T_FLOAT ay, T_FLOAT bx, T_FLOAT by)
{
  return ax * by - ay * bx;
}

//同じプリミティブ同士(Polygon以外)
bool Collision_Point(T_FLOAT ax, T_FLOAT ay, T_FLOAT bx, T_FLOAT by)
{
  return ax == bx && ay == by;
}

bool Collision_Line(T_FLOAT ax1, T_FLOAT ay1, T_FLOAT ax2, T_FLOAT ay2, T_FLOAT bx1, T_FLOAT by1, T_FLOAT bx2, T_FLOAT by2)
{
  const T_FLOAT v1dx = bx1 - ax1;
  const T_FLOAT v1dy = by1 - ay1;
  
  const T_FLOAT adx = ax2 - ax1;
  const T_FLOAT ady = ay2 - ay1;
  const T_FLOAT bdx = bx2 - bx1;
  const T_FLOAT bdy = by2 - by1;

  const T_FLOAT outer_a_b = OuterProduct(adx, ady, bdx, bdy);
  
  if (outer_a_b == 0.0f)
  {
    //平行状態
    return false;
  }
  const T_FLOAT outer_v1_a = OuterProduct(v1dx, v1dy, adx, ady);
  const T_FLOAT outer_v1_b = OuterProduct(v1dx, v1dy, bdx, bdy);

  const T_FLOAT t1 = outer_v1_b / outer_a_b;
  const T_FLOAT t2 = outer_v1_a / outer_a_b;

  const T_FLOAT eps = 0.00001f;
  if (t1 + eps < 0.0f || t1 - eps > 1.0f || t2 + eps < 0.0f || t2 - eps > 1.0f)
  {
    return false;
  }
  return true;
}

bool Collision_Circle(T_FLOAT ax, T_FLOAT ay, T_FLOAT ar, T_FLOAT bx, T_FLOAT by, T_FLOAT br)
{
  if (ar == 0.0f || br == 0.0f)
  {
    return false;
  }

  const T_FLOAT dx = ax - bx;
  const T_FLOAT dy = ay - by;
  const T_FLOAT r = ar + br;

  return dx * dx + dy * dy <= r * r;
}

bool Collision_Rect(T_FLOAT ax, T_FLOAT ay, T_FLOAT aw, T_FLOAT ah, T_FLOAT bx, T_FLOAT by, T_FLOAT bw, T_FLOAT bh)
{
  const T_FLOAT ax_min = ax;
  const T_FLOAT ax_max = ax + aw;
  const T_FLOAT ay_min = ay;
  const T_FLOAT ay_max = ay + ah;

  const T_FLOAT bx_min = bx;
  const T_FLOAT bx_max = bx + bw;
  const T_FLOAT by_min = by;
  const T_FLOAT by_max = by + bh;

  return ax_min <= bx_max && ax_max >= bx_min &&
         ay_min <= by_max && ay_max >= by_min;
}

//Point
bool Collision_Point_Circle(T_FLOAT ax, T_FLOAT ay, T_FLOAT bx, T_FLOAT by, T_FLOAT br)
{
  return Collision_Circle(ax, ay, 0, bx, by, br);
}

bool Collision_Point_Line(T_FLOAT ax, T_FLOAT ay, T_FLOAT bx1, T_FLOAT by1, T_FLOAT bx2, T_FLOAT by2)
{
  const T_FLOAT l1_square = Square(bx2 - bx1) + Square(by2 - by1);
  const T_FLOAT l2_square = Square(ax - bx1) + Square(ay - by1);
  if (l1_square < l2_square)
  {
    return false;
  }
  const T_FLOAT jdg = (bx1 - bx1) * (ax - bx1) + (by1 - by1) * (ay - by1);
  const T_FLOAT l1_l2_square = l1_square * l2_square;
  const T_FLOAT eps = 0.00001f;
  return fabs(jdg - sqrt(l1_l2_square)) <= eps;
}

bool Collision_Point_Rect(T_FLOAT ax, T_FLOAT ay, T_FLOAT bx, T_FLOAT by, T_FLOAT bw, T_FLOAT bh)
{
  return Collision_Rect(ax, ay, 0, 0, bx, by, bw, bh);
}

bool Collision_Point_Polygon(T_FLOAT ax, T_FLOAT ay, T_FLOAT bx, T_FLOAT by, const TVec2f* bv, T_UINT16 bv_num)
{
  //頂点数0なら判定を行わない
  if (bv_num == 0)
  {
    return false;
  }
  //頂点数1であれば点として判定
  if (bv_num == 1)
  {
    return Collision_Point(bx + bv[0].x, by + bv[0].y, ax, ay);
  }
  //頂点数2であれば線分として判定
  if (bv_num == 2)
  {
    return Collision_Point_Line(bx + bv[0].x, by + bv[0].y, bx + bv[1].x, by + bv[1].y, ax, ay);
  }
  //線分に対して点の位置が全て(右側|左側)で判定
  bool all_right = true;
  bool all_left = true;
  for (T_UINT16 i = 0; i < bv_num; ++i)
  {
    const TVec2f& v1 = bv[i];
    const TVec2f& v2 = bv[(i + 1) % bv_num];
    if ((v2.x - v1.x) * (ay - (by + v1.y)) - (ax - (bx + v1.x)) * (v2.y - v1.y) > 0)
    {
      all_right = false;
    }
    else
    {
      all_left = false;
    }
  }
  return all_right || all_left;
}

//Line
bool Collision_Line_Circle(T_FLOAT ax1, T_FLOAT ay1, T_FLOAT ax2, T_FLOAT ay2, T_FLOAT bx, T_FLOAT by, T_FLOAT br)
{
  const TVec2f pq = TVec2f(ax1 - ax2, ay1 - ay2);
  const TVec2f pm = TVec2f(ax1 - bx, ay1 - by);

  const T_FLOAT inner = InnerProduct(pq.x, pq.y, pm.x, pm.y);
  const T_FLOAT pqd2 = pq.LengthSquare();
  const T_FLOAT pmd2 = pm.LengthSquare();

  const T_FLOAT k = inner / pqd2;

  //kが線分pq上にあるか
  if (k < 0 || 1 < k)
  {
    return false;
  }

  const T_FLOAT phd2 = (inner * inner) / pqd2;
  const T_FLOAT d2 = pmd2 - phd2;

  return d2 < br * br;
}

bool Collision_Line_Rect(T_FLOAT ax1, T_FLOAT ay1, T_FLOAT ax2, T_FLOAT ay2, T_FLOAT bx, T_FLOAT by, T_FLOAT bw, T_FLOAT bh)
{
  //始点と四角形の当たり判定
  if (Collision_Point_Rect(ax1, ay1, bx, by, bw, bh))
  {
    return true;
  }

  //終点と四角形の当たり判定
  if (Collision_Point_Rect(ax2, ay2, bx, by, bw, bh))
  {
    return true;
  }

  //始点も終点も四角形の内側に無く、
  //その上線分が四角形と接触している場合は
  //必ず四角形の対角線に触れているので、
  //線分と四角形の対角線の当たり判定を行う

  //線分と対角線1
  if (Collision_Line(ax1, ay1, ax2, ay2, bx, by, bx + bw, by + bh))
  {
    return true;
  }

  //線分と対角線2
  return Collision_Line(ax1, ay1, ax2, ay2, bx + bw, by, bx, by + bh);
}

bool Collision_Line_Polygon(T_FLOAT ax1, T_FLOAT ay1, T_FLOAT ax2, T_FLOAT ay2, T_FLOAT bx, T_FLOAT by, const TVec2f* bv, T_UINT16 bv_num)
{
  //頂点数0なら判定を行わない
  if (bv_num == 0)
  {
    return false;
  }
  //頂点数1であれば点として判定
  if (bv_num == 1)
  {
    return Collision_Point_Line(bx + bv[0].x, by + bv[0].y, ax1, ay1, ax2, ay2);
  }
  //頂点数2であれば線分として判定
  if (bv_num == 2)
  {
    return Collision_Line(bx + bv[0].x, by + bv[0].y, bx + bv[1].x, by + bv[1].y, ax1, ay1, ax2, ay2);
  }

  //始点か終点の片方だけが多角形の内側に含まれているケースは
  //線分同士の当たり判定の時点でヒットする予定のため、
  //始点と終点のどちらかが多角形の内側にあるかどうかだけを判定すればいい

  //始点と多角形の判定
  if (Collision_Point_Polygon(ax1, ay1, bx, by, bv, bv_num))
  {
    return true;
  }
  //終点と多角形の判定
  if (Collision_Point_Polygon(ax2, ay2, bx, by, bv, bv_num))
  {
    return true;
  }

  //各線分と線分の当たり判定
  for (T_UINT16 i = 0; i < bv_num; ++i)
  {
    const T_UINT16 j = (i + 1) % bv_num;
    if (Collision_Line(ax1, ay1, ax2, ay2, bx + bv[i].x, by + bv[i].y, bx + bv[j].x, by + bv[j].y))
    {
      return true;
    }
  }

  return false;
}

//Circle
bool Collision_Circle_Rect(T_FLOAT ax, T_FLOAT ay, T_FLOAT ar, T_FLOAT bx, T_FLOAT by, T_FLOAT bw, T_FLOAT bh)
{
  //縦長と円
  if (Collision_Point_Rect(ax, ay, bx, by - ar, bw, bh + ar * 2))
  {
    return true;
  }
  //横長と円
  if (Collision_Point_Rect(ax, ay, bx - ar, by, bw + ar * 2, bh))
  {
    return true;
  }
  //左上の頂点と円
  if (Collision_Point_Circle(bx, by, ax, ay, ar))
  {
    return true;
  }
  //右上の頂点と円
  if (Collision_Point_Circle(bx + bw, by, ax, ay, ar))
  {
    return true;
  }
  //左下の頂点と円
  if (Collision_Point_Circle(bx, by + bh, ax, ay, ar))
  {
    return true;
  }
  //右下の頂点と円
  if (Collision_Point_Circle(bx + bw, by + bh, ax, ay, ar))
  {
    return true;
  }
  return false;
}

bool Collision_Circle_Polygon(T_FLOAT ax, T_FLOAT ay, T_FLOAT ar, T_FLOAT bx, T_FLOAT by, const TVec2f* bv, T_UINT16 bv_num)
{
  //頂点数0なら判定を行わない
  if (bv_num == 0)
  {
    return false;
  }
  //頂点数1であれば点として判定
  if (bv_num == 1)
  {
    return Collision_Point_Circle(bx + bv[0].x, by + bv[0].y, ax, ay, ar);
  }
  //頂点数2であれば線分として判定
  if (bv_num == 2)
  {
    return Collision_Line_Circle(bx + bv[0].x, by + bv[0].y, bx + bv[1].x, by + bv[1].y, ax, ay, ar);
  }
  //各頂点と円の当たり判定
  for (T_UINT16 i = 0; i < bv_num; ++i)
  {
    if (Collision_Point_Circle(bx + bv[i].x, by + bv[i].y, ax, ay, ar))
    {
      return true;
    }
  }
  //中点と多角形の判定
  if (Collision_Point_Polygon(ax, ay, bx, by, bv, bv_num))
  {
    return true;
  }
  //各線分と円の当たり判定
  for (T_UINT16 i = 0; i < bv_num; ++i)
  {
    const T_UINT16 j = (i + 1) % bv_num;
    if (Collision_Line_Circle(ax, ay, ar, bx + bv[i].x, by + bv[i].y, bx + bv[j].x, by + bv[j].y))
    {
      return true;
    }
  }
  return false;
}

//Rect
bool Collision_Rect_Polygon(T_FLOAT ax, T_FLOAT ay, T_FLOAT aw, T_FLOAT ah, T_FLOAT bx, T_FLOAT by, const TVec2f* bv, T_UINT16 bv_num)
{
  //頂点数0なら判定を行わない
  if (bv_num == 0)
  {
    return false;
  }
  //頂点数1であれば点として判定
  if (bv_num == 1)
  {
    return Collision_Point_Rect(bx + bv[0].x, by + bv[0].y, ax, ay, aw, ah);
  }
  //頂点数2であれば線分として判定
  if (bv_num == 2)
  {
    return Collision_Line_Rect(bx + bv[0].x, by + bv[0].y, bx + bv[1].x, by + bv[1].y, ax, ay, aw, ah);
  }
  //各頂点と四角形の当たり判定
  for (T_UINT16 i = 0; i < bv_num; ++i)
  {
    if (Collision_Point_Rect(bx + bv[i].x, by + bv[i].y, ax, ay, aw, ah))
    {
      return true;
    }
  }
  //四角形の中心と多角形の判定
  if (Collision_Point_Polygon(ax + aw * 0.5f, ay + ah * 0.5f, bx, by, bv, bv_num))
  {
    return true;
  }
  //各線分と四角形の当たり判定
  for (T_UINT16 i = 0; i < bv_num; ++i)
  {
    const T_UINT16 j = (i + 1) % bv_num;
    if (Collision_Line_Rect(ax, ay, aw, ah, bx + bv[i].x, by + bv[i].y, bx + bv[j].x, by + bv[j].y))
    {
      return true;
    }
  }
  return false;
}

//Polygon同士
bool Collision_Polygon(T_FLOAT ax, T_FLOAT ay, const TVec2f* av, T_UINT16 av_num, T_FLOAT bx, T_FLOAT by, const TVec2f* bv, T_UINT16 bv_num)
{
  //avの頂点数0なら判定を行わない
  if (av_num == 0)
  {
    return false;
  }
  //avの頂点数1であれば点として判定
  if (av_num == 1)
  {
    return Collision_Point_Polygon(ax + av[0].x, ay + av[0].y, bx, by, bv, bv_num);
  }
  //avの頂点数2であれば線分として判定
  if (av_num == 2)
  {
    return Collision_Line_Polygon(ax + av[0].x, ay + av[0].y, ax + av[1].x, ay + av[1].y, bx, by, bv, bv_num);
  }
  //多角形の中点と多角形の当たり判定
  T_FLOAT x_sum = 0;
  T_FLOAT y_sum = 0;
  for (T_UINT16 i = 0; i < av_num; ++i)
  {
    x_sum += av[i].x;
    y_sum += av[i].y;
  }
  if (Collision_Point_Polygon(ax + x_sum / av_num, ay + y_sum / av_num, bx, by, bv, bv_num))
  {
    return true;
  }
  //各線分と多角形の当たり判定
  for (T_UINT16 i = 0; i < av_num; ++i)
  {
    const T_UINT16 j = (i + 1) % av_num;
    if (Collision_Line_Polygon(ax + av[i].x, ay + av[i].y, ax + av[j].x, ay + av[j].y, bx, by, bv, bv_num))
    {
      return true;
    }
  }
  return false;
}

bool Prepare(ICollider2D& a, ICollider2D& b)
{
  if (!a.Prepare())
  {
    return false;
  }
  if (!b.Prepare())
  {
    return false;
  }
  return true;
}

#define PREPARE \
  if (!Prepare(a, b))\
  {\
    return false;\
  }

//ラフチェック
bool RoughCheck(ICollider2D& a, ICollider2D& b)
{
  return Collision_Circle(a.BoundX(), a.BoundY(), a.BoundRadius(), b.BoundX(), b.BoundY(), b.BoundRadius());
}

#define ROUGH_CHECK \
  if (!RoughCheck(a, b))\
  {\
    return false;\
  }

#define POINT(A) A.GetX(), A.GetY()
#define LINE(A) A.GetX1(), A.GetY1(), A.GetX2(), A.GetY2()
#define CIRCLE(A) A.GetX(), A.GetY(), A.GetRadius()
#define RECT(A) A.GetX(), A.GetY(), A.GetWidth(), A.GetHeight()
#define POLYGON(A) A.GetOffsetX(), A.GetOffsetY(), A.GetVertexes(), A.GetVertexCount()

bool Point_Point(IPointCollider2D& a, IPointCollider2D& b)
{
  PREPARE
  return Collision_Point(POINT(a), POINT(b));
}

bool Point_Line(IPointCollider2D& a, ILineCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Collision_Point_Line(POINT(a), LINE(b));
}

bool Point_Circle(IPointCollider2D& a, ICircleCollider2D& b)
{
  PREPARE
  return Collision_Point_Circle(POINT(a), CIRCLE(b));
}

bool Point_Rect(IPointCollider2D& a, IRectCollider2D& b)
{
  PREPARE
  return Collision_Point_Rect(POINT(a), RECT(b));
}

bool Point_Polygon(IPointCollider2D& a, IPolygonCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Collision_Point_Polygon(POINT(a), POLYGON(b));
}

bool Line_Point(ILineCollider2D& a, IPointCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Collision_Point_Line(POINT(b), LINE(a));
}

bool Line_Line(ILineCollider2D& a, ILineCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Collision_Line(LINE(a), LINE(b));
}

bool Line_Circle(ILineCollider2D& a, ICircleCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Collision_Line_Circle(LINE(a), CIRCLE(b));
}

bool Line_Rect(ILineCollider2D& a, IRectCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Collision_Line_Rect(LINE(a), RECT(b));
}

bool Line_Polygon(ILineCollider2D& a, IPolygonCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Collision_Line_Polygon(LINE(a), POLYGON(b));
}

bool Circle_Point(ICircleCollider2D& a, IPointCollider2D& b)
{
  PREPARE
  return Collision_Point_Circle(POINT(b), CIRCLE(a));
}

bool Circle_Line(ICircleCollider2D& a, ILineCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Collision_Line_Circle(LINE(b), CIRCLE(a));
}

bool Circle_Circle(ICircleCollider2D& a, ICircleCollider2D& b)
{
  PREPARE
  return Collision_Circle(CIRCLE(a), CIRCLE(b));
}

bool Circle_Rect(ICircleCollider2D& a, IRectCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Collision_Circle_Rect(CIRCLE(a), RECT(b));
}

bool Circle_Polygon(ICircleCollider2D& a, IPolygonCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Collision_Circle_Polygon(CIRCLE(a), POLYGON(b));
}

bool Rect_Point(IRectCollider2D& a, IPointCollider2D& b)
{
  PREPARE
  return Collision_Point_Rect(POINT(b), RECT(a));
}

bool Rect_Line(IRectCollider2D& a, ILineCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Collision_Line_Rect(LINE(b), RECT(a));
}

bool Rect_Circle(IRectCollider2D& a, ICircleCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Collision_Circle_Rect(CIRCLE(b), RECT(a));
}

bool Rect_Rect(IRectCollider2D& a, IRectCollider2D& b)
{
  PREPARE
  return Collision_Rect(RECT(a), RECT(b));
}

bool Rect_Polygon(IRectCollider2D& a, IPolygonCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Collision_Rect_Polygon(RECT(a), POLYGON(b));
}

bool Polygon_Point(IPolygonCollider2D& a, IPointCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Collision_Point_Polygon(POINT(b), POLYGON(a));
}

bool Polygon_Line(IPolygonCollider2D& a, ILineCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Collision_Line_Polygon(LINE(b), POLYGON(a));
}

bool Polygon_Circle(IPolygonCollider2D& a, ICircleCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Collision_Circle_Polygon(CIRCLE(b), POLYGON(a));
}

bool Polygon_Rect(IPolygonCollider2D& a, IRectCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Collision_Rect_Polygon(RECT(b), POLYGON(a));
}

bool Polygon_Polygon(IPolygonCollider2D& a, IPolygonCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Collision_Polygon(POLYGON(a), POLYGON(b));
}

}
