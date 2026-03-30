#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"
#include "../include/style_cyber.h"
#include "../include/calltrackapp.hpp"
/**************************************************************************************************TO DO:
    - cargar toda la llamada dentro de addCall y eliminar insertCall --- DONE
    - cada vez que se guarde una llamada resetear los valores de la pantalla y quitar el cambio de estado --- DONE
    - advertir al usuario que campos no ha rellenado --- DONE
    - problema con el dropdownbox --- DONE
    - actualizar labels de agent info --- DONE
    - CHECAR VALIDACIONES EN ADDCALL --- DONE
    ----
    CHECK
    - se deshace el rectangulo para obtener el nombre al escribir en �l, pasar a otro input box
        y volver al anterior y borrar --- NC
*************************************************/

void CallTrackApp::updateAgentInfo() {
    std::stringstream intAux;
    std::stringstream intAux2;
    std::stringstream intAux3;

    agentsMenuP.setDefaults();
    intAux << auxAgent->getNoEmployee();

    agentsMenuP.agentName += auxAgent->getName().toString();
    agentsMenuP.agentScheduleIn += auxAgent->getSchedule().getInTime().toString();
    agentsMenuP.agentScheduleOut += auxAgent->getSchedule().getOutTime().toString();
    agentsMenuP.agentSpeciality += auxAgent->specialityToStr();
    agentsMenuP.agentNoEmp += intAux.str();
    intAux2 << auxAgent->getCallList().getDataCount();
    agentsMenuP.agentNoOfCalls += intAux2.str();
    intAux3 << auxAgent->getOverTimeHours();
    agentsMenuP.agentOverTimeHrs += intAux3.str();
    }

void CallTrackApp::updateCallInfo() {
    agentProfileP.setDefaults();

    agentProfileP.userName += auxCall->getUser().toString() ;
    agentProfileP.callDate += auxCall->getCallDate().toStringFormat2();
    agentProfileP.callDuration += auxCall->getCallDuration().toString();
    agentProfileP.callTime += auxCall->getCallTime().toString();
    }

void CallTrackApp::updateAgentListView() {
    if (myAgentList->isEmpty()) {
        agentsMenuP.listElements = nullptr;
        return;
        }
    unsigned i(1);
    agentsMenuP.result.clear();
    for (; i < myAgentList->getDataCount(); i++) {
        agentsMenuP.result += myAgentList->retrive(i).getName().toString() + ";";
        }
    agentsMenuP.result += myAgentList->retrive(i).getName().toString();


    agentsMenuP.listElements = agentsMenuP.result.c_str();
    }

void CallTrackApp::updateCallListView() {
    if (agentProfileP.auxCallList.isEmpty()) {
        agentProfileP.listElements = nullptr;
        return;
        }
    unsigned i(1);
    Date auxDate;
    Date auxDate2;
    auxDate = agentProfileP.auxCallList.retrive(i).getCallDate();
    auxDate2 = agentProfileP.auxCallList.retrive(i).getCallDate();

    agentProfileP.result.clear();
    agentProfileP.result += agentProfileP.auxCallList.retrive(i).getCallDate().toStringFormat1() + " :: --- ";
    for (; i < agentProfileP.auxCallList.getDataCount(); i++) {
        if (auxDate != auxDate2){
            agentProfileP.result += agentProfileP.auxCallList.retrive(i).getCallDate().toStringFormat1() + " :: --- ";
            auxDate = auxDate2;
            }

        agentProfileP.result += agentProfileP.auxCallList.retrive(i).getCallTime().toString()+ " :: -- " +
                                agentProfileP.auxCallList.retrive(i).getUser().toString() + ";";

        auxDate2 = agentProfileP.auxCallList.retrive(i).getCallDate();
        }
    agentProfileP.result += agentProfileP.auxCallList.retrive(i).getCallDate().toStringFormat1() + " :: --- " +
                            agentProfileP.auxCallList.retrive(i).getCallTime().toString()+ " :: --- " +
                            agentProfileP.auxCallList.retrive(i).getUser().toString();

    agentProfileP.listElements = agentProfileP.result.c_str();
    }

void CallTrackApp::updateAgentInfoAgntProf() {
    agentProfileP.agntInfo = agentsMenuP.agentName + "\n\n" + agentsMenuP.agentScheduleIn + "\n\n" +
                             agentsMenuP.agentScheduleOut + "\n\n" + agentsMenuP.agentSpeciality + "\n\n" +
                             agentsMenuP.agentNoEmp + "\n\n" + agentsMenuP.agentNoOfCalls + "\n\n" +
                             agentsMenuP.agentOverTimeHrs;
    }

CallTrackApp::CallTrackApp(AgentList *myAList) : myAgentList(myAList), actualState(MAINMENU), auxAgent(nullptr), auxCall(nullptr) {
    InitWindow(SCREENWIDTH,SCREENHEIGHT,"Call Track App 2");

    Image icon = LoadImage("icon_test5.png");
    SetWindowIcon(icon);
    mainMenuP.myImage = LoadTexture("cta_image.png");
    GuiLoadStyleCyber();

    while(!WindowShouldClose()) {
        ClearBackground({20,70,100,100});
        BeginDrawing();

        switch (actualState) {
            case MAINMENU:
                mainMenu();
                break;
            case AGENTSMENU:
                agentsMenu();
                break;
            case SEARCHAGENT:
                searchAgent();
                break;
            case ADDAGENT:
                addAgent();
                break;
            case ADDCALL:
                addCall();
                break;
            case AGENTPROFILE:
                agentProfile();
                break;
            case SETTINGS:
                settings();
                break;
            }

        EndDrawing();
        }

    if (auxAgent != nullptr){
        delete auxAgent;
        }
    if (auxCall != nullptr){
        delete auxCall;
        }
    UnloadImage(icon);
    UnloadTexture(mainMenuP.myImage);
    CloseWindow();
    }

