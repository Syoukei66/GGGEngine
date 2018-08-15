#pragma once

#include "../Core/NativeType.h"
#include "../Core/Geometry.h"

//�����蔻��̏����̓p�t�H�[�}���X�ɑ傫���ւ��̂�
//Engine���ł͊Ǘ�/�������s��Ȃ�
//����ɉ��Z�ׂ̈̊֐��ƃC���^�[�t�F�[�X��p�ӂ���̂ŁA
//�����𗘗p���ăQ�[�����ɊǗ�/�������悤

class ICollider2D
{
public:
  //�Փ˔���Ɏg�p������W����o�E���f�B���O�{�b�N�X��
  //
  //���̎��_��false���A���Ă����ꍇ�A�Փ˔���v�Z���s�킸�A
  //����̌��ʂ�false�Ƃ���B
  virtual bool Prepare() = 0;

  //�����蔻�菈��������������ׂɕK�v
  //���G�ȓ����蔻�肪�K�v�ȏꍇ�́A
  //���炩���߉~�ł̃��t�`�F�b�N���s��
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
