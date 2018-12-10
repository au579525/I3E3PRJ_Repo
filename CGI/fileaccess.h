#ifndef FILEACCESS_H
#define FILEACCESS_H
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class fileaccess
{
public:
    fileaccess();
    string getsysmode();
    bool getwatermode();
    vector<string> getlog();
    void setsysmode(string);
    void setwatermode(bool);
    void manualcontrol(string);
    string getwaterlvl();
private:
    string path;
};

#endif // FILEACCESS_H
