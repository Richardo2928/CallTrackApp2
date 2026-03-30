#ifndef AGENT_HPP_INCLUDED
#define AGENT_HPP_INCLUDED

#include <iostream>
#include <sstream>

#include "calllist.hpp"
#include "name.hpp"
#include "schedule.hpp"

enum Speciality {
    NONE = 0,
    DESKTOP = 1,
    PRINTERS = 2,
    LAPTOPS = 3,
    LINUX = 4,
    NETWORKS = 5,
    SERVERS = 6
    };

class Agent {
    private:
        int No_employee;
        int No_extension;
        int overtimeHours;
        Date auxDate;
        Speciality speciality;
        Name name;
        Schedule schedule;
        CallList call_list;
    public:
        Agent(/* args */);
        Agent(const Agent&);
        ~Agent();

        int getNoEmployee()const;
        int getNoExtension()const;
        int getOverTimeHours()const;
        Speciality getSpeciality()const;
        Name getName()const;
        Schedule getSchedule()const;
        CallList getCallList()const;

        void setNoEmployee(const int&);
        void setNoExtension(const int&);
        void setOverTimeHours(const int&);
        void setSpeciality(const Speciality&);
        void setName(const Name&);
        void setSchedule(const Schedule&);
        void insertCall(const Call&);
        void insertCall(Call*);
        void deleteCall(const long long&);
        void deleteAll();

        static bool cmpGoIName(const Agent&, const Agent&);
        static bool cmpLoIName(const Agent&, const Agent&);

        static bool cmpGoISpclity(const Agent&, const Agent&);
        static bool cmpLoISpclity(const Agent&, const Agent&);

        std::string toString();
        std::string specialityToStr();

        void saveCallList();

        void loadCallList();

        Agent& operator = (const Agent&);
        bool operator == (const Agent&)const;
        bool operator != (const Agent&)const;
        bool operator < (const Agent&)const;
        bool operator > (const Agent&)const;
        bool operator <= (const Agent&)const;
        bool operator >= (const Agent&)const;

        friend std::ostream& operator << (std::ostream&, const Speciality&);
        friend std::ostream& operator << (std::ostream&, const Agent&);
        friend std::istream& operator >> (std::istream&, Speciality&);
        friend std::istream& operator >> (std::istream&, Agent&);
    };

#endif // AGENT_HPP_INCLUDED
