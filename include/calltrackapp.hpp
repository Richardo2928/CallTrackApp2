#ifndef CALLTRACKAPP_HPP_INCLUDED
#define CALLTRACKAPP_HPP_INCLUDED

#include <raylib.h>
#include <cstring>

#include "calltrackapp.hpp"
#include "agentlist.hpp"
#include "agent.hpp"
/*
    NOTAS:
    Rectangle = {x, y, ancho, alto}
*/
class CallTrackApp {
    private:
        int SCREENWIDTH = 500;
        int SCREENHEIGHT = 600;

        AgentList *myAgentList;

//        struct LISTS{
//            AgentList defaultList;
//            AgentList desktopList;
//            AgentList printersList;
//            AgentList laptopsList;
//            AgentList linuxList;
//            AgentList networksList;
//            AgentList serversList;
//            }myLists;

        enum AppStates {
            MAINMENU,
            AGENTSMENU,
            SEARCHAGENT,
            ADDAGENT,
            ADDCALL,
            AGENTPROFILE,
            SETTINGS
            };

        AppStates actualState;
        AppStates prevState;

        struct PROPERTIES0 {
            Texture2D myImage;

            } mainMenuP;

        struct PROPERTIES1 {
            //AGENTS LIST
            Vector2 scroll = {140,140};

            Rectangle bounds = {140,140,350,350};//tama�o del panel
            const char *text = {"AGENTES"};
            Rectangle content = {140,140, 336, 500};//tama�o total del contenido del panel
            Rectangle view;//tama�o del la vista

            std::string result;

            const char *listElements = nullptr;
            int activeElement = -1; // Elemento activo en la lista
            int scrollIndex;

            //TAB BAR
            int activeSpeciality = 0;
            //const char **specialities = nullptr;
            bool testEditMode = false;

            //AGENT INFO
            void setDefaults() {
                agentName = "Nombre: ";
                agentScheduleIn = "Hr Entrada: ";
                agentScheduleOut = "Hr Salida: ";
                agentSpeciality = "Especialidad: ";
                agentNoEmp = "No de Empleado: ";
                agentNoOfCalls = "No de llamadas: ";
                agentOverTimeHrs = "Hrs Extra: ";
                }
            std::string agentName = "Nombre: ";
            std::string agentScheduleIn = "Hr Entrada: ";
            std::string agentScheduleOut = "Hr Salida: ";
            std::string agentSpeciality = "Especialidad: ";
            std::string agentNoEmp = "No de Empleado: ";
            std::string agentNoOfCalls = "No de llamadas: ";
            std::string agentOverTimeHrs = "Hrs Extra: ";

            bool showDeleteAgent = false;
            bool showDeleteAll = false;

            int activeSortBy = -1;
            bool sortByEditMode = false;
            } agentsMenuP;

        struct PROPERTIES2 {
            bool searchAgent = false;
            Rectangle bounds = {75,150,350,300};
            char agentToFind[256] = "";

            std::string agntName;
            Name name;
            Agent agnt;

            void setDefaults() {
                searchAgent = false;
                bounds = {75,150,350,300};
                memset(agentToFind, 0, sizeof(agentToFind)); // Esto reinicia el array a un estado vac�o.
                agntName = "";
                name = Name();
                agnt = Agent();
                }

            bool showWarning = false;
            } searchP;

        struct PROPERTIES3 {
            // RESET DEFAULTS
            void setDefaults() {
                memset(agentName, 0, sizeof(agentName));
                nameEditMode = false;

                memset(agentLastName, 0, sizeof(agentLastName));
                lastNameEditMode = false;

                hourIn = -1;
                hourInEditMode = false;

                minuteIn = -1;
                minuteInEditMode = false;

                hourOut = -1;
                hourOutEditMode = false;

                minuteOut = -1;
                minuteOutEditMode = false;

                activeSpeciality = -1;
                specialityEditMode = false;

                noEmployee = -1;
                noEmpEditMode = false;

                noExtension = -1;
                noExEditMode = false;

                isAgentNameOK = true;
                isAgentLstNameOK = true;
                isAgentSpecialityOK = true;
                isScheduleOK = true;
                isAgentNoEmOK = true;
                isAgentNoExOK = true;
                }

