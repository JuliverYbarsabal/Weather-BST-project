#ifndef WINDLOGDATA_H
#define WINDLOGDATA_H
#include <map>
#include "BST.h"
#include "callback.h"
#include "Date.h"
#include "Time.h"

struct WindlogType
{
    /** date */
    Date d;
    /** time */
    Time t;
    /** Wind Speed*/
    float S;
    /** Solar Radiation*/
    float SR;
    /** Ambient Air Temperature */
    float T;
    bool operator <( const WindlogType & other )
    {
        return(t < other.t);
    }
    bool operator >( const WindlogType & other )
    {
        return(t > other.t);
    }
    bool operator ==( const WindlogType & other )
    {
        return(t == other.t);
    }
};
//Typedefs to make your code more clear
//Typedefs to make your code easier to modify
typedef BST<WindlogType> WindlogBST;
typedef map<int,WindlogBST> DayMap;
typedef map<int,DayMap> MonthMap;
typedef map<int,MonthMap> YearMap;
typedef DayMap::iterator DayMapItr;
typedef MonthMap::iterator MonthMapItr;
/**
* @author Juliver
* @date 25/05/2021
* @section description
* @brief The WindlogData class represents an accumulation of WindlogType data organised by date.
*/
class WindlogData
{
public:
    /**
    * @brief A constructor.
    * Construct a blank Windlog data object with no parameters.
    */
    WindlogData();
    /**
    * @brief Add a row of Windlogdata.
    * Inserts an instance of WindlogType sorted by date.
    * @param WindlogType dataRow
    * @return void
    */
    void Insert(WindlogType dataRow);
    /**
    * @brief Returns vector of Windlog data of a month and year.
    * used in userFirstOption, userSecondOption, userThirdOption, userFourthOption
    * @param int month, int year
    * @return vector<WindlogType>&
    */
    vector<WindlogType>& GetByMonth(int month,int year);
    /**
    * @brief Returns vector of Windlog data of a day, month and year.
    * used in userfifthOption
    * @param int day, int month, int year
    * @return vector<WindlogType>&
    */
    vector<WindlogType>& GetByDay(int day,int month,int year);
private:
    /** All Windlog data */
    YearMap WindlogMap;
    /** Currently extracted Windlog data */
    vector<WindlogType> WindlogVector;
};
#endif // WindlogDATA_
