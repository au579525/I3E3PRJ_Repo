#define BOOST_TEST_MODULE
#include <cstdlib>
#include <iostream>

#include <boost/test/included/unit_test.hpp>

#include <osapi/Time.hpp>

BOOST_AUTO_TEST_CASE(test1)
{
  osapi::Time t(100), t2(200), t3(100);

  BOOST_CHECK( !(t>t2) );
  BOOST_CHECK(! ((t>t3) || (t<t3)) );
  BOOST_CHECK(t<=t3);
}



