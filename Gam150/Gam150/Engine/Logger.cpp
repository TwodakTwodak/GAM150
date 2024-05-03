/*
Copyright (C) 2024 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Logger.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Seunghyeon Song
Created:    March 8, 2023
Updated:    March 8, 2024
*/

#include <iostream>
#include "Logger.h"

CS230::Logger::Logger(Logger::Severity severity, bool use_console, std::chrono::system_clock::time_point last_tick) : min_level(severity), out_stream("Trace.log"), start_time(last_tick) {
    SetTraceLogLevel(LOG_NONE);//?
    if (use_console == true) {
        out_stream.set_rdbuf(std::cout.rdbuf()); //?
    }
}

double CS230::Logger::seconds_since_start() {
    return std::chrono::duration<double>(std::chrono::system_clock::now() - start_time).count();
}

CS230::Logger::~Logger() {
    out_stream.flush(); //?
    out_stream.close(); //?
}

void CS230::Logger::log(CS230::Logger::Severity severity, std::string message) {
    //TODO: Write this function
    if (min_level <= severity) {
        out_stream.precision(4);
        out_stream << '[' << std::fixed << seconds_since_start() << "]\t";
        out_stream <<  char_severity[static_cast<int>(severity)] << "\t" << message << std::endl;
        //severity warning
    }
    return;
}
