#include "modes.hpp"

osapi::Mutex mut;


void modes::SPI_Set_normal_mode(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  fputc('A', fp);
  fclose(fp);

  mut.unlock();
}

void modes::SPI_Set_Manual_mode(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  fputc('B', fp);
  fclose(fp);

  mut.unlock();
}

void modes::SPI_Set_PowerSaving_mode(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  fputc('C', fp);
  fclose(fp);

  mut.unlock();
}

void modes::SPI_Set_Standby_mode(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  fputc('D', fp);
  fclose(fp);

  mut.unlock();
}

void modes::SPI_Set_AutomaticWatering_mode(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  fputc('E', fp);
  fclose(fp);

  mut.unlock();
}

void modes::SPI_move_left(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  fputc('F', fp);
  fclose(fp);

  mut.unlock();
}

void modes::SPI_move_right(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  fputc('G', fp);
  fclose(fp);

  mut.unlock();
}

void modes::SPI_move_up(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  fputc('H', fp);
  fclose(fp);

  mut.unlock();
}

void modes::SPI_move_down(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  fputc('I', fp);
  fclose(fp);

  mut.unlock();
}

void modes::SPI_start_shooting(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  fputc('J', fp);
  fclose(fp);

  mut.unlock();
}

void modes::SPI_stop_shooting(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  fputc('K', fp);
  fclose(fp);

  mut.unlock();
}

void modes::runLocker(){
  mut.lock();
}

void modes::runUnlocker(){
  mut.unlock();
}
