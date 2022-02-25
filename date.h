// date.h
// A class that stores essential information to record date including day, month, year

//---------------------------------------------------------------------------------
#ifndef DATE_H
#define DATE_H

//---------------------------------------------------------------------------------
#include<iostream>
#include<string>

using namespace std;
//---------------------------------------------------------------------------------

/**
* @class date
* @brief  Manages all function and information to record date
*
* day, month, year are being stored as integer number.\n
*
* @author Juliver Ybarsabal
* @version 01
* @date 24/05/2021 Juliver, Started
*
*
* @bug My program has no bugs. Well, maybe it has...
*/
class Date
{
public:
    /**
    * @brief  Default Constructor
    *
    * This function wills set day, month, year to 1/1/2000 by defualt
    *
    * @return none
    */
    Date();

    /**
    * @brief  Constructor with Parameter
    *
    * This function wills set day, month, year according to the parameter
    *
    * @param takes value of day, month, year in as integer number
    * @return none
    */
    Date(int d, int m, int y);

    /**
    * @brief  Public function to set the value of day
    *
    * @param d - value of day
    * @return void
    */
    void SetDay(int d);

    /**
    * @brief  Public function to set the value of month
    *
    * @param m - value of month
    * @return void
    */
    void SetMonth(int m);

    /**
    * @brief  Public function to set the value of year
    *
    * @param y - value of year
    * @return void
    */
    void SetYear(int y);

    /**
    * @brief  Public function to get the value of day
    *
    * retrieve day value within time class
    *
    * @return int
    */
    int GetDay() const;

    /**
    * @brief  Public function to get the value of month
    *
    * retrieve month value within time class
    *
    * @return int
    */
    int GetMonth() const;

    /**
    * @brief  Public function to get the value of year
    *
    * retrieve year value within time class
    *
    * @return int
    */
    int GetYear() const;

    void SetDate (int d, int m, int y);

    /**
    * @brief Determine if two dates are equal.
    *
    * used in BST template
    * used as a defaut operator==
    *
    * @return bool
    */
    bool operator ==( const Date & other );
    /**
    * @brief Determine if a date is before another date.
    *
    * used in BST template
    * used as a defaut operator <
    * @return bool
    */
    bool operator <( const Date & other );
    /**
    * @brief Determine if a date is after another date.
    *
    * used in BST template
    * used as a defaut operator >
    *
    * @return bool
    */
    bool operator >( const Date & other );


private:
    int day; /// one int number of day
    int month; /// one int number of month
    int year; /// one int number of year
};
#endif // DATE_H
