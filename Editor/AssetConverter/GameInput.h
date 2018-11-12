#pragma once

//GameInput
//�Q�[���̓��͂��`����
namespace GameInput
{

//�V�����{�^�����͂��`���������͂��̗񋓌^�ɒǉ����Ă���
//�ǉ������ꍇ�Acpp�t�@�C�����Ƀ{�^���̏ڍׂ��`���Ă���
enum
{
  X_AXIS, //X������
  Y_AXIS, //Y������

  MOUSE_CLICK_L, //�}�E�X�{�^������
  MOUSE_CLICK_C, //�}�E�X�{�^������
  MOUSE_CLICK_R, //�}�E�X�{�^������
  MOUSE_SCREEN_X, //�}�E�X���W�w
  MOUSE_SCREEN_Y, //�}�E�X���W�x
  MOUSE_MOVE_X, //�}�E�X���͂w
  MOUSE_MOVE_Y, //�}�E�X���͂x
  MOUSE_MOVE_Z, //�}�E�X�z�C�[��

  GAME_INPUT_DATANUM, //�����͐G��Ȃ�
};

//�����͐G��Ȃ�
const InputEntity* GetInputEntities();

}