#include "Collider3D.h"
#include "Collision3D.h"

// =================================================================
// Methods
// =================================================================
Collider3D::Collider3D(GameObject3D* entity)
  : entity_(entity)
{
}

void Collider3D::Prepare()
{
  this->position_ = this->entity_->GetTransform()->GetWorldPosition();
}

bool Collider3D::RoughCheck(const Collider3D& other)
{
  return Collision::Sphare_Sphare(
    this->GetPosition(),
    this->GetBoundRadius(),
    other.GetPosition(),
    other.GetBoundRadius()
    );
}

// =================================================================
// Sphare
// =================================================================
Collider3D_Sphare::Collider3D_Sphare(GameObject3D* entity)
  : Collider3D(entity)
{
}

bool Collider3D_Sphare::Collision(Collider3D_Sphare& other)
{
  this->Prepare();
  other.Prepare();
  Collision::Sphare_Sphare(
    this->GetPosition(),
    this->GetBoundRadius(),
    other.GetPosition(),
    other.GetBoundRadius()
  );
}

//bool Collider3D_Sphare::Collision(const Collider3D_Capsule & other)
//{
//  return false;
//}

T_FLOAT Collider3D_Sphare::GetBoundRadius() const
{
  return this->radius_;
}
