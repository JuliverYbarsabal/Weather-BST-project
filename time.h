// time.h
// A class that stores essential information to record time including hours and minutes

//---------------------------------------------------------------------------------
#ifndef TIME_H
#define TIME_H

//---------------------------------------------------------------------------------
#include <iostream>
#include <string>

using namespace std;

//--------------------------------------------------------------------------------

/**
* @class time
* @brief  Manages all function and information to record time
*
* hours and minutes are being stored as integer number.\n
*
* @author Juliver Ybarsabal
* @version 01
* @date 11/04/2021 Juliver, Started
*
*
* @bug My program has no bugs. Well, maybe it has...
*/
class Time
{
public:
    /**
    * @brief  Default Constructor
    *
    * This function wills set hours and minutes to 0
    *
    * @return none
    */
    Time();

    /**
    * @brief  Constructor with Parameter
    *
    * This function wills set hours and minutes according to the parameter
    *
    * @param takes value of hours and minutes in as integer number
    * @return none
    */
    Time(int h, int m);

    /**
    * @brief  Public function to set the value of hours
    *
    * @param h - value of hours
    * @return void
    */
    void SetHours(int h);

    /**
    * @brief  Public function to set the value of minutes
    *
    * @param m - value of minutes
    * @return void
    */
    void SetMinutes(int m);

    /**
    * @brief  Public function to get the value of hours
    *
    * retrieve hours value within time class
    *
    * @return int
    */
    int GetHours() const;

    /**
    * @brief  Public function to get the value of minutes
    *
    * retrieve minutes value within time class
    *
    * @return int
    */
    int GetMinutes() const;

    /**
    * @brief Determine if a time equal another time.
    *
    * @return bool
    */
    bool operator ==( const Time & other );
    /**
    * @brief Determine if a time is before another time.
    *
    * @return bool
    */
    bool operator <( const Time & other );
    /**
    * @brief Determine if a time is after another time.
    *
    * @return bool
    */
    bool operator >( const Time & other );

private:
    int hours; /// one int number of hours
    int minutes; /// one int number of minutes
};
#endif // TIME_H

