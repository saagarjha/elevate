#ifndef ELVT_MEMORY_H
#define ELVT_MEMORY_H

#include "algorithm.h"
#include <memory>

namespace elvt {

ELEVATE_FULL_COLLECTION_FORWARDER(uninitialized_copy, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(uninitialized_fill, void)
#if CXX_VERSION >= CXX_17
ELEVATE_FULL_COLLECTION_FORWARDER(uninitialized_move, ESC(extract_nth_t<0, Parameters...>))
ELEVATE_FULL_COLLECTION_FORWARDER(uninitialized_default_construct, void)
ELEVATE_FULL_COLLECTION_FORWARDER(destroy, void)
#endif

} // namespace elvt

#endif /* ELVT_MEMORY_H */
