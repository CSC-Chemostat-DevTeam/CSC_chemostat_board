#ifndef CMD_HANDLER_H
#define CMD_HANDLER_H

#include <SD.h>
#include "Base/2_utils.h"
#include "Base/3_AbsHandler.h"
#include "Base/3_CSVLineReader.h"
#include "Base/3_SerialHandler.h"
#include "Base/3_Chemostat.h"

#define TRY_READ_MSG_TIMEOUT 300 // ms

// A subsystem for reciving and executing commands from a PC
class MsgHandler :
    public AbsHandler
{       
	private:
		CSVLineReader csvline;
		unsigned long respcount;

	public:

		// ----------------------------------------------------
        // CONSTRUCTOR
		MsgHandler(Chemostat* Ch);

		// ----------------------------------------------------
        // SKETCH INTERFACE
		void onsetup();
		
		void onloop();

		// ----------------------------------------------------
        // TEST INTERFACE
        String getClassName();

		// ----------------------------------------------------
        // CMD INTERFACE
		virtual boolean handleMsg();

		// ----------------------------------------------------
        // CMD INTERFACE 2
		/**
			Will try to read a key pair from serial.
			[BLOKING] This will block till tout or msg is received.

			\param[in] tout Waiting time in millisecunds

			\return void
		*/
		void tryReadMsg(unsigned long tout);
		void reset();

		// unsigned int cmdhash();

		/**
			get the current key as String.
		*/
		// String getCmdKey();

		/**
			get the current val as String.
		*/
		// String getCmdVal();
		// String getCmdVal0();
		// String getCmdVal1();
		// String getCmdVal2();

		boolean hasValidMsg();
		unsigned int cmdHash();
		String cmdCSVLineString();

		// boolean hasKey(const String& str);
		// boolean hasKeyPrefix(const String& prefix);
		// boolean hasKeySuffix(const String& suffix);

		// ----------------------------------------------------
		// RESPONSE INTERFACE
		// template <typename T0, typename... Ts>
		// void response(T0 arg0, Ts... args) {
		// 	this->Ch->pSERIAL->println(this->respcount, " | ", arg0, args...);
		// 	this->respcount++;
		// };
		// void open_response();
		// void close_response();

		// ----------------------------------------------------
		// REQUEST INTERFACE
		// boolean request(String req);
};

#endif // CMD_HANDLER_H