#include "Fileaccess.hpp"
#include "modes.hpp"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sstream>

#include <osapi/Thread.hpp>
#include <osapi/ThreadFunctor.hpp>
#include <osapi/Utility.hpp>
#include <osapi/Mutex.hpp>


class spi_req_function : public osapi::ThreadFunctor{

public:
  spi_req_function(Fileaccess *);

private:
  Fileaccess * fileac;
  void run();
};

class queue_thread : public osapi::ThreadFunctor{

public:
  queue_thread(Fileaccess *);

private:
  Fileaccess * fileac;
  void run();
};