void CallTrackApp::mainMenu() {
    GuiSetStyle(DEFAULT, TEXT_SIZE, 14);
    GuiSetIconScale(2);


    DrawTexture(mainMenuP.myImage, 120, 50, WHITE);
    if (GuiButton({(float)GetScreenWidth()/2 - 100, (float)GetScreenHeight()/2 - 45, 200, 100}, GuiIconText(ICON_EXIT, "ENTRAR") )) {
        GuiSetIconScale(1);
        updateState(AGENTSMENU);
        }
//    if (GuiButton({(float)GetScreenWidth()/2 - 100, (float)GetScreenHeight()/2 + 75, 200, 100 }, GuiIconText(ICON_GEAR, "CONFIGURACION") )) {
//        updateState(SETTINGS);
//        }
    }

void CallTrackApp::agentsMenu() {
    if (agentsMenuP.showDeleteAgent || agentsMenuP.showDeleteAll) {
        GuiSetState(STATE_DISABLED);
        }

    //LISTA AGENTES
    GuiScrollPanel(agentsMenuP.bounds,
                   agentsMenuP.text,
                   agentsMenuP.content,
                   &agentsMenuP.scroll,
                   &agentsMenuP.view);

    BeginScissorMode(agentsMenuP.view.x,
                     agentsMenuP.view.y,
                     agentsMenuP.view.width,
                     agentsMenuP.view.height);
    GuiListView({agentsMenuP.scroll.x + agentsMenuP.view.x,
                 agentsMenuP.scroll.y + agentsMenuP.view.y,
                 agentsMenuP.content.width,
                 agentsMenuP.content.height
                },
                agentsMenuP.listElements,
                &agentsMenuP.scrollIndex,
                &agentsMenuP.activeElement);
    EndScissorMode();

    //FILTRAR AGENTES;
    //GuiComboBox({245,490,150,25}, "Default;De escritorio;Impresoras;Linux;Portatiles;Redes;Servidores", &agentsMenuP.activeSpeciality);

    //IFO DE AGENTE
    GuiGroupBox({100,20,325,100}, "Info del agente");
    if (agentsMenuP.activeElement != -1) {
        auxAgent = &(*myAgentList)[agentsMenuP.activeElement + 1];
        updateAgentInfo();
        GuiLabel({105,20,200,50}, agentsMenuP.agentName.c_str());
        GuiLabel({105,30,200,50}, agentsMenuP.agentSpeciality.c_str());
        GuiLabel({105,40,200,50}, agentsMenuP.agentNoEmp.c_str());
        GuiLabel({105,50,200,50}, agentsMenuP.agentNoOfCalls.c_str());
        GuiLabel({280,20,200,50}, agentsMenuP.agentScheduleIn.c_str());
        GuiLabel({280,30,200,50}, agentsMenuP.agentScheduleOut.c_str());
        GuiLabel({280,40,200,50}, agentsMenuP.agentOverTimeHrs.c_str());
        }

    //BUSCAR AGENTE
    if(GuiButton({25,35,50,50}, GuiIconText(ICON_LENS_BIG,nullptr))) {
        updateState(SEARCHAGENT);
        }

    //PERFIL DEL AGENTE
    if(GuiButton({10,140,100,50}, "Ver agente") and agentsMenuP.activeElement != -1) {
        agentProfileP.auxCallList = auxAgent->getCallList();
        GuiSetStyle(LISTVIEW, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
        updateState(AGENTPROFILE);
        }
    //ELIMINAR
    if(GuiButton({10,200,100,50}, GuiIconText(ICON_BIN, "Eliminar")) and agentsMenuP.activeElement != -1) {
        agentsMenuP.showDeleteAgent = !agentsMenuP.showDeleteAgent;
        }
    //AGREGAR AGENTE
    if (GuiButton({10,340,100,50}, "Agregar")) {
        auxAgent = new Agent;
        updateState(ADDAGENT); // A�ADIR AGENTES
        }
    //ELIMINAR TODOS LOS AGENTES
    if (GuiButton({10,410,100,50}, "Eliminar todos") && !myAgentList->isEmpty()) {
        agentsMenuP.showDeleteAll = !agentsMenuP.showDeleteAll;
        }
    //GUARADAR
    if (GuiButton({425,20,75,50},"GUARDAR")) {
        myAgentList->saveData();
        }
    //CARGAR
    if (GuiButton({425,70,75,50},"CARGAR")) {
        agentsMenuP.activeElement = -1;
        auxAgent = nullptr;
        myAgentList->loadData();
        updateAgentListView();
        }
    //ATRAS (SALIR)
    if (GuiButton({25,525,450,50}, GuiIconText(ICON_ARROW_LEFT_FILL,"Atras"))) {
        updateState(MAINMENU);
        }

    //ORDENAR
    GuiLabel({300,145,100,10}, "Ordenar por...");
    if (agentsMenuP.sortByEditMode) {
        auxAgent = nullptr;
        agentsMenuP.activeElement = -1;
        GuiLock();
        }
    if(!agentsMenuP.sortByEditMode) {
        GuiUnlock();
        }
    if (GuiDropdownBox({380,140,110,24},"Nombre;Especialidad",&agentsMenuP.activeSortBy,agentsMenuP.sortByEditMode)) {
        agentsMenuP.sortByEditMode = !agentsMenuP.sortByEditMode;
        }
    switch (agentsMenuP.activeSortBy) {
        case 0:
            myAgentList->sortBy(Agent::cmpGoIName,Agent::cmpLoIName);
            updateAgentListView();
            break;
        case 1:
            myAgentList->sortBy(Agent::cmpGoISpclity,Agent::cmpLoISpclity);
            updateAgentListView();
            break;
        }

    //VENTANA EMERGENTE PARA ELIMINAR AGENTE
    if (agentsMenuP.showDeleteAgent) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.3f));
        GuiSetState(STATE_NORMAL);

        std::string confirmation = "Desea eliminar a: " + auxAgent->getName().toString();
        int opt = GuiMessageBox({ (float)GetScreenWidth()/2 - 150, (float)GetScreenHeight()/2 - 75, 300, 140 },
                                "#15#", confirmation.c_str(), "Si;No");

        if ((opt == 0) || (opt == 2)) {
            agentsMenuP.showDeleteAgent = !agentsMenuP.showDeleteAgent;
            }
        else if (opt == 1) {
            myAgentList->deleteData(agentsMenuP.activeElement + 1);
            auxAgent = nullptr;
            agentsMenuP.activeElement = -1;
            updateAgentListView();
            agentsMenuP.showDeleteAgent = !agentsMenuP.showDeleteAgent;
            }
        }
    //VENTANA EMERGENTE PARA ELIMINAR TODOS LOS AGENTES
    if (agentsMenuP.showDeleteAll) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.3f));
        GuiSetState(STATE_NORMAL);

        int opt2 = GuiMessageBox({ (float)GetScreenWidth()/2 - 150, (float)GetScreenHeight()/2 - 75, 300, 140 },
                                 "#15#", "Desea eliminar a todos los agentes", "Si;No");

        if ((opt2 == 0) || (opt2 == 2)) {
            agentsMenuP.showDeleteAll = !agentsMenuP.showDeleteAll;
            }
        else if (opt2 == 1) {
            myAgentList->deleteAll();
            agentsMenuP.activeElement = -1;
            updateAgentListView();
            agentsMenuP.showDeleteAll = !agentsMenuP.showDeleteAll;
            }
        }
    }

