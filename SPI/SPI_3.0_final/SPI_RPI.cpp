#include "SPI_RPI.hpp"

//I Denne funktion skal tilføjes logging funktioner i stedet for cout
  spi_req_function::spi_req_function(Fileaccess * _fileac){
    fileac = _fileac;
  }

void spi_req_function::run(){
  while(1){
    modes runMode;
    ostringstream output;
    unsigned int data;
    FILE * fp;
    fp = fopen("/dev/spi_drv0","r");

    fscanf(fp,"%d",&data);
    runMode.runLocker();

    switch (data) {
      case 'a':
        unsigned int x, y;
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
      case 'd':
        fileac->log("vand tømt");
        break;
      case 'e':
        fileac->log("blomster vandet");
        break;
      //ny block
      case 'f':
        unsigned int level;
        fileac->log("Vandstanden måles");
        freopen("/dev/spi_drv0", "r", fp);
        fscanf(fp, "%d", &level);
        output << "Vandstandens niveau er:" << level << "mL";
        fileac->log(output.str());
        fileac->set_waterlvl(level);
        break;
      case 'c':
        fileac->log("System reset");
        fileac->reset();
        break;
      default:
        fileac->log("message from PSoC was misunderstood");
        output << data;
        fileac->log(output.str());
        break;
    }
    fclose(fp);
    runMode.runUnlocker();
  }
}

  queue_thread::queue_thread(Fileaccess * _fileac){
    fileac = _fileac;
  }

  void queue_thread::run(){
    modes mode;

    while(1){
      std::vector<string> v = fileac->getQueue();
      if(!v.empty()){
        for(std::vector<string>::iterator it = v.begin(); it != v.end(); ++it){

          if(string(*it).find("systemmode") != std::string::npos){
            if(string(*it).find("normal") != std::string::npos){
              mode.SPI_Set_normal_mode();
              fileac->set_mode("normal");
            }
            else if (string(*it).find("manual") != std::string::npos) {
              mode.SPI_Set_Manual_mode();
              fileac->set_mode("manual");
            }
            else if (string(*it).find("standby") != std::string::npos) {
              mode.SPI_Set_Standby_mode();
              fileac->set_mode("standby");
            }
            else if (string(*it).find("powersaving") != std::string::npos) {
              mode.SPI_Set_PowerSaving_mode();
              fileac->set_mode("powersaving");
            }
            else if (string(*it).find("watering") != std::string::npos) {
              mode.SPI_Set_PowerSaving_mode();
              fileac->set_mode("watering");
            }

          }
          else if (string(*it).find("manualcontrol") != std::string::npos){
            if(string(*it).find("up") != std::string::npos){
              mode.SPI_move_up();
              fileac->log("Manual: cannon moved up");
            }
            else if (string(*it).find("down") != std::string::npos) {
              mode.SPI_move_down();
              fileac->log("Manual: cannon moved down");
            }
            else if (string(*it).find("left") != std::string::npos) {
              mode.SPI_move_left();
              fileac->log("Manual: cannon moved left");
            }
            else if (string(*it).find("right") != std::string::npos) {
              mode.SPI_move_right();
              fileac->log("Manual: cannon moved right");
            }
            else if (string(*it).find("shoot") != std::string::npos) {
              mode.SPI_start_shooting();
              fileac->log("Manual: shoot");
              osapi::sleep(1500);
              mode.SPI_stop_shooting();
            }
          }
        }
      }
      osapi::sleep(50);
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
