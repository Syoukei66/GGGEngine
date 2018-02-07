#include "Bresenham.h"

void line_bresenham(GameObjectRenderState* state, T_FLOAT toX, T_FLOAT toY)
{
	//const T_FLOAT fromX = state->position.x;
	//const T_FLOAT fromY = state->position.y;
	//const T_FLOAT dx = toX - fromX;
	//const T_FLOAT dy = toY - fromY;
	//const T_FLOAT adx = fabs(dx);
	//const T_FLOAT ady = fabs(dy);
	//const T_INTEGER ux = dx > 0 ? 1 : -1;
	//const T_INTEGER uy = dy > 0 ? 1 : -1;

	//T_FLOAT e = 0;

	//if (dx == 0 && dy == 0)
	//{
	//	nativeMethod()->draw_point(state);
	//	return;
	//}
	//if (adx > ady)
	//{
	//	if (dx > 0)
	//	{
	//		for (; state->position.x < toX; state->position.x++)
	//		{
	//			nativeMethod()->draw_point(state);
	//			e += ady;
	//			if (e > adx)
	//			{
	//				e -= adx;
	//				state->position.y += uy;
	//			}
	//		}
	//	}
	//	else
	//	{
	//		for (; state->position.x >= toX; state->position.x--)
	//		{
	//			nativeMethod()->draw_point(state);
	//			e += ady;
	//			if (e > adx)
	//			{
	//				e -= adx;
	//				state->position.y += uy;
	//			}
	//		}
	//	}
	//}
	//else
	//{
	//	if (dy > 0)
	//	{
	//		for (; state->position.y < toY; state->position.y++)
	//		{
	//			nativeMethod()->draw_point(state);
	//			e += adx;
	//			if (e > ady)
	//			{
	//				e -= ady;
	//				state->position.x += ux;
	//			}
	//		}
	//	}
	//	else
	//	{
	//		for (; state->position.y >= toY; state->position.y--)
	//		{
	//			nativeMethod()->draw_point(state);
	//			e += adx;
	//			if (e > ady)
	//			{
	//				e -= ady;
	//				state->position.x += ux;
	//			}
	//		}
	//	}
	//}

	//state->position.x = fromX;
	//state->position.y = fromY;
}
