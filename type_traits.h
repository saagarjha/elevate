#ifndef ELVT_TYPE_TRAITS_H
#define ELVT_TYPE_TRAITS_H

#include <tuple>
#include <type_traits>

namespace elvt {

template <class T>
using remove_reference_t = typename std::remove_reference<T>::type;

template <class T>
using decay_t = typename std::decay<T>::type;

template <bool B, class T = void>
using enable_if_t = typename std::enable_if<B, T>::type;

template <std::size_t N, typename... Ts>
using extract_nth_t = typename std::tuple_element<N, std::tuple<Ts...>>::type;

} // namespace elvt

#endif /* ELVT_TYPE_TRAITS_H */
