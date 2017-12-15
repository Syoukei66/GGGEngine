#include "Matrix.h"
#include <d3d9.h>
#include <d3dx9.h>

T_MATRIX_4x4* matrix4x4_create()
{
	T_MATRIX_4x4* ret = new T_MATRIX_4x4();
	matrix4x4_init(ret);
	return ret;
}

void matrix4x4_init(T_MATRIX_4x4* matrix)
{
	D3DXMatrixIdentity(matrix);
}

void matrix4x4_delete(T_MATRIX_4x4* matrix)
{
	if (matrix)
	{
		delete matrix;
	}
}

void matrix4x4_multiply(T_MATRIX_4x4* dst, T_MATRIX_4x4* mat)
{
	D3DXMatrixMultiply(dst, dst, mat);
}

void matrix4x4_translate(T_MATRIX_4x4* mat, T_FLOAT32 x, T_FLOAT32 y)
{
	D3DXMatrixTranslation(mat, x, y, 0.0f);
}

void matrix4x4_scaling(T_MATRIX_4x4* mat, T_FLOAT32 x, T_FLOAT32 y)
{
	D3DXMatrixScaling(mat, x, y, 1.0f);
}

void matrix4x4_rotation(T_MATRIX_4x4* mat, T_FLOAT32 x, T_FLOAT32 y, T_FLOAT32 z)
{
	//D3DXMatrixRotationX(mat, x);
	//D3DXMatrixRotationY(mat, y);
	D3DXMatrixRotationZ(mat, z);
}

T_MATRIX_4x4_STACK* matrix4x4_stack_create()
{	

}

void matrix4x4_stack_push(T_MATRIX_4x4_STACK* stack, T_MATRIX_4x4* matrix)
{

}

void matrix4x4_stack_pop(T_MATRIX_4x4_STACK* stack)
{

}

void matrix4x4_stack_delete(T_MATRIX_4x4_STACK* stack)
{

}

void matrix4x4_stack_apply(EntityDrawState* state)
{

}