void CallTrackApp::searchAgent() {
    if (searchP.showWarning) {
        GuiSetState(STATE_DISABLED);
        }

    int opt = GuiTextInputBox(searchP.bounds,"BUSCAR","Ingresa el nombre del agente que deseas buscar",
                              "Buscar;Cancelar",searchP.agentToFind,256,nullptr);

    if (opt == 1 || IsKeyPressed(KEY_ENTER)) {
        searchP.agntName = searchP.agentToFind;
        searchP.name.setFirst(searchP.agntName);
        searchP.agnt.setName(searchP.name);
        if (myAgentList->isIn(searchP.agnt)) {
            agentsMenuP.activeElement = myAgentList->findDataInt(searchP.agnt) - 1;
            updateState(prevState);
            }
        else {
            searchP.showWarning = !searchP.showWarning;
            }
        }
    if (opt == 2 or opt == 0) {
        updateState(prevState);
        }

    if (searchP.showWarning) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.3f));
        GuiSetState(STATE_NORMAL);
        int opt = GuiMessageBox({ (float)GetScreenWidth()/2 - 200, (float)GetScreenHeight()/2 - 75, 400, 140 }
                                , "#15#", "Lo sentimos...   No encontramos resultados para tu busqueda", "Aceptar");
        if (opt == 0 || opt == 1) {
            searchP.setDefaults();
            searchP.showWarning = !searchP.showWarning;
            }
        }
    }

// ADD AGENT -----------------------------------------------------------------------------------------
void CallTrackApp::addAgent() {

    Name name;

    Schedule schedule;

    Time timeAux;

    //DATA INPUT WARNING && STUFF
    if (!addAgentP.isAgentLstNameOK ||
            !addAgentP.isAgentNameOK ||
            !addAgentP.isAgentSpecialityOK ||
            !addAgentP.isScheduleOK) {
        int defColor = GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL);
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 200);
        DrawRectangle(addAgentP.panelBounds.x,
                      (addAgentP.panelBounds.y/2) - 10,
                      addAgentP.panelBounds.width,
                      20,
                      Fade(RED, 0.8f));
        GuiLabel({addAgentP.panelBounds.x,
                  (addAgentP.panelBounds.y/2) - 10,
                  addAgentP.panelBounds.width,
                  20}, "Oops! Parece que olvidaste completar algunos campos...");
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, defColor);
        }

    if (!addAgentP.isScheduleOK) {
        GuiSetState(STATE_DISABLED);
        }

    //PANEL
    GuiPanel(addAgentP.panelBounds, "AGREGAR AGENTE");

    //NOMBRE
    if (!addAgentP.isAgentNameOK) {
        DrawRectangle(addAgentP.nameBounds.x,
                      addAgentP.nameBounds.y + addAgentP.nameBounds.height,
                      addAgentP.nameBounds.width + 20,
                      5,
                      Fade(RED, 0.8f));
        if (addAgentP.nameEditMode) {
            addAgentP.isAgentNameOK = !addAgentP.isAgentNameOK;
            }
        }

    GuiLine({addAgentP.nameBounds.x,
             addAgentP.nameBounds.y-35,
             addAgentP.nameBounds.width,
             addAgentP.nameBounds.height},
            "NOMBRE:");
    if (GuiTextBox(addAgentP.nameBounds,
                   addAgentP.agentName,256,
                   addAgentP.nameEditMode)) {
        addAgentP.nameEditMode = !addAgentP.nameEditMode;
        }

    std::string names = addAgentP.agentName;
    name.setFirst(names);

    //APELLIDOS
    if (!addAgentP.isAgentLstNameOK) {
        DrawRectangle(addAgentP.lastNameBounds.x,
                      addAgentP.lastNameBounds.y + addAgentP.lastNameBounds.height,
                      addAgentP.lastNameBounds.width + 20,
                      5,
                      Fade(RED, 0.8f));
        if (addAgentP.lastNameEditMode) {
            addAgentP.isAgentLstNameOK = !addAgentP.isAgentLstNameOK;
            }
        }

    GuiLine({addAgentP.lastNameBounds.x,
             addAgentP.lastNameBounds.y-35,
             addAgentP.lastNameBounds.width,
             addAgentP.lastNameBounds.height},
            "APELLIDOS:");
    if (GuiTextBox(addAgentP.lastNameBounds,
                   addAgentP.agentLastName,256,
                   addAgentP.lastNameEditMode)) {
        addAgentP.lastNameEditMode = !addAgentP.lastNameEditMode;
        }


    std::string lastName = addAgentP.agentLastName;
    name.setLast(lastName);


    auxAgent->setName(name);

    //HORARIOS
    // ## ENTRADA
    GuiLine({70,210,175,40},"HORARIO ENTRADA:");
    if (GuiSpinner({105,240,140,25},"HORA: ",
                   &addAgentP.hourIn,8,18,
                   addAgentP.hourInEditMode)) {
        addAgentP.hourInEditMode = !addAgentP.hourInEditMode;
        }

    timeAux.setHour(addAgentP.hourIn);

    if (GuiSpinner({105,275,140,25},"MINUTO: ",
                   &addAgentP.minuteIn,0,59,
                   addAgentP.minuteInEditMode)) {
        addAgentP.minuteInEditMode = !addAgentP.minuteInEditMode;
        }

    timeAux.setMinute(addAgentP.minuteOut);


    schedule.setInTime(timeAux);

    // ## SALIDA
    GuiLine({265,210,175,40},"HORARIO SALIDA:");
    if (GuiSpinner({300,240,140,25},"HORA: ",
                   &addAgentP.hourOut,8,18,
                   addAgentP.hourOutEditMode)) {
        addAgentP.hourOutEditMode = !addAgentP.hourOutEditMode;
        }

    timeAux.setHour(addAgentP.hourOut);

    if (GuiSpinner({300,275,140,25},"MINUTO: ",
                   &addAgentP.minuteOut,0,59,
                   addAgentP.minuteOutEditMode)) {
        addAgentP.minuteOutEditMode = !addAgentP.minuteOutEditMode;
        }

    timeAux.setMinute(addAgentP.minuteOut);


    schedule.setOutTime(timeAux);

    auxAgent->setSchedule(schedule);


    //NO EMPLEADO
    if (!addAgentP.isAgentNoEmOK) {
        DrawRectangle(addAgentP.noEmpBounds.x,
                      addAgentP.noEmpBounds.y + addAgentP.noEmpBounds.height,
                      addAgentP.noEmpBounds.width + 20,
                      5,
                      Fade(RED, 0.8f));
        if (addAgentP.noEmpEditMode) {
            addAgentP.isAgentNoEmOK = !addAgentP.isAgentNoEmOK;
            }
        }

    GuiLine({265,310,140,25}, "NO EMPLEADO");
    if(GuiValueBox(addAgentP.noEmpBounds,nullptr,
                   &addAgentP.noEmployee,0,9999,
                   addAgentP.noEmpEditMode
                  )) {
        addAgentP.noEmpEditMode = !addAgentP.noEmpEditMode;
        }

    auxAgent->setNoEmployee(addAgentP.noEmployee);

    //NO EXTENSION
    if (!addAgentP.isAgentNoExOK) {
        DrawRectangle(addAgentP.noExBounds.x,
                      addAgentP.noExBounds.y + addAgentP.noExBounds.height,
                      addAgentP.noExBounds.width + 20,
                      5,
                      Fade(RED, 0.8f));
        if (addAgentP.noExEditMode) {
            addAgentP.isAgentNoExOK = !addAgentP.isAgentNoExOK;
            }
        }

    GuiLine({265,360,140,25}, "NO EXTENSION");
    if(GuiValueBox(addAgentP.noExBounds,nullptr,
                   &addAgentP.noExtension,0,9999,
                   addAgentP.noExEditMode
                  )) {
        addAgentP.noExEditMode = !addAgentP.noExEditMode;
        }

    auxAgent->setNoExtension(addAgentP.noExtension);

    //AGREGAR LLAMADAS (opcional)
    if (GuiButton({70,375,180,50}, "AGREGAR LLAMADAS\n(opcional)")) {
        auxCall = new Call;
        updateState(ADDCALL);
        }


