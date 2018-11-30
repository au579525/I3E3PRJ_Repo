#include <osapi/Thread.hpp>

namespace osapi
{
  void* ThreadFunctor::threadMapper(void* thread)
  {
    /* Something is missing here - Determine what! */
    ThreadFunctor * tf = static_cast<ThreadFunctor*>(thread);
    tf->run();
    
    tf->threadDone_.signal();
    return NULL;
  }

}
