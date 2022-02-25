#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <vector>

#include "WindlogData.h"
#include "readweather.h" //my own dedicated I/O class
#include "Time.h"
#include "Date.h"

void userFirstOption(WindlogData &WL);
void userSecondOption(WindlogData &WL);
void userThirdOption(WindlogData &WL);
void userFourthOption(WindlogData &WL, ofstream &ofile);
void userFifthOption(WindlogData &WL);

string printMonth(unsigned m);
float computeVarianceWindSpeed(float mean, vector<WindlogType> numbers);
float computeVarianceAirTemp(float mean, vector<WindlogType> numbers);
float roundNumber(float decimal);
float CovertFromWm2ToKWhm2(float wm2);
int selectDay();
int selectMonth();
int selectYear();

int main()
{
    WindlogData WL;
    ifstream infilelist("data/met_index.txt");
    string fileName = "";
    cout << "Loading data..."<< endl;
    while(getline(infilelist,fileName))
    {
        fileName = "data/" + fileName;
        ifstream infile(fileName.c_str());
        infile >> WL;
        infile.close();
    }
    infilelist.close();
    string input;
    do
    {
        cout << " " <<endl;
        cout <<"---------------------------------------------------------------------------------------------------------------" << endl;
        cout <<"                                              WINDLOG MENU                                                      " << endl;
        cout <<"---------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Enter '1': The average wind speed and sample standard deviation for the wind speed given a specified month and year."<<'\n';
        cout << "Enter '2': Average ambient air temperature and sample standard deviation for each month of a specified year"<<'\n';
        cout << "Enter '3': Total solar radiation in kWh/m^2 for each month of a specified year."<<'\n';
        cout << "Enter '4': Average wind speed(km/h), ambient air temperature and total solar radiation in kWh/m^2 for each month of a specified year. The standard deviation is printed in () next to the average in a file named 'WindTempSolar.csv"<<'\n';
        cout << "Enter '5': Times for the highest solar radiation in kWh/m2 of a specified date." << endl;
        cout << "Enter '6': Exit the program." << endl;
        cout << '\n' << "Enter one of the numbers to perform its operation: ";
        cin >> input;
        if(input == "1")
        {
            userFirstOption(WL);
        }
        else if(input == "2")
        {
            userSecondOption(WL);
        }
        else if(input == "3")
        {
            userThirdOption(WL);
        }
        else if(input == "4")
        {
            ofstream ofile("WindTempSolar.csv");
            userFourthOption(WL,ofile);
            ofile.close();
        }
        else if(input == "5")
        {
            userFifthOption(WL);
        }
        else if(input != "6")
        {
            cout << '\n' << "You have not made a valid selection." << endl;
        }
    }
    while(input != "6");
    return 0;
}

