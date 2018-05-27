#pragma once

#include "Mesh.h"

namespace MeshFactory
{
namespace Plane
{

// UV1 �����Ŏw�肵��tile_count�𔽉f����UV
// UV2 Plane�S�̂̒��_���W��(0.0f ~ 1.0f)�ɃX�P�[�����O����UV
// UV3 UV1�Ɠ���
// UV4 UV1�Ɠ���

//
Mesh* Create(T_UINT32 format, T_FLOAT scale_x, T_FLOAT scale_y);
//
Mesh* Create(T_UINT32 format, T_FLOAT scale_x, T_FLOAT scale_y, T_UINT32 resolution_x, T_UINT32 resolution_y);
//
Mesh* Create(T_UINT32 format, T_FLOAT scale_x, T_FLOAT scale_y, T_UINT32 resolution_x, T_UINT32 resolution_y, T_FLOAT tile_count_x, T_FLOAT tile_count_y);

}
}
