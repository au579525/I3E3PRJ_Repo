#include "SPI_RPI.hpp"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <osapi/Thread.hpp>
#include <osapi/ThreadFunctor.hpp>
#include <osapi/Utility.hpp>
#include <osapi/Mutex.hpp>

osapi::Mutex mut;

//I Denne funktion skal tilføjes logging funktioner i stedet for cout
void SPI_req_function::run(){
  while(1){

    unsigned int data;
    FILE * fp;
    fp = fopen("/dev/spi_drv0","r");

    fscanf(fp,"%d",&data);
    mut.lock();

    switch (data) {
      case 'a':
        unsigned int x,y;
        std::cout << "due skudt" << '\n';
        freopen("/dev/spi_drv0","r", fp);
        fscanf(fp,"%d",&x);//Her læses ingen værdi ud,
        freopen("/dev/spi_drv0","r", fp);
        fscanf(fp,"%d",&y);//og ventes ikke på interrupt

        std::cout << "Duens position var X:" << x << " Y:" << y << '\n';
        break;
      case 'b':
        std::cout << " due detekteret " << '\n';
        break;
      case 'c':
        std::cout << "lavt vand" << '\n';
        break;
      case 'd':
        std::cout << "vand tømt" << '\n';
        break;
      case 'e':
        std::cout << "blomster vandet" << '\n';
        break;
      default:
        std::cout << "message from PSoC was misunderstood" << '\n';
        std::cout << data << std::endl;
        break;
    }
    fclose(fp);
    mut.unlock();
  }
}

void SPI_Set_normal_mode(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  int err = fputc('A', fp);
  fclose(fp);

  mut.unlock();
}

void SPI_Set_normal_mode(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  int err = fputc('A', fp);
  fclose(fp);

  mut.unlock();
}

void SPI_Set_Manual_mode(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  int err = fputc('B', fp);
  fclose(fp);

  mut.unlock();
}

void SPI_Set_PowerSaving_mode(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  int err = fputc('C', fp);
  fclose(fp);

  mut.unlock();
}

void SPI_Set_Standby_mode(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  int err = fputc('D', fp);
  fclose(fp);

  mut.unlock();
}

void SPI_Set_AutomaticWatering_mode(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  int err = fputc('E', fp);
  fclose(fp);

  mut.unlock();
}

void SPI_move_left(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  int err = fputc('F', fp);
  fclose(fp);

  mut.unlock();
}

void SPI_move_right(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  int err = fputc('G', fp);
  fclose(fp);

  mut.unlock();
}

void SPI_move_up(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  int err = fputc('H', fp);
  fclose(fp);

  mut.unlock();
}

void SPI_move_down(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  int err = fputc('I', fp);
  fclose(fp);

  mut.unlock();
}

void SPI_start_shooting(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  int err = fputc('J', fp);
  fclose(fp);

  mut.unlock();
}

void SPI_stop_shooting(){
  FILE * fp;

  mut.lock();

  fp = fopen("/dev/spi_drv0","w");
  int err = fputc('K', fp);
  fclose(fp);

  mut.unlock();
}
