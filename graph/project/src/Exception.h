#ifndef Exception_h
#define Exception_h

#include "Defs.h"

/* The Exception Interface, anything that implements this is an exception */
struct BaseException
{
        private:
                uint            lineno;
                std::string     filename;
        virtual void where(const uint, const char *) = 0;
        virtual void speak() = 0;
};

struct NoImpl : public BaseException
{
        where(const char * const, const int)
        speak();
}
