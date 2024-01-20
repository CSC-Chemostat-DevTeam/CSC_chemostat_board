#include "Base/2_utils.h"
#include "Base/3_AbsHandler.h"
#include "Base/3_MsgHandler.h"


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

// // ----------------------------------------------------
// CMD INTERFACE
boolean AbsHandler::handleMsg(){

    // Serial.println(">>> At AbsHandler::handleMsg <<<");

    MsgHandler* const pMSG = this->Ch->pMSG;

    // --------------------
    // Suffixes

    // /// --------------------
    // /// ENABLE INTERFACE
    // if (pMSG->hasKeySuffix("GET-EN")) {
    //     pMSG->response("enable: ", this->_enable());
    //     return true;
    // }
    // if (pMSG->hasKeySuffix("SET-EN")) {
    //     this->Enable(pMSG->getCmdVal().toInt() != 0);
    //     pMSG->response("enable: ", this->_enable());
    //     return true;
    // }
    // // enable0
    // if (pMSG->hasKeySuffix("GET-EN0")) {
    //     pMSG->response("enable0: ", this->_enable0());
    //     return true;
    // }
    // if (pMSG->hasKeySuffix("SET-EN0")) {
    //     this->Enable0(pMSG->getCmdVal().toInt() != 0);
    //     pMSG->response("enable0: ", this->_enable0());
    //     return true;
    // }
    return false;
}

// ----------------------------------------------------
// TEST INTERFACE
String AbsHandler::getClassName() { return "AbsHandler"; }
void AbsHandler::sayHi() {
    Ch->pSERIAL->println("Hi from ", this->getClassName(), " ", (unsigned int)this);
}