//The average wind speed and average temperature for a specified month and year.
void userFirstOption(WindlogData &WL)
{
    Date tempDate;

    unsigned int month = selectMonth();
    unsigned int year = selectYear();
    cout <<"---------------------------------------------------------------------------------------------------------------" << endl;
    cout <<"                The average wind speed and sample standard deviation for that wind speed                       " << endl;
    cout <<"---------------------------------------------------------------------------------------------------------------" << endl;
    if(month != 0 && year != 0)
    {
        vector<WindlogType> tempVector = WL.GetByMonth(month,year);
        float avgSpeed = 0; //wind speed
        float mean = 0;
        int count = 0;
        for(int i=0; i<tempVector.size(); i++)
        {
            avgSpeed += tempVector.at(i).S;
            count++;
        }
        mean = avgSpeed/count;

        //calculate standard deviation
        float variance = computeVarianceWindSpeed(mean, tempVector);
        float standardDeviation = sqrt(variance);

        if(count != 0)
        {
            cout << '\n' << printMonth(month) << " "
                 << year << ": "
                 << "Average speed: "<<roundNumber((avgSpeed/count)*3.6) << " km/h, " //times by 3.6 to convert to m/s to Km/h
                 << "Sample stdev: "<<roundNumber(standardDeviation)
                 << endl;
        }
        else
        {
            cout << '\n' << printMonth(month) << " "
                 << year << ": " << "No Data" << endl;
        }
    }
    else
    {
        cout << '\n' << "Input is invalid. Try again." << endl;
    }
}
//Average wind speed and average ambient air temperature for each month of a specified year. (print on screen only)
void userSecondOption(WindlogData &WL)
{
    Date tempDate;

    unsigned int year = selectYear();
    if(year != 0)
    {
        cout <<"---------------------------------------------------------------------------------------------------------------" << endl;
        cout <<"         Average ambient air temperature and sample standard deviation for each month in that year             " << endl;
        cout <<"---------------------------------------------------------------------------------------------------------------" << endl;
        cout << '\n' << year << endl;
        for(int i=1; i<13; i++)   //for each month
        {
            vector<WindlogType> tempVector = WL.GetByMonth(i,year);
            float avgTemp = 0; //temperature
            float mean = 0;
            int count = 0;
            for(int j=0; j<tempVector.size(); j++)
            {
                avgTemp += tempVector.at(j).T;
                count++;
            }
            mean = avgTemp/count;

            //calculate standard deviation
            float variance = computeVarianceAirTemp(mean, tempVector);
            float standardDeviation = sqrt(variance);

            if(count != 0)
            {
                cout << printMonth(i) << ": "
                     << "average: "<< roundNumber(avgTemp/count) << " degrees C, "
                     << "stdev: " << roundNumber(standardDeviation)
                     << endl;
            }
            else
            {
                cout << printMonth(i) << ": No Data" << endl;
            }
        }
    }
    else
    {
        cout << '\n' << "Input is invalid. Try again." << endl;
    }
}
//Total solar radiation in kWh/m^2 for each month of a specified year
void userThirdOption(WindlogData &WL)
{
    Date tempDate;

    unsigned int year = selectYear();
    if(year != 0)
    {
        cout <<"---------------------------------------------------------------------------------------------------------------" << endl;
        cout <<"                    The total solar radiation in kWh/m^2 for each month of a specified year                    " << endl;
        cout <<"---------------------------------------------------------------------------------------------------------------" << endl;
        cout << '\n' << year << endl;
        for(int i=1; i<13; i++)
        {
            vector<WindlogType> tempVector = WL.GetByMonth(i,year);
            float sum = 0; //of solar radiation
            int count = 0;
            for(int j=0; j<tempVector.size(); j++)
            {
                if(tempVector.at(j).SR >= 100)   //only values over 100
                {
                    sum += tempVector.at(j).SR;
                    count++;
                }
            }

            if(count != 0)
            {
                cout << printMonth(i) << ": "
                     << roundNumber(CovertFromWm2ToKWhm2(sum)) << " kWh/m2"
                     << endl;
            }
            else
            {
                cout << printMonth(i) << ": No Data" << endl;
            }
        }
    }
    else
    {
        cout << '\n' << "Input is invalid. Try again." << endl;
    }
}
//Average wind speed (km/h), average ambient air temperature and total solar radiation in kWh/m^2 for each month of aspecified year.
void userFourthOption(WindlogData &WL, ofstream &ofile)
{
    Date tempDate;

    unsigned int year = selectYear();
    if(year != 0)
    {
        cout <<"------------------------------------------------------------------------------------------------------------" << endl;
        cout <<"               Storing Avg ws, Avg aat, and sr with standard deviation in a CSV file                        " << endl;
        cout <<"------------------------------------------------------------------------------------------------------------" << endl;

        cout << '\n' << "Successfully printed to file 'WindTempSolar.csv'....." << endl;
        ofile << '\n' << year << '\n' << "  Month" << ',' << "  Avg ws" << ',' << "  Avg aat" << ',' << "  Total sr" << endl;
        bool found = false;
        for(int i=1; i<13; i++)
        {
            vector<WindlogType> tempVector = WL.GetByMonth(i,year);
            float avgSpeed = 0; //wind speed
            float avgTemp = 0; //temperature
            float avgSR = 0; //solar radiation
            float speedMean = 0;
            float TempMean = 0;
            int count = 0;

            for(int j=0; j<tempVector.size(); j++)
            {
                avgSpeed += tempVector.at(j).S;
                avgTemp += tempVector.at(j).T;
                if(tempVector.at(j).SR >= 100)   //only values over 100
                {
                    avgSR += tempVector.at(j).SR;
                }
                count++;
            }
            speedMean = avgSpeed/count;
            TempMean = avgTemp/count;

            //calculate standard deviation
            float varianceSpeed = computeVarianceWindSpeed(speedMean, tempVector);
            float stdDvSpeed = sqrt(varianceSpeed);

            float varianceTemp = computeVarianceAirTemp(TempMean, tempVector);
            float stdDvTemp = sqrt(varianceTemp);

            if(count != 0)
            {
                ofile << printMonth(i) << ","
                      << roundNumber((avgSpeed/count)*3.6)<<"("<<roundNumber(stdDvSpeed)<<")" << ","
                      << roundNumber(avgTemp/count) <<"("<<roundNumber(stdDvTemp)<<")"<< ","
                      << roundNumber(CovertFromWm2ToKWhm2(avgSR))<< endl;
                found = true;
            }
        }
        if(!found)
        {
            ofile << "No Data" << endl;
        }
    }
    else
    {
        cout << '\n' << "Input is invalid. Try again." << endl;
    }
}