//-----------------------------------------------
    // -------- GUARDAR
    if (GuiButton({200,445,100,50}, "GUARDAR") || IsKeyPressed(KEY_ENTER)) {
        addAgentP.isScheduleOK = auxAgent->getSchedule().getInTime() < auxAgent->getSchedule().getOutTime();

        if(addAgentP.areFieldsFilled() && addAgentP.isScheduleOK) {
            try {
                if (myAgentList->isIn(*auxAgent)) {
                    //-------------------------------------------------------- HACER ALGO (PENDIENTE)
                    return;
                    }

                myAgentList->insertData(*auxAgent);
                updateAgentListView();
                auxAgent = nullptr;
                }
            catch(const typename CallList::CallListException ex) {
                std::cout << "HUBO UN PEDO" << std::endl;
                //------------------------------------------------------------ HACER ALGO (PENDIENTE)
                }

            addAgentP.setDefaults();
            updateState(AGENTSMENU);
            return;
            }
        else {
            addAgentP.check();
            }
        }

    //ATRAS (SALIR)
    if (GuiButton({25,525,450,50}, GuiIconText(ICON_ARROW_LEFT_FILL,"Atras"))) {
        delete auxAgent;
        auxAgent = nullptr;
        addAgentP.setDefaults();
        updateState(AGENTSMENU);
        return;
        }

    //ESPECIALIDAD
    if (!addAgentP.isAgentSpecialityOK) {
        DrawRectangle(addAgentP.specialityBounds.x,
                      addAgentP.specialityBounds.y + addAgentP.specialityBounds.height,
                      addAgentP.specialityBounds.width + 10,
                      5,
                      Fade(RED, 0.8f));
        if (addAgentP.specialityEditMode) {
            addAgentP.isAgentSpecialityOK= !addAgentP.isAgentSpecialityOK;
            }
        }

    if (addAgentP.specialityEditMode) {
        addAgentP.upAndDownFun();
        GuiLock();
        }
    if (!addAgentP.specialityEditMode) {
        GuiUnlock();
        }

    GuiLine({70,310,180,25},"ESPECIALIDA");
    if (GuiDropdownBox(addAgentP.specialityBounds,"Servidores;De escritorio;Portatiles;Linux;Impresoras;Redes",
                       &addAgentP.activeSpeciality,
                       addAgentP.specialityEditMode)) {
        addAgentP.specialityEditMode = !addAgentP.specialityEditMode;
        }

    switch (addAgentP.activeSpeciality) {
        case 0:
            auxAgent->setSpeciality(SERVERS);
            break;
        case 1:
            auxAgent->setSpeciality(DESKTOP);
            break;
        case 2:
            auxAgent->setSpeciality(LAPTOPS);
            break;
        case 3:
            auxAgent->setSpeciality(LINUX);
            break;
        case 4:
            auxAgent->setSpeciality(PRINTERS);
            break;
        case 5:
            auxAgent->setSpeciality(NETWORKS);
            break;
        }
    // NOTE: GuiDropdownBox must draw after any other control that can be covered on unfolding


    //TAB FUNCIONALITY
    if (IsKeyPressed(KEY_TAB)) {
        addAgentP.tabFuncionality();
        }


    //EXTRA WINDOWS...
    if (!addAgentP.isScheduleOK) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.3f));
        GuiSetState(STATE_NORMAL);
        int opt = GuiMessageBox({ (float)GetScreenWidth()/2 - 150, (float)GetScreenHeight()/2 - 75, 300, 140 }
                                , "#15#", "El horario de entrada NO debe ser menor\no igual al de salida",
                                "Aceptar");
        if (opt == 0 || opt == 1) {
            addAgentP.isScheduleOK = !addAgentP.isScheduleOK;
            }
        }
    }

