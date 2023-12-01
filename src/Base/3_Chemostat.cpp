#include <Arduino.h>

#include "Base/1_config.h"
#include "Base/3_CmdHandler.h"
#include "Base/3_Chemostat.h"

// ----------------------------------------------------
// CONSTRUCTOR
Chemostat::Chemostat() {
    
    // Serial.println(">>> At Chemostat::Chemostat <<<");

    // HANDLERS
    this->pCMD = new CmdHandler(this); // TODO: [HEAP] Check proper free/delete
    
    // CALLERS INTERFACES
    /// CMD INTERFACE
    this->_CMD_HANDLERS_BUFFER[0] = NULL;
    this->pushCmdHandler(this->pCMD);

}

// ----------------------------------------------------
// CMD INTERFACE
boolean Chemostat::execCmd(String& cmd, String& val) {

    // Serial.println(">>> Chemostat::execCmd <<<");

    if (cmd.equals("TEST-CMD")) {
        Serial.print("Hi from Chemostat ");
        Serial.println((int) this);
        return true;
    }

    return false;
}

// ----------------------------------------------------
// CALLERS INTERFACES

// pCMD INTERFACE
void Chemostat::execAllCmd(){

    // Serial.println(">>> Chemostat::execAllCmd <<<");

    // no cmd is a noop
    if (!this->pCMD->hasCmd()) { return; }

    // Get cmd data
    String key = this->pCMD->getCmdKey();
    String val = this->pCMD->getCmdVal();

    // call myself
    if (this->execCmd(key, val)) { return; }

    // call handlers
    for (int i = 0; i < HANDLERS_BUFFER_SIZE; i++) {
        if (_CMD_HANDLERS_BUFFER[i] == NULL){ break; }
        if (_CMD_HANDLERS_BUFFER[i]->execCmd(key, val)) { break; }
    }

}

void Chemostat::pushCmdHandler(AbsHandler* h) {
    // TODO: fix cmd handling
    // Serial.println(">>> Chemostat::pushCmdHandler <<< ");
    for (int i = 0; i < HANDLERS_BUFFER_SIZE; i++) {
        // Serial.print("i "); Serial.print(i);
        if (_CMD_HANDLERS_BUFFER[i] != NULL){ continue; }
        _CMD_HANDLERS_BUFFER[i] = h;
        // Serial.print(", _CMD_HANDLERS_BUFFER[i] ");
        // Serial.print((unsigned int)_CMD_HANDLERS_BUFFER[i]);
        if (i+1 == HANDLERS_BUFFER_SIZE) { break; }
        _CMD_HANDLERS_BUFFER[i+1] = NULL;
        // Serial.print(", _CMD_HANDLERS_BUFFER[i+1] ");
        // Serial.print((unsigned int)_CMD_HANDLERS_BUFFER[i+1]);
        // Serial.println();
        break;
    }
}

// ----------------------------------------------------
// SKETCH INTERFACE
void Chemostat::onsetup(){
    // Serial.println(">>> Chemostat::onsetup <<<");

    // CHEMOSTAT SETUP

    // CALL HANDLERS SETUP
    this->pCMD->onsetup();
}
    
void Chemostat::onloop(){
    // Serial.println(">>> Chemostat::onloop <<<");
    
    // CHEMOSTAT ONLOOP

    // CALL HANDLERS ONLOOPS
    this->pCMD->onloop();
}