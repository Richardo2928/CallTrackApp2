#ifndef AGENTNODE_HPP_INCLUDED
#define AGENTNODE_HPP_INCLUDED

#include "agent.hpp"
#include "agentnodeexception.hpp"

class AgentNode {
public:
    typedef AgentNode* Position;
    private:
        Agent* dataPtr;
        Position next;
        Position prev;
    public:

        AgentNode();
        AgentNode(const Position&);
        AgentNode(const Agent&);
        AgentNode(Agent*);
        //GETTERS
        Agent* getDataPtr();
        Agent& getData();
        Position getNext()const;
        Position getPrev()const;
        //SETTERS
        void setDataPtr(Agent*);
        void setData(const Agent&);
        void setNext(const Position&);
        void setPrev(const Position&);
    };

#endif // AGENTNODE_HPP_INCLUDED
