#ifndef PUMP_SUBSYSTEM_H
#define PUMP_SUBSYSTEM_H

#include "1_config.h"
#include "2_utils.h"
#include "3_Timer.h"
#include "3_SubSystem.h"

class PumpSubsystem :
    public SubSystem
{       
	private:

	public:
		Timer timer;
        long pulse_duration;
        long pulse_period;

        // ----------------------------------------------------
        // CONSTRUCTOR
        
        PumpSubsystem();

        // ----------------------------------------------------
        // SKETCH INTERFACE
        void onsetup();
        
        void onloop();

        // ----------------------------------------------------
        // CMD INTERFACE
		boolean execCmd(String& key, String& val);

        // ----------------------------------------------------
        // BLOCKING INTERFACE
        void beforeBlock();

        void afterBlock();

        // ----------------------------------------------------
        // BOTTOM INTERFACE
        void onBottomPressed();

        // ----------------------------------------------------
        // STOP INTERFACE
        void onStop();
};

#endif // PUMP_SUBSYSTEM_H