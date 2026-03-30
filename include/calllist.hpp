#ifndef CALLLIST_HPP_INCLUDED
#define CALLLIST_HPP_INCLUDED

#include <string>
#include <exception>
#include <sstream>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "callnode.hpp"
#include "call.hpp"

class CallList {
    public:
        using Position = typename CallNode::Position;
    private:

        // CLASS LIST *****
        Position anchor;
        unsigned dataCount;

        /// BLOCK 0 **********
        bool isValidPos(const Position&)const;
        void copyAll(const CallList&);

        std::string intToString(unsigned);

        Position intToPos(const long long&)const;

    public:
        /// BLOCK 1 **********
        CallList();
        CallList(const CallList&);
        ~CallList();

        bool isEmpty()const;

        /// BLOCK 2 **********
        void insertData(const Position&, const Call&);//RECIBE UNA POSICION
        void insertData(const long long&, const Call&);//RECIBE UN ENTERO POSITIVO COMO POSICION
        void insertData(const Call&);//INSERCI�N SIEMPRE AL FINAL
        void insertData(Call*);//... PERO RECIBE UN APUNTADOR AL DATO
        void insertOrdered(const Call&);
        void insertOrdered(Call*);

        /// BLOCK 3 **********
        void deleteData(const Position&);
        void deleteData(const long long&);//...
        void deleteAll();

        /// BLOCK 4 **********
        Position getFirstPos()const;
        Position getLastPos()const;
        Position getPrevPos(const Position&);
        Position getNextPos(const Position&);

        /// BLOCK 5 **********
        Position findData(const Call&);
        Position explcitFindData(bool cmp(const Call&, const Call&), const Call&);
        Call retrive(const Position&)const;
        Call retrive(const long long&)const;//RECIBE UN ENTERO COMO POSICION

        std::string toString();
        unsigned int getDataCount()const;

        /// BLOCK 6 **********
        void saveData(const std::string&);
        void loadData(const std::string&);

        /// BLOCK 7 **********
        CallList& operator = (const CallList&);

        Call& operator [](const long long&);
        friend std::ostream& operator << (std::ostream&, const CallList&);
        friend std::istream& operator >> (std::istream&, CallList&);


        // LIST EXCEPTION *****
        //<>CLASS LIST EXCEPTION<> CLASS LIST EXCEPTION<>
        class CallListException : public std::exception {
            private:
                std::string msg;

            public:
                CallListException()noexcept : msg("Error indefinido") {}

                CallListException(const CallListException& ex) noexcept : msg(ex.msg) {}

                CallListException(const std::string& m) : msg(m) {}

                CallListException& operator = (const CallListException& ex) noexcept {
                    msg = ex.msg;
                    return *this;
                    }

                virtual ~CallListException() {}

                virtual const char* what() const noexcept {
                    return msg.c_str();
                    }
            };
    };


#endif // CALLLIST_HPP_INCLUDED