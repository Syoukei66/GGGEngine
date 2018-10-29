#pragma once

/*!
 * @brief インデックスバッファの基底クラス
 * プラットフォーム毎の処理を派生クラス側で定義する
 */
class rcIndexBuffer : public GGObject
{
  // =================================================================
  // GGG Statement
  // =================================================================
  GG_OBJECT_NAME(rcIndexBuffer);

  // =================================================================
  // Factory Method
  // =================================================================
public:
  static UniqueRef<rcIndexBuffer> Create(T_UINT32 vertex_count, T_UINT32 polygon_count);

  // =================================================================
  // Constructor / Destructor
  // =================================================================
protected:
  rcIndexBuffer() {}
  virtual ~rcIndexBuffer() {}

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void Lock(void** dest) = 0;
  virtual void Unlock() = 0;
  virtual void SetIndices() const = 0;
  
  // =================================================================
  // Setter / Getter
  // =================================================================
public:
  virtual T_UINT32 GetVertexesCount() const = 0;
  virtual T_UINT32 GetPolygonCount() const = 0;

};