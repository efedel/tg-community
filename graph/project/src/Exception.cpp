#ifndef Exception_h
#define Exception_h

#include <iostream>
#include "Exception.h"

using namespace std;


NoImpl::NoImpl(const char * const fname, const int line) 
{ 
        std::cout << fname      
                << ":" 
                << line 
                << " Not Implemented yet, slacker!" 
                << std::endl;
}

#endif
