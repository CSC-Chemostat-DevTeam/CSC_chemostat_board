#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/3_CSVLineReader.h"
#include "Base/3_MsgHandler.h"
#include "Base/3_SerialHandler.h"

// Interfaces will be called using the Chemostat object

// ----------------------------------------------------
// CONSTRUCTOR
MsgHandler::MsgHandler(Chemostat* Ch) :
    AbsHandler(
        /* Chemostat */ Ch
    ){
    // Serial.println(">>> At MsgHandler::MsgHandler <<<");
    this->csvline = CSVLineReader();
    this->respcount = 0;
}

// ----------------------------------------------------
// SKETCH INTERFACE
void MsgHandler::onsetup(){ ; }

void MsgHandler::onloop(){
    
    // Serial.println(">>> MsgHandler::onloop <<<");

    // read cmd
    SerialHandler* pSERIAL = this->Ch->pSERIAL;
    if (pSERIAL->available() > 0) {
        this->tryReadMsg(TRY_READ_MSG_TIMEOUT);
    }

    // handle all handlers commands
    this->Ch->handleAllMsgs();

    // Reset reader
    this->reset(); // reset reader
}

// ----------------------------------------------------
// CMD INTERFACE

/// -------------------------
/// EXEC CMD
boolean MsgHandler::handleMsg() {

    MsgHandler* const pMSG = this->Ch->pMSG;
    SerialHandler* const pSERIAL = this->Ch->pSERIAL;

    // DEV TODEL
    pSERIAL->println(pMSG->cmdCSVLineString());
    return true;

    // // Unique
    // if (pMSG->hasKey("ECHO")) {
    //     int n = 1;
    //     if (!pMSG->getCmdVal1().equals("")) {
    //         n = getCmdVal1().toInt();
    //     }
    //     for (int i = 0; i < n; i++) {
    //         pMSG->response(pMSG->getCmdVal0());
    //     }
    //     return true;
    // }

    // // Prefix Depedent
    // if (pMSG->hasKeyPrefix("CMD-")) { return false; }

    // // Call parent
    // // if (this->AbsHandler::handleMsg()) { return true; }

    // return false;

}

/// -------------------------
/// MSG QUERYS
// boolean MsgHandler::hasKey(const String& str) {
//     return this->getCmdKey().equals(str);
// }

// boolean MsgHandler::hasKeyPrefix(const String& prefix) {
//     return this->getCmdKey().startsWith(prefix);
// }

// boolean MsgHandler::hasKeySuffix(const String& suffix) {
//     return this->getCmdKey().startsWith(suffix);
// }

// unsigned int MsgHandler::cmdhash(){
//     return this->csvline.hash();
// }

/// -------------------------
void MsgHandler::reset(){
    this->csvline.reset(); // reset reader
}

// If cmd buffers are empty, listen for incoming commands for 'tout' time;
void MsgHandler::tryReadMsg(unsigned long tout){

    // Serial.println(">>> MsgHandler::tryReadMsg <<<");

    // If non reset called, skip
    if (this->hasValidMsg()) { return; }

    // local
    SerialHandler* pSERIAL = this->Ch->pSERIAL;
    long t0 = millis();
    while (1) { 
        if (millis() - t0 > tout) { break; } // TIME OUT
        while (pSERIAL->available() > 0) {
            // parse char
            char c = pSERIAL->read();
            boolean ok_flag = this->csvline.parseChar(c);
            if (!ok_flag) { this->reset(); break; }
            delay(1); // Stability?
        } 
        if (this->hasValidMsg()) { break; }
    }
}

// /// -------------------------
// /// RESPONSE INTERFACE
// void MsgHandler::open_response(){
//     this->Ch->pSERIAL->println(
//         "\n"
//         ">>> ", "CMD RECEIVED ", 
//         "[", millis(), "-", this->cmdHash(), "] ",
//         this->cmdCSVLineString(), " >>>"
//     );
// }

// void MsgHandler::close_response(){
//     this->Ch->pSERIAL->println(
//         "<<< ", 
//         "CMD FINISHED ",
//         "[", millis(), "-", this->cmdHash(), "-", this->respcount, "] ",
//         this->cmdCSVLineString(),
//         " <<<"
//     );
//     this->respcount = 0;
// }

// /// ----------------------------------------------------
// /// REQUEST INTERFACE

// String _request_str(String& req) { return "$$$ " + req + " $$$"; }
// unsigned int _request_hash(String& req) { return crc16_hash(0, req); }

// // [BLOKING]
// // This will wait for a confirmation
// // If a new CMd arrive that is not a confirmation it returns
// // without reseting the reader
// boolean MsgHandler::request(String req) {

//     // TODO: add bloking interface
//     SerialHandler* pSERIAL = this->Ch->pSERIAL;

//     // request
//     String req_str = _request_str(req);
//     pSERIAL->println("\n", req_str);

//     // wait Confirmation
//     String req_hash = String(_request_hash(req_str));
//     boolean ko_flag = false;
//     for (int i = 0; i < 3; i++) {
//         this->tryReadMsg(TRY_READ_MSG_TIMEOUT);
//         if (this->hasValidMsg()) {
//             if (!this->hasKey("RQCONF")) { return false; }
//             ko_flag = this->getCmdVal().equals(req_hash);
//             this->reset(); // If RQCONF reset
//             break;
//         }
//     }

//     if (ko_flag) {
//         pSERIAL->println(">>> REQUEST: CONFIRMED, req: ", req, ", hash: ", req_hash, " <<<");
//     } else {
//         pSERIAL->println(">>> REQUEST: FAILED, req: ", req, ", hash: ", req_hash, " <<<");
//     }

//     return ko_flag;
// }

// ----------------------------------------------------
// CSVLineReader INTERFACE

boolean MsgHandler::hasValidMsg(){
    return this->csvline.valid_input;
}

unsigned int MsgHandler::cmdHash(){
    return this->csvline.hash();
}

String MsgHandler::cmdCSVLineString(){
    return this->csvline.csvLineString();
}

// String MsgHandler::getCmdKey() {
//     return this->csvline.getKey();
// }

// String MsgHandler::getCmdVal() {
//     return this->csvline.getVal();
// }
// String MsgHandler::getCmdVal0() {
//     return this->csvline.getVal0();
// }
// String MsgHandler::getCmdVal1() {
//     return this->csvline.getVal1();
// }
// String MsgHandler::getCmdVal2() {
//     return this->csvline.getVal2();
// }


// ----------------------------------------------------
// TEST INTERFACE
String MsgHandler::getClassName() { return "MsgHandler"; }