            void tabFuncionality() {
                bool *editModes[9] = {&nameEditMode,&lastNameEditMode,
                                      &hourInEditMode,&minuteInEditMode,&hourOutEditMode,
                                      &minuteOutEditMode,&specialityEditMode,&noEmpEditMode,
                                      &noExEditMode
                                     };

                for (int i(0); i < 9 ; i++) {
                    if (*editModes[i]) {
                        if (i == 8) {
                            *editModes[i] = false;
                            *editModes[0] = true;
                            return;
                            }
                        else {
                            *editModes[i] = false;
                            *editModes[i+1] = true;
                            return;
                            }
                        }
                    }

                *editModes[0] = true;
                }


            //TO SAVE
            bool areFieldsFilled() {
                if (agentName[0] == 0 || agentLastName[0] == 0 || activeSpeciality == -1 ||
                        noEmployee == 0 || noExtension == 0) {
                    return false;
                    }
                return true;
                }

            bool isAgentNameOK = true;
            bool isAgentLstNameOK = true;
            bool isAgentSpecialityOK = true;
            bool isScheduleOK = true;
            bool isAgentNoEmOK = true;
            bool isAgentNoExOK = true;

            void check() {
                isAgentNameOK = agentName[0] != 0;
                isAgentLstNameOK = agentLastName[0] != 0;
                isAgentSpecialityOK = activeSpeciality != -1;
                isAgentNoEmOK = noEmployee != 0;
                isAgentNoExOK = noExtension != 0;
                }

            //PANEL
            Rectangle panelBounds = {50,50,400,450};

            //AGENT NAME
            Rectangle nameBounds = {70,100,300,40};
            char agentName[256] = { 0 };
            bool nameEditMode = false;

            //AGENT LASTNAME
            Rectangle lastNameBounds = {70,170,300,40};
            char agentLastName[256] = { 0 };
            bool lastNameEditMode = false;

            //SCHEDULE
            // ## IN
            int hourIn = -1;
            bool hourInEditMode = false;

            int minuteIn = -1;
            bool minuteInEditMode = false;

            // ## OUT
            int hourOut = -1;
            bool hourOutEditMode = false;

            int minuteOut = -1;
            bool minuteOutEditMode = false;

            //SPECIALITY
            Rectangle specialityBounds = {70,330,180,25};
            int activeSpeciality = -1;
            bool specialityEditMode = false;

            void upAndDownFun() {
                if(IsKeyPressed(KEY_DOWN)) {
                    if (activeSpeciality != 5) {
                        activeSpeciality++;
                        return;
                        }
                    else {
                        activeSpeciality = 0;
                        return;
                        }
                    }

                if (IsKeyPressed(KEY_UP)) {
                    if (activeSpeciality != 0) {
                        activeSpeciality--;
                        return;
                        }
                    else {
                        activeSpeciality = 5;
                        return;
                        }
                    }

                if (IsKeyPressed(KEY_ENTER)) {
                    specialityEditMode = !specialityEditMode;
                    noEmpEditMode = !noEmpEditMode;
                    }
                }

            //NO EMPLOYEE
            Rectangle noEmpBounds = {265,330,140,25};
            int noEmployee = 0;
            bool noEmpEditMode = false;

            //NO EXTENSION
            Rectangle noExBounds = {265,380,140,25};
            int noExtension = 0;
            bool noExEditMode = false;
            } addAgentP;

        struct PROPERTIES4 {

            //RESEET DEFAULTS
            void setDefaults() {
                //GET NAME
                memset(customerName, 0, sizeof(customerName));
                custNameEditMode = false;

                //GET LAST NAME
                memset(cusLstName, 0, sizeof(cusLstName));
                custLstNameEditMode = false;

                //CALL TIME IN
                callHour = 8;
                hourEditMode = false;
                callMinute = 0;
                minuteEditMode = false;

                //CALL DURATION
                callDurationMin = 0;
                callDurEditModeMin = false;
                callDurationHr = 0;
                callDurEditModeHr = false;

                //CALL DATE
                day = 1;
                dayEditMode = false;
                month = 0;
                //monthEditMode = false;
                year = 2023;
                yearEditMode = false;
                takeActualDate = true;


                //TO SAVE
                isCusNameOK = true;
                isCallTimeInOK = true;
                isCallDurationOk = true;
                isCallDateOK = true;
                }

