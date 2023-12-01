#include "Base/3_AbsHandler.h"

// ----------------------------------------------------
// CONSTRUCTORS
AbsHandler::AbsHandler(Chemostat* Ch){
    // Serial.println(">>> At AbsHandler::AbsHandler <<<");
    this->Ch = Ch;
    this->enable = false;
    this->enable0 = false;
}

// ----------------------------------------------------
// ENABLE INTERFACE
void AbsHandler::Enable(boolean flag){
    // Serial.println(">>> At AbsHandler::Enable <<<");
    this->enable = flag;
}
void AbsHandler::Enable0(boolean flag){
    // Serial.println(">>> At AbsHandler::Enable <<<");
    this->enable0 = flag;
}
// "privates"
boolean AbsHandler::_enable(){
    return this->enable;
}
boolean AbsHandler::_enable0(){
    return this->enable0;
}

boolean AbsHandler::isEnable(){
    // Serial.println(">>> At AbsHandler::isEnable <<<");
    if (!this->enable) { return false; }
    if (!this->enable0) { return false; }
    return true;
}

// TODO: Use high level function for CMD response printing, or printing in general

// ----------------------------------------------------
// CMD INTERFACE
boolean AbsHandler::execCmd(String& cmd, String& val){

    // Serial.println(">>> At AbsHandler::execCmd <<<");

    // --------------------
    // ENABLE INTERFACE
    if (cmd.equals("GET-EN")) {
        Serial.print("enable: ");
        Serial.println(this->_enable());
        return true;
    }
    if (cmd.equals("SET-EN")) {
        this->Enable(val.toInt() != 0);
        Serial.print("enable: ");
        Serial.println(this->_enable());
        return true;
    }
    // enable0
    if (cmd.equals("GET-EN0")) {
        Serial.print("enable0: ");
        Serial.println(this->_enable0());
        return true;
    }
    if (cmd.equals("SET-EN0")) {
        this->Enable0(val.toInt() != 0);
        Serial.print("enable0: ");
        Serial.println(this->_enable0());
        return true;
    }
    return false;
}

// ----------------------------------------------------
// TEST INTERFACE
void AbsHandler::sayHi() {
    Serial.print("Hi from AbsHandler ");
    Serial.println((unsigned int)this);
}