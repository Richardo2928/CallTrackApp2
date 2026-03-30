#ifndef CALL_HPP_INCLUDED
#define CALL_HPP_INCLUDED

#include <string>
#include <iostream>
#include <limits>
#include "time.hpp"
#include "name.hpp"
#include "date.hpp"

class Call {
    private:
        Name user;
        Time callDuration;
        Time callTime;
        Date callDate;
    public:
        Call();
        Call(const Call&);

        Name getUser()const;
        Time getCallDuration()const;
        Time getCallTime()const;
        Date getCallDate()const;

        void setUser(const Name&);
        void setCallDuration(const Time&);
        void setCallTime(const Time&);
        void setCallDate(const Date&);

        Call& operator = (const Call&);
        bool operator == (const Call&)const;
        bool operator != (const Call&)const;
        bool operator < (const Call&)const;
        bool operator > (const Call&)const;
        bool operator <= (const Call&)const;
        bool operator >= (const Call&)const;

        friend std::ostream& operator << (std::ostream&, const Call&);
        friend std::istream& operator >> (std::istream&, Call&);
    };

#endif // CALL_HPP_INCLUDED
