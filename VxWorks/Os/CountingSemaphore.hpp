// ======================================================================
// \title Os/VxWorks/CountingSemaphore.hpp
// \brief VxWorks definitions for Os::CountingSemaphore
// ======================================================================
#ifndef OS_VXWORKS_COUNTING_SEMAPHORE_HPP
#define OS_VXWORKS_COUNTING_SEMAPHORE_HPP
#include <semLib.h>
#include <Os/CountingSemaphore.hpp>

namespace Os {
namespace VxWorks {
namespace Semaphore {

struct VxWorksCountingSemaphoreHandle : public CountingSemaphoreHandle {
    SEM_ID m_semaphore;
};

class VxWorksCountingSemaphore : public CountingSemaphoreInterface {
  public:
    VxWorksCountingSemaphore(U32 initial_count);

    ~VxWorksCountingSemaphore() override;

    VxWorksCountingSemaphore(const VxWorksCountingSemaphore& other) = delete;

    CountingSemaphoreInterface& operator=(const CountingSemaphoreInterface& other) = delete;

    VxWorksCountingSemaphore::Status wait() override;

    VxWorksCountingSemaphore::Status tryWait() override;

    VxWorksCountingSemaphore::Status waitTimeout(const Fw::TimeInterval& interval) override;

    VxWorksCountingSemaphore::Status post() override;

    CountingSemaphoreHandle* getHandle() override;

  private:
    VxWorksCountingSemaphoreHandle m_handle;
};

}  // namespace Semaphore
}  // namespace VxWorks
}  // namespace Os
#endif  // OS_VXWORKS_COUNTING_SEMAPHORE_HPP
