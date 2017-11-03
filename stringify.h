#ifndef ELVT_STRINGIFY_H
#define ELVT_STRINGIFY_H

#include "iterator.h"
#include "string.h"
#include "type_traits.h"
#include <iostream>
#include <tuple>
#include <utility>

template <typename P1, typename P2>
inline std::ostream &operator<<(std::ostream &output, const std::pair<P1, P2> &pair) {
	output << "(" << pair.first << ", " << pair.second << ")";
	return output;
}

template <std::size_t N, typename... Ts>
struct tuple_printer {
	static void print(std::ostream &output, const std::tuple<Ts...> tuple) {
		tuple_printer<N - 1, Ts...>::print(output, tuple);
		output << ", ";
		output << std::get<N>(tuple);
	}
};

template <typename... Ts>
struct tuple_printer<0, Ts...> {
	static void print(std::ostream &output, const std::tuple<Ts...> tuple) {
		output << std::get<0>(tuple);
	}
};

template <typename... Ts>
inline std::ostream &operator<<(std::ostream &output, const std::tuple<Ts...> tuple) {
	output << "(";
	tuple_printer<std::tuple_size<decltype(tuple)>::value - 1, Ts...>::print(output, tuple);
	output << ")";
	return output;
}

template <typename Collection>
inline elvt::enable_if_t<!std::is_same<elvt::decay_t<elvt::collection_value_type<Collection &>>, char>::value, std::ostream &>
    &operator<<(std::ostream &output, const Collection &collection) {
	output << "[";
	elvt::join(output, collection, ", ");
	output << "]";
	return output;
}

#endif /* ELVT_STRINGIFY_H */
