#pragma once

#include "RenderState.h"

class RenderPipeline
{
public:
  /*
     �J�����O�����p�����[�^�[
     �@�ERenderer
       �E�\�[�g�����ƂȂ�f�[�^

     �J�����O���s�p�����[�^�[
     �@�ERenderer
       �E�J�����O���s���������@�ˁ@�J�����O�͒��O�̎��s�����Ŏ��s����\���������̂�

  �@�P�D�`�惊�X�g�̃��X�^���C�Y����

      ����ƃJ�����O�ׂ̈ɃL���b�V��������Ă�������
 
      �J�����O����/���s���X�g�@�ˁ@�����_���̐������̈���m��

      �����_���̍X�V��T�m�@�ˁ@�X�V����Ȃ��ꍇ�̓J�����O���X�L�b�v
    �@  �P�������_�����X�V����Ȃ������ꍇ�̓J�����O��������X�L�b�v�����ڕ`��

      �J�����O����
  �@    [�J�����O���s���X�g]�ł̃J�����O�@�ˁ@�����������[�ǉ��J�����O�������X�g]��
  �@    [�J�����O�������X�g]�ł̃J�����O�@�ˁ@���s�������[�ǉ��J�����O���s���X�g]��
      ���񏈗����s����̂ł�

      [�ǉ��J�����O�������X�g]�̓��e��[�J�����O�������X�g]�֒ǉ�
      [�ǉ��J�����O���s���X�g]�̓��e��[�J�����O���s���X�g]�֒ǉ�

    �Q�D�`�揈��
      
      ���_�C�i�~�b�N�����W�iHDR�j vs ��_�C�i�~�b�N�����W�iLDR�j
      ���j�A���[�N�t���[ vs �K���}���[�N�t���[
      �}���`�T���v���A���`�G�C���A�V���O vs �|�X�g�v���Z�X�A���`�G�C���A�V���O
      �����x�[�X�����_�����O�}�e���A�� vs �ʏ�̃}�e���A��
      ���C�e�B���O���� vs ���C�e�B���O�Ȃ�
      ���C�e�B���O�̎�@
      �V���h�[�C���O�̎�@
      
      �\�[�g����
      ���C�g�v���[�u�⃉�C�g�}�b�v�̐ݒ�
      �o�b�`���O��C���X�^���V���O�̎g�p�L��
      ���݂̃h���[�R�[���ɂǂ̃V�F�[�_�[�p�X���g�p���邩

      �Ȃǂ��L�q

      [�J�����O�������X�g]���\�[�g��������Ƀ\�[�g
      [�J�����O�������X�g]�ŕ`����s��
      
    �R�D�|�X�g�v���Z�X
      
      �����_�[�^�[�Q�b�g��RenderState����擾�\
      RenderTarget��nullptr�̏ꍇ�͖����������͌x��


  */
protected:
  enum FrustumCullingFailureKind
  {
    CULL_FRUSUTUM_FAILED_NEAR,
    CULL_FRUSUTUM_FAILED_LEFT,
    CULL_FRUSUTUM_FAILED_RIGHT,
    CULL_FRUSUTUM_FAILED_TOP,
    CULL_FRUSUTUM_FAILED_BOTTOM,
    CULL_FRUSUTUM_FAILED_FAR,
    CULL_FRUSUTUM_SUCCESS,
  };

  struct SuccessCache
  {
    Renderer* renderer_;
    T_FLOAT distance_;
  };

  struct FailureCache
  {
    Renderer* renderer_;
    bool enabled_failed_;
    bool material_failed_;
    bool layer_id_failed_;
    FrustumCullingFailureKind fustum_failed_;
    bool occlusion_failed_;
  };

private:
  std::vector<SuccessCache> successes_;
  std::vector<FailureCache> failures_;

};
