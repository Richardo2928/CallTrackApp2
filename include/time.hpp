#ifndef TIME_HPP_INCLUDED
#define TIME_HPP_INCLUDED

#include <string>
#include <sstream>
#include <iostream>
class Time {
    private:
        int hour;
        int minute;
        int second;
        bool isValid(const Time&);
    public:
        Time();
        Time(const Time&);
        Time(const int&, const int&);
        Time(const int&, const int&, const int&);

        int getHour()const;
        int getMinute()const;
        int getSecond()const;

        void setHour(const int&);
        void setMinute(const int&);
        void setSecond(const int&);

        long long toInt()const;
        std::string toString()const;

        Time& operator = (const Time&);
        Time operator + (const Time&);
        bool operator == (const Time&)const;
        bool operator != (const Time&)const;
        bool operator < (const Time&)const;
        bool operator > (const Time&)const;
        bool operator <= (const Time&)const;
        bool operator >= (const Time&)const;

        friend std::ostream& operator << (std::ostream&, const Time&);
        friend std::istream& operator >> (std::istream&, Time&);
    };

#endif // TIME_HPP_INCLUDED
