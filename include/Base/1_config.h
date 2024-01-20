#ifndef CONFIG_H
#define CONFIG_H

// ----------------------------------------------------
// Serial communication (to be sync with PC side)

#define IO_BAUDRATE               115200



// ----------------------------------------------------
// StaticStrings.h

#define STATIC_STRING_BUFFER_LEN 128

// ----------------------------------------------------
// Chemostat.h

#define CHEMOSTAT_HANDLERS_BUFFER_SIZE 32

// ----------------------------------------------------
// CSVLineReader.h

#define CSV_LINE_READER_VALS_NUMBER 5

// (to be sync with PC side)
// Example of CSV line $key:VAL0:VAL1%
#define CSV_LINE_INIT_CHAR '$'
#define SCV_LINE_SEP_CHAR ':'
#define SCV_LINE_END_CHAR '%'

// ----------------------------------------------------
// MsgHandler

// (to be sync with PC side)
#define MSG_RECIEVED_TOKEN "RECIEVED!!!"
#define MSG_RESPONSE_DONE_TOKEN  "DONE!!!"
#define UNKNOWN_CMD_ERROR_TOKEN "ERROR, UNKNOWN COMMAND!!!"

#endif // CONFIG_H