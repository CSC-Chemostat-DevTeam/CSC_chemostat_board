#ifndef DATALOGGER_SYBSYSTEM_H
#define DATALOGGER_SYBSYSTEM_H

#include "1_config.h"
#include "2_utils.h"
#include "3_Timer.h"
#include "3_SubSystem.h"
#include "3_concurrent_task.h"

#define LOGGER_LOG_FREC 10000 // ms

class DataLoggerSubsystem :
    public SubSystem
{       
    private:
        
        String wchapter;
        String wheader; // TODO: use STATIC STRING
        String wline; // TODO: use STATIC STRING
        Timer log_timer;

    public:
        // ----------------------------------------------------
        // CONSTRUCTOR
        DataLoggerSubsystem();

        // ----------------------------------------------------
        // SKETCH INTERFACE
        void onsetup();
        
        void onloop();

        // ----------------------------------------------------
        // CMD INTERFACE
        boolean execCmd(String& key, String& val);
        
        // ----------------------------------------------------
        // LOGGER INTERFACE
        
        void appendHeader(String header);

        void appendValue(String val);

        void onLogWrite(DataLoggerSubsystem& logger);

        // ----------------------------------------------------
        // PROGRAM INTERFACE
        void onProgramUpdate(String chapterid);

        // ----------------------------------------------------
        // STOP INTERFACE
        void onStop();

};

#endif // DATALOGGER_SYBSYSTEM_H