//------------------------------------ ADDCALL -----------------------------------------------------

void CallTrackApp::addCall() {


    Time auxTimeDur;
    Name auxName;
    Time auxTimeIn;
    Date auxDate;

    //WARNINGS && STUFF
    if (!addCallP.isCusNameOK) {
        int defColor = GuiGetStyle(DEFAULT, TEXT_COLOR_NORMAL);
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 200);
        DrawRectangle(addAgentP.panelBounds.x,
                      (addAgentP.panelBounds.y/2) - 10,
                      addAgentP.panelBounds.width,
                      20,
                      Fade(RED, 0.8f));
        GuiLabel({addAgentP.panelBounds.x,
                  (addAgentP.panelBounds.y/2) - 10,
                  addAgentP.panelBounds.width,
                  20}, "Oops!   Parece que olvidaste darle un nombre al usuario...");
        GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, defColor);

        if (addCallP.custNameEditMode){
            addCallP.isCusNameOK = !addCallP.isCusNameOK;
            }
        }
    if (addCallP.showCallDateWar || addCallP.showCallDurWar || addCallP.showCallTimeWar) {
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.3f));
        GuiSetState(STATE_DISABLED);
        }

    //PANEL PRINCIPAL
    GuiPanel(addCallP.panelBounds, "AGREGAR LLAMADA");

    //NOMBRE DEL CLIENTE
    GuiLine(addCallP.getNameRec, "Nombre del usuario atendido");
    if (GuiTextBox({addCallP.getNameRec.x,
                    addCallP.getNameRec.y+30,
                    addCallP.getNameRec.width,
                    addCallP.getNameRec.height},
                   addCallP.customerName,256,
                   addCallP.custNameEditMode)) {
        addCallP.custNameEditMode = !addCallP.custNameEditMode;
        }

    std::string auxNm(addCallP.customerName);
    auxName.setFirst(auxNm);//------------------------A�ADIR NOMBRE DE CLIENTE

    //APELLIDO DEL CLIENTE
    GuiLine(addCallP.cusLstNameRec, "Apellido (opcional)");
    if (GuiTextBox({addCallP.cusLstNameRec.x,
                    addCallP.cusLstNameRec.y+30,
                    addCallP.cusLstNameRec.width,
                    addCallP.cusLstNameRec.height},
                   addCallP.cusLstName,256,
                   addCallP.custLstNameEditMode)) {
        addCallP.custLstNameEditMode = !addCallP.custLstNameEditMode;
        }

    std::string auxLstNm(addCallP.cusLstName);
    auxName.setLast(auxLstNm);//----------------------A�ADIR APELLIDO (OPCIONAL)

    auxCall->setUser(auxName);//-----------------------CREAR OBJETO NOMBRE

    //HORA DE ATENCION
    if (!addCallP.isCallTimeInOK) {
        DrawRectangle(addCallP.callTimeRec.x,
                      addCallP.callTimeRec.y + addCallP.callTimeRec.height + 30,
                      addCallP.callTimeRec.width + 50,
                      5,
                      Fade(RED, 0.8f));
        if (addCallP.hourEditMode || addCallP.minuteEditMode) {
            addCallP.isCallTimeInOK = !addCallP.isCallTimeInOK;
            }
        if (GuiButton({addCallP.callTimeRec.x + addCallP.callTimeRec.width + 30,
                       addCallP.callTimeRec.y + addCallP.callTimeRec.height + 35,
                       20,
                       20}, "#15#")) {
            addCallP.showCallTimeWar = !addCallP.showCallTimeWar;
            }
        }


    GuiLine(addCallP.callTimeRec, "Hora de atencion");
    if (GuiSpinner({addCallP.callTimeRec.x + 20,
                    addCallP.callTimeRec.y+30,
                    addCallP.callTimeRec.width/2 - 20,
                    addCallP.callTimeRec.height},
                   "Hora:",&addCallP.callHour,8,18,addCallP.hourEditMode)) {
        addCallP.hourEditMode = !addCallP.hourEditMode;
        }
    auxTimeIn.setHour(addCallP.callHour);//-----------HORA DE LA LLAMADA

    if (GuiSpinner({addCallP.callTimeRec.x + 90 + addCallP.callTimeRec.width/2 - 20,
                    addCallP.callTimeRec.y+30,
                    addCallP.callTimeRec.width/2 - 20,
                    addCallP.callTimeRec.height},
                   "Minuto:",&addCallP.callMinute,0,59,addCallP.minuteEditMode)) {
        addCallP.minuteEditMode = !addCallP.minuteEditMode;
        }
    auxTimeIn.setMinute(addCallP.callMinute);//-------HORA DE LLAMADA

    auxCall->setCallTime(auxTimeIn);//-----------------CREAR UN OBJETO TIEMPO


    //DURACION DE LLAMADA
    if (!addCallP.isCallDurationOk) {
        DrawRectangle(addCallP.callDurationRec.x,
                      addCallP.callDurationRec.y + addCallP.callDurationRec.height + 30,
                      addCallP.callDurationRec.width + 70,
                      5,
                      Fade(RED, 0.8f));
        if (addCallP.callDurEditModeMin || addCallP.callDurEditModeHr) {
            addCallP.isCallDurationOk = !addCallP.isCallDurationOk;
            }
        if (GuiButton({addCallP.callDurationRec.x + addCallP.callDurationRec.width + 50,
                       addCallP.callDurationRec.y + addCallP.callDurationRec.height + 35,
                       20,
                       20}, "#15#")) {
            addCallP.showCallDurWar = !addCallP.showCallDurWar;
            }
        }


    GuiLine(addCallP.callDurationRec, "Duracion de llamada (En minutos)");
    if (GuiValueBox({addCallP.callDurationRec.x + 30,
                     addCallP.callDurationRec.y+30,
                     addCallP.callDurationRec.width/4,
                     addCallP.callDurationRec.height},
                    "Minutos:",&addCallP.callDurationMin,0,9999,
                    addCallP.callDurEditModeMin)) {
        addCallP.callDurEditModeMin = !addCallP.callDurEditModeMin;
        }
    auxTimeDur.setMinute(addCallP.callDurationMin);//-DURACI�N DE LLAMADA MINUTO


    if (GuiValueBox({addCallP.callDurationRec.x + 110 + addCallP.callDurationRec.width/4,
                     addCallP.callDurationRec.y+30,
                     addCallP.callDurationRec.width/4,
                     addCallP.callDurationRec.height},
                    "Hora (opc):",&addCallP.callDurationHr,0,9999,
                    addCallP.callDurEditModeHr)) {
        addCallP.callDurEditModeHr = !addCallP.callDurEditModeHr;
        }
    auxTimeDur.setHour(addCallP.callDurationHr);//----DURACI�N DE LLAMADA HORA (OPCIONAL)


    auxCall->setCallDuration(auxTimeDur);//------------CREAR OBJETO TIEMPO
    //FECHA DE LLAMADA
    if (!addCallP.isCallDateOK) {
        DrawRectangle(addCallP.callDateRec.x,
                      addCallP.callDateRec.y + addCallP.callDateRec.height + 40,
                      (addCallP.callDateRec.x + addCallP.callDateRec.width + 50 + addCallP.callDateRec.width/2) - addCallP.callDateRec.x,
                      5,
                      Fade(RED, 0.8f));
        if (addCallP.dayEditMode || addCallP.yearEditMode) {
            addCallP.isCallDateOK = !addCallP.isCallDateOK;
            }
        if (GuiButton({addCallP.callDateRec.x + addCallP.callDateRec.width + 50 + addCallP.callDateRec.width/2,
                       addCallP.callDateRec.y + addCallP.callDateRec.height + 40,
                       20,
                       20}, "#15#")) {
            addCallP.showCallDateWar = !addCallP.showCallDateWar;
            }
        }


    GuiLine({75,345,199,40}, "FECHA");
    GuiCheckBox({280,360,15,15}, "Tomar fecha actual", &addCallP.takeActualDate);
    if (addCallP.takeActualDate){
        GuiSetState(STATE_DISABLED);
        }
        try{
            //D�A
            if (addCallP.dayEditMode && IsKeyPressed(KEY_LEFT)){
                if (addCallP.day == 1){
                    addCallP.day = auxDate.getMaxDay();
                    }
                else {
                    addCallP.day--;
                    }
                }
            if (addCallP.dayEditMode && IsKeyPressed(KEY_RIGHT)){
                if (addCallP.day == auxDate.getMaxDay()){
                    addCallP.day = 1;
                    }
                else {
                    addCallP.day++;
                    }
                }
            if (GuiSpinner({addCallP.callDateRec.x,
                            addCallP.callDateRec.y + 40,
                            addCallP.callDateRec.width/2,
                            addCallP.callDateRec.height},
                           nullptr,&addCallP.day,1,auxDate.getMaxDay(),
                           addCallP.dayEditMode)) {
                addCallP.dayEditMode = !addCallP.dayEditMode;
                }
            auxDate.setDay(addCallP.day);//------------------- DIA DE LA LLAMADA

            //MES
            GuiComboBox({addCallP.callDateRec.x + addCallP.callDateRec.width/2 + 20,
                                addCallP.callDateRec.y + 40,
                                110,
                                addCallP.callDateRec.height},
                        "Enero;Febrero;Marzo;Abril;Mayo;Junio;Julio;Agosto;Septiembre;Octubre;Noviembre;Diciembre",
                        &addCallP.month);
            if (!addCallP.takeActualDate){
                auxDate.setMonth(addCallP.month + 1);
                }

            //A�O
            if (addCallP.yearEditMode && IsKeyPressed(KEY_LEFT)){
                addCallP.year--;
                }
            if (addCallP.yearEditMode && IsKeyPressed(KEY_RIGHT)){
                addCallP.year++;
                }
            if (GuiSpinner({addCallP.callDateRec.x + addCallP.callDateRec.width + 50,
                            addCallP.callDateRec.y + 40,
                            addCallP.callDateRec.width/2,
                            addCallP.callDateRec.height},
                           nullptr,&addCallP.year,2000,3000,
                           addCallP.yearEditMode)) {
                addCallP.yearEditMode = !addCallP.yearEditMode;
                }
            auxDate.setYear(addCallP.year);//---------------- A�O DE LA LLAMADA
            }
        catch (const std::invalid_argument){
            addCallP.day = 1;
            }

        auxCall->setCallDate(auxDate);//----------------- FECHA DE LA LLAMADA
    if (addCallP.takeActualDate){
        GuiSetState(STATE_NORMAL);
        }
    //GUARDAR
    if ((GuiButton({200,445,100,50}, "GUARDAR") && addCallP.isCusNmOk()) || IsKeyPressed(KEY_ENTER)) {
        Date todayDate;

        addCallP.isCallTimeInOK = auxCall->getCallTime() >= auxAgent->getSchedule().getInTime();
        addCallP.isCallDurationOk = auxCall->getCallDuration().toInt() + auxCall->getCallTime().toInt() < auxAgent->getSchedule().getOutTime().toInt() + (auxAgent->getOverTimeHours() * 1000);
        addCallP.isCallDateOK = auxDate <= todayDate;

        std::cout << *auxCall << std::endl;
        if (addCallP.isEverythingOK()) {
            auxAgent->insertCall(*auxCall);
            agentProfileP.auxCallList = auxAgent->getCallList();
            std::cout << agentProfileP.auxCallList << std::endl;
            auxCall = nullptr;
            auxCall = new Call;
            addCallP.setDefaults();
            }
        }//------------------------------------------ PENDIENTE --- (decirle al usuario que se a�adio la llamada)

    //ATRAS (SALIR)
    if (GuiButton({25,525,450,50}, GuiIconText(ICON_ARROW_LEFT_FILL,"Atras"))) {
        delete auxCall;
        auxCall = nullptr;
        addCallP.setDefaults();
        updateState(prevState);
        return;
        }

    //TAB FUNCIONALITY
    if (IsKeyPressed(KEY_TAB)) {
        addCallP.tabFuncionality();
        }


    //WIN WARNINGS
    if (addCallP.showCallDateWar) {
        GuiSetState(STATE_NORMAL);
        int opt = GuiMessageBox({ (float)GetScreenWidth()/2 - 210, (float)GetScreenHeight()/2 - 80, 420, 150 }
                                , "#15#", "Eres del futuro 0.o? La fecha seleccionada supera a la actual",
                                "Aceptar");
        if (opt == 0 || opt == 1) {
            addCallP.showCallDateWar = !addCallP.showCallDateWar;
            }
        }
    if (addCallP.showCallDurWar) {
        GuiSetState(STATE_NORMAL);
        int opt = GuiMessageBox({ (float)GetScreenWidth()/2 - 190, (float)GetScreenHeight()/2 - 75, 380, 140 }
                                , "#15#", "La duracion no coincide con las horas trabajadas!",
                                "Aceptar");
        if (opt == 0 || opt == 1) {
            addCallP.showCallDurWar = !addCallP.showCallDurWar;
            }
        }
    if (addCallP.showCallTimeWar) {
        GuiSetState(STATE_NORMAL);
        int opt = GuiMessageBox({ (float)GetScreenWidth()/2 - 190, (float)GetScreenHeight()/2 - 75, 380, 140 }
                                , "#15#", "La hora de llamada no coincide con las horas trabajadas!",
                                "Aceptar");
        if (opt == 0 || opt == 1) {
            addCallP.showCallTimeWar = !addCallP.showCallTimeWar;
            }
        }

    //FECHA DE LLAMADA (MES) --------------------
        //SI SE TOMA LA FECHA ACTUAL DESHABILITAR LOS CONTROLES
