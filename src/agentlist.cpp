#include "../include/agentlist.hpp"

//********************************************************
///>>> >> >|BLOCK 00|< << <<<#>>> >> >|BLOCK 00|< << <<<
//********************************************************
/*
    |*|~~ isValidPos
    |*|~~~~ copyAll
*/

bool AgentList::isValidPos(const Position& pos)const {
    Position aux(headerPtr->getNext());

    while (aux != headerPtr) {
        if(aux == pos) {
            return true;
            }
        aux = aux->getNext();
        }
    return false;
    }


void AgentList::copyAll(const AgentList& otherAgentList) {
    Position aux(otherAgentList.headerPtr->getNext());
    Position newNode(nullptr);

    while (aux != otherAgentList.headerPtr) {

        try {
            if((newNode = new AgentNode(aux->getData())) == nullptr) {
                throw AgentListException("\nLA INSERCION NO SE REALIZO\nrazon: Memoria no disponible || fuctionMember: copyAll...");
                }
            }
        catch (const AgentNodeException &ex) {
            throw AgentListException(ex.what());
            }

        newNode->setPrev(headerPtr->getPrev());
        newNode->setNext(headerPtr);

        headerPtr->getPrev()->setNext(newNode);
        headerPtr->setPrev(newNode);

        aux = aux->getNext();
        }
    }


typename AgentList::Position AgentList::intToPos(const unsigned &intPos) {
    if (intPos < 1)
        return headerPtr->getNext();
    if (intPos > dataCount)
        return headerPtr->getPrev();

    unsigned i(1);

    Position aux(headerPtr->getNext());
    for (; aux != headerPtr && i <= dataCount && i < intPos; aux = aux->getNext()) {
        i++;
        }
    return aux;
    }

void AgentList::swapPtr(const Position &a, const Position &b) {
    Agent *tmpA;

    tmpA = &a->getData();
    a->setDataPtr(b->getDataPtr());
    b->setDataPtr(tmpA);
    }



//********************************************************
///>>> >> >|BLOCK 1|< << <<<#>>> >> >|BLOCK 1|< << <<<
//********************************************************
/*
    |*|~~ AgentList
    |*|~~~~ AgentList
    |*|~~~~~~ ~AgentList();
    |*|~~~~~~~~ isEmpty
*/

AgentList::AgentList() : headerPtr(new AgentNode), dataCount(0) {
    if(headerPtr == nullptr) {
        throw AgentListException("Memoria no disponible || fuction member: AgentList...");
        }
    headerPtr->setNext(headerPtr);
    headerPtr->setPrev(headerPtr);
    }


AgentList::AgentList(const AgentList& otherAgentList) : AgentList() {
    copyAll(otherAgentList);
    }


AgentList::~AgentList() {
    deleteAll();

    delete headerPtr;
    }


bool AgentList::isEmpty() const {
    return headerPtr->getNext() == headerPtr;
    }

bool AgentList::isIn(const Agent& a)const {
    return findData(a) != nullptr;
    }



//********************************************************
///>>> >> >|BLOCK 2|< << <<<#>>> >> >|BLOCK 2|< << <<<
//********************************************************
/*
    |*|~~ insertData
    |*|~~~~ deleteData
*/

void AgentList::insertData(const Position& pos, const Agent& elem) {
    if(!isValidPos(pos)) {
        throw AgentListException("\nLA INSERCION NO SE REALIZO\nrazon: Posicion invalida || fuction member: insertData...");
        }


    Position aux;
    try {
        if ((aux = new AgentNode(elem)) == nullptr) {
            throw AgentListException("\nLA INSERCION NO SE REALIZO\nrazon: Memoria no disponible || fuctionMember: insertData...");
            }
        }
    catch (const AgentNodeException& ex) {
        throw AgentListException(ex.what());
        }

    //INSERCION
    if(pos == headerPtr->getNext()) {//INSERCION AL PRINCIPIO
        aux->setNext(headerPtr->getNext());
        aux->setPrev(headerPtr);
        pos->setPrev(aux);
        headerPtr->setNext(aux);
        }
    else if(pos == nullptr) {//INSERTAR AL FINAL
        aux->setNext(headerPtr);
        aux->setPrev(headerPtr->getPrev());
        headerPtr->getPrev()->setNext(aux);
        headerPtr->setPrev(aux);
        }
    else {//INSERCION EN CUALQUIER LUGAR
        aux->setNext(pos);
        aux->setPrev(pos->getPrev());
        pos->getPrev()->setNext(aux);
        pos->setPrev(aux);
        }
    dataCount++;
    }

