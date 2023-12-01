#include "Base/1_config.h"
#include "Base/3_KVReader.h"
#include "Base/3_CmdHandler.h"

// Interfaces will be called using the Chemostat object

// ----------------------------------------------------
// CONSTRUCTOR
CmdHandler::CmdHandler(Chemostat* Ch) :
    AbsHandler(
        /* Chemostat */ Ch
    ){
    // Serial.println(">>> At CmdHandler::CmdHandler <<<");
    this->kvreader = KVReader();
}

// ----------------------------------------------------
// SKETCH INTERFACE
void CmdHandler::onsetup(){ ; }

void CmdHandler::onloop(){
    
    // Serial.println(">>> CmdHandler::onloop <<<");

    // check if there is something to read
    if (Serial.available() == 0) { return; }

    // read cmd
    this->receive_cmd(CMD_INPUT_TIMEOUT);

    // exec all handlers commands
    this->Ch->execAllCmd();
}

void CmdHandler::receive_cmd(unsigned long tout){

    // Serial.println(">>> CmdHandler::receive_cmd <<<");

    // local
    long t0 = millis();

    // reset reader
    this->kvreader.reset();

    while (1) { 

        // TIME OUT
        if (millis() - t0 > tout) { break; }

        // Read chars
        while (Serial.available() > 0) {

            // parse char
            char c = Serial.read();
            boolean err_flag = this->kvreader.parseChar(c);

            // break if error
            if (err_flag) { break; }

            delay(1); // Stability?
            
        } // while (Serial.available() > 0) {

        // break if valid was found
        if (this->kvreader.valid_input) { break; }

    } // while(1)

    // Send akw
    if (this->kvreader.valid_input) { 
        String akw = "";
        akw += "Cmd Recieved ";
        akw += millis();
        akw += "-";
        akw += this->kvreader.hash();
        akw += " ";
        akw += this->kvreader.kvString();
        Serial.println(akw);

        delay(1);
    } else {
        this->kvreader.reset();
    }
}

unsigned int CmdHandler::cmdhash(){
    return this->kvreader.hash();
}

// ----------------------------------------------------
// CMD INTERFACE
boolean CmdHandler::execCmd(String& key, String& val) {

    // without prefix
    if (key.equals("ECHO")) {
        Serial.println(val);
        return true;
    }

    // get cmd
    String cmd = _parseCmdString(key, "CMD-");
    if (cmd.equals("")) {return false; }

    // Call parent
    if (this->AbsHandler::execCmd(cmd, val)) { return true; }

    return false;

}

// ----------------------------------------------------
// KVReader INTERFACE

boolean CmdHandler::hasCmd(){
    return this->kvreader.valid_input;
}

String CmdHandler::getCmdKey() {
    return this->kvreader.getKey();
}

String CmdHandler::getCmdVal() {
    return this->kvreader.getVal();
}

// ----------------------------------------------------
// Returns "" if prefix does not match
String _parseCmdString(String& key, const String& prefix){
    if (!key.startsWith(prefix)) { return ""; }
    return key.substring(prefix.length());
}