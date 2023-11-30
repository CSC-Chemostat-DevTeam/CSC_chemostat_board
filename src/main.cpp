// Global libs
#include <Arduino.h>
#include <SPI.h>
#include <SD.h>

// Local libs
#include "Base/1_config.h"
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

// DEV //
class _Chemostat;
class _SubSystem;

class _SubSystem{
  public:
    _Chemostat* Ch;
    String id;

    _SubSystem(_Chemostat* Ch, String id);

    void hiSub1();
    void hiSub2();

    void hi();
    void from();
};

class _Chemostat {
  public:
    _SubSystem* _sub1;
    _SubSystem* _sub2;
    _Chemostat();

};


_Chemostat::_Chemostat() {
  this->_sub1 = new _SubSystem(this, "sub1");
  this->_sub2 = new _SubSystem(this, "sub2");
}

_SubSystem::_SubSystem(_Chemostat* Ch, String id) {
    this->Ch = Ch;
    this->id = id;
  }

void _SubSystem::hiSub1(){ this->from(); this->Ch->_sub1->hi(); }
void _SubSystem::hiSub2(){ this->from(); this->Ch->_sub2->hi(); }
void _SubSystem::hi() {
  Serial.print("Hi, I'm ");
  Serial.println(this->id);
}
void _SubSystem::from() {
  Serial.print("from ");
  Serial.println(this->id);
}



void setup() {
  // Create a Serial System?
  // Serial.begin(IO_BAUDRATE); // TODO: move rate to config
  Serial.begin(115200); // TODO: move rate to config
  while (!Serial) {
      ;  // wait for serial port to connect. Needed for native USB port only
  }
  Serial.println("Hello");

  // DEV
  _Chemostat _ch = _Chemostat();
  _ch._sub1->hiSub1();
  _ch._sub1->hiSub2();
  _ch._sub2->hiSub1();
  _ch._sub2->hiSub2();

  while(1);

}

void loop(){
  ;
}


// // ----------------------------------------------------
// // Subsystems
// CmdSubsystem CMDSYS = CmdSubsystem();
// SDSubsystem SDSYS = SDSubsystem();
// BottomSubsystem BTTSYS = BottomSubsystem();
// StirrelSubsystem STIRSYS = StirrelSubsystem();
// DOSubsystem DOSYS = DOSubsystem();
// PumpSubsystem PUMPSYS = PumpSubsystem();
// ProgramSubsystem PROGSYS = ProgramSubsystem();
// TControlSubsystem TCONTRLSYS = TControlSubsystem();
// DataLoggerSubsystem LOGGERSYS = DataLoggerSubsystem();
// UploaderSubsystem UPLOADERSYS = UploaderSubsystem();

// void setup() {
//   // Create a Serial System?
//   Serial.begin(115200); // TODO: move rate to config
//   while (!Serial) {
//       ;  // wait for serial port to connect. Needed for native USB port only
//   }
//   Serial.println("Hello");

//   // SUBSYSTEMS ONSETUP
//   CMDSYS.onsetup();
//   SDSYS.onsetup();
//   BTTSYS.onsetup();
//   STIRSYS.onsetup();
//   DOSYS.onsetup();
//   PUMPSYS.onsetup();
//   PROGSYS.onsetup();
//   TCONTRLSYS.onsetup();
//   LOGGERSYS.onsetup();
//   UPLOADERSYS.onsetup();

// }

// void loop() {

//   // SUBSYSTEMS ONLOOP
//   CMDSYS.onloop();
//   SDSYS.onloop();
//   BTTSYS.onloop();
//   TCONTRLSYS.onloop();
//   STIRSYS.onloop();
//   DOSYS.onloop(); // BLOKING
//   PUMPSYS.onloop(); // BLOKING
//   PROGSYS.onloop();
//   LOGGERSYS.onloop();
//   UPLOADERSYS.onloop(); // BLOKING d
// }


