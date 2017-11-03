#ifndef ELVT_CYCLE_H
#define ELVT_CYCLE_H

#include "comparison.h"
#include "iterator.h"
#include "type_traits.h"
#include <algorithm>
#include <iterator>
#include <limits>

namespace elvt {

template <typename Iterator>
class cycle_iterator : std::iterator<typename std::iterator_traits<Iterator>::iterator_category,
                                     typename std::iterator_traits<Iterator>::value_type,
                                     typename std::iterator_traits<Iterator>::difference_type,
                                     typename std::iterator_traits<Iterator>::pointer,
                                     typename std::iterator_traits<Iterator>::reference> {
  public:
	using iterator_type = Iterator;
	using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;
	using value_type = typename std::iterator_traits<Iterator>::value_type;
	using difference_type = typename std::iterator_traits<Iterator>::difference_type;
	using reference = typename std::iterator_traits<Iterator>::reference;
	using pointer = typename std::iterator_traits<Iterator>::pointer;

  private:
	iterator_type iterator;
	iterator_type begin;
	iterator_type end;
	difference_type _steps = 0;

	cycle_iterator(iterator_type iterator, iterator_type begin, iterator_type end, difference_type steps = 0) : iterator(iterator), begin(begin), end(end), _steps(steps) {
	}

  public:
	cycle_iterator() : iterator(), begin(), end() {
	}

	cycle_iterator(iterator_type begin, iterator_type end) : iterator(begin), begin(begin), end(end) {
	}

	Iterator base() const {
		return iterator;
	}

	difference_type period() const {
		static difference_type period = 0;
		return period ? period : period = std::distance(begin, end);
	}

	difference_type steps() const {
		return _steps;
	}

	reference operator*() {
		return *iterator;
	}

	const reference operator*() const {
		return *iterator;
	}

	pointer operator->() {
		return &(operator*());
	}

	const pointer operator->() const {
		return &(operator*());
	}

	cycle_iterator &operator++() {
		iterator = ++iterator == end ? begin : iterator;
		++_steps;
		return *this;
	}

	cycle_iterator operator++(int) {
		auto outdated = cycle_iterator(iterator++, begin, end, _steps);
		if (iterator == end) {
			iterator = begin;
		}
		++_steps;
		return outdated;
	}

	cycle_iterator &operator--() {
		iterator = iterator == end ? begin : --iterator;
		--_steps;
		return *this;
	}

	cycle_iterator operator--(int) {
		auto outdated = cycle_iterator(iterator, begin, end, _steps);
		if (outdated == begin) {
			iterator = end;
		} else {
			iterator--;
		}
		--_steps;
		return outdated;
	}

  private:
	cycle_iterator &increment_by_n(cycle_iterator<iterator_type> &i, difference_type n, std::random_access_iterator_tag) {
		n = n % i.period();
		auto leeway = std::distance(i.iterator, i.end);
		if (leeway <= n) {
			i.iterator = begin;
			n -= leeway;
		}
		i.iterator += n;
		return i;
	}

	cycle_iterator &increment_by_n(cycle_iterator<iterator_type> &i, difference_type n, std::forward_iterator_tag) {
		while (--n) {
			if (++i.iterator == end) {
				i.iterator = begin;
			}
		}
		return i;
	}

	static cycle_iterator &decrement_by_n(cycle_iterator<iterator_type> &i, difference_type n, std::random_access_iterator_tag) {
		n = n % i.period();
		auto leeway = std::distance(i.begin, i.iterator);
		if (leeway < n) {
			i.iterator = i.end;
			n -= leeway;
		}
		i.iterator -= n;
		return i;
	}

	static cycle_iterator &decrement_by_n(cycle_iterator<iterator_type> &i, difference_type n, std::bidirectional_iterator_tag) {
		while (--n) {
			if (i.iterator == i.begin) {
				i = i.end;
			}
			--i;
		}
		return i;
	}

  public:
	cycle_iterator &operator+=(const difference_type n) {
		increment_by_n(*this, n, iterator_category());
		_steps += n;
		return *this;
	}

	cycle_iterator operator+(const difference_type n) {
		auto updated = cycle_iterator(iterator, begin, end);
		updated._steps += n;
		return increment_by_n(updated, n, iterator_category());
	}

	cycle_iterator operator-=(const difference_type n) {
		decrement_by_n(*this, n, iterator_category());
		_steps -= n;
		return *this;
	}

	cycle_iterator operator-(const difference_type n) {
		auto updated = cycle_iterator(iterator, begin, end);
		updated._steps -= n;
		return decrement_by_n(updated, n, iterator_category());
	}

	difference_type operator-(const cycle_iterator<iterator_type> &iterator) {
		return this->_steps - iterator._steps;
	}

	reference operator[](const difference_type n) {
		return *(iterator + n);
	}

	SYNTHESIZE_EQUALITY(cycle_iterator<iterator_type>, lhs, rhs, return lhs.steps() == rhs.steps();)
	SYNTHESIZE_COMPARISON(elvt::cycle_iterator<iterator_type>, lhs, rhs, return lhs.steps() < rhs.steps();)
};

template <typename Collection>
class cycle_base {
  public:
	using value_type = collection_value_type<Collection>;
	using reference = value_type &;
	using const_reference = const value_type &;
	using iterator = cycle_iterator<collection_iterator_type<Collection>>;
	using difference_type = typename std::iterator_traits<iterator>::difference_type;
	using size_type = difference_type;

