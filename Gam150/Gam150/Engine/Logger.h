/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Logger.h
Project:    


Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#ifndef LOGGER_H
#define LOGGER_H 

#include <string>
#include <fstream>
#include <raylib.h>
#include <chrono>

namespace Gam150 {
    class Logger {
    public:
        enum class Severity {
            Verbose,  //Minor messages
            Debug,    //Only used while actively debugging
            Event,    //General event, like key press or state change
            Error     //Errors, such as file load errors
        };
        Logger(Severity severity, bool use_console, std::chrono::system_clock::time_point last_tick);
        ~Logger();
        void LogError(std::string text) {
            log(Severity::Error, text);
        }
        void LogEvent(std::string text) {
            log(Severity::Event, text);
        }
        void LogDebug(std::string text) {
            log(Severity::Debug, text);
        }
        void LogVerbose(std::string text) {
            log(Severity::Verbose, text);
        }
    private:
        Severity min_level;
        std::ofstream out_stream;
        void log(Severity severity, std::string message);
        std::chrono::system_clock::time_point start_time;
        double seconds_since_start();
        const std::string char_severity[4] = { "Verbose", "Debug", "Event", "Error" }; //Remebering + Not okay?
    };
}

#endif
