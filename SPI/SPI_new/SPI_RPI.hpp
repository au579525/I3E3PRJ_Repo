#pragma once

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
  spi_req_function(){};

private:
  void run();
};
