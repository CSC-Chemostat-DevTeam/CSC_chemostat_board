#ifndef BOTTOM_SUBSYSTEM_H
#define BOTTOM_SUBSYSTEM_H

#include "1_config.h"
#include "3_SubSystem.h"
#include "3_Timer.h"

// TODO move subsystems to namespaces
class BottomSubsystem :
    public SubSystem
{       
    public:
        Timer timer;
        byte state;

        // ----------------------------------------------------
        // CONSTRUCTOR
        BottomSubsystem();

        // ----------------------------------------------------
        // SKETCH INTERFACE
        void onsetup();

        void onloop();

        // ----------------------------------------------------
        // BOTTOM INTERFACE
        void onBottomPressed();

        // ----------------------------------------------------
        // STOP INTERFACE
        void onStop();

};

#endif // BOTTOM_SUBSYSTEM_H