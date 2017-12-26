#ifndef HAL_ENGINE_SHAPE_SPRITE_VBO_SPRITEVERTEXBUFFEROBJECT_H
#define HAL_ENGINE_SHAPE_SPRITE_VBO_SPRITEVERTEXBUFFEROBJECT_H

#include "IVertexBufferObject.h"
#include "ITextureRegion.h"

class Shape;

// TODO: 2D�̃I�u�W�F�N�g��VertexBuffer��IndexBuffer���g�p���ĕ`�悷��悤�ɐ؂�ւ���
//       ����width, height�̕ύX�𒸓_���W�̕ύX�ł͂Ȃ��A�X�P�[�����O�ŕ\��
//       �X�P�[�����O�Ɋւ��ẮA�I�u�W�F�N�g�̑傫���p�̃X�P�[���ƁA
//       �����Ǝq�I�u�W�F�N�g�S�̂ɂ�����X�P�[���̂Q��ނ�p�ӂ�����������̂�������Ȃ�
class SpriteVertexBufferObject : public IVertexBufferObject
{

  enum SpriteVertexIndexes
  {
    V_VERTEX_V0,
    V_VERTEX_V1,
    V_VERTEX_V2,
    V_VERTEX_V3,
    V_VERTEX_MAX,
  };

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static SpriteVertexBufferObject* Create();

  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  virtual ~SpriteVertexBufferObject() {};
protected:
  SpriteVertexBufferObject();

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
protected:
  virtual void OnInit() override;
  virtual void OnUpdateCoord(GameObject* entity) override;

public:
  virtual T_UINT32 GetVertexesCount() const override;
  virtual const void* GetVertexes() const override;
  virtual const T_UINT16* GetIndexes() const override;
  virtual INativeProcess_Graphics::PrimitiveType GetPrimitiveType() override;
  virtual INativeProcess_Graphics::VertexType GetVertexType() override;

  // =================================================================
  // Method
  // =================================================================
public:
  void OnVertexUvDirty();
  virtual void UpdateTexture(Shape* entity, ITextureRegion* region);

  // =================================================================
  // Data Member
  // =================================================================
private:
  bool vertex_uv_dirty_;
  SpriteVertex vertexes_[V_VERTEX_MAX];
};

#endif//HAL_ENGINE_SHAPE_SPRITE_VBO_SPRITEVERTEXBUFFEROBJECT_H