//    if (addCallP.takeActualDate) {
//        GuiSetState(STATE_DISABLED);
//        }
//        //SI SE UTILIZA EL DROPDOWNBOX BLOQUEAR LA GUI
//        if (addCallP.monthEditMode) {
//            GuiLock();
//            }
//        //SI NO SE UTILIZA DESBLOQUEARLA
//        if (!addCallP.monthEditMode) {
//            GuiUnlock();
//            }
        //SI SE UTILIZA CAMBIAR LA BANDERA
//        if (GuiDropdownBox({addCallP.callDateRec.x + addCallP.callDateRec.width/2 + 20,
//                            addCallP.callDateRec.y + 40,
//                            110,
//                            addCallP.callDateRec.height},
//                            "Enero;Febrero;Marzo;Abril;Mayo;Junio;Julio;Agosto;Septiembre;Octubre;Noviembre;Diciembre",
//                           &addCallP.month,
//                           addCallP.monthEditMode)) {
//            addCallP.monthEditMode = !addCallP.monthEditMode;
//            }

        //VOLVER A HABILITAR LOS CONTROLES PARA EVITAR DESHABILITAR TODO
//    if (addCallP.takeActualDate) {
//        GuiSetState(STATE_NORMAL);
//        }
    }

void CallTrackApp::agentProfile() {
    //BLOQUEAR VISTA PARA MOSTRAR "VENTANAS EMERGENTES"
    if (agentProfileP.showDeleteCall || agentProfileP.showDeleteAll || agentProfileP.showAgentInfo || agentProfileP.addExtraHrs){
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.2f));
        GuiSetState(STATE_DISABLED);
        }

    //ACTUALIZAR LA LISTA. AGRANDAR EL ICONO
    updateCallListView();
    GuiSetIconScale(2);

    //BOTON PARA MOSTRAR AGENTE
    int aux = GuiGetStyle(DEFAULT, TEXT_SIZE);
    std::string agntPrfl = "\n\n\n\n\n\n" + auxAgent->getName().toString();
    GuiSetStyle(DEFAULT, TEXT_SIZE, 14);
    if (GuiButton({10,10,120,100}, GuiIconText(ICON_PLAYER, agntPrfl.c_str()))) {
        agentProfileP.showAgentInfo = !agentProfileP.showAgentInfo;
        }
    GuiSetStyle(DEFAULT, TEXT_SIZE, aux);

    //MOSTRAR INFO DE LA LLAMADA SELECCIONADA
    GuiGroupBox({140,20,350,100}, "Info de la llamada");
    if (agentProfileP.activeElement != -1) {
        auxCall = &agentProfileP.auxCallList[agentProfileP.activeElement + 1];
        updateCallInfo();
        GuiLabel({150,20,200,50}, agentProfileP.userName.c_str());
        GuiLabel({150,40,200,50}, agentProfileP.callTime.c_str());
        GuiLabel({150,50,200,50}, agentProfileP.callDuration.c_str());
        GuiLabel({150,60,200,50}, agentProfileP.callDate.c_str());
        }

    //LISTA DE LLAMADAS
    GuiScrollPanel(agentProfileP.bounds,
                   agentProfileP.text,
                   agentProfileP.content,
                   &agentProfileP.scroll,
                   &agentProfileP.view);

    BeginScissorMode(agentProfileP.view.x,
                     agentProfileP.view.y,
                     agentProfileP.view.width,
                     agentProfileP.view.height);
    GuiListView({agentProfileP.scroll.x + agentProfileP.view.x,
                 agentProfileP.scroll.y + agentProfileP.view.y,
                 agentProfileP.content.width,
                 agentProfileP.content.height
                },
                agentProfileP.listElements,
                &agentProfileP.scrollIndex,
                &agentProfileP.activeElement);
    EndScissorMode();

    //VOLVER A LA NORMALIDAD EL TAMANIOO DE LOS ICONOS.
    GuiSetIconScale(1);

    //AGREGAR LLAMADA
    if (GuiButton({10,140,100,50}, "Agregar")) {
        auxCall = new Call;
        updateState(ADDCALL); // ANADIR AGENTES
        }
    //ELIMINAR LLAMADA
    if(GuiButton({10,200,100,50}, GuiIconText(ICON_BIN, "Eliminar")) and agentProfileP.activeElement != -1) {
        agentProfileP.showDeleteCall = !agentProfileP.showDeleteCall;
        }
    //BOT�N AGREGAR HRS EXTRA
    if (GuiButton({10,305,100,50}, GuiIconText(ICON_TARGET_SMALL_FILL, "\n\n\nHrs extra"))){
        agentProfileP.addExtraHrs = !agentProfileP.addExtraHrs;
        }
    //ELIMINAR TODAS LAS LLAMADAS
    if (GuiButton({10,410,100,50}, "Eliminar todas")) {
        agentProfileP.showDeleteAll = !agentProfileP.showDeleteCall;
        }

    //ATRAS
    if (GuiButton({25,525,450,50}, GuiIconText(ICON_ARROW_LEFT_FILL,"Atras"))) {
        GuiSetStyle(LISTVIEW, TEXT_ALIGNMENT, TEXT_ALIGN_CENTER);
        updateState(AGENTSMENU);
        }

    //MOSTRAR INFO DEL AGENTE
    if (agentProfileP.showAgentInfo) {
        updateAgentInfoAgntProf();
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(RAYWHITE, 0.3f));
        GuiSetState(STATE_NORMAL);
        int opt = GuiMessageBox({ (float)GetScreenWidth()/2 - 150, (float)GetScreenHeight()/2 - 200, 300, 400 },
                                auxAgent->getName().toString().c_str(),
                                agentProfileP.agntInfo.c_str(), "Aceptar");
        if (opt == 0 || opt == 1) {
            agentProfileP.showAgentInfo = !agentProfileP.showAgentInfo;
            }
        }

    //VENTANA EMERGENTE PARA ELIMINAR LLAMADA
    if (agentProfileP.showDeleteCall){
        GuiSetState(STATE_NORMAL);
        int opt = GuiMessageBox({ (float)GetScreenWidth()/2 - 150, (float)GetScreenHeight()/2 - 75, 300, 140 },
                                "#15#", "Desea eliminar la llamada?", "Si;No");

        if ((opt == 0) || (opt == 2)) {
            agentProfileP.showDeleteCall = !agentProfileP.showDeleteCall;
            }
        else if (opt == 1) {
            auxAgent->deleteCall(agentProfileP.activeElement + 1);
            agentProfileP.activeElement = -1;
            agentProfileP.auxCallList = auxAgent->getCallList();
            updateCallListView();
            agentProfileP.showDeleteCall = !agentProfileP.showDeleteCall;
            }
        }
    //VENTANA EMERGENTE PARA ELIMINAR TODAS LAS LLAMADAS
    if (agentProfileP.showDeleteAll){
        GuiSetState(STATE_NORMAL);
        int opt2 = GuiMessageBox({ (float)GetScreenWidth()/2 - 150, (float)GetScreenHeight()/2 - 75, 300, 140 },
                                "#15#", "Desea eliminar todas las llamada?", "Si;No");

        if ((opt2 == 0) || (opt2 == 2)) {
            agentProfileP.showDeleteAll = !agentProfileP.showDeleteAll;
            }
        else if (opt2 == 1) {
            auxAgent->deleteAll();
            agentProfileP.activeElement = -1;
            agentProfileP.auxCallList = auxAgent->getCallList();
            updateCallListView();
            agentProfileP.showDeleteAll = !agentProfileP.showDeleteAll;
            }
        }
    //AGREGAR HRS EXTRA
    if (agentProfileP.addExtraHrs){
        GuiSetState(STATE_NORMAL);
        int xd = GuiWindowBox({ (float)GetScreenWidth()/2 - 150, (float)GetScreenHeight()/2 - 75, 300, 130 },
                     "#221#Hrs extra");
        if (xd == 1){
            agentProfileP.addExtraHrs = !agentProfileP.addExtraHrs;
            agentProfileP.setDefaultOverTime();
            }

        if (GuiValueBox({ (float)GetScreenWidth()/2 - 75, (float)GetScreenHeight()/2 - 40, 150, 40},
                    nullptr, &agentProfileP.overTime, 0,
                    auxAgent->getSchedule().getOutTime().getHour() - auxAgent->getSchedule().getInTime().getHour(),
                    agentProfileP.addExHrsEditMode)){
            agentProfileP.addExHrsEditMode = !agentProfileP.addExHrsEditMode;
            }
        if (GuiButton({ (float)GetScreenWidth()/2 - 50, (float)GetScreenHeight()/2 + 10, 100, 30}, "Agregar")){
            auxAgent->setOverTimeHours(agentProfileP.overTime);
            agentProfileP.setDefaultOverTime();
            updateAgentInfo();
            agentProfileP.addExtraHrs = !agentProfileP.addExtraHrs;
            }
        }
    }

void CallTrackApp::updateState(const AppStates &nextState) {
    /*ESTOY EN UN CUARTO Y TENGO UNA CUERDA QUE ME ATA A
    ALGUIEN QUE SE ENCUENTRA EN EL CUARTO EN EL QUE ESTUVE PREVIAMENTE,
    CREO UNA PERSONA EN EL CUARTO EN EL QUE ESTOY Y DE ALGUN MODO
    ME DICE EN QUE CUARTO LA CREE, ME VOY A OTRO CUARTO,
    Y LE DIGO A LA PERSONA QUE ESTA ATADA A M� QUE VAYA AL CUARTO QUE ME
    DICE LA PERSONA QUE CREE*/
    AppStates aux = actualState;
    actualState = nextState;
    prevState = aux;
    }

void CallTrackApp::settings() {
    if (GuiLabelButton({(float)GetScreenWidth()/2 - 100, (float)GetScreenHeight()/2 - 200, 300, 400},
                       "TODAVIA TRABAJAMOS EN ELLO...")) {
        updateState(prevState);
        }
    }
