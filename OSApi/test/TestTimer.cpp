#include <iostream>
#include <osapi/Thread.hpp>
#include <osapi/ThreadFunctor.hpp>
#include <osapi/Message.hpp>
#include <osapi/MsgQueue.hpp>
#include <osapi/Timer.hpp>
#include <osapi/Log.hpp>
#include <osapi/Utility.hpp>

class TestTimer : public osapi::ThreadFunctor
{
public:
  TestTimer()
    : mq_(100), running_(true)
  {
  }
  
  osapi::MsgQueue* getMsgQueue() 
  {
    return &mq_;
  }

  
  
  ~TestTimer()
  {
    delete timer1_;
    delete timer2_;
    delete timer3_;
  }
  
  
  enum { 
    ID_TIME_OUT_1,
    ID_TIME_OUT_2,
    ID_TIME_OUT_3,
    ID_TERMINATE
  };


private:
  void handleTimeOut1();
  void handleTimeOut2();
  void handleTimeOut3();
  void handler(unsigned long id, osapi::Message* m);
  virtual void run();
  osapi::MsgQueue   mq_;
  bool              running_;
  osapi::ITimerId*  timer1_;
  osapi::ITimerId*  timer2_;
  osapi::ITimerId*  timer3_;
};


void TestTimer::handleTimeOut1()
{
  OSAPI_LOG_DBG("Got timeout1, rearming...");
  timer1_->reArm(); // Timeout in 1sec
}

void TestTimer::handleTimeOut2()
{
  OSAPI_LOG_DBG("Got timeout 2, rearming...");
  timer2_->reArm(); // Timeout in 1sec
}

void TestTimer::handleTimeOut3()
{
  OSAPI_LOG_DBG("Got timeout 3, rearming...");
  timer3_->reArm(); // Timeout in 1sec
}


void TestTimer::handler(unsigned long id, osapi::Message* m)
{
  switch(id)
  {
    case ID_TIME_OUT_1:
      handleTimeOut1();
      break;

    case ID_TIME_OUT_2:
      handleTimeOut2();
      break;

    case ID_TIME_OUT_3:
      handleTimeOut3();
      break;
      
    case ID_TERMINATE:
      OSAPI_LOG_DBG("Got termination signal");      
      running_=false;
      break;
      
    default:
      OSAPI_LOG_EMG("Arg, got unknown message");
  }
  
}


void TestTimer::run()
{
  OSAPI_LOG_DBG("Creating and arming timer...");
  timer1_ = osapi::createNewTimer(&mq_, ID_TIME_OUT_1);
  timer1_->arm(1000); // Timeout in 1sec

  timer2_ = osapi::createNewTimer(&mq_, ID_TIME_OUT_2);
  timer2_->arm(1000); // Timeout in 1sec

  timer3_ = osapi::createNewTimer(&mq_, ID_TIME_OUT_3);
  timer3_->arm(2500); // Timeout in 1sec

  OSAPI_LOG_DBG("Starting event loop");
  
  while(running_)
  {
    unsigned long id;
    osapi::Message* m = mq_.receive(id);
    handler(id, m);
    delete m;
  }

  timer1_->disArm();
  timer2_->disArm();
  timer3_->disArm();

  OSAPI_LOG_DBG("Thread terminating...");
}


int main(int argc, char* argv[])
{
  TestTimer tt;
  osapi::Thread t(&tt);
  t.start();
  osapi::sleep(4000);
  tt.getMsgQueue()->send(TestTimer::ID_TERMINATE);
  t.join();
  
  return 0;
}
