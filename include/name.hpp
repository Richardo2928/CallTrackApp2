#ifndef NAME_H_INCLUDED
#define NAME_H_INCLUDED

#include <string>
#include <iostream>
class Name {
    private:
        /* data */
        std::string first;
        std::string last;

        bool theresNoNameLol();
    public:
        Name(/* args */);
        Name(const Name&);
        Name(const std::string&, const std::string&);

        std::string getFirst()const;
        std::string getLast()const;

        void setFirst(const std::string&);
        void setLast(const std::string&);

        std::string toString()const;
        Name& operator = (const Name&);
        bool operator == (const Name&)const;
        bool operator != (const Name&)const;
        bool operator < (const Name&)const;
        bool operator > (const Name&)const;
        bool operator <= (const Name&)const;
        bool operator >= (const Name&)const;
        friend std::ostream& operator << (std::ostream&, const Name&);
        friend std::istream& operator >> (std::istream&, Name&);
    };

#endif // NAME_H_INCLUDED