void AgentList::insertData(const unsigned& intPos, const Agent& elem) {
    Position pos(intToPos(intPos));
    /*
    if(!isValidPos(pos)) {
        throw AgentListException("\nLA INSERCION NO SE REALIZO\nrazon: Posicion invalida || fuction member: insertData...");
        }
        */



    Position aux;
    try {
        if ((aux = new AgentNode(elem)) == nullptr) {
            throw AgentListException("\nLA INSERCION NO SE REALIZO\nrazon: Memoria no disponible || fuctionMember: insertData...");
            }
        }
    catch (const AgentNodeException& ex) {
        throw AgentListException(ex.what());
        }

    //INSERCION
    if(pos == headerPtr->getNext()) {//INSERCION AL PRINCIPIO
        aux->setNext(headerPtr->getNext());
        aux->setPrev(headerPtr);
        pos->setPrev(aux);
        headerPtr->setNext(aux);
        }
    else if(pos == nullptr) {//INSERTAR AL FINAL
        aux->setNext(headerPtr);
        aux->setPrev(headerPtr->getPrev());
        headerPtr->getPrev()->setNext(aux);
        headerPtr->setPrev(aux);
        }
    else {//INSERCION EN CUALQUIER LUGAR
        aux->setNext(pos);
        aux->setPrev(pos->getPrev());
        pos->getPrev()->setNext(aux);
        pos->setPrev(aux);
        }
    dataCount++;
    }

void AgentList::insertData(const Agent& elem) {
    Position pos;
    pos = isEmpty()? headerPtr : getLastPos();
    Position aux;

    try {
        if ((aux = new AgentNode(elem)) == nullptr) {
            throw AgentListException("\nLA INSERCION NO SE REALIZO\nrazon: Memoria no disponible || fuctionMember: insertData...");
            }
        }
    catch (const AgentNodeException& ex) {
        throw AgentListException(ex.what());
        }

    aux->setNext(headerPtr);
    aux->setPrev(pos);

    if (pos == nullptr)
        headerPtr->setNext(aux);
    else
        pos->setNext(aux);

    headerPtr->setPrev(aux);
    dataCount++;
    }

void AgentList::insertData(Agent* agentPtr) {
    Position pos;
    pos = isEmpty()? headerPtr : getLastPos();
    Position aux;
    try {
        if ((aux = new AgentNode(agentPtr)) == nullptr) {
            throw AgentListException("\nLA INSERCION NO SE REALIZO\nrazon: Memoria no disponible || fuctionMember: insertData...");
            }
        }
    catch (const AgentNodeException& ex) {
        throw AgentListException(ex.what());
        }

    aux->setNext(headerPtr);
    aux->setPrev(pos);

    headerPtr->setPrev(aux);
    pos->setNext(aux);

    dataCount++;
    }

void AgentList::deleteData(const Position& pos) {
    if (!isValidPos(pos)) {
        throw AgentListException("LA ELIMINACION NO SE REALIZO\nrazon: posicion invalida || fuctionMembre: deleteData...");
        }
    if (pos == headerPtr) {
        throw AgentListException("LA ELIMINACION NO SE REALIZO\nrazon: posicion invalida || fuctionMembre: deleteData...");
        }

    pos->getPrev()->setNext(pos->getNext());
    pos->getNext()->setPrev(pos->getPrev());

    delete pos;
    dataCount--;
    }

