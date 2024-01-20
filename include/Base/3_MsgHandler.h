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

		// Response
		unsigned long respcount;
		unsigned int hash;

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
        // MSG INTERFACE
		virtual boolean handleMsg();

		// ----------------------------------------------------
        // MSG INTERFACE 2
		/**
			Will try to read a key pair from serial.
			[BLOKING] This will block till tout or msg is received.

			\param[in] tout Waiting time in millisecunds

			\return void
		*/
		void tryReadMsg(unsigned long tout);
		void reset();

		// unsigned int cmdhash();

		String getValString(byte i);

		boolean hasValidMsg();
		unsigned int msgHash();
		String msgCsvLineString();

		// ----------------------------------------------------
		// MSG VAL STRING QUERIES
		boolean hasValString(byte i, const String& str);
		boolean hasValStringPrefix(byte i, const String& prefix);
		boolean hasValStringSuffix(byte i, const String& suffix);

		// ----------------------------------------------------
		// SEND MSG
		template <typename Arg>
		void sendMsg(Arg arg0) {
			this->Ch->pSERIAL->println(CSV_LINE_INIT_CHAR, arg0, SCV_LINE_END_CHAR);
		}
		template <typename T0, typename... Ts>
		void sendMsg(T0 arg0, Ts... args) {
			this->Ch->pSERIAL->print(CSV_LINE_INIT_CHAR);
			_printCSVVals(arg0, args...);
			this->Ch->pSERIAL->println(SCV_LINE_END_CHAR);
		};

		// utils
		template <typename Arg>
		void _printCSVVals(Arg arg) { this->Ch->pSERIAL->print(arg);}
		// variadic template with one or more arguments.
		template <typename First, typename... Args>
		void _printCSVVals(First first, Args... args) {
			this->Ch->pSERIAL->print(first); 
			this->Ch->pSERIAL->print(SCV_LINE_SEP_CHAR); 
			_printCSVVals(args...);
		}

		// ----------------------------------------------------
		// RESPONSE INTERFACE
		// Example $RES:MSG-HASH:TIMETAG:RECIEVED%
		// Example $RES:MSG-HASH:RES_COUNT:BLA:BLE:BLI%
		// Example $RES:MSG-HASH:TIMETAG:DONE%
		template <typename T0, typename... Ts>
		void sendMsgResponse(T0 arg0, Ts... args) {
			this->sendMsg("RES", this->hash, this->respcount, arg0, args...);
			this->respcount++;
		};
		void openMsgResponse();
		void closeMsgResponse();

		// ----------------------------------------------------
		// REQUEST INTERFACE
		// boolean request(String req);
};

#endif // CMD_HANDLER_H