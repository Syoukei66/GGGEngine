#pragma once

#include "Renderer.h"
#include "NativeVertexBuffer.h"
#include "NativeIndexBuffer.h"

class RenderState;
class CommandBuffer;

/*
    �`��̍ŏ��P��
    RenderCommand�P���`��P��\���B
    ���I�o�b�`���O�ׂ̈�
    �������_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�A�}�e���A�����g�p���Ă���`���
    �ɗ͂܂Ƃ߂��悤�ɂ���
    �܂��ACommandBuffer���̕`�揇�\�[�g��t�B���^�����O�Ȃǂ̎��s���Œ���ɗ}�������̂ŁA
    ���ꂼ��L���b�V�������悤�ɂ��Ă����B
*/

class RenderCommand
{
protected:
  RenderCommand(CommandBuffer* buffer);
  virtual ~RenderCommand();

public:
  void Release();

public:
  //�`��̊�ƂȂ郏�[���h�s��
  virtual const Matrix4x4& GetWorldMatrix() = 0;
  //�`��^�C�v�i����/�s����/�\�ʉ��g�U�Ȃǁj�B�p�C�v���C���̑I����t�B���^�����O�Ɏg�p�B
  virtual T_UINT8 GetAttributeId() = 0;
  //�t�B���^�����O�Ɏg�p����p�����[�^
  virtual T_UINT8 GetLayerId() = 0;
  //�J�����O�Ɏg�p����p�����[�^
  virtual T_UINT8 GetIndexId() = 0;

  virtual Material* GetMaterial() = 0;
  virtual INativeVertexBuffer* GetVertexBuffer() = 0;
  virtual INativeIndexBuffer* GetIndexBuffer() = 0;

private:
  CommandBuffer* buffer_;

};

