#ifndef CHEMOSTAT_H
#define CHEMOSTAT_H

#include "1_config.h"

// foward declaration
class AbsHandler;
class MsgHandler;
class SerialHandler;

// TODO: make a sayHi system for tracking obj pointers
// To see why they change with time

// TODO: use 'cost' stuff whn required

class Chemostat {
    private: 
        AbsHandler* _MSG_HANDLERS_BUFFER[CHEMOSTAT_HANDLERS_BUFFER_SIZE];
        AbsHandler* _ALL_HANDLERS_BUFFER[CHEMOSTAT_HANDLERS_BUFFER_SIZE];

    public:
        // ----------------------------------------------------
        // HANDLERS
        MsgHandler* pMSG;
        SerialHandler* pSERIAL;

        // ----------------------------------------------------
        // CONSTRUCTOR
        Chemostat();

        // ----------------------------------------------------
        // SKETCH INTERFACE
        void onsetup();
            
        void onloop();

        // ----------------------------------------------------
        // _DEV INTERFACE
        String getClassName();
        void sayHi();

        // ----------------------------------------------------
        // MSG INTERFACE
        boolean handleMsg();

        // ----------------------------------------------------
        // TIME INTERFACE
        // Use a clock module if present, otherwise use millis or progress
        String nowTimeTag();
        
        // ----------------------------------------------------
        // HANDLERS INTERFACE

        // MSG INTERFACE
        void handleAllMsgs();
        void pushMsgHandler(AbsHandler* h);

        void pushHandler(AbsHandler* h);
        
        // ----------------------------------------------------
        // OTHERS
        void printWelcome();
};


void _pushHandler(AbsHandler* buffer[], AbsHandler* h);

#endif // CHEMOSTAT_H