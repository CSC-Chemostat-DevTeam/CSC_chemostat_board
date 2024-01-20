// #ifndef LOG_HANDLER_H
// #define LOG_HANDLER_H

// #include <Arduino.h>

// #include "Base/1_config.h"
// #include "Base/2_utils.h"
// #include "Base/3_Chemostat.h"
// #include "Base/3_AbsHandler.h"

// // // TODO: Move out log function
// // #define LOG_ERROR_LEVEL 0
// // #define LOG_WARN_LEVEL 1
// // #define LOG_INFO_LEVEL 2
// // #define LOG_DEV_LEVEL 3

// // Think about both Serial and SD logs, maybe with different frequencies and independent levels
// class LogHandler : 
//     public AbsHandler
// {
//     private:
//         // byte serial_vlevel;
//         // byte sd_vlevel;

//     public:
//         // ----------------------------------------------------
//         // CONSTRUCTOR
// 		LogHandler(Chemostat* Ch);

//         // ----------------------------------------------------
//         // SKETCH INTERFACE
//         void onsetup();
//         void onloop();

//         // ----------------------------------------------------
//         // SERIAL LOG INTERFACE
//         // TODO: Use msg interface
        
//         // byte getVLevel();
//         // void setVLevel(byte vlv);

//         // template <typename T0, typename... Ts>
//         // void _log(T0 tag, Ts... args) {
//         //     _println(">>> ", tag, ":"); 
//         //     _println(args...);
//         //     _println("<<<"); 
//         // }
        
//         // template <typename T0, typename... Ts>
//         // void error(T0 arg0, Ts... args) {
//         //     if (this->vlevel < LOG_ERROR_LEVEL) { return; }
//         //     _log("ERROR", arg0, args...);
//         // }

//         // template <typename T0, typename... Ts>
//         // void info(T0 arg0, Ts... args) {
//         //     if (this->vlevel < LOG_INFO_LEVEL) { return; }
//         //     _log("INFO", arg0, args...);
//         // }

//         // template <typename T0, typename... Ts>
//         // void warn(T0 arg0, Ts... args) {
//         //     if (this->vlevel < LOG_WARN_LEVEL) { return; }
//         //     _log("WARN", arg0, args...);
//         // }

//         // template <typename T0, typename... Ts>
//         // void dev(T0 arg0, Ts... args) {
//         //     if (this->vlevel < LOG_DEV_LEVEL) { return; }
//         //     _log("DEV", arg0, args...);
//         // }
        
// };


// #endif // LOG_HANDLER_H