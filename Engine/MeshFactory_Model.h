#pragma once

#include "Mesh.h"
#include "ModelData.h"

namespace MeshFactory
{
namespace Model
{  
//TODO: ����Node���Ƀ��b�V�����쐬���Ă��邪�A
//      �p�t�H�[�}���X����/�C���X�^���V���O�ׂ̈�
//      ���_�o�b�t�@�Ȃǂ����L�������b�V����p�ӂ���K�v������B
Mesh* Create(ModelData* model, ModelNodeData* node, bool readonly);
}
}