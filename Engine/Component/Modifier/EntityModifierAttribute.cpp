#include "EntityModifierAttribute.h"
#include <Engine/GameObject/GameObject.h>

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
  virtual void SetValue(GameObject* entity, const T_FLOAT next) const override
  {
    entity->GetTransform()->SetX(next);
  }
  virtual T_FLOAT GetValue(GameObject* entity) const override
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
  virtual void SetValue(GameObject* entity, const T_FLOAT next) const override
  {
    entity->GetTransform()->SetY(next);
  }
  virtual T_FLOAT GetValue(GameObject* entity) const override
  {
    return entity->GetTransform()->GetY();
  }
};

class EntityAttribute_Translate_Z : public EntityModifierAttribute {
private:
  EntityAttribute_Translate_Z() {}
public:
  static const EntityAttribute_Translate_Z* GetInstance()
  {
    static const EntityAttribute_Translate_Z self;
    return &self;
  }
public:
  virtual void SetValue(GameObject* entity, const T_FLOAT next) const override
  {
    entity->GetTransform()->SetZ(next);
  }
  virtual T_FLOAT GetValue(GameObject* entity) const override
  {
    return entity->GetTransform()->GetZ();
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
  virtual void SetValue(GameObject* entity, const T_FLOAT next) const override
  {
    entity->GetTransform()->SetScaleX(next);
  }
  virtual T_FLOAT GetValue(GameObject* entity) const override
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
  virtual void SetValue(GameObject* entity, const T_FLOAT next) const override
  {
    entity->GetTransform()->SetScaleY(next);
  }
  virtual T_FLOAT GetValue(GameObject* entity) const override
  {
    return entity->GetTransform()->GetScaleY();
  }
};

class EntityAttribute_Scale_Z : public EntityModifierAttribute {
private:
  EntityAttribute_Scale_Z() {}
public:
  static const EntityAttribute_Scale_Z* GetInstance()
  {
    static const EntityAttribute_Scale_Z self;
    return &self;
  }
public:
  virtual void SetValue(GameObject* entity, const T_FLOAT next) const override
  {
    entity->GetTransform()->SetScaleZ(next);
  }
  virtual T_FLOAT GetValue(GameObject* entity) const override
  {
    return entity->GetTransform()->GetScaleZ();
  }
};

//=========================================================================
// Rotation
//=========================================================================
class EntityAttribute_Rotation_X : public EntityModifierAttribute {
private:
  EntityAttribute_Rotation_X() {}
public:
  static const EntityAttribute_Rotation_X* GetInstance()
  {
    static const EntityAttribute_Rotation_X self;
    return &self;
  }
public:
  virtual void SetValue(GameObject* entity, const T_FLOAT next) const override
  {
    entity->GetTransform()->SetEularX(next);
  }
  virtual T_FLOAT GetValue(GameObject* entity) const override
  {
    return entity->GetTransform()->GetEularX();
  }
};

class EntityAttribute_Rotation_Y : public EntityModifierAttribute {
private:
  EntityAttribute_Rotation_Y() {}
public:
  static const EntityAttribute_Rotation_Y* GetInstance()
  {
    static const EntityAttribute_Rotation_Y self;
    return &self;
  }
public:
  virtual void SetValue(GameObject* entity, const T_FLOAT next) const override
  {
    entity->GetTransform()->SetEularY(next);
  }
  virtual T_FLOAT GetValue(GameObject* entity) const override
  {
    return entity->GetTransform()->GetEularY();
  }
};

class EntityAttribute_Rotation_Z : public EntityModifierAttribute {
private:
  EntityAttribute_Rotation_Z() {}
public:
  static const EntityAttribute_Rotation_Z* GetInstance()
  {
    static const EntityAttribute_Rotation_Z self;
    return &self;
  }
public:
  virtual void SetValue(GameObject* entity, const T_FLOAT next) const override
  {
    entity->GetTransform()->SetEularZ(next);
  }
  virtual T_FLOAT GetValue(GameObject* entity) const override
  {
    return entity->GetTransform()->GetEularZ();
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
  virtual void SetValue(GameObject* entity, const T_FLOAT next) const override
  {
    //entity->GetRenderer()->GetMaterial()->GetMainColor().r = next > 1.0f ? 1.0f : next;
  }
  virtual T_FLOAT GetValue(GameObject* entity) const override
  {
    //return entity->GetRenderer()->GetMaterial()->GetMainColor().r;
    return 1.0f;
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
  virtual void SetValue(GameObject* entity, const T_FLOAT next) const override
  {
    //entity->GetRenderer()->GetMaterial()->GetMainColor().g = next > 1.0f ? 1.0f : next;
  }
  virtual T_FLOAT GetValue(GameObject* entity) const override
  {
    //return entity->GetRenderer()->GetMaterial()->GetMainColor().g;
    return 1.0f;
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
  virtual void SetValue(GameObject* entity, const T_FLOAT next) const override
  {
    //entity->GetRenderer()->GetMaterial()->GetMainColor().b = next > 1.0f ? 1.0f : next;
  }
  virtual T_FLOAT GetValue(GameObject* entity) const override
  {
    //return entity->GetRenderer()->GetMaterial()->GetMainColor().b;
    return 1.0f;
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
  virtual void SetValue(GameObject* entity, const T_FLOAT next) const override
  {
    //entity->GetRenderer()->GetMaterial()->GetMainColor().a = next > 1.0f ? 1.0f : next;
  }
  virtual T_FLOAT GetValue(GameObject* entity) const override
  {
    //return entity->GetRenderer()->GetMaterial()->GetMainColor().a;
    return 1.0f;
  }
};

static const EntityModifierAttribute* ATTRIBUTE_LIST[EntityModifierAttribute::MODIFIER_ATTR_DATANUM] =
{
  EntityAttribute_Translate_X::GetInstance(),
  EntityAttribute_Translate_Y::GetInstance(),
  EntityAttribute_Translate_Z::GetInstance(),
  EntityAttribute_Scale_X::GetInstance(),
  EntityAttribute_Scale_Y::GetInstance(),
  EntityAttribute_Scale_Z::GetInstance(),
  EntityAttribute_Rotation_X::GetInstance(),
  EntityAttribute_Rotation_Y::GetInstance(),
  EntityAttribute_Rotation_Z::GetInstance(),
  EntityAttribute_Color_R::GetInstance(),
  EntityAttribute_Color_G::GetInstance(),
  EntityAttribute_Color_B::GetInstance(),
  EntityAttribute_Color_A::GetInstance(),
};

const EntityModifierAttribute* EntityModifierAttribute::Create(T_UINT8 id)
{
  return ATTRIBUTE_LIST[id];
}
