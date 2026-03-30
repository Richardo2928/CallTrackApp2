#include "../include/calllist.hpp"

///IMPLEMENTATION IMPLEMENTATION IMPLEMENTATION IMPLEMENTATION ***


//<> LIST <><> LIST <><> LIST <><> LIST <><> LIST <><> LIST <><> LIST <><> LIST <><> LIST <><> LIST <>

//********************************************************
///>>> >> >|BLOCK 00|< << <<<#>>> >> >|BLOCK 00|< << <<<
//********************************************************
/*
    |*|~~ isValidPos
    |*|~~~~ isValidPos
    |*|~~~~~~ copyAll
    |*|~~~~~~~~ intToPos
*/

bool CallList::isValidPos(const Position& pos)const {
    Position aux(anchor);

    while (aux != nullptr) {
        if(aux == pos) {
            return true;
            }
        aux = aux->getNext();
        }
    return false;
    }


void CallList::copyAll(const CallList& otherList) {
    Position aux(otherList.anchor);

    while (aux != nullptr) {
        insertData(aux->getData());

        aux = aux->getNext();
        }
    dataCount = otherList.dataCount;
    }


typename CallList::Position CallList::intToPos(const long long& intPos) const {
    if (isEmpty()){
        return nullptr;
        }
    if (intPos < 1) {
        return anchor;
        }
    if (intPos > dataCount) {
        return getLastPos();
        }
    long long i(1);

    Position aux(anchor);
    while(i != intPos and i <= dataCount) {
        aux = aux->getNext();
        i++;
        }

    return aux;
    }

//********************************************************
///>>> >> >|BLOCK 1|< << <<<#>>> >> >|BLOCK 1|< << <<<
//********************************************************
/*
    |*|~~ CallList
    |*|~~~~ CallList
    |*|~~~~~~ ~CallList();
    |*|~~~~~~~~ isEmpty
*/

CallList::CallList() : anchor(nullptr), dataCount(0) {    }


CallList::CallList(const CallList& otherCallList) : CallList() {
    copyAll(otherCallList);
    }


CallList::~CallList() {
    deleteAll();
    }


bool CallList::isEmpty() const {
    return anchor == nullptr;
    }

//********************************************************
///>>> >> >|BLOCK 2|< << <<<#>>> >> >|BLOCK 2|< << <<<
//********************************************************
/*
    |*|~~ insertData
    |*|~~~~ insertData (int pos)
    |*|~~~~~~ insertData (at the end)
    |*|~~~~~~~~ insertData (ptr)
*/

void CallList::insertData(const Position& pos, const Call& elem) {
    Position aux;
    try {
        if ((aux = new CallNode(elem)) == nullptr) { // PRIMERO DESIGNAMOS MEMORIA A
            // UN NUEVO NODO AL QUE INICIAMOS CON EL ELEMENTO QUE QUEREMOS ALMACENAR AHI
            // SI ESTE APUNTADOR A NODO (aux) SALE APUNTANDO A nulo LANZAMOS UNA EXCEPCI�N
            throw CallListException("\nLA INSERCION NO SE REALIZO\nrazon: Memoria no disponible || fuctionMember: insertData...");
            }
        }
    catch (const typename CallNode::CallNodeException& ex) {
        throw CallListException(ex.what());
        }

    //INSERCI�N

    if (pos->getNext() == nullptr) {//INSERCION AL FINAL
        aux->setNext(nullptr);
        getLastPos()->setNext(aux);
        }
    else {
        aux->setNext(pos);
        if(pos == anchor) { //AL PRINCIPIO
            anchor = aux;
            }
        else {//CUALQUIER OTRA POSICION
            getPrevPos(pos)->setNext(aux);
            }
        }

    dataCount++;
    }


