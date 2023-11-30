// Global libs
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

// Local libs
#include "1_config.h"
#include "4_bottom_subsystem.h"
#include "4_sd_subsystem.h"
#include "4_cmd_subsystem.h"
#include "4_stirrel_subsystem.h"
#include "4_do_subsystem.h"
#include "4_pump_subsystem.h"
#include "4_program_subsystem.h"
#include "4_Tcontrol_subsystem.h"
#include "4_datalogger_subsystem.h"
#include "4_uploader_subsystem.h"
#include "5_interfaces.h"

// ----------------------------------------------------
// Subsystems
CmdSubsystem CMDSYS = CmdSubsystem();
SDSubsystem SDSYS = SDSubsystem();
BottomSubsystem BTTSYS = BottomSubsystem();
StirrelSubsystem STIRSYS = StirrelSubsystem();
DOSubsystem DOSYS = DOSubsystem();
PumpSubsystem PUMPSYS = PumpSubsystem();
ProgramSubsystem PROGSYS = ProgramSubsystem();
TControlSubsystem TCONTRLSYS = TControlSubsystem();
DataLoggerSubsystem LOGGERSYS = DataLoggerSubsystem();
UploaderSubsystem UPLOADERSYS = UploaderSubsystem();

void setup() {
  // Create a Serial System?
  Serial.begin(115200); // TODO: move rate to config
  while (!Serial) {
      ;  // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Hello");

  // SUBSYSTEMS ONSETUP
  CMDSYS.onsetup();
  SDSYS.onsetup();
  BTTSYS.onsetup();
  STIRSYS.onsetup();
  DOSYS.onsetup();
  PUMPSYS.onsetup();
  PROGSYS.onsetup();
  TCONTRLSYS.onsetup();
  LOGGERSYS.onsetup();
  UPLOADERSYS.onsetup();

}

void loop() {

  // SUBSYSTEMS ONLOOP
  CMDSYS.onloop();
  SDSYS.onloop();
  BTTSYS.onloop();
  TCONTRLSYS.onloop();
  STIRSYS.onloop();
  DOSYS.onloop(); // BLOKING
  PUMPSYS.onloop(); // BLOKING
  PROGSYS.onloop();
  LOGGERSYS.onloop();
  UPLOADERSYS.onloop(); // BLOKING d
}


// ----------------------------------------------------
// class SubSystem{
//   private:
//     boolean enable0;
//     boolean enable;

//   public:
//     SubSystem(boolean enable, boolean enable0){
//       Serial.println("At SubSystem::SubSystem");
//       this->enable = enable;
//       this->enable0 = enable0;
//     }

//     // ----------------------------------------------------
//     // ENABLE INTERFACE
//     virtual boolean isEnable(){
//       Serial.println("At SubSystem::isEnable");
//       if (!this->enable) { return false; }
//       if (!this->enable0) { return false; }
//       return true;
//     }
// };

// #define TEST_SYS_INCLUDE_FLAG true
// class TestSubSystem: public SubSystem {
//   public:
//     TestSubSystem() 
//     : SubSystem(/* enable */ true, /* enable0 */ TEST_SYS_INCLUDE_FLAG) {
//       Serial.println("At TestSubSystem::TestSubSystem");
//     }

//     boolean isEnable(){
//       Serial.println("At TestSubSystem::isEnable");
//       return this->SubSystem::isEnable(); // call parent
//     }
// };