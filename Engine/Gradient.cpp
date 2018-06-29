#include "Gradient.h"

Gradient::Gradient()
  : id_max_(0)
  , table_()
{
}

void Gradient::Reset()
{
  this->id_max_ = 0;
  this->table_.clear();
}

Gradient::GradientTable& Gradient::AddColor(T_FLOAT location, const Color4F& color)
{
  this->table_.emplace_back(this->id_max_, location, color);
  GradientTable& ret = this->table_.back();
  std::sort(this->table_.begin(), this->table_.end(), [](const GradientTable& a, const GradientTable& b) {
    return a.location < b.location;
  });
  ++this->id_max_;
  return ret;
}

void Gradient::RemoveColor(const GradientTable& table)
{
  this->RemoveColor(table.id);
}

void Gradient::RemoveColor(T_UINT8 id)
{
  for (std::vector<GradientTable>::iterator itr = this->table_.begin(), end = this->table_.end(); itr != end; ++itr)
  {
    if ((*itr).id == id)
    {
      this->table_.erase(itr);
      return;
    }
  }
}

Color4F Gradient::Evaluate(T_FLOAT time) const
{
  GradientTable prev = this->table_.front();
  for (const GradientTable& table : this->table_)
  {
    if (time < table.location)
    {
      if (prev.id == table.id)
      {
        return table.color;
      }
      return Color4F::Lerp(
        prev.color, table.color,
        (time - prev.location) / (table.location - prev.location)
      );
    }
    prev = table;
  }
  return this->table_.back().color;
}
