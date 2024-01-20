#ifndef ABS_HANDLER_H
#define ABS_HANDLER_H

//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---
// A general base class for each handler.
// A main goal is to group all handlers in a single array on the 
// Chemostat class
//  --- --- --- --- --- --- --- --- --- --- --- --- --- ---

#include <Arduino.h>

#include "Base/3_Chemostat.h"

// ----------------------------------------------------
// TODO: Add an 'info' 'warn' 'error' function to print stuff

// ----------------------------------------------------
class AbsHandler {
  private:
    boolean enable0;
    boolean enable;
    // String id; // For dev

  public:
    Chemostat* Ch;

    AbsHandler(Chemostat* Ch);

    // ----------------------------------------------------
    // ENABLE INTERFACE
    virtual boolean _enable();
    virtual boolean _enable0();
    virtual void Enable(boolean flag);
    virtual void Enable0(boolean flag);
    virtual boolean isEnable();

    // ----------------------------------------------------
    // CMD INTERFACE
    virtual boolean handleMsg();

    // ----------------------------------------------------
    // TEST INTERFACE
    virtual String getClassName();
    virtual void sayHi();
    

};

#endif // ABS_HANDLER_H