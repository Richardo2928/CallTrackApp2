#ifndef AGENTLIST_HPP_INCLUDED
#define AGENTLIST_HPP_INCLUDED

#include <string>
#include <sstream>
#include <stdlib.h>
#include <filesystem>

#include <iostream>

#include "agentnode.hpp"
#include "agentlistexception.hpp"

class AgentList {
    public:
        typedef AgentNode* Position;
    private:
        Position headerPtr;
        unsigned dataCount;
        //<>MEMBER FUCTIONS<>MEMBER FUCTIONS<>MEMBER FUCTIONS
        ///BLOCK 00
        bool isValidPos(const Position&)const;
        void copyAll(const AgentList&);

        Position intToPos(const unsigned&);
        void sortBy(bool(const Agent&, const Agent&),bool(const Agent&, const Agent&),
                    const Position&, const Position&);
        void swapPtr(const Position&, const Position&);

    public:
        ///BLOCK 1
        AgentList();
        AgentList(const AgentList&);
        ~AgentList();

        bool isEmpty()const;
        bool isIn(const Agent&)const;
        ///BLOCK 2
        void insertData(const Position&, const Agent&);//POSICION DE LISTA
        void insertData(const unsigned&, const Agent&);//POSICION ENTERA
        void insertData(const Agent&);//INSERCI�N SIEMPRE AL FINAL
        void insertData(Agent*);//... PERO RECIBE UN APUNTADOR AL DATO
        void insertOrdered(const Agent&);
        void insertOrdered(Agent*);

        ///BLOCK 3
        void deleteData(const Position&);
        void deleteData(const unsigned&);//...
        void deleteAll();

        ///BLOCK 3
        Position getFirstPos()const;
        Position getLastPos()const;
        Position getPrevPos(const Position&);
        Position getNextPos(const Position&);
        ///BLOCK 4
        int findDataInt(const Agent&)const;
        Position findData(const Agent&)const;
        Position explcitFindData(bool(const Agent&, const Agent&), const Agent&);

        Agent retrive(const Position&);
        Agent retrive(const long long&);
        ///BLOCK 5
        std::string toString();
        void sortBy(bool(const Agent&, const Agent&),bool(const Agent&, const Agent&));
        unsigned getDataCount()const;

        ///BLOCK 6
        void saveData();
        void loadData();
        ///BLOCK 7
        AgentList& operator =(const AgentList&);
        Agent& operator [](const int&);
    };

#endif // AGENTLIST_HPP_INCLUDED