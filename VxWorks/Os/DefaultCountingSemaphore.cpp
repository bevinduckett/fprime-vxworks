// ======================================================================
// \title Os/VxWorks/DefaultCountingSemaphore.cpp
// \brief sets default Os::CountingSemaphore VxWorks implementation via linker
// ======================================================================
#include "Os/Delegate.hpp"
#include "VxWorks/Os/CountingSemaphore.hpp"

namespace Os {

CountingSemaphoreInterface* CountingSemaphoreInterface::getDelegate(
    CountingSemaphoreHandleStorage& aligned_new_memory,
    U32 initial_count) {
    return new (aligned_new_memory) Os::VxWorks::Semaphore::VxWorksCountingSemaphore(initial_count);
}
}  // namespace Os
