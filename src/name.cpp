#include "../include/name.hpp"

Name::Name() : first(""), last(""){}
Name::Name(const Name& otherName):first(otherName.getFirst()),last(otherName.getLast()){}
Name::Name(const std::string& frst, const std::string& lst):first(frst),last(lst){}

std::string Name::getFirst()const{
    return first;
    }
std::string Name::getLast()const{
    return last;
    }

void Name::setFirst(const std::string& frst){
    first = frst;
    }
void Name::setLast(const std::string& lst){
    last = lst;
    }

std::string Name::toString()const{
    std::string _name;
    if (last == ""){
        _name = first;
        }
    else{
        _name = first + ' ' + last;
        }

    return _name;
    }
Name& Name::operator = (const Name& otherName){
    if(this == &otherName)
        return *this;

    this->first = otherName.first;
    this->last = otherName.last;

    return *this;
    }
bool Name::operator == (const Name& otherName)const{
    return this->toString() == otherName.toString();
    }
bool Name::operator != (const Name& otherName)const{
    return !(*this == otherName);
    }
bool Name::operator < (const Name& otherName)const{
    return this->toString() < otherName.toString();
    }
bool Name::operator > (const Name& otherName)const{
    return this->toString() > otherName.toString();
    }
bool Name::operator <= (const Name& otherName)const{
    return !(this->toString() > otherName.toString());
    }
bool Name::operator >= (const Name& otherName)const{
    return !(this->toString() < otherName.toString());
    }
std::ostream& operator << (std::ostream& os, const Name& nm){
    os << "[Nombre]" << nm.getFirst() << '|' << nm.getLast() << std::endl;

    return os;
    }
std::istream& operator >> (std::istream& is, Name& nm){
    std::string separator;
    std::getline(is, separator, ']');
    std::getline(is, nm.first, '|');
    std::getline(is, nm.last);
    return is;
    }
