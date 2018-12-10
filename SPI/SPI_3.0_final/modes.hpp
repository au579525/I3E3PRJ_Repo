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

class modes{
public:
  void SPI_Set_normal_mode();
  void SPI_Set_Manual_mode();
  void SPI_Set_PowerSaving_mode();
  void SPI_Set_Standby_mode();
  void SPI_Set_AutomaticWatering_mode();
  void SPI_move_left();
  void SPI_move_right();
  void SPI_move_up();
  void SPI_move_down();
  void SPI_start_shooting();
  void SPI_stop_shooting();
  void runLocker();
  void runUnlocker();
};