  protected:
	Collection collection;
	typename iterator::difference_type _size;
	iterator begin_iterator;
	iterator end_iterator;

  public:
	cycle_base() {
	}

	cycle_base(const Collection &collection) : collection(collection) {
		_size = distance(collection);
		begin_iterator = iterator(RANGE_OF(collection));
		end_iterator = begin_iterator + _size;
	}

	cycle_base(const Collection &collection, typename iterator::difference_type size) : collection(collection), _size(size) {
		begin_iterator = iterator(RANGE_OF(collection));
		end_iterator = begin_iterator + _size;
	}

	iterator begin() const {
		return begin_iterator;
	}

	iterator end() const {
		return end_iterator;
	}

	size_type size() const {
		return size;
	}

	size_type max_size() const {
		return std::numeric_limits<size_type>::max();
	}

	bool empty() const {
		return _size == 0;
	}
};

template <typename Collection, typename Enable = void>
class cycle : public cycle_base<Collection> {
	using base = cycle_base<Collection>;

	using base::base;
};

template <typename Collection>
class cycle<Collection, enable_if_t<std::is_convertible<typename std::iterator_traits<collection_iterator_type<Collection>>::iterator_category, std::bidirectional_iterator_tag>::value>> : public cycle_base<Collection> {
	using base = cycle_base<Collection>;

  public:
	using reverse_iterator = cycle_iterator<collection_reverse_iterator_type<Collection>>;

  private:
	reverse_iterator rbegin_iterator;
	reverse_iterator rend_iterator;

  public:
	cycle(const Collection &collection) : base(collection) {
		rbegin_iterator = reverse_iterator(rbegin(collection), rend(collection));
		rend_iterator = rbegin_iterator + base::_size;
	}

	cycle(const Collection &collection, typename base::iterator::difference_type size) : cycle_base<Collection>(collection, size) {
		rbegin_iterator = reverse_iterator(elvt::rbegin(collection), elvt::rend(collection));
		rend_iterator = rbegin_iterator + base::_size;
	}

	reverse_iterator rbegin() const {
		return rbegin_iterator;
	}

	reverse_iterator rend() const {
		return rend_iterator;
	}
};

template <typename Collection>
cycle<Collection> cycle_over(Collection &&collection, typename std::iterator_traits<collection_iterator_type<Collection>>::difference_type size = std::numeric_limits<typename std::iterator_traits<collection_iterator_type<Collection>>::difference_type>::max()) {
	return cycle<Collection>(std::forward<Collection>(collection), size);
}

} // namespace elvt

#endif /* ELVT_CYCLE_H */
