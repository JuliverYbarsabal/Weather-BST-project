//date.cpp
//
// class for managing date information
//
// Version
// 11/04/2021 Juliver Ybarsabal
//    Started
//---------------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Includes
#include <iostream>
#include "Date.h"

//----------------------------------------------------------------------------
//Default Constructor
Date::Date()
{
    day = 1;
    month = 1;
    year = 2000;
}

//----------------------------------------------------------------------------
//Constructor with Parameter
Date::Date(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}

//----------------------------------------------------------------------------
//This function will set the value of day
void Date::SetDay(int d)
{
    day = d;
}

//----------------------------------------------------------------------------
//This function will set the value of month
void Date::SetMonth(int m)
{
    month = m;
}

//----------------------------------------------------------------------------
//This function will set the value of year
void Date::SetYear(int y)
{
    year = y;
}

//----------------------------------------------------------------------------
//This function will get the value of day
int Date::GetDay() const
{
    return day;
}

//----------------------------------------------------------------------------
//This function will get the value of month
int Date::GetMonth() const
{
    return month;
}

//----------------------------------------------------------------------------
//This function will get the value of year
int Date::GetYear() const
{
    return year;
}

void Date::SetDate(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}

bool Date::operator ==( const Date & other )
{
    if(this->GetYear() == other.GetYear())
    {
        if(this->GetMonth() == other.GetMonth())
        {
            if(this->GetDay() == other.GetDay())
            {
                return true;
            }
        }
    }
    return false;
}
bool Date::operator >( const Date & other )
{
    if(this->GetYear() > other.GetYear())
    {
        return true;
    }
    else if(this->GetYear() == other.GetYear())
    {
        if(this->GetMonth() > other.GetMonth())
        {
            return true;
        }
        else if(this->GetMonth() == other.GetMonth())
        {
            if(this->GetDay() > other.GetDay())
            {
                return true;
            }
        }
    }
    return false;
}
bool Date::operator <( const Date & other )
{
    if(this->GetYear() < other.GetYear())
    {
        return true;
    }
    else if(this->GetYear() == other.GetYear())
    {
        if(this->GetMonth() < other.GetMonth())
        {
            return true;
        }
        else if(this->GetMonth() == other.GetMonth())
        {
            if(this->GetDay() < other.GetDay())
            {
                return true;
            }
        }
    }
    return false;
}
