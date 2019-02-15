#pragma once

class GGObject;

/*!
 * @brief SFINAEの為にポインタの型チェックに用いる
 */
template <class To_, class From_>
using GGRefConvertible = std::enable_if_t<
  std::is_same<From_, To_>::value ||
  std::is_base_of<To_, From_>::value ||
  std::is_convertible<From_, To_>::value,
  std::nullptr_t
>;

/*!
 * @brief SFINAEの為にポインタの型チェックに用いる
 */
template <class From_, class To_>
using GGRefStaticCastbale = std::enable_if_t<
  std::is_same<From_, To_>::value ||
  std::is_base_of<To_, From_>::value ||
  std::is_convertible<From_, To_>::value,
  std::nullptr_t
>;

/*!
 * @brief SFINAEの為にポインタの型チェックに用いる
 */
template <class Obj_>
using GGIsObject = std::enable_if_t<
    std::is_same<Obj_, GGObject>::value ||
    std::is_base_of<GGObject, Obj_>::value ||
    std::is_convertible<Obj_, GGObject>::value,
  std::nullptr_t
>;
