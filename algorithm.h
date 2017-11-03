#ifndef ELVT_ALGORITHM_H
#define ELVT_ALGORITHM_H

#include "iterator.h"
#include "type_traits.h"
#include "version.h"
#include <algorithm>
#include <functional>
#include <iterator>

namespace elvt {

#define ESC(...) __VA_ARGS__

#define RANGE_OF(collection) std::begin(collection), std::end(collection)

#define ELEVATE_FULL_COLLECTION_FORWARDER(func, return_type)                 \
	template <typename Collection, typename... Parameters>                   \
	return_type func(Collection &&collection, Parameters &&... parameters) { \
		return std::func(                                                    \
		    RANGE_OF(std::forward<Collection>(collection)),                  \
		    std::forward<Parameters>(parameters)...);                        \
	}

#define ELEVATE_FULL_2_COLLECTION_FORWARDER(func, return_type)                                            \
	template <typename Collection1, typename Collection2, typename... Parameters>                         \
	return_type func(Collection1 &&collection1, Collection2 &&collection2, Parameters &&... parameters) { \
		return std::func(                                                                                 \
		    RANGE_OF(std::forward<Collection1>(collection1)),                                             \
		    RANGE_OF(std::forward<Collection2>(collection2)),                                             \
		    std::forward<Parameters>(parameters)...);                                                     \
	}

#define ITERATOR_DIFFERENCE_TYPE(type) std::iterator_traits<type>::difference_type

ELEVATE_FULL_COLLECTION_FORWARDER(all_of, bool)
ELEVATE_FULL_COLLECTION_FORWARDER(any_of, bool)
ELEVATE_FULL_COLLECTION_FORWARDER(none_of, bool)
ELEVATE_FULL_COLLECTION_FORWARDER(for_each, ESC(extract_nth_t<0, Parameters...>))
#if CXX_VERSION >= CXX_17
ELEVATE_FULL_COLLECTION_FORWARDER(for_each_n, collection_iterator_type<const Collection &>)
#endif
ELEVATE_FULL_COLLECTION_FORWARDER(count, typename ITERATOR_DIFFERENCE_TYPE(collection_iterator_type<const Collection &>))
ELEVATE_FULL_COLLECTION_FORWARDER(count_if, typename ITERATOR_DIFFERENCE_TYPE(collection_iterator_type<const Collection &>))
ELEVATE_FULL_COLLECTION_FORWARDER(mismatch, ESC(std::pair<collection_iterator_type<const Collection &>, ESC(extract_nth_t<0, Parameters...>)>))
ELEVATE_FULL_COLLECTION_FORWARDER(find, collection_iterator_type<const Collection &>)
ELEVATE_FULL_COLLECTION_FORWARDER(find_if, collection_iterator_type<const Collection &>)
ELEVATE_FULL_COLLECTION_FORWARDER(find_if_not, collection_iterator_type<const Collection &>)
ELEVATE_FULL_2_COLLECTION_FORWARDER(find_end, collection_iterator_type<Collection1>)
ELEVATE_FULL_2_COLLECTION_FORWARDER(find_first_of, collection_iterator_type<Collection1>)
ELEVATE_FULL_COLLECTION_FORWARDER(adjacent_find, collection_iterator_type<Collection>)
ELEVATE_FULL_2_COLLECTION_FORWARDER(search, collection_iterator_type<Collection1>)
ELEVATE_FULL_COLLECTION_FORWARDER(search_n, collection_iterator_type<Collection>)
ELEVATE_FULL_COLLECTION_FORWARDER(copy, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(copy_if, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(copy_backward, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(move, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(move_backward, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(fill, void)
ELEVATE_FULL_COLLECTION_FORWARDER(transform, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(generate, void)
ELEVATE_FULL_COLLECTION_FORWARDER(remove, collection_iterator_type<const Collection &>)
ELEVATE_FULL_COLLECTION_FORWARDER(remove_if, collection_iterator_type<const Collection &>)
ELEVATE_FULL_COLLECTION_FORWARDER(remove_copy, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(remove_copy_if, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(replace, void)
ELEVATE_FULL_COLLECTION_FORWARDER(replace_if, void)
ELEVATE_FULL_COLLECTION_FORWARDER(replace_copy, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(replace_copy_if, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(swap_ranges, ESC(collection_iterator_type<extract_nth_t<0, Parameters...>>))
ELEVATE_FULL_COLLECTION_FORWARDER(swap_ranges, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(reverse_copy, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(reverse, void)
#if CXX_VERSION < CXX_17
ELEVATE_FULL_COLLECTION_FORWARDER(random_shuffle, void)
#endif
ELEVATE_FULL_COLLECTION_FORWARDER(shuffle, void)
ELEVATE_FULL_COLLECTION_FORWARDER(unique, collection_iterator_type<Collection>)
ELEVATE_FULL_COLLECTION_FORWARDER(unique, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(is_partitioned, bool)
ELEVATE_FULL_COLLECTION_FORWARDER(partition, collection_iterator_type<Collection>)
ELEVATE_FULL_COLLECTION_FORWARDER(stable_partition, collection_iterator_type<Collection>)
ELEVATE_FULL_COLLECTION_FORWARDER(partition_point, collection_iterator_type<Collection>)
ELEVATE_FULL_COLLECTION_FORWARDER(is_sorted, bool)
ELEVATE_FULL_COLLECTION_FORWARDER(is_sorted_until, collection_iterator_type<Collection>)
ELEVATE_FULL_COLLECTION_FORWARDER(sort, void)
ELEVATE_FULL_COLLECTION_FORWARDER(stable_sort, void)
ELEVATE_FULL_COLLECTION_FORWARDER(lower_bound, collection_iterator_type<Collection>)
ELEVATE_FULL_COLLECTION_FORWARDER(upper_bound, collection_iterator_type<Collection>)
ELEVATE_FULL_COLLECTION_FORWARDER(binary_search, bool)
ELEVATE_FULL_COLLECTION_FORWARDER(equal_range, ESC(std::pair<collection_iterator_type<Collection>, collection_iterator_type<Collection>>))
ELEVATE_FULL_2_COLLECTION_FORWARDER(merge, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_2_COLLECTION_FORWARDER(includes, bool)
ELEVATE_FULL_2_COLLECTION_FORWARDER(set_difference, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_2_COLLECTION_FORWARDER(set_intersection, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_2_COLLECTION_FORWARDER(set_symmetric_difference, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_2_COLLECTION_FORWARDER(set_union, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(is_heap, bool)
ELEVATE_FULL_COLLECTION_FORWARDER(is_heap_until, collection_iterator_type<Collection>)
ELEVATE_FULL_COLLECTION_FORWARDER(make_heap, void)
ELEVATE_FULL_COLLECTION_FORWARDER(push_heap, void)
ELEVATE_FULL_COLLECTION_FORWARDER(pop_heap, void)
ELEVATE_FULL_COLLECTION_FORWARDER(sort_heap, void)
ELEVATE_FULL_COLLECTION_FORWARDER(min_element, collection_iterator_type<Collection>)
ELEVATE_FULL_COLLECTION_FORWARDER(minmax_element, ESC(std::pair<collection_iterator_type<Collection>, collection_iterator_type<Collection>>))
ELEVATE_FULL_2_COLLECTION_FORWARDER(lexicographical_compare, bool)
ELEVATE_FULL_2_COLLECTION_FORWARDER(is_permutation, bool)
ELEVATE_FULL_COLLECTION_FORWARDER(next_permutation, bool)
ELEVATE_FULL_COLLECTION_FORWARDER(prev_permutation, bool)

#undef ITERATOR_DIFFERENCE_TYPE

template <typename Collection, typename Predicate = std::less<const collection_value_type<Collection> &>>
inline void sort(Collection &collection) {
	std::sort(RANGE_OF(collection), Predicate());
}

template <typename Collection, typename Predicate = std::less<const collection_value_type<Collection> &>>
inline void stable_sort(Collection &collection) {
	std::stable_sort(RANGE_OF(collection), Predicate());
}

template <typename Collection, typename Predicate>
inline void filter(Collection &collection, const Predicate &predicate) {
	collection.erase(remove_if(collection, predicate));
}

template <typename Collection>
inline Collection repeat(const Collection &collection, int times) {
	Collection c = {};
	while (times--) {
		for (auto &e : collection) {
			c.push_back(e);
		}
	}
	return c;
}

} // namespace elvt

#endif /* ELVT_ALGORITHM_H */
