#pragma once

#include "../Core/Vector2.h"
#include "Collider2D.h"

//Collider A_BÇ≈îªíËÇçsÇ§
//Collider A_BÇ∆B_AÇÃèàóùì‡óeÇÕïœÇÌÇÁÇ»Ç¢
namespace Collision2D
{

bool Point(T_FLOAT ax, T_FLOAT ay, T_FLOAT bx, T_FLOAT by);
bool Point_Circle(T_FLOAT ax, T_FLOAT ay, T_FLOAT bx, T_FLOAT by, T_FLOAT br);
bool Point_Line(T_FLOAT ax, T_FLOAT ay, T_FLOAT bx1, T_FLOAT by1, T_FLOAT bx2, T_FLOAT by2);
bool Point_Rect(T_FLOAT ax, T_FLOAT ay, T_FLOAT bx, T_FLOAT by, T_FLOAT bw, T_FLOAT bh);
bool Point_Polygon(T_FLOAT ax, T_FLOAT ay, T_FLOAT bx, T_FLOAT by, const TVec2f* bv, T_UINT16 bv_num);

bool Line(T_FLOAT ax1, T_FLOAT ay1, T_FLOAT ax2, T_FLOAT ay2, T_FLOAT bx1, T_FLOAT by1, T_FLOAT bx2, T_FLOAT by2);
bool Line_Circle(T_FLOAT ax1, T_FLOAT ay1, T_FLOAT ax2, T_FLOAT ay2, T_FLOAT bx, T_FLOAT by, T_FLOAT br);
bool Line_Rect(T_FLOAT ax1, T_FLOAT ay1, T_FLOAT ax2, T_FLOAT ay2, T_FLOAT bx, T_FLOAT by, T_FLOAT bw, T_FLOAT bh);
bool Line_Polygon(T_FLOAT ax1, T_FLOAT ay1, T_FLOAT ax2, T_FLOAT ay2, T_FLOAT bx, T_FLOAT by, const TVec2f* bv, T_UINT16 bv_num);

bool Circle(T_FLOAT ax, T_FLOAT ay, T_FLOAT ar, T_FLOAT bx, T_FLOAT by, T_FLOAT br);
bool Circle_Rect(T_FLOAT ax, T_FLOAT ay, T_FLOAT ar, T_FLOAT bx, T_FLOAT by, T_FLOAT bw, T_FLOAT bh);
bool Circle_Polygon(T_FLOAT ax, T_FLOAT ay, T_FLOAT ar, T_FLOAT bx, T_FLOAT by, const TVec2f* bv, T_UINT16 bv_num);

bool Rect(T_FLOAT ax, T_FLOAT ay, T_FLOAT aw, T_FLOAT ah, T_FLOAT bx, T_FLOAT by, T_FLOAT bw, T_FLOAT bh);
bool Rect_Polygon(T_FLOAT ax, T_FLOAT ay, T_FLOAT aw, T_FLOAT ah, T_FLOAT bx, T_FLOAT by, const TVec2f* bv, T_UINT16 bv_num);

bool Polygon(T_FLOAT ax, T_FLOAT ay, const TVec2f* av, T_UINT16 av_num, T_FLOAT bx, T_FLOAT by, const TVec2f* bv, T_UINT16 bv_num);

bool Point_Point(IPointCollider2D& a, IPointCollider2D& b);
bool Point_Line(IPointCollider2D& a, ILineCollider2D& b);
bool Point_Circle(IPointCollider2D& a, ICircleCollider2D& b);
bool Point_Rect(IPointCollider2D& a, IRectCollider2D& b);
bool Point_Polygon(IPointCollider2D& a, IPolygonCollider2D& b);

bool Line_Point(ILineCollider2D& a, IPointCollider2D& b);
bool Line_Line(ILineCollider2D& a, ILineCollider2D& b);
bool Line_Circle(ILineCollider2D& a, ICircleCollider2D& b);
bool Line_Rect(ILineCollider2D& a, IRectCollider2D& b);
bool Line_Polygon(ILineCollider2D& a, IPolygonCollider2D& b);

bool Circle_Point(ICircleCollider2D& a, IPointCollider2D& b);
bool Circle_Line(ICircleCollider2D& a, ILineCollider2D& b);
bool Circle_Circle(ICircleCollider2D& a, ICircleCollider2D& b);
bool Circle_Rect(ICircleCollider2D& a, IRectCollider2D& b);
bool Circle_Polygon(ICircleCollider2D& a, IPolygonCollider2D& b);

bool Rect_Point(IRectCollider2D& a, IPointCollider2D& b);
bool Rect_Line(IRectCollider2D& a, ILineCollider2D& b);
bool Rect_Circle(IRectCollider2D& a, ICircleCollider2D& b);
bool Rect_Rect(IRectCollider2D& a, IRectCollider2D& b);
bool Rect_Polygon(IRectCollider2D& a, IPolygonCollider2D& b);

bool Polygon_Point(IPolygonCollider2D& a, IPointCollider2D& b);
bool Polygon_Line(IPolygonCollider2D& a, ILineCollider2D& b);
bool Polygon_Circle(IPolygonCollider2D& a, ICircleCollider2D& b);
bool Polygon_Rect(IPolygonCollider2D& a, IRectCollider2D& b);
bool Polygon_Polygon(IPolygonCollider2D& a, IPolygonCollider2D& b);
}