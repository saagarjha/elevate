#ifndef ELVT_COMPARISON_H
#define ELVT_COMPARISON_H

#define SYNTHESIZE_COMPARISON_FRIENDS(type)                   \
	friend bool operator<(const type &lhs, const type &rhs);  \
	friend bool operator<=(const type &lhs, const type &rhs); \
	friend bool operator>(const type &lhs, const type &rhs);  \
	friend bool operator>=(const type &lhs, const type &rhs);

#define TEMPLATED_SYNTHESIZE_COMPARISON_FRIENDS(type, template_parameters) \
	template <template_parameters>                                         \
	friend bool operator<(const type &lhs, const type &rhs);               \
	template <template_parameters>                                         \
	friend bool operator<=(const type &lhs, const type &rhs);              \
	template <template_parameters>                                         \
	friend bool operator>(const type &lhs, const type &rhs);               \
	template <template_parameters>                                         \
	friend bool operator>=(const type &lhs, const type &rhs);

#define SYNTHESIZE_EQUALITY(type, lhs, rhs, predicate)         \
	friend bool operator==(const type &lhs, const type &rhs) { \
		predicate                                              \
	}                                                          \
                                                               \
	friend bool operator!=(const type &lhs, const type &rhs) { \
		return !(rhs == lhs);                                  \
	}

#define TEMPLATED_SYNTHESIZE_EQUALITY(type, template_parameters, lhs, rhs, predicate) \
	template <template_parameters>                                                    \
	friend bool operator==(const type &lhs, const type &rhs) {                        \
		predicate                                                                     \
	}                                                                                 \
                                                                                      \
	template <template_parameters>                                                    \
	friend bool operator!=(const type &lhs, const type &rhs) {                        \
		return !(rhs == lhs);                                                         \
	}

#define SYNTHESIZE_COMPARISON(type, lhs, rhs, predicate)       \
	friend bool operator<(const type &lhs, const type &rhs) {  \
		predicate                                              \
	}                                                          \
                                                               \
	friend bool operator<=(const type &lhs, const type &rhs) { \
		return lhs < rhs || lhs == rhs;                        \
	}                                                          \
                                                               \
	friend bool operator>(const type &lhs, const type &rhs) {  \
		return !(lhs < rhs || lhs == rhs);                     \
	}                                                          \
                                                               \
	friend bool operator>=(const type &lhs, const type &rhs) { \
		return !(lhs < rhs);                                   \
	}

#define TEMPLATED_SYNTHESIZE_COMPARISON(type, template_parameters, lhs, rhs, predicate) \
	template <template_parameters>                                                      \
	friend bool operator<(const type &lhs, const type &rhs) {                           \
		predicate                                                                       \
	}                                                                                   \
                                                                                        \
	template <template_parameters>                                                      \
	friend bool operator<=(const type &lhs, const type &rhs) {                          \
		return lhs < rhs || lhs == rhs;                                                 \
	}                                                                                   \
                                                                                        \
	template <template_parameters>                                                      \
	friend bool operator>(const type &lhs, const type &rhs) {                           \
		return !(lhs < rhs || lhs == rhs);                                              \
	}                                                                                   \
                                                                                        \
	template <template_parameters>                                                      \
	friend bool operator>=(const type &lhs, const type &rhs) {                          \
		return !(lhs < rhs);                                                            \
	}

#endif /* ELVT_COMPARISON_H */
