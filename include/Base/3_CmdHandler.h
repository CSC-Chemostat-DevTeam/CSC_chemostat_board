#ifndef CMD_HANDLER_H
#define CMD_HANDLER_H

#include <SD.h>
#include "Base/3_AbsHandler.h"
#include "Base/3_ConcurrentTask.h"
#include "Base/3_KVReader.h"
#include "Base/3_Chemostat.h"

#define CMD_INPUT_TIMEOUT 300 // ms

// A subsystem for reciving and executing commands from a PC
class CmdHandler :
    public AbsHandler
{       
	private:
		KVReader kvreader;

	public:

		// ----------------------------------------------------
        // CONSTRUCTOR
		CmdHandler(Chemostat* Ch);

		// ----------------------------------------------------
        // SKETCH INTERFACE
		void onsetup();
		
		void onloop();

		// ----------------------------------------------------
        // CMD INTERFACE
		boolean execCmd(String& key, String& val);

		// ----------------------------------------------------
        // CMD INTERFACE 2
		/**
			Will try to read a key pair from serial.
			[BLOKING] This will block till tout or msg is received.

			\param[in] tout Waiting time in millisecunds

			\return void
		*/
		void receive_cmd(unsigned long tout);

		unsigned int cmdhash();

		// TODO: implement a full recieve responce cmd system
		// Serial.print the responce of the commands
		// Responce ex. HASH reponse...
		// The current Akw message is just a responce

		/**
			get the current key as String.
		*/
		String getCmdKey();

		/**
			get the current val as String.
		*/
		String getCmdVal();

		boolean hasCmd();
};

// ----------------------------------------------------
// Static Tools
String _parseCmdString(String& key, const String& prefix);

#endif // CMD_HANDLER_H