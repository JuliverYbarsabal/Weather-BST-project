//time.cpp
//
// class for managing time information
//
// Version
// 11/04/2021 Juliver Ybarsabal
//    Started
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes

#include "Time.h"

//----------------------------------------------------------------------------
//Default Constructor
Time::Time()
{
    hours = 0;
    minutes = 0;
}

//----------------------------------------------------------------------------
//Constructor with Parameter
Time::Time(int h, int m)
{
    hours = h;
    minutes = m;
}

//----------------------------------------------------------------------------
//This function will set the value of hours
void Time::SetHours(int h)
{
    hours = h;
}

//----------------------------------------------------------------------------
//This function will set the value of minutes
void Time::SetMinutes(int m)
{
    minutes = m;
}

//----------------------------------------------------------------------------
//This function will get the value of hours
int Time::GetHours() const
{
    return hours;
}

//----------------------------------------------------------------------------
//This function will get the value of minutes
int Time::GetMinutes() const
{
    return minutes;
}

bool Time::operator ==( const Time & other )
{
    if(this->GetHours() == other.GetHours())
    {
        if(this->GetMinutes() == other.GetMinutes())
        {
            return true;
        }
    }
    return false;
}
bool Time::operator <( const Time & other )
{
    if(this->GetHours() < other.GetHours())
    {
        if(this->GetMinutes() < other.GetMinutes())
        {
            return true;
        }
    }
    return false;
}
bool Time::operator >( const Time & other )
{
    if(this->GetHours() > other.GetHours())
    {
        if(this->GetMinutes() > other.GetMinutes())
        {
            return true;
        }
    }
    return false;
}
