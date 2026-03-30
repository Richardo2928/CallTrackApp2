#include "../include/callnode.hpp"

//<>NODE<>NODE<>NODE<>NODE<>NODE<>NODE<>NODE<>NODE<>NODE<>NODE **


CallNode::CallNode() : next(nullptr) {    }


CallNode::CallNode(const Position& otherPos):
    next(otherPos->getNext()) {    }


CallNode::CallNode(const Call&e) : dataPtr(new Call(e)), next(nullptr) {
    if(dataPtr == nullptr) {
        throw CallNodeException("NO FUE POSIBLE CREAR EL NODO\nrazon: Memoria no disponible || fuction member: CallNode...");
        }
    }


CallNode::CallNode(Call* ePtr) : dataPtr(ePtr), next(nullptr) {    }

// Si el objeto a almacenar no se copia correctamente
// o si tiene algún problema en su constructor de copia
// getData producira errores

Call CallNode::getData() const {
    if (dataPtr == nullptr) {
        throw CallNodeException("Dato inexistente || fuction member: List::CallNode::getData...");
        }
    return *dataPtr;
    }


typename CallNode::Position CallNode::getNext() const {
    return next;
    }


Call* CallNode::getDataPtr() const {
    return dataPtr;
    }


void CallNode::setData(const Call& elem) {
    if(dataPtr == nullptr) {
        if ((dataPtr = new Call(elem)) == nullptr) {
            throw CallNodeException("Memoria no disponible || fuction member: List::CallNode::setData...");
            }
        }
    *dataPtr = elem;
    }

void CallNode::setNext(const Position& pos) {
    next = pos;
    }


void CallNode::setDataPtr(Call* ptr) {
    dataPtr = ptr;
    }
