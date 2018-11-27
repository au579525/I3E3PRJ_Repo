#include <stdio.h>

#include <osapi/Thread.hpp>
#include <osapi/ThreadFunctor.hpp>
#include <osapi/Utility.hpp>
#include <osapi/Mutex.hpp>

osapi::Mutex mut;

FILE * SPI_driver;

class spi_req_function : public osapi::ThreadFunctor{

public:
  spi_req_function(){}

private:
  void run(){
    while(1){

      std::cout << "in spi_req_function" << '\n';
      int data;
      int * dataptr = &data;
      int err;
      err = fread(dataptr,1,1, SPI_driver);

      mut.lock();
      switch (data) {
        case 10:
          int x,y;
          std::cout << "due skudt" << '\n';
          err = fread(&x,1,1, SPI_driver);
          err = fread(&y,1,1, SPI_driver);
          std::cout << "Duens position var X:" << x << " Y:" << y << '\n';
          break;
        case 11:
          std::cout << " due detekteret " << '\n';
          break;
        case 12:
          std::cout << "lavt vand" << '\n';
          break;
        case 13:
          std::cout << "vand tømt" << '\n';
          break;
        case 14:
          std::cout << "blomster vandet" << '\n';
          break;
        default:
          std::cout << "message from PSoC was misunderstood" << '\n';
          break;
      }
      mut.unlock();
    }
  }
};

class main_thread : public osapi::ThreadFunctor{

public:
  main_thread(){

  }
private:
  void run(){
    while(1){
      mut.lock();
      std::cout << "in main_thread" << '\n';
      int data;
      int * dataptr = &data;
      std::cout << "read request from user, write an int" << '\n';
      std::cin >> data;
      std::cout << "writing " << data << " to PSoC over SPI" << '\n';
      int err = fwrite(dataptr,1,1,SPI_driver);
      std::cout << "data written" << '\n';
      mut.unlock();
    }
  }

};

int main()
{
  SPI_driver = fopen("/dev/spi_drv0","r+");

  spi_req_function spi_req_f;
  main_thread main_f;

  osapi::Thread p(&spi_req_f);
  osapi::Thread t(&main_f);

  p.start();
  t.start();

  p.join();
  t.join();

  return 0;
}
