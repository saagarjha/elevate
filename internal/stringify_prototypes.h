#ifndef ELVT_STRINGIFY_PROTOTYPES_H
#define ELVT_STRINGIFY_PROTOTYPES_H

#include "../iterator.h"
#include "../type_traits.h"
#include <iostream>

template <typename P1, typename P2>
std::ostream &operator<<(std::ostream &output, const std::pair<P1, P2> &pair);

template <typename... Ts>
std::ostream &operator<<(std::ostream &output, const std::tuple<Ts...> tuple);

template <typename Collection>
elvt::enable_if_t<!std::is_same<elvt::decay_t<elvt::collection_value_type<Collection &>>, char>::value, std::ostream &>
    &operator<<(std::ostream &output, const Collection &collection);

#endif /* ELVT_STRINGIFY_PROTOTYPES_H */