void CallList::insertData(const long long& intPos, const Call& elem) {//RECIBE UNA POSICION ENTERA Y UN ELEMENTO
    Position pos(intToPos(intPos));

    Position aux;
    try {
        if ((aux = new CallNode(elem)) == nullptr) { // PRIMERO DESIGNAMOS MEMORIA A
            // UN NUEVO NODO AL QUE INICIAMOS CON EL ELEMENTO QUE QUEREMOS ALMACENAR AHI
            // SI ESTE APUNTADOR A NODO (aux) SALE APUNTANDO A nulo LANZAMOS UNA EXCEPCI�N
            throw CallListException("\nLA INSERCION NO SE REALIZO\nrazon: Memoria no disponible || fuctionMember: insertData...");
            }
        }
    catch (const typename CallNode::CallNodeException& ex) {
        throw CallListException(ex.what());
        }

    //INSERCI�N
    if (pos->getNext() == nullptr) {//INSERCION AL FINAL
        aux->setNext(nullptr);
        getLastPos()->setNext(aux);
        }
    else {
        aux->setNext(pos);
        if(pos == anchor) {//INSERCION AL PRINCIPIO
            anchor = aux;
            }
        else {//CUALQUIER OTRA POSICION
            getPrevPos(pos)->setNext(aux);
            }
        }

    dataCount++;
    }


void CallList::insertData(const Call& elem) {//RECIBE UN ELEMENTO Y LO INCERTA AL FINAL
    Position aux;
    try {
        if ((aux = new CallNode(elem)) == nullptr) { // PRIMERO DESIGNAMOS MEMORIA A
            // UN NUEVO NODO AL QUE INICIAMOS CON EL ELEMENTO QUE QUEREMOS ALMACENAR AHI
            // SI ESTE APUNTADOR A NODO (aux) SALE APUNTANDO A nulo LANZAMOS UNA EXCEPCI�N
            throw CallListException("\nLA INSERCION NO SE REALIZO\nrazon: Memoria no disponible || fuctionMember: insertData...");
            }
        }
    catch (const typename CallNode::CallNodeException& ex) {
        throw CallListException(ex.what());
        }

    //INSERCI�N
    aux->setNext(nullptr);
    if(isEmpty()) {//SI ESTA VACIA ASIGNAMOS EL ANCLA A AUXILIAR
        anchor = aux;
        }
    else {//SINO ASIGNAMOS EL ULTIMO A AUXILIAR
        getLastPos()->setNext(aux);
        }

    dataCount++;
    }


void CallList::insertData(Call* elemPtr) {//RECIBE UN APUNTADOR A ELEMENTO Y LO INCERTA AL FINAL
    Position aux;
    try {
        if ((aux = new CallNode(elemPtr)) == nullptr) { // PRIMERO DESIGNAMOS MEMORIA A
            // UN NUEVO NODO AL QUE INICIAMOS CON EL ELEMENTO QUE QUEREMOS ALMACENAR AHI
            // SI ESTE APUNTADOR A NODO (aux) SALE APUNTANDO A nulo LANZAMOS UNA EXCEPCI�N
            throw CallListException("\nLA INSERCION NO SE REALIZO\nrazon: Memoria no disponible || fuctionMember: insertData...");
            }
        }
    catch (const typename CallNode::CallNodeException& ex) {
        throw CallListException(ex.what());
        }

    //INSERCI�N
    aux->setNext(nullptr);
    if(isEmpty()) {//SI ESTA VACIA ASIGNAMOS EL ANCLA A AUXILIAR
        anchor = aux;
        }
    else {//SINO ASIGNAMOS EL ULTIMO A AUXILIAR
        getLastPos()->setNext(aux);
        }
    dataCount++;
    }

void CallList::insertOrdered(const Call& elem) {
    Position aux = new CallNode(elem);

    if (aux == nullptr) {
        throw CallListException("\nLA INSERCION NO SE REALIZO\nrazon: Memoria no disponible || fuctionMember: insertData...");
        }

    //INSERCION
    if (isEmpty()) {
        aux->setNext(nullptr);
        anchor = aux;
        }
    else {
        Position pos(anchor);
        while (pos != nullptr && aux->getData() < pos->getData()) {
            pos = pos->getNext();
            }

        aux->setNext(pos);
        if (pos != nullptr){
            if (getPrevPos(pos) == nullptr){
                anchor = aux;
                }
            else {
                getPrevPos(pos)->setNext(aux);
                }
            }
        else {
            getLastPos()->setNext(aux);
            }
        }

    dataCount++;
    }

