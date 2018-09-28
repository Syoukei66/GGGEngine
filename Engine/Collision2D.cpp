#include "Collision2D.h"

#include <Core/Mathf.h>
#include <math.h>

#include "Collider2D.h"

namespace Collision2D
{

//�ėp
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

//�����v���~�e�B�u���m(Polygon�ȊO)
bool Point(T_FLOAT ax, T_FLOAT ay, T_FLOAT bx, T_FLOAT by)
{
  return ax == bx && ay == by;
}

bool Line(T_FLOAT ax1, T_FLOAT ay1, T_FLOAT ax2, T_FLOAT ay2, T_FLOAT bx1, T_FLOAT by1, T_FLOAT bx2, T_FLOAT by2)
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
    //���s���
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

bool Circle(T_FLOAT ax, T_FLOAT ay, T_FLOAT ar, T_FLOAT bx, T_FLOAT by, T_FLOAT br)
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

bool Rect(T_FLOAT ax, T_FLOAT ay, T_FLOAT aw, T_FLOAT ah, T_FLOAT bx, T_FLOAT by, T_FLOAT bw, T_FLOAT bh)
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
bool Point_Circle(T_FLOAT ax, T_FLOAT ay, T_FLOAT bx, T_FLOAT by, T_FLOAT br)
{
  return Circle(ax, ay, 0, bx, by, br);
}

bool Point_Line(T_FLOAT ax, T_FLOAT ay, T_FLOAT bx1, T_FLOAT by1, T_FLOAT bx2, T_FLOAT by2)
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

bool Point_Rect(T_FLOAT ax, T_FLOAT ay, T_FLOAT bx, T_FLOAT by, T_FLOAT bw, T_FLOAT bh)
{
  return Rect(ax, ay, 0, 0, bx, by, bw, bh);
}

bool Point_Polygon(T_FLOAT ax, T_FLOAT ay, T_FLOAT bx, T_FLOAT by, const TVec2f* bv, T_UINT16 bv_num)
{
  //���_��0�Ȃ画����s��Ȃ�
  if (bv_num == 0)
  {
    return false;
  }
  //���_��1�ł���Γ_�Ƃ��Ĕ���
  if (bv_num == 1)
  {
    return Point(bx + bv[0].x, by + bv[0].y, ax, ay);
  }
  //���_��2�ł���ΐ����Ƃ��Ĕ���
  if (bv_num == 2)
  {
    return Point_Line(bx + bv[0].x, by + bv[0].y, bx + bv[1].x, by + bv[1].y, ax, ay);
  }
  //�����ɑ΂��ē_�̈ʒu���S��(�E��|����)�Ŕ���
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
bool Line_Circle(T_FLOAT ax1, T_FLOAT ay1, T_FLOAT ax2, T_FLOAT ay2, T_FLOAT bx, T_FLOAT by, T_FLOAT br)
{
  const TVec2f pq = TVec2f(ax1 - ax2, ay1 - ay2);
  const TVec2f pm = TVec2f(ax1 - bx, ay1 - by);

  const T_FLOAT inner = InnerProduct(pq.x, pq.y, pm.x, pm.y);
  const T_FLOAT pqd2 = pq.LengthSquare();
  const T_FLOAT pmd2 = pm.LengthSquare();

  const T_FLOAT k = inner / pqd2;

  //k������pq��ɂ��邩
  if (k < 0 || 1 < k)
  {
    return false;
  }

  const T_FLOAT phd2 = (inner * inner) / pqd2;
  const T_FLOAT d2 = pmd2 - phd2;

  return d2 < br * br;
}

bool Line_Rect(T_FLOAT ax1, T_FLOAT ay1, T_FLOAT ax2, T_FLOAT ay2, T_FLOAT bx, T_FLOAT by, T_FLOAT bw, T_FLOAT bh)
{
  //�n�_�Ǝl�p�`�̓����蔻��
  if (Point_Rect(ax1, ay1, bx, by, bw, bh))
  {
    return true;
  }

  //�I�_�Ǝl�p�`�̓����蔻��
  if (Point_Rect(ax2, ay2, bx, by, bw, bh))
  {
    return true;
  }

  //�n�_���I�_���l�p�`�̓����ɖ����A
  //���̏�������l�p�`�ƐڐG���Ă���ꍇ��
  //�K���l�p�`�̑Ίp���ɐG��Ă���̂ŁA
  //�����Ǝl�p�`�̑Ίp���̓����蔻����s��

  //�����ƑΊp��1
  if (Line(ax1, ay1, ax2, ay2, bx, by, bx + bw, by + bh))
  {
    return true;
  }

  //�����ƑΊp��2
  return Line(ax1, ay1, ax2, ay2, bx + bw, by, bx, by + bh);
}

bool Line_Polygon(T_FLOAT ax1, T_FLOAT ay1, T_FLOAT ax2, T_FLOAT ay2, T_FLOAT bx, T_FLOAT by, const TVec2f* bv, T_UINT16 bv_num)
{
  //���_��0�Ȃ画����s��Ȃ�
  if (bv_num == 0)
  {
    return false;
  }
  //���_��1�ł���Γ_�Ƃ��Ĕ���
  if (bv_num == 1)
  {
    return Point_Line(bx + bv[0].x, by + bv[0].y, ax1, ay1, ax2, ay2);
  }
  //���_��2�ł���ΐ����Ƃ��Ĕ���
  if (bv_num == 2)
  {
    return Line(bx + bv[0].x, by + bv[0].y, bx + bv[1].x, by + bv[1].y, ax1, ay1, ax2, ay2);
  }

  //�n�_���I�_�̕Е����������p�`�̓����Ɋ܂܂�Ă���P�[�X��
  //�������m�̓����蔻��̎��_�Ńq�b�g����\��̂��߁A
  //�n�_�ƏI�_�̂ǂ��炩�����p�`�̓����ɂ��邩�ǂ��������𔻒肷��΂���

  //�n�_�Ƒ��p�`�̔���
  if (Point_Polygon(ax1, ay1, bx, by, bv, bv_num))
  {
    return true;
  }
  //�I�_�Ƒ��p�`�̔���
  if (Point_Polygon(ax2, ay2, bx, by, bv, bv_num))
  {
    return true;
  }

  //�e�����Ɛ����̓����蔻��
  for (T_UINT16 i = 0; i < bv_num; ++i)
  {
    const T_UINT16 j = (i + 1) % bv_num;
    if (Line(ax1, ay1, ax2, ay2, bx + bv[i].x, by + bv[i].y, bx + bv[j].x, by + bv[j].y))
    {
      return true;
    }
  }

  return false;
}

//Circle
bool Circle_Rect(T_FLOAT ax, T_FLOAT ay, T_FLOAT ar, T_FLOAT bx, T_FLOAT by, T_FLOAT bw, T_FLOAT bh)
{
  //�c���Ɖ~
  if (Point_Rect(ax, ay, bx, by - ar, bw, bh + ar * 2))
  {
    return true;
  }
  //�����Ɖ~
  if (Point_Rect(ax, ay, bx - ar, by, bw + ar * 2, bh))
  {
    return true;
  }
  //����̒��_�Ɖ~
  if (Point_Circle(bx, by, ax, ay, ar))
  {
    return true;
  }
  //�E��̒��_�Ɖ~
  if (Point_Circle(bx + bw, by, ax, ay, ar))
  {
    return true;
  }
  //�����̒��_�Ɖ~
  if (Point_Circle(bx, by + bh, ax, ay, ar))
  {
    return true;
  }
  //�E���̒��_�Ɖ~
  if (Point_Circle(bx + bw, by + bh, ax, ay, ar))
  {
    return true;
  }
  return false;
}

bool Circle_Polygon(T_FLOAT ax, T_FLOAT ay, T_FLOAT ar, T_FLOAT bx, T_FLOAT by, const TVec2f* bv, T_UINT16 bv_num)
{
  //���_��0�Ȃ画����s��Ȃ�
  if (bv_num == 0)
  {
    return false;
  }
  //���_��1�ł���Γ_�Ƃ��Ĕ���
  if (bv_num == 1)
  {
    return Point_Circle(bx + bv[0].x, by + bv[0].y, ax, ay, ar);
  }
  //���_��2�ł���ΐ����Ƃ��Ĕ���
  if (bv_num == 2)
  {
    return Line_Circle(bx + bv[0].x, by + bv[0].y, bx + bv[1].x, by + bv[1].y, ax, ay, ar);
  }
  //�e���_�Ɖ~�̓����蔻��
  for (T_UINT16 i = 0; i < bv_num; ++i)
  {
    if (Point_Circle(bx + bv[i].x, by + bv[i].y, ax, ay, ar))
    {
      return true;
    }
  }
  //���_�Ƒ��p�`�̔���
  if (Point_Polygon(ax, ay, bx, by, bv, bv_num))
  {
    return true;
  }
  //�e�����Ɖ~�̓����蔻��
  for (T_UINT16 i = 0; i < bv_num; ++i)
  {
    const T_UINT16 j = (i + 1) % bv_num;
    if (Line_Circle(ax, ay, ar, bx + bv[i].x, by + bv[i].y, bx + bv[j].x, by + bv[j].y))
    {
      return true;
    }
  }
  return false;
}

//Rect
bool Rect_Polygon(T_FLOAT ax, T_FLOAT ay, T_FLOAT aw, T_FLOAT ah, T_FLOAT bx, T_FLOAT by, const TVec2f* bv, T_UINT16 bv_num)
{
  //���_��0�Ȃ画����s��Ȃ�
  if (bv_num == 0)
  {
    return false;
  }
  //���_��1�ł���Γ_�Ƃ��Ĕ���
  if (bv_num == 1)
  {
    return Point_Rect(bx + bv[0].x, by + bv[0].y, ax, ay, aw, ah);
  }
  //���_��2�ł���ΐ����Ƃ��Ĕ���
  if (bv_num == 2)
  {
    return Line_Rect(bx + bv[0].x, by + bv[0].y, bx + bv[1].x, by + bv[1].y, ax, ay, aw, ah);
  }
  //�e���_�Ǝl�p�`�̓����蔻��
  for (T_UINT16 i = 0; i < bv_num; ++i)
  {
    if (Point_Rect(bx + bv[i].x, by + bv[i].y, ax, ay, aw, ah))
    {
      return true;
    }
  }
  //�l�p�`�̒��S�Ƒ��p�`�̔���
  if (Point_Polygon(ax + aw * 0.5f, ay + ah * 0.5f, bx, by, bv, bv_num))
  {
    return true;
  }
  //�e�����Ǝl�p�`�̓����蔻��
  for (T_UINT16 i = 0; i < bv_num; ++i)
  {
    const T_UINT16 j = (i + 1) % bv_num;
    if (Line_Rect(ax, ay, aw, ah, bx + bv[i].x, by + bv[i].y, bx + bv[j].x, by + bv[j].y))
    {
      return true;
    }
  }
  return false;
}

//Polygon���m
bool Polygon(T_FLOAT ax, T_FLOAT ay, const TVec2f* av, T_UINT16 av_num, T_FLOAT bx, T_FLOAT by, const TVec2f* bv, T_UINT16 bv_num)
{
  //av�̒��_��0�Ȃ画����s��Ȃ�
  if (av_num == 0)
  {
    return false;
  }
  //av�̒��_��1�ł���Γ_�Ƃ��Ĕ���
  if (av_num == 1)
  {
    return Point_Polygon(ax + av[0].x, ay + av[0].y, bx, by, bv, bv_num);
  }
  //av�̒��_��2�ł���ΐ����Ƃ��Ĕ���
  if (av_num == 2)
  {
    return Line_Polygon(ax + av[0].x, ay + av[0].y, ax + av[1].x, ay + av[1].y, bx, by, bv, bv_num);
  }
  //���p�`�̒��_�Ƒ��p�`�̓����蔻��
  T_FLOAT x_sum = 0;
  T_FLOAT y_sum = 0;
  for (T_UINT16 i = 0; i < av_num; ++i)
  {
    x_sum += av[i].x;
    y_sum += av[i].y;
  }
  if (Point_Polygon(ax + x_sum / av_num, ay + y_sum / av_num, bx, by, bv, bv_num))
  {
    return true;
  }
  //�e�����Ƒ��p�`�̓����蔻��
  for (T_UINT16 i = 0; i < av_num; ++i)
  {
    const T_UINT16 j = (i + 1) % av_num;
    if (Line_Polygon(ax + av[i].x, ay + av[i].y, ax + av[j].x, ay + av[j].y, bx, by, bv, bv_num))
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

//���t�`�F�b�N
bool RoughCheck(ICollider2D& a, ICollider2D& b)
{
  return Circle(a.BoundX(), a.BoundY(), a.BoundRadius(), b.BoundX(), b.BoundY(), b.BoundRadius());
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
  return Point(POINT(a), POINT(b));
}

bool Point_Line(IPointCollider2D& a, ILineCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Point_Line(POINT(a), LINE(b));
}

bool Point_Circle(IPointCollider2D& a, ICircleCollider2D& b)
{
  PREPARE
  return Point_Circle(POINT(a), CIRCLE(b));
}

bool Point_Rect(IPointCollider2D& a, IRectCollider2D& b)
{
  PREPARE
  return Point_Rect(POINT(a), RECT(b));
}

bool Point_Polygon(IPointCollider2D& a, IPolygonCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Point_Polygon(POINT(a), POLYGON(b));
}

bool Line_Point(ILineCollider2D& a, IPointCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Point_Line(POINT(b), LINE(a));
}

bool Line_Line(ILineCollider2D& a, ILineCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Line(LINE(a), LINE(b));
}

bool Line_Circle(ILineCollider2D& a, ICircleCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Line_Circle(LINE(a), CIRCLE(b));
}

bool Line_Rect(ILineCollider2D& a, IRectCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Line_Rect(LINE(a), RECT(b));
}

bool Line_Polygon(ILineCollider2D& a, IPolygonCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Line_Polygon(LINE(a), POLYGON(b));
}

bool Circle_Point(ICircleCollider2D& a, IPointCollider2D& b)
{
  PREPARE
  return Point_Circle(POINT(b), CIRCLE(a));
}

bool Circle_Line(ICircleCollider2D& a, ILineCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Line_Circle(LINE(b), CIRCLE(a));
}

bool Circle_Circle(ICircleCollider2D& a, ICircleCollider2D& b)
{
  PREPARE
  return Circle(CIRCLE(a), CIRCLE(b));
}

bool Circle_Rect(ICircleCollider2D& a, IRectCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Circle_Rect(CIRCLE(a), RECT(b));
}

bool Circle_Polygon(ICircleCollider2D& a, IPolygonCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Circle_Polygon(CIRCLE(a), POLYGON(b));
}

bool Rect_Point(IRectCollider2D& a, IPointCollider2D& b)
{
  PREPARE
  return Point_Rect(POINT(b), RECT(a));
}

bool Rect_Line(IRectCollider2D& a, ILineCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Line_Rect(LINE(b), RECT(a));
}

bool Rect_Circle(IRectCollider2D& a, ICircleCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Circle_Rect(CIRCLE(b), RECT(a));
}

bool Rect_Rect(IRectCollider2D& a, IRectCollider2D& b)
{
  PREPARE
  return Rect(RECT(a), RECT(b));
}

bool Rect_Polygon(IRectCollider2D& a, IPolygonCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Rect_Polygon(RECT(a), POLYGON(b));
}

bool Polygon_Point(IPolygonCollider2D& a, IPointCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Point_Polygon(POINT(b), POLYGON(a));
}

bool Polygon_Line(IPolygonCollider2D& a, ILineCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Line_Polygon(LINE(b), POLYGON(a));
}

bool Polygon_Circle(IPolygonCollider2D& a, ICircleCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Circle_Polygon(CIRCLE(b), POLYGON(a));
}

bool Polygon_Rect(IPolygonCollider2D& a, IRectCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Rect_Polygon(RECT(b), POLYGON(a));
}

bool Polygon_Polygon(IPolygonCollider2D& a, IPolygonCollider2D& b)
{
  PREPARE
  ROUGH_CHECK
  return Polygon(POLYGON(a), POLYGON(b));
}

}
