#ifndef CHEMOSTAT_H
#define CHEMOSTAT_H

// foward declaration
class AbsHandler;
class CmdHandler;

#define HANDLERS_BUFFER_SIZE 32

// TODO: make a sayHi system for tracking obj pointers
// To see why they change with time

class Chemostat {
    private: 
        AbsHandler* _CMD_HANDLERS_BUFFER[HANDLERS_BUFFER_SIZE];

    public:
        // ----------------------------------------------------
        // HANDLERS
        CmdHandler* pCMD;

        // ----------------------------------------------------
        // CONSTRUCTOR
        Chemostat();

        // ----------------------------------------------------
        // SKETCH INTERFACE
        void onsetup();
            
        void onloop();

        // ----------------------------------------------------
        // CMD INTERFACE
        boolean execCmd(String& key, String& val);
        
        // ----------------------------------------------------
        // ALL CALLERS

        // CMD INTERFACE
        void execAllCmd();
        void pushCmdHandler(AbsHandler* h);
};


#endif // CHEMOSTAT_H