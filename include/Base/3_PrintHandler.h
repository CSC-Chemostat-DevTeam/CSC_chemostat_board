#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include "Base/3_AbsHandler.h"

#define LOG_ERROR_LEVEL 0
#define LOG_WARN_LEVEL 1
#define LOG_INFO_LEVEL 2

#include <Arduino.h>
#include "Base/2_utils.h"
#include "Base/3_Chemostat.h"

class PrintHandler : 
    public AbsHandler
{
    private:
        byte vlevel;
    public:
        // ----------------------------------------------------
        // CONSTRUCTOR
		PrintHandler(Chemostat* Ch);

        // ----------------------------------------------------
        // PRINT INTERFACE
        
};




#endif // SERIAL_HANDLER_H