#include "osapi/linux/Mutex.hpp"

namespace osapi
{
  Mutex::Mutex(){
	  pthread_mutex_init(&mut, NULL);
  }


  void Mutex::lock(){
    pthread_mutex_lock(&mut);
    

  }

  void Mutex::unlock(){
    pthread_mutex_unlock(&mut);
  }

  Mutex::~Mutex(){
    pthread_mutex_destroy(&mut);
  }

}
