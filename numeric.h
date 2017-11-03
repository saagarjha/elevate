#ifndef ELVT_NUMERIC_H
#define ELVT_NUMERIC_H

#include "algorithm.h"
#include <numeric>

namespace elvt {

ELEVATE_FULL_COLLECTION_FORWARDER(iota, void)
ELEVATE_FULL_COLLECTION_FORWARDER(accumulate, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(inner_product, ESC(extract_nth_t<1, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(adjacent_difference, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(partial_sum, ESC(extract_nth_t<0, Parameters...>))
#if CXX_VERSION >= CXX_17
ELEVATE_FULL_COLLECTION_FORWARDER(reduce, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(exclusive_scan, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(inclusive_scan, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(transform_exclusive_scan, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(transform_inclusive_scan, ESC(extract_nth_t<0, Parameters...>))
#endif

} // namespace elvt

#endif /* ELVT_NUMERIC_H */