void AgentList::deleteData(const unsigned& intPos) {
    Position pos(intToPos(intPos));
    if (!isValidPos(pos)) {
        throw AgentListException("LA ELIMINACION NO SE REALIZO\nrazon: posicion invalida || fuctionMembre: deleteData...");
        }
    if (pos == headerPtr) {
        throw AgentListException("LA ELIMINACION NO SE REALIZO\nrazon: posicion invalida || fuctionMembre: deleteData...");
        }

    pos->getPrev()->setNext(pos->getNext());
    pos->getNext()->setPrev(pos->getPrev());

    delete pos;
    dataCount--;
    }



//********************************************************
///>>> >> >|BLOCK 3|< << <<<#>>> >> >|BLOCK 3|< << <<<
//********************************************************
/*
    |*|~~ getFirstPos
    |*|~~~~ getLastPos
    |*|~~~~~~ getPrevPos
    |*|~~~~~~~~ getNextPos
*/

typename AgentList::Position AgentList::getFirstPos() const {
    return isEmpty()? nullptr : headerPtr->getNext();
    }


typename AgentList::Position AgentList::getLastPos() const {
    return isEmpty()? nullptr : headerPtr->getPrev();
    }


typename AgentList::Position AgentList::getPrevPos(const Position& pos) {
    return (pos == headerPtr->getNext() or !isValidPos(pos))? nullptr : pos->getNext();
    }


typename AgentList::Position AgentList::getNextPos(const Position& pos) {
    return (pos == headerPtr->getPrev() or !isValidPos(pos))? nullptr : pos->getPrev();
    }





//********************************************************
///>>> >> >|BLOCK 4|< << <<<#>>> >> >|BLOCK 4|< << <<<
//********************************************************
/*
    |*|~~ findData (implicit)
    |*|~~~~ findData (explicit)
    |*|~~~~~~ retrive
    |*|~~~~~~~~ deleteAll
*/

int AgentList::findDataInt(const Agent& a) const {
    int auxInt(1);
    Position aux(headerPtr->getNext());

    while (aux != headerPtr) {
        if (aux->getData() == a) {
            return auxInt;
            }
        aux = aux->getNext();
        auxInt++;
        }
    return -1;
    }

typename AgentList::Position AgentList::findData(const Agent& a) const {
    Position aux(headerPtr->getNext());

    while (aux != headerPtr) {
        if (aux->getData() == a) {
            return aux;
            }
        aux = aux->getNext();
        }
    return nullptr;
    }


typename AgentList::Position AgentList::explcitFindData(bool cmp(const Agent &data, const Agent &elem), const Agent &elem) {
    Position aux(headerPtr->getNext());

    while (aux != headerPtr) {
        if (cmp(aux->getData(), elem)) {
            return aux;
            }
        aux = aux->getNext();
        }
    return nullptr;
    }


Agent AgentList::retrive(const Position& pos) {

    if(!isValidPos(pos)) {
        throw AgentListException("LA ACCION NO SE PUDO COMPLETAR\nrazon: el elemento no existe || fuction member: retrive");
        }
    return pos->getData();
    }

Agent AgentList::retrive(const long long& intPos) {
    Position pos(intToPos(intPos));
//    if(!isValidPos(pos)) {
//        throw AgentListException("LA ACCION NO SE PUDO COMPLETAR\nrazon: el elemento no existe || fuction member: retrive");
//        }
    return pos->getData();
    }


void AgentList::deleteAll() {
    Position aux;

    while (headerPtr->getNext() != headerPtr) {
        aux = headerPtr->getNext();

        headerPtr->setNext(aux->getNext());

        delete aux;
        dataCount--;
        }
    headerPtr->setPrev(headerPtr);
    }




//********************************************************
///>>> >> >|BLOCK 5|< << <<<#>>> >> >|BLOCK 5|< << <<<
//********************************************************
/*
    |*|~~ toString
    |*|~~~~ getDataCount
*/

std::string AgentList::toString() {
    std::stringstream ss;
    unsigned index(1);
    Position aux(headerPtr->getNext());

    while(aux!=headerPtr) {
        ss << index++ << ". " << aux->getData() << std::endl;
        aux = aux->getNext();
        }

    return ss.str();
    }

