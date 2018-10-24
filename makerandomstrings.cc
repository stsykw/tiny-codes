/*
  dice code with boost library
  (c) yukawa satoshi 2007
 $Id: makerandomstrings.cc 12282 2016-03-03 03:51:42Z yuk $
 */

#include <iostream>
#include <boost/random.hpp>


int main(int argc,char* argv[]){
  boost::mt19937 rnd(12345678);
  boost::uniform_int<> range(32,126);
  boost::variate_generator<boost::mt19937&, boost::uniform_int<> >
  die(rnd,range);
  for(int j=0;j<40;j++){
    for(int i=0;i<60;i++){
      std::cout  <<  (char) die() ;
    }
    std::cout <<'\n';
  }
  return 0;
}
