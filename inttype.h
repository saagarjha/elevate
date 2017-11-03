#ifndef ELVT_INTTYPE_H
#define ELVT_INTTYPE_H

#include "type_traits.h"
#include <cmath>

namespace elvt {

template <typename Integer>
struct is_even {
	constexpr bool operator()(const Integer &n) const {
		return n % 2 == 0;
	};
};

template <typename Integer>
struct is_odd {
	constexpr bool operator()(const Integer &n) const {
		return n % 2;
	};
};

template <typename Integer>
struct is_prime {
	bool operator()(const Integer &n) const {
		for (int i = 2; i < n; ++i) {
			if (n % i == 0) {
				return false;
			}
		}
		return n >= 2;
	};
};

} // namespace elvt

#endif /* ELVT_INTTYPE_H */
