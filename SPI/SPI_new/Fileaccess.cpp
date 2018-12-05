#include "Fileaccess.hpp"

Fileaccess::Fileaccess(){
    ifstream pathsettings;
    ifstream mode;
    ifstream watermode;
    ifstream log;
    ifstream queue;
    pathsettings.open("path.txt");
    //check if file is open
    if(pathsettings.is_open()){
      string line;
      getline(pathsettings,path);
    }
    //if file doesnt open use standard path
    else{
      ofstream pathsettings;
      pathsettings.open("path.txt", ios::trunc);
      pathsettings << "/opt/pigeon/";
      path = "/opt/pigeon/";
    }
    mode.open(path + "systemmode");
    if(!mode.is_open()){
      ofstream modew;
      modew.open(path + "systemmode", ios::trunc);
      modew << "normal";
    }
    watermode.open(path + "watermode");
    if(!watermode.is_open()){
      ofstream watermodew;
      watermodew.open(path + "watermode", ios::trunc);
      watermodew << "disabled";
    }
    log.open(path + "log");
    if(!log.is_open()){
      ofstream logw;
      logw.open(path + "log", ios::trunc);
    }
    queue.open(path + "queue");
    if(!queue.is_open()){
      ofstream queuew;
      queuew.open(path + "queue", ios::trunc);
    }
}

void Fileaccess::set_mode(string mode){
     ofstream file;
     file.open(path + "systemmode", ios::trunc);
     if(file.is_open()){
       file << mode;
     }
}

void Fileaccess::set_AutomaticWatering_mode(){
    bool enabled = false;
    ifstream fileread;
    ofstream filewrite;
    fileread.open(path + "watermode");
    if(fileread.is_open()){
      string line;
      getline(fileread, line);
      if(line == "enabled"){
        enabled = true;
      }
    }
    fileread.close();
    filewrite.open(path + "watermode", ios::trunc);
    if(filewrite.is_open()){
      if(enabled){
        filewrite << "enabled";
      }
      else{
        filewrite << "disabled";
      }
    }
}

void Fileaccess::log(string message){
      ofstream file;
      file.open(path + "log", ios::app);
      time_t curtime;
      time(&curtime);
      if(file.is_open()){
        file << ctime(&curtime) << ": " << message << endl;
      }
}

vector<string> Fileaccess::getQueue(){
    vector<string> queue;
    ifstream file;
    file.open(path + "queue");
    for(string line; getline(file, line);){
      queue.push_back(line);
    }
    return queue;
}
