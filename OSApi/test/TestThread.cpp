#include <iostream>
#include <osapi/Thread.hpp>
#include <osapi/Utility.hpp>

class TestThread : public osapi::ThreadFunctor
{
public:
protected:
  virtual void run()
  {
    int count = 0;
    
    for(;;)
    {
      std::cout << "Iteration : " << count << std::endl;
      ++count;
      if(count > 5)
        break;
      osapi::sleep(1000);
    }
    
  }

};


int main(int argc, char* argv[])
{
  {
    
    TestThread tt;

    osapi::Thread t(&tt);
    t.start();
    osapi::sleep(1000);
    t.setPriority(osapi::Thread::PRIORITY_ABOVE_NORMAL);
    osapi::sleep(1000);
    t.join();
    
  }
}
