#include "Renderer.h"

void Renderer::SetMaterial(Material& material)
{
  if (this->materials_.size() == 0)
  {
    this->materials_.push_back(nullptr);
  }
  this->materials_[0] = &material;
}
