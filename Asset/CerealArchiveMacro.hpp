#pragma once

//�}�N��������̂Ńw�b�_�[���ŃC���N���[�h���s��Ȃ�����
//����Archive�t�@�C���ɂ�������

#define SAFE_NEW(var, value) if (!var)\
{\
  var = new value();\
}
