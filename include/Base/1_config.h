#ifndef CONFIG_H
#define CONFIG_H

// ----------------------------------------------------
// Serial communication (to be sync with PC side)

#define IO_BAUDRATE               115200



// ----------------------------------------------------
// StaticStrings.h

#define STATIC_STRING_BUFFER_LEN 128

// ----------------------------------------------------
// Cehmostat.h

#define CHEMOSTAT_HANDLERS_BUFFER_SIZE 32

// ----------------------------------------------------
// CSVLineReader.h
// Example of CSV line $key:VAL0:VAL1%
#define SCV_LINE_INIT_CHAR '$'
#define SCV_LINE_SEP_CHAR ':'
#define SCV_LINE_END_CHAR '%'

#define CSV_LINE_READER_VALS_NUMBER 5

#endif // CONFIG_H