            void tabFuncionality() {
                bool *editModes[8] = {&custNameEditMode,&custLstNameEditMode,
                                      &hourEditMode,&minuteEditMode,&callDurEditModeMin,
                                      &callDurEditModeHr,&dayEditMode,&yearEditMode
                                     };

                for (int i(0); i < 8 ; i++) {
                    if (*editModes[i] && !takeActualDate) {
                        if (i == 7) {
                            *editModes[i] = false;
                            *editModes[0] = true;
                            return;
                            }
                        else {
                            *editModes[i] = false;
                            *editModes[i+1] = true;
                            return;
                            }
                        }
                    else if(*editModes[i] && takeActualDate) {
                        if (i == 5) {
                            *editModes[i] = false;
                            *editModes[0] = true;
                            return;
                            }
                        else {
                            *editModes[i] = false;
                            *editModes[i+1] = true;
                            return;
                            }
                        }
                    }

                *editModes[0] = true;
                }

            Rectangle panelBounds = {50,50,400,450};

            //TO SAVE
            bool isEverythingOK() {
                return isCallTimeInOK && isCallDurationOk && isCallDateOK && isCusNameOK ;
                }
            bool isEverythingWrong() {
                return !isCallTimeInOK && !isCallDurationOk && !isCallDateOK;
                }
            bool isCusNmOk() {
                if (customerName[0] == 0) {
                    isCusNameOK = false;
                    return false;
                    }
                return true;
                }

            bool isCusNameOK = true;
            bool isCallTimeInOK = true;
            bool isCallDurationOk = true;
            bool isCallDateOK = true;

            bool showCallTimeWar = false;
            bool showCallDurWar = false;
            bool showCallDateWar = false;

            //GETNAME
            Rectangle getNameRec = {75,70,300,40};
            char customerName[256] = {0};
            bool custNameEditMode = false;

            //GET LAST NAME
            Rectangle cusLstNameRec = {75,130,300,40};
            char cusLstName[256] = {0};
            bool custLstNameEditMode = false;

            //HORA DE LLAMADA
            Rectangle callTimeRec = {75,200,300,40};
            int callHour = 8;
            bool hourEditMode = false;
            int callMinute = 0;
            bool minuteEditMode = false;

            //Duracion de la llamada
            Rectangle callDurationRec = {75,270,300,40};
            int callDurationMin = 0;
            bool callDurEditModeMin = false;
            int callDurationHr = 0;
            bool callDurEditModeHr = false;

            //Fecha de llamada
            Rectangle callDateRec = {75,345,200,40};
            int day = 1;
            bool dayEditMode = false;
            int month = 0;
            bool monthEditMode = false;
            int year = 2023;
            bool yearEditMode = false;
            bool takeActualDate = true;

            } addCallP; //ADD CALL PROP

        struct PROPERTIES5 {
            CallList auxCallList;
            Vector2 scroll = {140,100};

            Rectangle bounds = {140,140,350,350};//tama�o del panel
            const char *text = {"LLAMADAS"};
            Rectangle content = {140,100, 336, 500};//tama�o total del contenido del panel
            Rectangle view;//tama�o del la vista

            std::string result;

            const char *listElements = nullptr;
            int activeElement = -1; // Elemento activo en la lista
            int scrollIndex;

            //CALL INFO
            void setDefaults() {
                userName = "Usuario: ";
                callTime = "Hr de llamada: ";
                callDuration = "Duracion de llamada: ";
                callDate = "Fecha: ";
                agntInfo = "";
                }
            std::string userName = "Usuario: ";
            std::string callTime = "Hr de llamada: ";
            std::string callDuration = "Duracion de llamada: ";
            std::string callDate = "Fecha: ";

            //AGENT INFO
            std::string agntInfo;

            bool showDeleteCall = false;
            bool showDeleteAll = false;

            bool showAgentInfo = false;

            //ADD EXTRA HRS
            void setDefaultOverTime() {
                overTime = 0;
                }
            bool addExtraHrs = false;
            int overTime;
            bool addExHrsEditMode = false;
            } agentProfileP; //AGENT PROFILE PROP

        void updateAgentInfo();
        void updateCallInfo();
        void updateAgentListView();
        void updateCallListView();
        void updateAgentInfoAgntProf();

        Call *auxCall;
        Agent *auxAgent;

    public:
        CallTrackApp(AgentList*);
        //~CallTrackApp();
        void mainMenu();
        void agentsMenu();
        void searchAgent();
        void addAgent();
        void addCall();
        void agentProfile();
        void settings();

        void updateState(const AppStates&);
    };

/*************************************************************************


***************************************************************************/

#endif // CALLTRACKAPP_HPP_INCLUDED