// ======================================================================
// \title Os/VxWorks/CountingSemaphore.cpp
// \brief VxWorks implementations for Os::CountingSemaphore
// ======================================================================
#include "VxWorks/Os/CountingSemaphore.hpp"
#include "VxWorks/Os/error.hpp"
#include "Fw/Types/Assert.hpp"
#include "Fw/Time/TimeInterval.hpp"
#include <sysLib.h>
#include <errnoLib.h>

namespace Os {
namespace VxWorks {
namespace Semaphore {

VxWorksCountingSemaphore::VxWorksCountingSemaphore(U32 initial_count) {
    int options = SEM_Q_PRIORITY;
    this->m_handle.m_semaphore = semCCreate(options, static_cast<int>(initial_count));
    FW_ASSERT(this->m_handle.m_semaphore != NULL);
}

VxWorksCountingSemaphore::~VxWorksCountingSemaphore() {
    if (this->m_handle.m_semaphore != NULL) {
        (void)semDelete(this->m_handle.m_semaphore);
    }
}

VxWorksCountingSemaphore::Status VxWorksCountingSemaphore::tryWait() {
    STATUS vxstatus = semTake(this->m_handle.m_semaphore, NO_WAIT);
    FW_ASSERT(vxstatus == VXWORKS_OK || errnoGet() != 0, vxstatus);
    return vxworks_status_to_semaphore_status(vxstatus);
}

VxWorksCountingSemaphore::Status VxWorksCountingSemaphore::wait() {
    STATUS vxstatus = semTake(this->m_handle.m_semaphore, WAIT_FOREVER);
    FW_ASSERT(vxstatus == VXWORKS_OK || errnoGet() != 0, vxstatus);
    return vxworks_status_to_semaphore_status(vxstatus);
}

VxWorksCountingSemaphore::Status VxWorksCountingSemaphore::waitTimeout(const Fw::TimeInterval& interval) {
    U32 timeout_ms = (interval.getSeconds() * 1000) + (interval.getUSeconds() / 1000);
    FW_ASSERT(timeout_ms > 0);
    int ticks = (timeout_ms * sysClkRateGet()) / 1000;
    if (ticks == 0) {
        ticks = 1;
    }
    STATUS vxstatus = semTake(this->m_handle.m_semaphore, ticks);
    FW_ASSERT(vxstatus == VXWORKS_OK || errnoGet() != 0, vxstatus);
    return vxworks_status_to_semaphore_status(vxstatus);
}

VxWorksCountingSemaphore::Status VxWorksCountingSemaphore::post() {
    STATUS vxstatus = semGive(this->m_handle.m_semaphore);
    FW_ASSERT(vxstatus == VXWORKS_OK || errnoGet() != 0, vxstatus);
    return vxworks_status_to_semaphore_status(vxstatus);
}

CountingSemaphoreHandle* VxWorksCountingSemaphore::getHandle() {
    return &m_handle;
}

}  // namespace Semaphore
}  // namespace VxWorks
}  // namespace Os