void CallList::insertOrdered(Call* elem) {
    Position aux;
    try {
        if ((aux = new CallNode(elem)) == nullptr) { // PRIMERO DESIGNAMOS MEMORIA A
            // UN NUEVO NODO AL QUE INICIAMOS CON EL ELEMENTO QUE QUEREMOS ALMACENAR AHI
            // SI ESTE APUNTADOR A NODO (aux) SALE APUNTANDO A nulo LANZAMOS UNA EXCEPCI�N
            throw CallListException("\nLA INSERCION NO SE REALIZO\nrazon: Memoria no disponible || fuctionMember: insertData...");
            }
        }
    catch (const typename CallNode::CallNodeException& ex) {
        throw CallListException(ex.what());
        }

    //INSERCION
    if(isEmpty()) {
        aux->setNext(nullptr);
        anchor = aux;
        }
    else {
        Position pos(anchor);
        while(*elem > pos->getData()) {
            pos = pos->getNext();
            }

        aux->setNext(pos);
        getPrevPos(pos)->setNext(aux);
        }

    dataCount++;
    }

//********************************************************
///>>> >> >|BLOCK 3|< << <<<#>>> >> >|BLOCK 3|< << <<<
//********************************************************
/*
    |*|~~ deleteData
    |*|~~~~ deleteData (int pos)
    |*|~~~~~~ deleteAll
*/
void CallList::deleteData(const Position& pos) {//RECIBE UN POSICION DE NODO (APUNTADOR A NODO)
    if (!isValidPos(pos)) {
        throw CallListException("LA ELIMINACION NO SE REALIZO\nrazon: posicion invalida || fuctionMembre: deleteData...");
        }

    if (pos == anchor) { //ELIMINAR EL PRIMERO
        anchor = pos->getNext();
        }
    else {//ELIMINAR EN X POSICION
        getPrevPos(pos)->setNext(pos->getNext());
        }

    delete pos;
    dataCount--;
    }


void CallList::deleteData(const long long& intPos) {//RECIBE UNA POSICION ENTERA
    Position pos(intToPos(intPos));

    if (pos == anchor) { //ELIMINAR EL PRIMERO
        anchor = pos->getNext();
        }
    else {//ELIMINAR EN X POSICION
        getPrevPos(pos)->setNext(pos->getNext());
        }

    delete pos;
    dataCount--;
    }


void CallList::deleteAll() {
    Position aux(anchor);

    while (aux != nullptr) {
        anchor = aux->getNext();

        delete aux;
        dataCount--;
        aux = anchor;
        }
    }

//********************************************************
///>>> >> >|BLOCK 4|< << <<<#>>> >> >|BLOCK 4|< << <<<
//********************************************************
/*
    |*|~~ getFirstPos
    |*|~~~~ getLastPos
    |*|~~~~~~ getPrevPos
    |*|~~~~~~~~ getNextPos
*/

typename CallList::Position CallList::getFirstPos() const {
    return anchor;
    }


typename CallList::Position CallList::getLastPos() const {
    if (isEmpty()) {
        return nullptr;
        }
    Position aux(anchor);

    while (aux->getNext() != nullptr) {
        aux = aux->getNext();
        }
    return aux;
    }


typename CallList::Position CallList::getPrevPos(const Position& pos) {
    if (isEmpty() || pos == nullptr || pos == anchor) {
        return nullptr;
    }

    Position aux(anchor);

    while (aux != nullptr && aux->getNext() != pos) {
        aux = aux->getNext();
    }

    return aux;
    }


typename CallList::Position CallList::getNextPos(const Position& pos) {
    if (!isValidPos(pos)) {
        return nullptr;
        }
    return pos->getNext();
    }


//********************************************************
///>>> >> >|BLOCK 5|< << <<<#>>> >> >|BLOCK 5|< << <<<
//********************************************************
/*
    |*|~~ findData (implicit)
    |*|~~~~ findData (explicit)
    |*|~~~~~~ retrive
    |*|~~~~~~~~ retrive (int pos)
    |*|~~~~~~~~~~ toString
    |*|~~~~~~~~~~~~ getElemCount
*/

