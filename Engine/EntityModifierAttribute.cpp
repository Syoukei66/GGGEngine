#include "EntityModifierAttribute.h"
#include "GameObject2D.h"

//=========================================================================
// Translate
//=========================================================================
class EntityAttribute_Translate_X : public EntityModifierAttribute {
private:
  EntityAttribute_Translate_X() {}
public:
  static const EntityAttribute_Translate_X* GetInstance()
  {
    static const EntityAttribute_Translate_X self;
    return &self;
  }
public:
  virtual void SetValue(GameObject2D* entity, const T_FLOAT next) const override
  {
    entity->GetTransform()->SetX(next);
  }
  virtual T_FLOAT GetValue(GameObject2D* entity) const override
  {
    return entity->GetTransform()->GetX();
  }
};

class EntityAttribute_Translate_Y : public EntityModifierAttribute {
private:
  EntityAttribute_Translate_Y() {}
public:
  static const EntityAttribute_Translate_Y* GetInstance()
  {
    static const EntityAttribute_Translate_Y self;
    return &self;
  }
public:
  virtual void SetValue(GameObject2D* entity, const T_FLOAT next) const override
  {
    entity->GetTransform()->SetY(next);
  }
  virtual T_FLOAT GetValue(GameObject2D* entity) const override
  {
    return entity->GetTransform()->GetY();
  }
};

//=========================================================================
// Scale
//=========================================================================
class EntityAttribute_Scale_X : public EntityModifierAttribute {
private:
  EntityAttribute_Scale_X() {}
public:
  static const EntityAttribute_Scale_X* GetInstance()
  {
    static const EntityAttribute_Scale_X self;
    return &self;
  }
public:
  virtual void SetValue(GameObject2D* entity, const T_FLOAT next) const override
  {
    entity->GetTransform()->SetScaleX(next);
  }
  virtual T_FLOAT GetValue(GameObject2D* entity) const override
  {
    return entity->GetTransform()->GetScaleX();
  }
};

class EntityAttribute_Scale_Y : public EntityModifierAttribute {
private:
  EntityAttribute_Scale_Y() {}
public:
  static const EntityAttribute_Scale_Y* GetInstance()
  {
    static const EntityAttribute_Scale_Y self;
    return &self;
  }
public:
  virtual void SetValue(GameObject2D* entity, const T_FLOAT next) const override
  {
    entity->GetTransform()->SetScaleY(next);
  }
  virtual T_FLOAT GetValue(GameObject2D* entity) const override
  {
    return entity->GetTransform()->GetScaleY();
  }
};

//=========================================================================
// Rotation
//=========================================================================
class EntityAttribute_Rotation : public EntityModifierAttribute {
private:
  EntityAttribute_Rotation() {}
public:
  static const EntityAttribute_Rotation* GetInstance()
  {
    static const EntityAttribute_Rotation self;
    return &self;
  }
public:
  virtual void SetValue(GameObject2D* entity, const T_FLOAT next) const override
  {
    entity->GetTransform()->SetRotation(next);
  }
  virtual T_FLOAT GetValue(GameObject2D* entity) const override
  {
    return entity->GetTransform()->GetRotation();
  }
};

//=========================================================================
// Color
//=========================================================================
class EntityAttribute_Color_R : public EntityModifierAttribute {
private:
  EntityAttribute_Color_R() {}
public:
  static const EntityAttribute_Color_R* GetInstance()
  {
    static const EntityAttribute_Color_R self;
    return &self;
  }
public:
  virtual void SetValue(GameObject2D* entity, const T_FLOAT next) const override
  {
    entity->GetRenderer()->GetMaterial()->GetDiffuse().SetRed(next > 1.0f ? 1.0f : next);
  }
  virtual T_FLOAT GetValue(GameObject2D* entity) const override
  {
    return entity->GetRenderer()->GetMaterial()->GetDiffuse().GetRed();
  }
};

class EntityAttribute_Color_G : public EntityModifierAttribute {
private:
  EntityAttribute_Color_G() {}
public:
  static const EntityAttribute_Color_G* GetInstance()
  {
    static const EntityAttribute_Color_G self;
    return &self;
  }
public:
  virtual void SetValue(GameObject2D* entity, const T_FLOAT next) const override
  {
    entity->GetRenderer()->GetMaterial()->GetDiffuse().SetGreen(next > 1.0f ? 1.0f : next);
  }
  virtual T_FLOAT GetValue(GameObject2D* entity) const override
  {
    return entity->GetRenderer()->GetMaterial()->GetDiffuse().GetGreen();
  }
};

class EntityAttribute_Color_B : public EntityModifierAttribute {
private:
  EntityAttribute_Color_B() {}
public:
  static const EntityAttribute_Color_B* GetInstance()
  {
    static const EntityAttribute_Color_B self;
    return &self;
  }
public:
  virtual void SetValue(GameObject2D* entity, const T_FLOAT next) const override
  {
    entity->GetRenderer()->GetMaterial()->GetDiffuse().SetBlue(next > 1.0f ? 1.0f : next);
  }
  virtual T_FLOAT GetValue(GameObject2D* entity) const override
  {
    return entity->GetRenderer()->GetMaterial()->GetDiffuse().GetBlue();
  }
};

class EntityAttribute_Color_A : public EntityModifierAttribute {
private:
  EntityAttribute_Color_A() {}
public:
  static const EntityAttribute_Color_A* GetInstance()
  {
    static const EntityAttribute_Color_A self;
    return &self;
  }
public:
  virtual void SetValue(GameObject2D* entity, const T_FLOAT next) const override
  {
    entity->GetRenderer()->GetMaterial()->GetDiffuse().SetAlpha(next > 1.0f ? 1.0f : next);
  }
  virtual T_FLOAT GetValue(GameObject2D* entity) const override
  {
    return entity->GetRenderer()->GetMaterial()->GetDiffuse().GetAlpha();
  }
};

static const EntityModifierAttribute* ATTRIBUTE_LIST[EntityModifierAttribute::MODIFIER_ATTR_DATANUM] =
{
  EntityAttribute_Translate_X::GetInstance(),
  EntityAttribute_Translate_Y::GetInstance(),
  EntityAttribute_Scale_X::GetInstance(),
  EntityAttribute_Scale_Y::GetInstance(),
  EntityAttribute_Rotation::GetInstance(),
  EntityAttribute_Color_R::GetInstance(),
  EntityAttribute_Color_G::GetInstance(),
  EntityAttribute_Color_B::GetInstance(),
  EntityAttribute_Color_A::GetInstance(),
};

const EntityModifierAttribute* EntityModifierAttribute::Create(T_UINT8 id)
{
  return ATTRIBUTE_LIST[id];
}
