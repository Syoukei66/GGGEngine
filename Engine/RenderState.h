#pragma once

#include "NativeType.h"
#include "RenderPipeline.h"
#include "GraphicsConstants.h"

#include "Matrix4x4.h"
#include "Viewport.h"

class Renderer;

class RenderState
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  RenderState();
  virtual ~RenderState();

  // =================================================================
  // Method
  // =================================================================
public:
  void Init();
  void Draw();
  void AddRenderer(const Renderer* renderer);
  void AddRenderers(std::vector<Renderer*>::iterator& begin, std::vector<Renderer*>::iterator& end);
  void RemoveRenderer(const Renderer* renderer);
  void RemoveRenderers(std::vector<Renderer*>::iterator& begin, std::vector<Renderer*>::iterator& end);

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  inline void SetEnabled(bool enabled)
  {
    this->enabled_ = enabled;
  }
  inline bool IsEnabled() const
  {
    return this->enabled_;
  }

  inline void AddTargetLayerId(T_UINT8 layer_id)
  {
    layer_state_ |= 1 << layer_id;
  }
  inline void AddAllTargetLayerIds()
  {
    layer_state_ = 0xffffffff;
  }
  inline void RemoveTargetLayerId(T_UINT8 layer_id)
  {
    layer_state_ &= ~(1 << layer_id);
  }
  inline void ClearTargetLayerIds()
  {
    layer_state_ = 0x00000000;
  }
  inline bool IsTargetedLayer(T_UINT8 layer_id)
  {
    return layer_state_ & (1 << layer_id);
  }

  inline void SetViewport(const Viewport& viewport)
  {
    this->viewport_ = viewport;
  }
  inline const Viewport& GetViewport() const
  {
    return this->viewport_;
  }

  inline void SetWorldMatrix(const Matrix4x4& world)
  {
    this->world_matrix_ = world;
  }
  inline const Matrix4x4& GetWorldMatrix() const
  {
    return this->world_matrix_;
  }

  inline void SetViewMatrix(const Matrix4x4& view)
  {
    this->view_matrix_ = view;
  }
  inline const Matrix4x4& GetViewMatrix() const
  {
    return this->view_matrix_;
  }

  inline void SetProjectionMatrix(const Matrix4x4& proj)
  {
    this->projection_matrix_ = proj;
  }
  inline const Matrix4x4& getProjectionMatrix() const
  {
    return this->projection_matrix_;
  }

  inline void SetColorBuffer(RenderBuffer* color_buffer)
  {
    this->color_buffer_ = color_buffer;
  }
  inline RenderBuffer* GetColorBuffer()
  {
    return this->color_buffer_;
  }
  inline const RenderBuffer* GetColorBuffer() const
  {
    return this->color_buffer_;
  }

  inline void SetDepthStencilBuffer(RenderBuffer* depth_stencil_buffer)
  {
    this->depth_stencil_buffer_ = depth_stencil_buffer_;
  }
  inline RenderBuffer* GetDepthStencilBuffer()
  {
    return this->depth_stencil_buffer_;
  }
  inline const RenderBuffer* GetDepthStencilBuffer() const
  {
    return this->depth_stencil_buffer_;
  }

  inline void SetClearFlag(bool clear_flag)
  {
    this->clear_flag_ = clear_flag;
  }
  inline bool GetClearFlag() const
  {
    return this->clear_flag_;
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  bool enabled_;

  Viewport viewport_;
  //TODO:�e�}�g���b�N�X����������邩
  Matrix4x4 world_matrix_;
  Matrix4x4 view_matrix_;
  Matrix4x4 projection_matrix_;

  RenderBuffer* color_buffer_;
  RenderBuffer* depth_stencil_buffer_;
  bool clear_flag_;

  //�`��Ώۂ̑������w�肷��RenderAttribute  �� RenderQueue���ɐݒ�
  //�`��Ώۂ̃t�B���^�����O������Layer      �� RenderState���ɐݒ�
  //�`�揇���̐�����s��Index                �� Renderer���ɐݒ�

  //Renderer��Enabled���ύX���ꂽ
  //Renderer��Material���ύX���ꂽ
  //Renderer��RenderAttribute���ύX���ꂽ�@�� RenderQueue�̍č\�z�@���ׁF��
  //Renderer��Layer���ύX���ꂽ�@�� �J�����O���Ď��s�@���ׁF��
  //Renderer��Index���ύX���ꂽ�@�� �\�[�g���Ď��s�@���ׁF��

  T_UINT32 layer_state_;
  RenderPipeline* pipeline_[Graphics::R_ATTR_DATANUM];
};
