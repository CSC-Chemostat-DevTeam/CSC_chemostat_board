#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/3_StaticString.h"
#include "Base/4_SDHandler.h"
#include "Base/4_MsgHandler.h"
#include "Base/4_SerialHandler.h"
#include "Base/4_LogHandler.h"

// ----------------------------------------------------
// CONSTRUCTOR
SDHandler::SDHandler(Chemostat* Ch) :
    AbsHandler(
        /* Chemostat */ Ch
    ){
    this->_LINE_BUFFER = StaticString();
}


// ----------------------------------------------------
// SKETCH INTERFACE
void SDHandler::onsetup() {
    // TODO: This is a fatal error, do ErrorHandler
    // TODO: Add proper printing stuff
    // TODO: Add enable stuff

    Serial.print("Initializing SD card...");

    // see if the card is present and can be initialized:
    if (!SD.begin(SD_CS_PIN)) {
        Serial.println("Card failed, or not present");
        // Error just if enable
        // if (this->isEnable()) { 
        //     // TODO: Add ERROR INTERFACE ex: SD logging + led signal + soud + Serial log
            
        //     // if (DEV_MODE) {
        //     //     Serial.println("DEV MODE: card initialized.");
        //     // } else {
        //         Serial.println("Stoping till fix");
        //         while (1);
        //     // }
        // }
    } else {
        Serial.println("card initialized.");
    }
}

void SDHandler::onloop() {

}


// -------------------------
// HANDLE MSG INTERFACE
boolean SDHandler::handleMsg() {

    MsgHandler* const pMSG = this->Ch->pMSG;

    // Check target code
    if (!pMSG->hasValString(0, "SD")) { return false; }

    // CHECK WRITE & READ
    // Example: $SD:CHECK-WR%
    if (pMSG->hasValString(1, "CHECK-WR")) {
        // empty msg, just akc
        pMSG->sendMsgResponse("write_test_check", this->checkReadWrite());
        return true;
    }

    return false;
}

// ----------------------------------------------------
// _DEV INTERFACE
String SDHandler::getClassName() { return "SDHandler"; }
void SDHandler::sayHi() { 
    AbsHandler::sayHi(); // Parent
    Ch->pSERIAL->println(TAB, "SD_CS_PIN: ", SD_CS_PIN);
    Ch->pSERIAL->println(TAB, "SD_MOSI_PIN: ", SD_MOSI_PIN);
    Ch->pSERIAL->println(TAB, "SD_MISO_PIN: ", SD_MISO_PIN);
    Ch->pSERIAL->println(TAB, "SD_SCK_PIN: ", SD_SCK_PIN);
}


// ----------------------------------------------------
// SD INTERFACE

/// ----------------------------------------------------
/// LINE FILE INTERFACE
String SDHandler::readLineFile(String file, String onerr) {
    // reset
    this->_LINE_BUFFER.reset();

    // open the file for reading:
    this->exists(file); // TODO: fix this, I'm using it only for logging
    File IO = SD.open(file, FILE_READ);
    char c = '0';
    if (IO) {
        while(IO.available()){
            if (this->_LINE_BUFFER.isFull()) {
                // TOLOG
                Serial.print("Single line file too long!!!");
                Serial.println(file);

                this->_LINE_BUFFER.reset();
                IO.close();
                return onerr;
            }
            c = IO.read();
            if (c == '\n') { break; } // end of line
            this->_LINE_BUFFER.push(c);
        }
    } else {
        // TO ERR HANDLE
        Serial.print("Reading failed ");
        Serial.println(file);
        IO.close();
        return onerr;
    }
    String str = this->_LINE_BUFFER.toString();
    str.trim();
    IO.close();
    return str;
}

String SDHandler::getLineString() {
    String str = this->_LINE_BUFFER.toString();
    str.trim();
    return str;
}

// TRIM line
boolean SDHandler::writeLineFile(String file, String line) {
    line.trim();
    // open the file for reading:
    this->remove(file);
    // TODO: make this stable (on DataHandle interface)
    File IO = SD.open(file, FILE_WRITE);
    if (IO) {
        IO.print(line);
        IO.close();
        return true;
    } else {
        // TOLOG
        Serial.print("Writing failed ");
        Serial.println(file);
        IO.close();
        return false;
    };
}

/// ----------------------------------------------------
/// HARDWARE TEST INTERFACE
// - check file write and read
boolean SDHandler::checkReadWrite() {
    this->remove(SD_TEST_FILE_PATH);
    if (this->exists(SD_TEST_FILE_PATH)) { return false; }
    String token = String(millis());
    if (!writeLineFile(SD_TEST_FILE_PATH, token)) {return false; }
    if (!this->exists(SD_TEST_FILE_PATH)) { return false; }
    String line = readLineFile(SD_TEST_FILE_PATH, "_");
    this->remove(SD_TEST_FILE_PATH);
    return line.equals(token);
}

/// ----------------------------------------------------
/// FILE UTILS

boolean SDHandler::exists(String file) {
    boolean e = SD.exists(file);
    this->Ch->pLOG->dev("SD.exists(\"", file, "\") = ", e);
    return e;
}

void SDHandler::mkdir(String file) {
    if (!this->exists(file)) {
        this->Ch->pLOG->dev("SD.mkdir(\"", file, "\")");
        SD.mkdir(file);
        this->exists(file); // check
    }
}

void SDHandler::remove(String file) {
    if (this->exists(file)) {
        SD.rmdir(file);
        SD.remove(file);
        this->Ch->pLOG->dev("SD.remove(\"", file, "\")");
        this->exists(file); // check
    }
}

