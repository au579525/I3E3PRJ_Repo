#include <iostream>
#include <osapi/Thread.hpp>
#include <osapi/ThreadFunctor.hpp>
#include <osapi/Message.hpp>
#include <osapi/MsgQueue.hpp>
#include <osapi/Timer.hpp>
#include <osapi/Log.hpp>
#include <osapi/Utility.hpp>
#include <osapi/Mutex.hpp>
#include <osapi/Conditional.hpp>

bool open = true;


osapi::Mutex mut;

osapi::Conditional cond;



class locker : public osapi::ThreadFunctor{

public:
  locker(){}

private:
  void run(){
    while(1){
      mut.lock();
      open = false;
      cond.signal();
      while (open == false){
        std::cout << "Mut is locked" << '\n';
        cond.wait(mut);
      }
      std::cout << "out of while" << '\n';
      osapi::sleep(1000);
      mut.unlock();
    }
  }
};

class opener : public osapi::ThreadFunctor{

public:
  opener(){

  }
private:
  void run(){
    while(1){
      mut.lock();
      while (open == true){
        cond.wait(mut);
      }
      std::cout << "Mut is open" << '\n';
      osapi::sleep(2000);
      open = true;
      cond.signal();
      mut.unlock();
    }
  }

};

int main(){
  opener open;
  locker lock;


  osapi::Thread p(&lock);
  osapi::Thread t(&open);
  
  t.start();
  p.start();

  p.join();
  t.join();


}
