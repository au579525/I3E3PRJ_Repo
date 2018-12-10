#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

class Fileaccess {
public:
  Fileaccess();
  void set_mode(string);
  void setwaterlvl(int);
  void set_AutomaticWatering_mode();
  void log(string);
  vector<string> getQueue();
private:
  string path;
};
