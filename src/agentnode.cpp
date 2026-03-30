#include "../include/agentnode.hpp"

AgentNode::AgentNode() : dataPtr(nullptr), next(nullptr), prev(nullptr) {    }


AgentNode::AgentNode(const Position& otherPos):
     dataPtr(otherPos->getDataPtr()), next(otherPos->getNext()), prev(otherPos->getPrev()) {    }


AgentNode::AgentNode(const Agent&e) : dataPtr(new Agent(e)), next(nullptr), prev(nullptr) {
    if (dataPtr == nullptr) {
        throw AgentNodeException("\nNO FUE POSIBLE CREAR EL NODO\nrazon: Memoria no disponible || fuction member: AgentNode...");
        }
    }

AgentNode::AgentNode(Agent* agentPtr) : dataPtr(agentPtr){}


Agent* AgentNode::getDataPtr() {
    return dataPtr;
    }


Agent& AgentNode::getData() {
    if (dataPtr == nullptr) {
        throw AgentNodeException("Dato inexistente || fuction member: getData...");
        }
    return *dataPtr;
    }


typename AgentNode::Position AgentNode::getNext() const {
    return next;
    }


typename AgentNode::Position AgentNode::getPrev() const {
    return prev;
    }


void AgentNode::setDataPtr(Agent* p) {
    dataPtr = p;
    }


void AgentNode::setData(const Agent& elem) {
    if(dataPtr == nullptr) {
        if ((dataPtr = new Agent(elem)) == nullptr) {
            throw AgentNodeException("Memoria no disponible || fuction member: setData...");
            }
        }
    *dataPtr = elem;
    }


void AgentNode::setNext(const Position& pos) {
    next = pos;
    }


void AgentNode::setPrev(const Position& pos) {
    prev = pos;
    }
