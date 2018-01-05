#pragma once

#include "GameComponent.h"
#include "Geometry.h"

class Collider3D_Sphare;
class Collider3D_Capsule;

class Collider3D : public GameComponent
{
public:
  virtual TVec3f& BoundPosition() = 0;
  virtual T_FLOAT BoundRadius() = 0;
  bool RoughCheck(const Collider3D& other);

public:
  virtual bool Collision(const Collider3D_Sphare& other) = 0;
  virtual bool Collision(const Collider3D_Capsule& other) = 0;

public:
  const T_UINT8 kind;
};

// =================================================================
// Sphare
// =================================================================
class Collider3D_Sphare : public Collider3D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Collider3D_Sphare();

  // =================================================================
  // Setter / Getter
  // =================================================================
private:

};

// =================================================================
// Capsule
// =================================================================
class Collider3D_Capsule : public Collider3D
{
  // =================================================================
  // Constructor / Destructor
  // =================================================================
public:
  Collider3D_Capsule();

  // =================================================================
  // Setter / Getter
  // =================================================================
private:

};

