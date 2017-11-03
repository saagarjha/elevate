#ifndef ELVT_STRING_H
#define ELVT_STRING_H

#include "internal/stringify_prototypes.h"
#include <iostream>
#include <sstream>
#include <string>

namespace elvt {

template <typename Collection>
inline std::ostream &join(std::ostream &output, const Collection &collection, const std::string &separator) {
	for (auto iterator = std::begin(collection); iterator != std::end(collection); ++iterator) {
		if (iterator != std::begin(collection)) {
			output << separator;
		}
		output << *iterator;
	}
	return output;
}

template <typename Collection>
inline std::string join(const Collection &collection, const std::string &separator) {
	std::ostringstream result;
	join<Collection>(result, collection, separator);
	return result.str();
}

} // namespace elvt

#endif /* ELVT_STRING_H */
