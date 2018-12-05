#include "SPI_RPI.hpp"

osapi::Mutex mut;

//I Denne funktion skal tilføjes logging funktioner i stedet for cout
  spi_req_function::spi_req_function(Fileaccess * _fileac){
    fileac = _fileac;
  }

void spi_req_function::run(){
  while(1){
    ostringstream output;
    unsigned int data;
    FILE * fp;
    fp = fopen("/dev/spi_drv0","r");

    fscanf(fp,"%d",&data);
    mut.lock();

    switch (data) {
      case 'a':
        unsigned int x,y;
        fileac->log("due skudt");
        freopen("/dev/spi_drv0","r", fp);
        fscanf(fp,"%d",&x);//Her læses ingen værdi ud,
        freopen("/dev/spi_drv0","r", fp);
        fscanf(fp,"%d",&y);//og ventes ikke på interrupt
        output << "Duens position var X:" << x << " Y:" << y;
        fileac->log(output.str());
        break;
      case 'b':
        fileac->log("due detekteret");
        break;
      case 'c':
        fileac->log("lavt vand");
        break;
      case 'd':
        fileac->log("vand tømt");
        break;
      case 'e':
        fileac->log("blomster vandet");
        break;
      default:
        fileac->log("message from PSoC was misunderstood");
        output << data;
        fileac->log(output.str());
        break;
    }
    fclose(fp);
    mut.unlock();
  }
}

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

  queue_thread::queue_thread(Fileaccess * _fileac){
    fileac = _fileac;
  }

  void queue_thread::run(){

    while(1){
      std::vector<string> v = fileac->getQueue();
      if(!v.empty()){
        for(std::vector<string>::iterator it = v.begin(); it != v.end(); ++it){
          if(string(*it).find("systemmode") != std::string::npos){
            if(string(*it).find("normal") != std::string::npos){
              SPI_Set_normal_mode();
            }
            else if (string(*it).find("manual") != std::string::npos) {
              SPI_Set_Manual_mode();
            }
            else if (string(*it).find("standby") != std::string::npos) {
              SPI_Set_Standby_mode();
            }
            else if (string(*it).find("powersaving") != std::string::npos) {
              SPI_Set_PowerSaving_mode();
            }
          }
          else if (string(*it).find("watermode") != std::string::npos) {
            SPI_Set_AutomaticWatering_mode();
          }
          else if (string(*it).find("manualcontrol") != std::string::npos){
            if(string(*it).find("up") != std::string::npos){
              SPI_move_up();
            }
            else if (string(*it).find("down") != std::string::npos) {
              SPI_move_down();
            }
            else if (string(*it).find("left") != std::string::npos) {
              SPI_move_left();
            }
            else if (string(*it).find("right") != std::string::npos) {
              SPI_move_right();
            }
            else if (string(*it).find("shoot") != std::string::npos) {
              SPI_start_shooting();
            }
          }
        }
      }
      osapi::sleep(5000);
    }
  }

int main()
{
  try
{
  Fileaccess f;

  spi_req_function spi_req_f(&f);
  queue_thread queue_t(&f);

  osapi::Thread p(&spi_req_f);
  osapi::Thread t(&queue_t);

  p.start();
  t.start();

  p.join();
  t.join();
}
catch (std::exception& e)
{
  std::cout<<"error found: " << e.what() << '\n';
}


  return 0;
}
