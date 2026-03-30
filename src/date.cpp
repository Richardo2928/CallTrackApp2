#include "../include/date.hpp"

bool Date::isLeapYear(const int &y) const {
    return (y % 4 == 0 && (y % 100 != 0 || y % 400 == 0));
    }

Date::Date() {
    time_t now = time(0);
    tm* ltm = localtime(&now);

    day = ltm->tm_mday;
    month = ltm->tm_mon + 1;
    year = ltm->tm_year + 1900;
    }

Date::Date(const int &d,const int &m, const int &y) {
    if (!isValid(d,m,y)) {
        throw std::invalid_argument("Fecha invalida");
        }

    day = d;
    month = m;
    year = y;
    }

Date::Date(const int &d,const int&m) {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    year = ltm->tm_year + 1900;

    if (!isValid(d,m)) {
        throw std::invalid_argument("Fecha invalida");
        }

    day = d;
    month = m;
    }

Date::Date(const int &d) {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    month = ltm->tm_mon + 1;
    year = ltm->tm_year + 1900;

    if (!isValidDay(d)) {
        throw std::invalid_argument("Fecha invalida");
        }

    day = d;
    }

bool Date::isValid(const int &d,const int &m, const int &y) {
    if ((m < 1) || (m > 12) || (d < 1) || (d > 31)) {
        return false;
        }

    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDays = daysInMonth[m - 1];

    if (m == 2 && isLeapYear(y)) {
        maxDays = 29;
        }

    return ((d >= 1) && (d <= maxDays));
    }

bool Date::isValid(const int &d, const int &m) {
    if ((m < 1) || (m > 12) || (d < 1) || (d > 31)) {
        return false;
        }

    static const int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int maxDays = daysInMonth[m - 1];

    if (m == 2 && isLeapYear(year)) {
        maxDays = 29;
        }

    return ((d >= 1) && (d <= maxDays));
    }

bool Date::isValidDay(const int &d) {
    if ((d < 1) || (d > 31)) {
        return false;
        }

    int maxDays = getMaxDay();

    if (month == 2 && isLeapYear(year)) {
        maxDays = 29;
        }

    return ((d >= 1) && (d <= maxDays));
    }

bool Date::isValidMonth(const int &m) {
    if ((m < 1) || (m > 12)) {
        return false;
        }

    switch (m) {
        case 2:
            return day <= (isLeapYear(year) ? 29 : 28);
        case 4:
        case 6:
        case 9:
        case 11:
            return (day <= 30);
        default:
            return (day <= 31);
        }
    }

int Date::getDay() const {
    return day;
    }

int Date::getMonth() const {
    return month;
    }

int Date::getYear() const {
    return year;
    }

int Date::getMaxDay() const {
    switch (month) {
        case 2:
            return isLeapYear(year) ? 29 : 28;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            return 31;
        }
    }

void Date::setDay(const int &d) {
    if (!isValidDay(d)) {
        throw std::invalid_argument("Dia invalido");
        }

    day = d;
    }

void Date::setMonth(const int &m) {
    if (!isValidMonth(m)) {
        throw std::invalid_argument("Mes invalido");
        }

    month = m;
    }

void Date::setYear(const int &y) {
    year = y;
    }

int Date::toInt() const {
    return (year * 1000) + (month * 10) + day;
    }

std::string Date::toStringFormat1() const {
    return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    }

std::string Date::toStringFormat2() const {
    std::string mnth;
    switch (month) {
        case 1:
            mnth = "Enero";
            break;
        case 2:
            mnth = "Febrero";
            break;
        case 3:
            mnth = "Marzo";
            break;
        case 4:
            mnth = "Abril";
            break;
        case 5:
            mnth = "Mayo";
            break;
        case 6:
            mnth = "Junio";
            break;
        case 7:
            mnth = "Julio";
            break;
        case 8:
            mnth = "Agosto";
            break;
        case 9:
            mnth = "Septiembre";
            break;
        case 10:
            mnth = "Octubre";
            break;
        case 11:
            mnth = "Noviembre";
            break;
        case 12:
            mnth = "Diciembre";
            break;
        }

    return std::to_string(day) + "/" + mnth + "/" + std::to_string(year);
    }

Date& Date::operator = (const Date& otherDate) {
    if(*this == otherDate)
        return *this;

    day = otherDate.day;
    month = otherDate.month;
    year = otherDate.year;
    return *this;
    }
bool Date::operator == (const Date& otherDate) const {
    return toInt() == otherDate.toInt();
    }
bool Date::operator != (const Date& otherDate) const {
    return !(*this == otherDate);
    }
bool Date::operator < (const Date& otherDate) const {
    return toInt() < otherDate.toInt();
    }
bool Date::operator > (const Date& otherDate) const {
    return !(*this < otherDate);
    }
bool Date::operator <= (const Date& otherDate) const {
    return (*this < otherDate) or (*this == otherDate);
    }
bool Date::operator >= (const Date& otherDate) const {
    return (*this > otherDate) or (*this == otherDate);
    }

std::ostream& operator << (std::ostream& os, const Date& d) {
    os << d.toStringFormat1();

    return os;
    }

std::istream& operator >> (std::istream& is, Date& d) {

    is >> d.day;

    is.ignore();
    is >> d.month;

    is.ignore();
    is >> d.year;

    return is;
    }
