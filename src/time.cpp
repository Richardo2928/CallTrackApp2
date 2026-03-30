#include "../include/time.hpp"

bool Time::isValid(const Time& t) {
    return (t.getHour() <=24 and t.getHour() >= 0 )
           and (t.getMinute() <= 59 and t.getMinute() >= 0)
           and (t.getSecond() <= 59 and t.getSecond() >= 0);
    }

Time::Time():hour(0),minute(0),second(0) {}

Time::Time(const int& hour, const int& minute) {
    this->hour = hour;
    this->hour = minute;
    this->second = 0;
    }
Time::Time(const int& hour, const int& minute, const int& second) {
    if ((hour >= 0) || (hour < 24)){
        this->hour = hour;
        }
    else{
        this->hour = 0;
        }
    if ((minute >= 0) || (minute < 60)){
        this->minute = minute;
        }
    else{
        this->minute = 0;
        }
    if ((second >= 0) || (second < 60)){
        this->second = second;
        }
    else {
        this->second = 0;
        }
    }

Time::Time(const Time& otherTime){
    if(isValid(otherTime)){
        hour = otherTime.getHour();
        minute = otherTime.getMinute();
        second = otherTime.getSecond();
        }
    else{
        hour = 0;
        minute = 0;
        second = 0;
        }
    }
int Time::getHour()const {
    return hour;
    }
int Time::getMinute()const {
    return minute;
    }
int Time::getSecond()const {
    return second;
    }

void Time::setHour(const int& h) {
    if ((h >= 0) || (h < 24)){
        hour = h;
        return;
        }
    hour = 0;
    }
void Time::setMinute(const int& m) {
    if ((m >= 0) || (m < 60)){
        minute = m;
        return;
        }
    minute = 0;
    }
void Time::setSecond(const int& s) {
    if ((s >= 0) || (s < 0)){
        second = s;
        }
    second = 0;
    return;
    }

long long Time::toInt()const {
    long long time;
    time = (hour * 1000) + (minute * 100) + second;

    return time;
    }

std::string Time::toString()const{
    std::stringstream ss;

    ss << hour << ':' << minute << ':' << second;
    return ss.str();
    }

Time& Time::operator = (const Time& otherTime) {
    hour = otherTime.hour;
    minute = otherTime.minute;
    second = otherTime.second;

    return *this;
    }
Time Time::operator + (const Time& otherTime) {
    Time tm;
    tm.hour = this->hour + otherTime.hour;
    tm.minute = this->minute + otherTime.minute;
    tm.second = this->second + otherTime.second;

    return tm;
    }
bool Time::operator == (const Time& otherTime) const{
    return this->toInt() == otherTime.toInt();
    }
bool Time::operator != (const Time& otherTime) const{
    return !(*this == otherTime);
    }
bool Time::operator < (const Time& otherTime) const{
    return this->toInt() < otherTime.toInt();
    }
bool Time::operator > (const Time& otherTime) const{
    return !(*this < otherTime or *this == otherTime);
    }
bool Time::operator <= (const Time& otherTime) const{
    return (*this < otherTime)or (*this == otherTime);
    }
bool Time::operator >= (const Time& otherTime) const{
    return (*this > otherTime) or (*this == otherTime);
    }

std::ostream& operator << (std::ostream& os, const Time& t) {
    os << t.hour << ':' << t.minute << ':' << t.second;

    return os;
    }
std::istream& operator >> (std::istream& is, Time& t) {
    is >> t.hour;
    is.ignore();
    is >> t.minute;
    is.ignore();
    is >> t.second;

    return is;
    }
