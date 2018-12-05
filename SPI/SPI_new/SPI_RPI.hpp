#pragma once

#include "Fileaccess.hpp"
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

void SPI_Set_normal_mode();

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
