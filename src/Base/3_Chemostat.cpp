#include <Arduino.h>

#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/3_Chemostat.h"
#include "Base/3_SerialHandler.h"
#include "Base/3_MsgHandler.h"

// ----------------------------------------------------
// CONSTRUCTOR
Chemostat::Chemostat() {
    
    // Serial.println(">>> At Chemostat::Chemostat <<<");

    // HANDLERS
    this->pMSG = new MsgHandler(this); // TODO: [HEAP] Check proper free/delete
    this->pSERIAL = new SerialHandler(this); // TODO: [HEAP] Check proper free/delete
    
    // CALLERS INTERFACES
    /// CMD INTERFACE
    this->_CMD_HANDLERS_BUFFER[0] = NULL;
    this->pushMsgHandler(this->pMSG);
}

// ----------------------------------------------------
// TEST INTERFACE
String Chemostat::getClassName() { return "Chemostat"; }
void Chemostat::sayHi() {
    pSERIAL->println("Hi from ", this->getClassName(), " ", (unsigned int)this);
    // Handlers
    pSERIAL->sayHi();
    pMSG->sayHi();
}

// ----------------------------------------------------
// CMD INTERFACE
// boolean Chemostat::handleMsg() {

//     MsgHandler* const pMSG = this->pMSG;

//     // EQUAL
//     if (pMSG->hasKey("TEST-CMD")) {
//         pMSG->response("Hi from Chemostat ", (int) this);
//         return true;
//     }

//     // Prefix Depedent
//     if (pMSG->hasKeyPrefix("CH-")) { return false; }

//     return false;
// }

// ----------------------------------------------------
// CALLERS INTERFACES

// pMSG INTERFACE
void Chemostat::handleAllMsgs(){

    // Serial.println(">>> Chemostat::handleAllMsgs <<<");
    MsgHandler* const pMSG = this->pMSG;

    // no cmd is a noop
    if (!this->pMSG->hasValidMsg()) { return; }

    // DEV TODEL
    // call handlers
    for (int i = 0; i < CHEMOSTAT_HANDLERS_BUFFER_SIZE; i++) {
        if (_CMD_HANDLERS_BUFFER[i] == NULL){ break; }
        if (_CMD_HANDLERS_BUFFER[i]->handleMsg()) { 
            // close response
            // pMSG->close_response(); 
            return; 
        }
    }


    // // Open response
    // pMSG->open_response(); 

    // call myself
    // if (this->handleMsg()) { 
    //     // close response
    //     pMSG->close_response(); 
    //     return; 
    // }

    // // call handlers
    // for (int i = 0; i < CHEMOSTAT_HANDLERS_BUFFER_SIZE; i++) {
    //     if (_CMD_HANDLERS_BUFFER[i] == NULL){ break; }
    //     if (_CMD_HANDLERS_BUFFER[i]->handleMsg()) { 
    //         // close response
    //         pMSG->close_response(); 
    //         return; 
    //     }
    // }

    // // fallback
    // pMSG->response("ERROR, UNKNOWN COMMAND");
    // // close response
    // pMSG->close_response();

}

void Chemostat::pushMsgHandler(AbsHandler* h) {
    for (int i = 0; i < CHEMOSTAT_HANDLERS_BUFFER_SIZE; i++) {
        if (_CMD_HANDLERS_BUFFER[i] != NULL){ continue; }
        _CMD_HANDLERS_BUFFER[i] = h;
        if (i+1 == CHEMOSTAT_HANDLERS_BUFFER_SIZE) { break; }
        _CMD_HANDLERS_BUFFER[i+1] = NULL;
        break;
    }
}

// ----------------------------------------------------
// SKETCH INTERFACE
void Chemostat::onsetup(){
    // Serial.println(">>> Chemostat::onsetup <<<");

    // ---------------------
    // CHEMOSTAT SETUP

    // ---------------------
    // SETUP HANDLERS

    // this->pMSG->onsetup();
    this->pSERIAL->onsetup();

    // ---------------------
    // WELCOME
    pSERIAL->println("");
    pSERIAL->println("----------------------");
    pSERIAL->println(" WELCOME TO CSC-CHEMOSTAT");
    pSERIAL->println(" info at https://github.com/CSC-Chemostat-DevTeam");
    this->sayHi();
    pSERIAL->println("----------------------");
    pSERIAL->println("");
}
    
void Chemostat::onloop(){
    // Serial.println(">>> Chemostat::onloop <<<");
    
    // CHEMOSTAT ONLOOP

    // CALL HANDLERS ONLOOPS
    this->pMSG->onloop();
    this->pSERIAL->onloop();
}