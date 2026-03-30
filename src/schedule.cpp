#include "../include/schedule.hpp"

Schedule::Schedule(/* args */){}
Schedule::Schedule(const Schedule& otherSch) : inTime(otherSch.inTime), outTime(otherSch.outTime){}
Schedule::Schedule(const Time& inT, const Time& outT) : inTime(inT), outTime(outT){}

Time Schedule::getInTime()const{
    return inTime;
    }
Time Schedule::getOutTime()const{
    return outTime;
    }

void Schedule::setInTime(const Time& tm){
    inTime = tm;
    }
void Schedule::setOutTime(const Time& tm){
    outTime = tm;
    }

std::string Schedule::toString(){
    std::stringstream ss;

    ss << "[Entrada]" << inTime << "[Salida]" << outTime;
    return ss.str();
    }
long long Schedule::toInt()const{
    return inTime.toInt() - outTime.toInt();
    }

Schedule& Schedule::operator = (const Schedule& otherSch){
    if(*this == otherSch)
        return *this;

    this->inTime = otherSch.inTime;
    this->outTime = otherSch.outTime;
    return *this;
    }
bool Schedule::operator == (const Schedule& otherSch)const{
    return (this->inTime == otherSch.inTime) && (this->outTime == otherSch.outTime);
    }
bool Schedule::operator != (const Schedule& otherSch)const{
    return !(*this == otherSch);
    }
bool Schedule::operator < (const Schedule& otherSch)const{
    return this->toInt() < otherSch.toInt();
    }
bool Schedule::operator > (const Schedule& otherSch)const{
    return this->toInt() > otherSch.toInt();
    }
bool Schedule::operator <= (const Schedule& otherSch)const{
    return !(*this > otherSch);
    }
bool Schedule::operator >= (const Schedule& otherSch)const{
    return !(*this < otherSch);
    }
std::ostream& operator << (std::ostream& os, const Schedule& sch){
    os << "[Entrada]" << sch.inTime << std::endl <<
    "[Salida]" << sch.outTime;

    return os;
    }
std::istream& operator >> (std::istream& is, Schedule& sch){
    std::string separator;
    std::getline(is, separator, ']');
    is >> sch.inTime;
    std::getline(is, separator, ']');
    is >> sch.outTime;

    return is;
    }
