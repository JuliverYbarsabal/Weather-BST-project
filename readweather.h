#ifndef READWEATHER_H
#define READWEATHER_H
#include <iostream>

#include "Time.h"
#include "WindlogData.h"

/**My own dedicated I/O class**/
//input stream operator
istream & operator >>(istream &input, WindlogData &WD);

//used in userFifthOption
//output for time "--:--"
ostream & operator <<(ostream &os, const Time &T);
#endif // READWEATHER_H
