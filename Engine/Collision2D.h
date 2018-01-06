#pragma once

#include "Geometry.h"
#include "Collider2D.h"

//Collider A_BÇ≈îªíËÇçsÇ§
//Collider A_BÇ∆B_AÇÃèàóùì‡óeÇÕïœÇÌÇÁÇ»Ç¢
namespace Collision2D
{
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