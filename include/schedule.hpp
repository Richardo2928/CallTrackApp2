#ifndef SCHEDULE_HPP_INCLUDED
#define SCHEDULE_HPP_INCLUDED

#include <string>
#include <sstream>
#include <iostream>
#include "time.hpp"
class Schedule {
    private:
        /* data */
        Time inTime;
        Time outTime;
    public:
        Schedule(/* args */);
        Schedule(const Schedule&);
        Schedule(const Time&, const Time&);

        Time getInTime()const;
        Time getOutTime()const;

        void setInTime(const Time&);
        void setOutTime(const Time&);

        std::string toString();
        long long toInt()const;

        Schedule& operator = (const Schedule&);
        bool operator == (const Schedule&)const;
        bool operator != (const Schedule&)const;
        bool operator < (const Schedule&)const;
        bool operator > (const Schedule&)const;
        bool operator <= (const Schedule&)const;
        bool operator >= (const Schedule&)const;
        friend std::ostream& operator << (std::ostream&, const Schedule&);
        friend std::istream& operator >> (std::istream&, Schedule&);
    };

#endif // SCHEDULE_HPP_INCLUDED
