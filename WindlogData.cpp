#include "WindlogData.h"
WindlogData::WindlogData()
{
}
void WindlogData::Insert(WindlogType dataRow)
{
    Date newDate = dataRow.d;
    Time newTime = dataRow.t;
    if(WindlogMap.find(newDate.GetYear()) != WindlogMap.end())   //if year is not in map
    {
        if(WindlogMap.at(newDate.GetYear()).find(newDate.GetMonth()) != WindlogMap.at(newDate.GetYear()).end())   //if month is not in map
        {

            if(WindlogMap.at(newDate.GetYear()).at(newDate.GetMonth()).find(newDate.GetDay()) != WindlogMap.at(newDate.GetYear()).at(newDate.GetMonth()).end())   //if day is not in map
            {

                WindlogMap.at(newDate.GetYear()).at(newDate.GetMonth()).at(newDate.GetDay()).Insert(dataRow);
            }
            else
            {
                WindlogBST tempBST;
                tempBST.Insert(dataRow);

                WindlogMap.at(newDate.GetYear()).at(newDate.GetMonth()).insert(make_pair(newDate.GetDay(),tempBST));
            }
        }
        else
        {
            WindlogBST tempBST;
            tempBST.Insert(dataRow);
            DayMap dm;
            dm.insert(make_pair(newDate.GetDay(),tempBST));

            WindlogMap.at(newDate.GetYear()).insert(make_pair(newDate.GetMonth(),dm));
        }
    }
    else
    {
        WindlogBST tempBST;
        tempBST.Insert(dataRow);
        DayMap dm;
        dm.insert(make_pair(newDate.GetDay(),tempBST));
        MonthMap mm;
        mm.insert(make_pair(newDate.GetMonth(),dm));
        WindlogMap.insert(make_pair(newDate.GetYear(),mm));
    }
}

vector<WindlogType>& WindlogData::GetByMonth(int month,int year)
{
    WindlogVector.clear();
    if(WindlogMap.find(year) != WindlogMap.end())   //if selected year exists
    {
        if(WindlogMap.at(year).find(month) != WindlogMap.at(year).end())   //if selected month exists
        {
            MonthMapItr i = WindlogMap.at(year).find(month); //for that month
            for(DayMapItr j = i->second.begin(); j != i->second.end(); j++)
            {
                //for each day
                callback<WindlogType> tempCall;
                j->second.InOrder(tempCall.GetData);
                for(int k=0; k<tempCall.size(); k++)
                {
                    WindlogVector.push_back(tempCall[k]); //collect data
                }
                tempCall.clear();
            }
        }
    }
    return WindlogVector;
}
vector<WindlogType>& WindlogData::GetByDay(int day,int month,int year)
{
    WindlogVector.clear();
    if(WindlogMap.find(year) != WindlogMap.end())   //if exists
    {
        if(WindlogMap.at(year).find(month) != WindlogMap.at(year).end())  //if selected month exists
        {
            if(WindlogMap.at(year).at(month).find(day) !=
                    WindlogMap.at(year).at(month).end())   //if selected day exists
            {
                DayMapItr i = WindlogMap.at(year).at(month).find(day); //for that day
                callback<WindlogType> tempCall;
                i->second.InOrder(tempCall.GetData);
                for(int j=0; j<tempCall.size(); j++)
                {
                    WindlogVector.push_back(tempCall[j]); //collect data
                }
                tempCall.clear();
            }
        }
    }
    return WindlogVector;
}