// show the times for the highest solarradiation for that Date. Output to screen using this sample format: (There will be one or more
void userFifthOption(WindlogData &WL)
{
    Date tempDate;

    unsigned int day = selectDay();
    unsigned int month = selectMonth();
    unsigned int year = selectYear();
    if(day != 0 && month != 0 && year != 0)
    {
        cout <<"------------------------------------------------------------------------------------------------------------" << endl;
        cout <<"               Times for the highest solar radiation in kWh/m2 of a specified date                       " << endl;
        cout <<"------------------------------------------------------------------------------------------------------------" << endl;
        vector<WindlogType> tempVector = WL.GetByDay(day,month,year);
        if(tempVector.size() != 0)
        {
            vector<Time> timeVector;
            float highest = 0;
            for(int i=0; i<tempVector.size(); i++)
            {
                if(tempVector.at(i).SR > highest)
                {
                    timeVector.clear();
                    timeVector.push_back(tempVector.at(i).t);
                    highest = tempVector.at(i).SR;
                }
                else if(tempVector.at(i).SR == highest)
                {
                    timeVector.push_back(tempVector.at(i).t);
                }
            }
            cout << '\n' << "High solar radiation for the day: " <<
                 roundNumber(highest) << " W/m2" << endl;
            cout << "Time:" << endl;
            for(int i=0; i<timeVector.size(); i++)
            {
                cout << timeVector.at(i) << endl;
            }
        }
        else
        {
            cout << '\n' << "No data." << endl;
        }
    }
    else
    {
        cout << '\n' << "Input is invalid. Try again." << endl;
    }
}
//converts month to its text equivalent
string printMonth(unsigned m)
{
    string output = "";
    switch(m)
    {
    case 1:
        output = "January";
        break;
    case 2:
        output = "February";
        break;
    case 3:
        output = "March";
        break;
    case 4:
        output = "April";
        break;
    case 5:
        output = "May";
        break;
    case 6:
        output = "June";
        break;
    case 7:
        output = "July";
        break;
    case 8:
        output = "August";
        break;
    case 9:
        output = "September";
        break;
    case 10:
        output = "October";
        break;
    case 11:
        output = "November";
        break;
    case 12:
        output = "December";
        break;
    }
    return output;
}
//calculate varience for wind speed
float computeVarianceWindSpeed(float mean, vector<WindlogType> tempVector)
{
    float sum = 0;
    float count = 0;
    for(int i=0; i<tempVector.size(); i++)
    {
        sum += (tempVector.at(i).S - mean)*(tempVector.at(i).S - mean);
        count++;
    }

    return sum / (count - 1);
}
//calculate varience for air temperature
float computeVarianceAirTemp(float mean, vector<WindlogType> tempVector)
{
    float sum = 0;
    float count = 0;
    for(int i=0; i<tempVector.size(); i++)
    {
        sum += (tempVector.at(i).T - mean)*(tempVector.at(i).T - mean);
        count++;
    }

    return sum / (count - 1);
}
float roundNumber(float decimal)
{
    float value = (int)(decimal*10 + 0.5);
    return (float) value/10;
}

//Convert a float from W/m2 to kWh/m2
float CovertFromWm2ToKWhm2(float wm2)
{
    return((wm2*((float)1/6))/1000);
}

//ensures that user input in month and year is a valid input else returns error message
unsigned int validateInput(unsigned int valid)
{
    while(cin.fail())
    {
        cout << "Error: invalid input please try again " << endl;
        cin.clear();
        cin.ignore(256,'\n');
        cin >> valid;
    }
    return valid;
}

//function that let user input month else return false
int selectMonth()
{
    unsigned int month;
    bool b1 = true;
    while(b1)
    {
        cout << "Enter month: ";
        cin >> month;
        if( 1 <= month && month <= 12)
        {
            month = validateInput(month);
            b1 = false;
        }
        else
        {
            cout << '\n' << "Invalid month!" << '\n' << endl;
            month = validateInput(month);
        }
    }
    return month;
}

//function that let user input year else return false
int selectYear()
{
    unsigned int year;
    cout << "Please enter year: ";
    cin >> year;
    year = validateInput(year);
    return year;
}

//function that let user input year else return false
int selectDay()
{
    unsigned int day;
    bool b1 = true;
    while(b1)
    {
        cout << "Please enter day: ";
        cin >> day;
        if( 1 <= day && day <= 31)
        {
            day = validateInput(day);
            b1 = false;
        }
        else
        {
            cout << '\n' << "Invalid day!" << '\n' << endl;
            day = validateInput(day);
        }
    }
    return day;
}