void AgentList::sortBy(bool cmpGoI(const Agent &data, const Agent &elem),
                       bool cmpLoI(const Agent &data, const Agent &elem)) {
    sortBy(cmpGoI, cmpLoI, headerPtr->getNext(), headerPtr->getPrev());
    }

void AgentList::sortBy(bool cmpGoI(const Agent &data, const Agent &elem),
                       bool cmpLoI(const Agent &data, const Agent &elem),
                       const Position &leftEdge, const Position &rightEdge) {
    if (leftEdge == rightEdge) {
        return;
        }

    if (leftEdge->getNext() == rightEdge) {
        if (!cmpLoI(leftEdge->getData(), rightEdge->getData())){
            swapPtr(leftEdge, rightEdge);
            }
        return;
        }

    Position i(leftEdge), j(rightEdge);

    while (i != j) {
        while (i != j and cmpLoI(i->getData(), rightEdge->getData())) {
            i = i->getNext();
            }

        while (i != j and cmpGoI(j->getData(), rightEdge->getData())) {
            j = j->getPrev();
            }

        if (i != j) {
            swapPtr(i,j);
            }
        }

    if (i != rightEdge) {
        swapPtr(i, rightEdge);
        }

    if (leftEdge != i) {
        sortBy(cmpGoI,cmpLoI,leftEdge, i->getPrev());
        }

    if (i != rightEdge) {
        sortBy(cmpGoI,cmpLoI,i->getNext(),rightEdge);
        }

    }

unsigned AgentList::getDataCount() const {
    return dataCount;
    }

//********************************************************
///>>> >> >|BLOCK 6|< << <<<#>>> >> >|BLOCK 6|< << <<<
//********************************************************
/*
    |*|~~ saveData
    |*|~~~~ loadData
*/
void AgentList::saveData() {
    namespace fs = std::filesystem;

    if (fs::exists("data")){
        fs::remove_all("data");
        }

    fs::create_directory("data");

    fs::create_directory("data/callusers");

    std::ofstream dataFile;
    Position aux(headerPtr->getNext());

    dataFile.open("data/agentes.txt", std::ios_base::trunc);
    if(!dataFile.is_open()) {
        dataFile.close();
        throw AgentListException("LA ACCION NO SE PUDO COMPLETAR\nrazon: No se pudo abrir el archivo || fuction member: writeDataFile");
        }

    while(aux != headerPtr) {
        dataFile << aux->getData() << std::endl;
        aux->getData().saveCallList();
        aux = aux->getNext();
        }

    dataFile.close();
    }


void AgentList::loadData() {
    if (!std::filesystem::exists("data")){
        return;
        }

    if (!std::filesystem::exists("data/agentes.txt")){
        return;
    }
    std::ifstream dataFile;

    dataFile.open("data/agentes.txt");
    if(!dataFile.is_open()) {
        throw AgentListException("LA ACCION NO SE PUDO COMPLETAR\nrazon: No se pudo abrir el archivo || fuction member: readDataFile");
        }

    deleteAll();
    Agent data;
    try {
        while(dataFile >> data) {
            data.loadCallList();
            insertData(data);
            }
        }
    catch(const AgentListException& ex) {
        dataFile.close();
        throw AgentListException(ex.what());
        }

    dataFile.close();
    }

//********************************************************
///>>> >> >|BLOCK 7|< << <<<#>>> >> >|BLOCK 7|< << <<<
//********************************************************
/*
    |*|~~ operator =
*/

AgentList& AgentList::operator=(const AgentList& otherAgentList) {
    deleteAll();

    copyAll(otherAgentList);
    return *this;
    }


Agent& AgentList::operator[](const int& intPos) {
    Position aux(intToPos(intPos));
    if(aux == nullptr) {
        throw AgentListException("\n>>> !POSICION INVALIDA...[?]� <<<\n");
        }
    return aux->getData();
    }
