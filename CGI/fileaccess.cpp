#include "fileaccess.h"

fileaccess::fileaccess()
{
    //get path of folder with queue and setting files
    ifstream pathsettings;
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
}

string fileaccess::getsysmode()
{
    //open file and read systemmode
    string line;
    ifstream file;
    file.open(path + "systemmode");
    if(file.is_open()){
        getline(file, line);
        return line;
    }
    else{
        return("error");
    }
}

bool fileaccess::getwatermode()
{
    //open file and read wateringmode
    string line;
    ifstream file;
    file.open(path + "watermode");
    if(file.is_open()){
        getline(file, line);
        if(line == "enabled"){
            return true;
        }

    }
    return false;
}

vector<string> fileaccess::getlog()
{
    //open file and read log
    vector<string> content;
    ifstream file;
    file.open(path + "log");
    if(file.is_open()){
        for(string line; getline(file, line);){
            content.push_back(line);
        }
    }
    return content;
}

void fileaccess::setsysmode(string mode)
{
    //open file and write to queue to change sysmode
    ofstream file;
    file.open(path + "queue", ios::app);
    if(file.is_open()){
        file << endl << "systemmode " << mode;
    }
}

void fileaccess::setwatermode(bool mode)
{
    //open file and write to queue to change wateringmode
    ofstream file;
    file.open(path + "queue", ios::app);
    if(file.is_open()){
        if(mode){
            file << endl << "watermode enabled";
        }
        else{
            file << endl << "watermode disabled";
        }
    }
}

void fileaccess::manualcontrol(string action)
{
    //write to manualcontrol to queue
    ofstream file;
    file.open(path + "queue", ios::app);
    if(file.is_open()){
        file << endl << "manualcontrol " << action;
    }
}

string fileaccess::getwaterlvl(){
    string line;
    ifstream file;
    file.open(path + "waterlevel");
    if(file.is_open()){
        getline(file, line);
        return line;
    }
    return "999";
}
