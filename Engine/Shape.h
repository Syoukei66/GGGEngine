#ifndef HAL_ENGINE_ENTITY_SHAPE_H_
#define HAL_ENGINE_ENTITY_SHAPE_H_

#include "GameObject2D.h"
#include "IVertexBufferObject.h"

class Shape : public GameObject2D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  virtual ~Shape() {}

  // =================================================================
  // Methods for/from SuperClass/Interfaces
  // =================================================================
public:
  virtual void Init() override;
  virtual void Update() override;

  // =================================================================
  // Method
  // =================================================================
public:
  virtual void OnVertexCoordChanged();

  // =================================================================
  // setter/getter
  // =================================================================
public:
  //VBOのインスタンスは各サブクラスで保持。
  //ただし解放、初期化などの共通処理はこのメソッドを通してShapeクラスが行う。
  virtual IVertexBufferObject* GetVbo() const = 0;
  
  void SetSize(const TSizef& size);
  void SetSize(T_FLOAT width, T_FLOAT height);
  inline const TSizef& GetSize() const
  {
    return this->size_;
  }

  void SetWidth(T_FLOAT width);
  inline T_FLOAT GetWidth() const
  {
    return this->size_.width;
  }
  inline T_FLOAT GetWidthScaled() const
  {
    return this->size_.width * this->GetTransform()->GetScaleX();
  }

  void SetHeight(T_FLOAT height);
  inline T_FLOAT GetHeight() const
  {
    return this->size_.height;
  }
  inline T_FLOAT GetHeightScaled() const
  {
    return this->size_.height * this->GetTransform()->GetScaleY();
  }

  // =================================================================
  // Data Member
  // =================================================================
private:
  TSizef size_;
};

#endif//HAL_ENGINE_ENTITY_SHAPE_H_
