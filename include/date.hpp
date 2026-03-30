#ifndef DATE_HPP_INCLUDED
#define DATE_HPP_INCLUDED

#include <iostream>
#include <ctime>
#include <stdexcept>

class Date{
private:
    int day;
    int month;
    int year;

    bool isLeapYear(const int &) const;
public:
    Date();
    Date(const int&,const int&, const int&);
    Date(const int&,const int&);
    Date(const int&);

    bool isValid(const int&,const int &, const int&);
    bool isValid(const int&,const int&);
    bool isValidDay(const int&);
    bool isValidMonth(const int&);

    int getDay() const;
    int getMonth() const;
    int getYear() const;

    int getMaxDay() const;

    void setDay(const int&);
    void setMonth(const int&);
    void setYear(const int&);

    int toInt() const;
    std::string toStringFormat1() const;
    std::string toStringFormat2() const;

    Date& operator = (const Date&);
    bool operator == (const Date&)const;
    bool operator != (const Date&)const;
    bool operator < (const Date&)const;
    bool operator > (const Date&)const;
    bool operator <= (const Date&)const;
    bool operator >= (const Date&)const;

    friend std::ostream& operator << (std::ostream&, const Date&);
    friend std::istream& operator >> (std::istream&, Date&);
    };

#endif // DATE_HPP_INCLUDED
