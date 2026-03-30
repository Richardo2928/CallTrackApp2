#include "../include/call.hpp"

Call::Call() {}
Call::Call(const Call& otherCall) : user(otherCall.getUser()), callDuration(otherCall.getCallDuration()),
                                    callTime(otherCall.getCallTime()), callDate(otherCall.callDate) {}

Name Call::getUser()const {
    return user;
    }
Time Call::getCallDuration()const {
    return callDuration;
    }
Time Call::getCallTime()const {
    return callTime;
    }

Date Call::getCallDate()const {
    return callDate;
    }

void Call::setUser(const Name& nameUser) {
    user = nameUser;
    }
void Call::setCallDuration(const Time& inCallDura) {
    callDuration = inCallDura;
    }
void Call::setCallTime(const Time& inCallTm) {
    callTime = inCallTm;
    }

void Call::setCallDate(const Date& dt) {
    callDate = dt;
    }

Call& Call::operator = (const Call& otherCall) {
    if(*this == otherCall)
        return *this;

    this->callDuration = otherCall.callDuration;
    this->callTime = otherCall.callTime;
    this->user = otherCall.user;
    this->callDate = otherCall.callDate;
    return *this;
    }
bool Call::operator == (const Call& otherCall) const{
    return (user == otherCall.user)
           and (callDuration == otherCall.callDuration)
           and (callTime == otherCall.callTime)
           and (callDate == otherCall.callDate);
    }
bool Call::operator != (const Call& otherCall) const{
    return !(*this == otherCall);
    }
bool Call::operator < (const Call& otherCall) const{
    return (callTime < otherCall.callTime) || (callDate < otherCall.callDate);
    }
bool Call::operator > (const Call& otherCall) const{
    return !(*this < otherCall);
    }
bool Call::operator <= (const Call& otherCall) const{
    return (*this < otherCall) or (*this == otherCall);
    }
bool Call::operator >= (const Call& otherCall) const{
    return (*this > otherCall) or (*this == otherCall);
    }

std::ostream& operator << (std::ostream& os, const Call& c) {
    os << c.user << c.callDuration << '|' << c.callTime << std::endl <<
    c.callDate;

    return os;
    }

std::istream& operator >> (std::istream& is, Call& c) {
    std::string separator;

    is >> c.user;

    is >> c.callDuration;

    is.ignore();
    is >> c.callTime;

    is >> c.callDate;
    return is;
    }
