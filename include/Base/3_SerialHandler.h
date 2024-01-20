#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include <Arduino.h>

#include "Base/1_config.h"
#include "Base/2_utils.h"
#include "Base/3_Chemostat.h"
#include "Base/3_AbsHandler.h"

// All Chemostat serial printing must use this Handler
class SerialHandler : 
    public AbsHandler
{
    private:
        // byte vlevel;
        unsigned long baud_rate;

    public:
        // ----------------------------------------------------
        // CONSTRUCTOR
		SerialHandler(Chemostat* Ch);

        // ----------------------------------------------------
        // SKETCH INTERFACE
        void onsetup();
        void onloop();

        // ----------------------------------------------------
        // SERIAL INTERFACE
        // void setBaudRate(unsigned long brate);
        unsigned long getBaudRate();

        template <typename T0, typename... Ts>
        void print(T0 arg0, Ts... args) {
            _print(arg0, args...);
        }

        template <typename T0, typename... Ts>
        void println(T0 arg0, Ts... args) {
            _println(arg0, args...);
        }

        int available() { return Serial.available(); }
        int read() { return Serial.read(); }

        // ----------------------------------------------------
        // TEST INTERFACE
        String getClassName();

};




#endif // SERIAL_HANDLER_H