typename CallList::Position CallList::findData(const Call& elem) {
    Position aux(anchor);

    while (aux != nullptr
            and aux->getData() != elem) {
        aux = aux->getNext();
        }
    return aux;
    }


typename CallList::Position CallList::explcitFindData(bool cmp(const Call &data, const Call &elem), const Call &elem) {
    Position aux(anchor);

    while (aux != nullptr
            and !cmp(aux->getData(), elem)) {
        aux = aux->getNext();
        }
    return aux;
    }



Call CallList::retrive(const Position& pos) const {
    if(!isValidPos(pos)) {
        throw CallListException("LA ACCION NO SE PUDO COMPLETAR\nrazon: posicion invalida || fuction member: retrive");
        }
    return pos->getData();
    }


Call CallList::retrive(const long long& intPos) const {
    Position pos(intToPos(intPos));

    return retrive(pos);
    }


std::string CallList::toString() {
    std::stringstream ss;
    Position aux(anchor);
    unsigned i(1);

    while (aux != nullptr) {
        ss << i++ << ". " << aux->getData() << std::endl;

        //Si este objeto no se copia correctamente
        // o si tiene alg�n problema en su constructor copia
        // No se mostraran correctamente los datos

        aux = aux->getNext();
        }

    return ss.str();
    }


unsigned CallList::getDataCount() const {
    return dataCount;
    }


//********************************************************
///>>> >> >|BLOCK 6|< << <<<#>>> >> >|BLOCK 6|< << <<<
//********************************************************
/*
    |*|~~ saveData
    |*|~~~~ loadData
*/

void CallList::saveData(const std::string& fileName) {
    std::ofstream dataFile;
    Position aux(anchor);

    dataFile.open(fileName, std::ios_base::trunc);
    if(!dataFile.is_open()) {
        throw CallListException("LA ACCION NO SE PUDO COMPLETAR\nrazon: No se pudo abrir el archivo || fuction member: writeDataFile");
        }

    while(aux != nullptr) {
        dataFile << aux->getData() << std::endl;
        aux = aux->getNext();
        }

    dataFile.close();
    }


void CallList::loadData(const std::string& fileName) {
    if (!std::filesystem::exists("data")) {
        return;
        }

    if (!std::filesystem::exists(fileName)) {
        return;
        }

    std::ifstream dataFile;

    dataFile.open(fileName);
    if(!dataFile.is_open()) {
        throw CallListException("LA ACCION NO SE PUDO COMPLETAR\nrazon: No se pudo abrir el archivo || fuction member: readDataFile");
        }

    deleteAll();

    Call data;
    try {
        while(dataFile >> data) {
            insertOrdered(data);
            }
        }
    catch(const CallListException& ex) {
        throw CallListException(ex.what());
        dataFile.close();
        }
    dataFile.close();
    }


//********************************************************
///>>> >> >|BLOCK 7|< << <<<#>>> >> >|BLOCK 7|< << <<<
//********************************************************
/*
    |*|~~ operator =
    |*|~~~~ operator []
*/

CallList& CallList::operator=(const CallList& otherList) {
    deleteAll();

    copyAll(otherList);
    return *this;
    }


Call& CallList::operator[](const long long& intPos) {
    Position aux(intToPos(intPos));

    if(aux == nullptr) {
        throw CallListException("\n>>> ERROR: !LISTA VACIA� || fuction member: Operator []<<<\n");
        }
    return *aux->getDataPtr();

    }

std::ostream& operator << (std::ostream& os, const CallList& callL) {
    CallList::Position aux(callL.anchor);

    os << callL.dataCount << std::endl;

    for (; aux != nullptr ; aux = aux->getNext())
        os << aux->getData() << std::endl;

    return os;
    }
std::istream& operator >> (std::istream& is, CallList& callL) {
    Call aux;

    is >> callL.dataCount;
    is.ignore();
    while (is >> aux)
        callL.insertData(aux);

    return is;
    }
