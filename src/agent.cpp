#include "../include/agent.hpp"

Agent::Agent(/* args */) : overtimeHours(0), speciality(Speciality::NONE) {}
Agent::Agent(const Agent& otherA):No_employee(otherA.getNoEmployee()),
    No_extension(otherA.getNoExtension()), overtimeHours(otherA.getOverTimeHours()),
    speciality(otherA.getSpeciality()),name(otherA.getName()),
    schedule(otherA.getSchedule()),call_list(otherA.getCallList()) {}

Agent::~Agent(){
    call_list.deleteAll();
    }

int Agent::getNoEmployee()const {
    return No_employee;
    }
int Agent::getNoExtension()const {
    return No_extension;
    }
int Agent::getOverTimeHours()const {
    return overtimeHours;
    }
Speciality Agent::getSpeciality()const {
    return speciality;
    }
Name Agent::getName()const {
    return name;
    }
Schedule Agent::getSchedule()const {
    return schedule;
    }
CallList Agent::getCallList()const {
    return call_list;
    }

void Agent::setNoEmployee(const int& noEmp) {
    No_employee = noEmp;
    }
void Agent::setNoExtension(const int& noExt) {
    No_extension = noExt;
    }
void Agent::setOverTimeHours(const int& ovTim) {
    overtimeHours += ovTim;
    }
void Agent::setSpeciality(const Speciality& sp) { //agent1.setSpeciality(Agent::DESKTOP)
    speciality = sp;
    }
void Agent::setName(const Name& nm) {
    name = nm;
    }
void Agent::setSchedule(const Schedule& sch) {
    schedule = sch;
    }
void Agent::insertCall(const Call& call) {
    call_list.insertOrdered(call);
    }

void Agent::insertCall(Call *call) {
    call_list.insertOrdered(call);
    }

void Agent::deleteCall(const long long &pos){
    call_list.deleteData(pos);
    }

void Agent::deleteAll(){
    call_list.deleteAll();
    }

bool Agent::cmpGoIName(const Agent &cmp1, const Agent &cmp2) {
    return cmp1.getName() >= cmp2.getName();
    }

bool Agent::cmpLoIName(const Agent &cmp1, const Agent &cmp2) {
    return cmp1.getName() <= cmp2.getName();
    }

bool Agent::cmpGoISpclity(const Agent &cmp1, const Agent &cmp2) {
    return cmp1.getSpeciality() >= cmp2.getSpeciality();
    }

bool Agent::cmpLoISpclity(const Agent &cmp1, const Agent &cmp2) {
    return cmp1.getSpeciality() <= cmp2.getSpeciality();
    }

std::string Agent::toString() {
    std::stringstream ss;

    ss << name << "\n" <<
       schedule << "\n" <<
       speciality << "\n" <<
       "[No Empleado]" << No_employee << "\n" <<
       "[No Extension]" << No_extension << "\n" <<
       "[Hrs Extra]" << overtimeHours << "\n" <<
       "[LISTA DE LLAMADAS]" << "\n" << call_list;

    return ss.str();
    }
std::string Agent::specialityToStr() {
    std::string specialityStr;

    switch (speciality){
    case DESKTOP:
        specialityStr = "De escritorio";
        break;
    case LAPTOPS:
        specialityStr = "Laptops";
        break;
    case LINUX:
        specialityStr = "Linux";
        break;
    case NETWORKS:
        specialityStr = "Redes";
        break;
    case PRINTERS:
        specialityStr = "Impresoras";
        break;
    case SERVERS:
        specialityStr = "Servidores";
        break;
    default:
        specialityStr = "NINGUNO(?";
        }

    return specialityStr;
    }

void Agent::saveCallList(){
    call_list.saveData("data/callusers/" + name.toString() + ".txt");
    }

void Agent::loadCallList(){
    call_list.loadData("data/callusers/" + name.toString() + ".txt");
    }

Agent& Agent::operator = (const Agent& otherAgent) {
    if (this == &otherAgent)
        return *this;

    this->No_employee = otherAgent.getNoEmployee();
    this->No_extension = otherAgent.getNoExtension();
    this->overtimeHours = otherAgent.getOverTimeHours();
    this->speciality = otherAgent.getSpeciality();
    this->name = otherAgent.getName();
    this->schedule = otherAgent.getSchedule();
    this->call_list = otherAgent.getCallList();

    return *this;
    }
bool Agent::operator == (const Agent& otherAgent)const {
    return name == otherAgent.getName();
    }
bool Agent::operator != (const Agent& otherAgent)const {
    return name != otherAgent.getName();
    }
bool Agent::operator < (const Agent& otherAgent)const {
    return name < otherAgent.getName();
    }
bool Agent::operator > (const Agent& otherAgent)const {
    return name > otherAgent.getName();
    }
bool Agent::operator <= (const Agent& otherAgent)const {
    return name <= otherAgent.getName();
    }
bool Agent::operator >= (const Agent& otherAgent)const {
    return name >= otherAgent.getName();
    }

std::ostream& operator << (std::ostream& os, const Speciality& sp) {
    os << "[Especialidad]";
    switch (sp) {
        case Speciality::SERVERS:
            os << "Servidores";
            break;
        case Speciality::DESKTOP:
            os << "Escritorio";
            break;
        case Speciality::LAPTOPS:
            os << "Portatiles";
            break;
        case Speciality::LINUX:
            os << "Linux";
            break;
        case Speciality::PRINTERS:
            os << "Impresoras";
            break;
        case Speciality::NETWORKS:
            os << "Redes";
            break;
        case Speciality::NONE:
            os << "Ninguna";
            break;
        }
    return os;
    }

std::ostream& operator << (std::ostream& os, const Agent& agnt) {
    os << agnt.name << agnt.schedule << std::endl <<
       agnt.speciality << std::endl <<
       "[No Empleado]" << agnt.No_employee << std::endl <<
       "[No Extension]" << agnt.No_extension << std::endl <<
       "[fechaAuxiliar]" << agnt.auxDate << std::endl <<
       "[Hrs Extra]" << agnt.overtimeHours;
    return os;
    }
std::istream& operator >> (std::istream&is, Speciality& sp) {
    std::string separator;
    std::string input;
    std::getline(is, separator, ']');
    is >> input;

    if (input == "Servidores") {
        sp = Speciality::SERVERS;
        }
    else if (input == "Escritorio") {
        sp = Speciality::DESKTOP;
        }
    else if (input == "Portatiles") {
        sp = Speciality::LAPTOPS;
        }
    else if (input == "Linux") {
        sp = Speciality::LINUX;
        }
    else if (input == "Impresoras") {
        sp = Speciality::PRINTERS;
        }
    else if (input == "Redes") {
        sp = Speciality::NETWORKS;
        }
    else if (input == "Ninguno") {
        sp = Speciality::NONE;
        }

    return is;
    }
std::istream& operator >> (std::istream&is, Agent& agnt) {
    std::string separator;
    Date auxDate;
    is >> agnt.name;
    is >> agnt.schedule;
    is >> agnt.speciality;
    std::getline(is, separator, ']');
    is >> agnt.No_employee;
    std::getline(is, separator, ']');
    is >> agnt.No_extension;
    std::getline(is, separator, ']');
    is >> auxDate;
    std::getline(is, separator, ']');
    if (auxDate != agnt.auxDate){
        agnt.overtimeHours = 0;
        }
    else if (auxDate == agnt.auxDate){
        is >> agnt.overtimeHours;
        }
//    std::getline(is, separator, ']');
//    is >> agnt.overtimeHours;
    return is;
    }
