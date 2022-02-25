#include "readweather.h"


istream &operator >>(istream &input, WindlogData &WL)
{
    string line;
    while (!input.eof())
    {

            bool valid = true;
//Date and Time
//Date
            string tday, tmonth, tyear, tmin, thour, dwind, dsRad, dtemp;;
            getline(input, tday, '/');
            getline(input, tmonth,'/');
            getline(input, tyear, ' ');
            Date d(atoi(tday.c_str()),atoi(tmonth.c_str()),atoi(tyear.c_str()));
            if(d.GetDay() == 0 && d.GetMonth() == 0 && d.GetYear() == 0)
            {
                valid = false;
            }
//Time
            getline(input, thour,':');
            getline(input, tmin,',');
            int hours = atoi(thour.c_str());
            int minutes = atoi(tmin.c_str());
            if(hours == 0)
            {
                if(thour != "0" && thour != "00")
                {
                    valid = false;
                }
            }
            if(minutes == 0)
            {
                if(tmin != "0" && tmin != "00")
                {
                    valid = false;
                }
            }
            Time t(hours,minutes);
            if(t.GetHours() == 24 && t.GetMinutes() == 60)
            {
                valid = false;
            }


            //S
            for(int i = 0; i<9; i++)
            {
                input.ignore(256, ',');
            }
            getline(input, dwind, ',');
            float S = atof(dwind.c_str());
            if(S == 0)
            {
                if(dwind != "0")
                {
                    valid = false;
                }
            }
            //SR
            getline(input, dsRad, ',');
            float SR = atof(dsRad.c_str());
            if(SR == 0)
            {

                if(dsRad != "0")
                {
                    valid = false;
                }
            }

            //T
            for(int i = 0; i<5; i++)
            {
                input.ignore(256, ',');
            }
            getline(input, dtemp, '\n');
            float T = atof(dtemp.c_str());
            if(T == 0)
            {
                if(dtemp != "0")
                {
                    valid = false;
                }
            }
            if(valid)
            {
                WindlogType tempWST;
                tempWST.d = d;
                tempWST.t = t;
                tempWST.S = S;
                tempWST.SR = SR;
                tempWST.T = T;
                WL.Insert(tempWST);
            }
    }
    return input;
}


ostream &operator <<(ostream &os, const Time &T)
{
    if(T.GetHours() == 24 && T.GetMinutes() == 60)   //fix with invalid time later
    {
        os << "--:--";
    }
    else
    {
//output hours
        if(T.GetHours() < 10)
        {
            os << "0" << T.GetHours();
        }
        else
        {
            os << T.GetHours();
        }
        os << ":";
//output minutes
        if(T.GetMinutes() < 10)
        {
            os << "0" << T.GetMinutes();
        }
        else
        {
            os << T.GetMinutes();
        }
    }
    return os;
}
