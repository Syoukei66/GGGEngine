#pragma once

class rcRenderBuffer;

class rcTexture : public GGAssetObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT_NAME(rcTexture);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcTexture> CreateFromFile(const char* path);
  static UniqueRef<rcTexture> Create(T_UINT16 width, T_UINT16 height, void* native_obj);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcTexture(T_UINT16 width, T_UINT16 height, void* native_obj);
  virtual ~rcTexture();

  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  GG_INLINE void* GetNativeObject()
  {
    return this->native_obj_;
  }
  GG_INLINE const void* GetNativeObject() const
  {
    return this->native_obj_;
  }

  GG_INLINE T_UINT16 GetWidth() const
  {
    return this->width_;
  }
  GG_INLINE T_UINT16 GetHeight() const
  {
    return this->height_;
  }
  GG_INLINE T_UINT16 GetTwoPoweredWidth() const
  {
    return two_powered_width_;
  }
  GG_INLINE T_UINT16 GetTwoPoweredHeight() const
  {
    return two_powered_height_;
  }
  GG_INLINE SharedRef<rcRenderBuffer> GetColorBuffer()
  {
    return this->color_buffer_;
  }
  GG_INLINE SharedRef<const rcRenderBuffer> GetColorBuffer() const
  {
    return this->color_buffer_;
  }

  // =================================================================
  // Data Members
  // =================================================================
protected:
  void* native_obj_;

  T_UINT16 width_;
  T_UINT16 height_;

  T_UINT16 two_powered_width_;
  T_UINT16 two_powered_height_;

  SharedRef<rcRenderBuffer> color_buffer_;
};