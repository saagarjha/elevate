#ifndef ELVT_ITERATOR_H
#define ELVT_ITERATOR_H

#include "version.h"
#include <cstddef>
#include <iterator>

namespace elvt {

template <typename Collection>
using collection_value_type = decltype(*std::begin(std::declval<Collection>()));

template <typename Collection>
using collection_iterator_type = decltype(std::begin(std::declval<Collection>()));

template <typename Collection>
inline auto rbegin(Collection &collection) -> decltype(collection.rbegin()) {
	return collection.rbegin();
}

template <typename Collection>
inline auto rbegin(const Collection &collection) -> decltype(collection.rbegin()) {
	return collection.rbegin();
}

template <typename Collection>
inline auto crbegin(const Collection &collection) -> decltype(collection.rbegin()) {
	return collection.rbegin();
}

template <typename Collection>
inline auto rend(Collection &collection) -> decltype(collection.rend()) {
	return collection.rend();
}

template <typename Collection>
inline auto rend(const Collection &collection) -> decltype(collection.rend()) {
	return collection.rend();
}

template <typename Collection>
inline auto crend(const Collection &collection) -> decltype(collection.rend()) {
	return collection.rend();
}

template <typename T, std::size_t size>
inline std::reverse_iterator<T *> rbegin(T (&collection)[size]) {
	return std::reverse_iterator<T *>(collection + size);
}

template <typename T, std::size_t size>
inline std::reverse_iterator<T *> rend(T (&collection)[size]) {
	return std::reverse_iterator<T *>(collection);
}

#if CXX_VERSION >= CXX_14
template <typename Collection>
using collection_reverse_iterator_type = decltype(std::rbegin(std::declval<Collection>()));
#else
template <typename Collection>
using collection_reverse_iterator_type = decltype(rbegin(std::declval<Collection>()));
#endif

} // namespace elvt

#endif /* ELVT_ITERATOR_H */
