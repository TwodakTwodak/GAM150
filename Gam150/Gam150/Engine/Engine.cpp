/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Engine.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Seunghyeon Song
Created:    March 8, 2023
Updated:    March 14, 2024
*/

#include "Engine.h"

Engine::Engine() : last_tick(std::chrono::system_clock::now()),
    //delegating is setting value at the start part must put , at the end!
#ifdef _DEBUG
    logger(CS230::Logger::Severity::Debug, true, last_tick)
    //"last_tick" where should i put this?
#else
    logger(CS230::Logger::Severity::Event, false)
#endif
{
}

void Engine::AddFont(const std::filesystem::path& file_name)
{
    fonts.push_back(file_name);
}

void Engine::Start(std::string window_title) {
    unsigned int seed = time(NULL);
    srand(seed);
    logger.LogEvent(std::to_string(seed));
    logger.LogEvent("Engine Started");
    window.Start(window_title);
    //Start other services
    last_test = last_tick;
}

void Engine::Stop() {
    //Stop all services
    logger.LogEvent("Engine Stopped");
}

void Engine::Update() {
    const std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    double dt = std::chrono::duration<double>(now - last_tick).count();
    //why if? for (double time = 0; time <= (1.0 / TargetFPS); time += dt);
    //not a milli second
    //it show 0.00000fps at the first debug
    if (dt >= 1/ TargetFPS) {
        logger.LogVerbose("Engine Update");
        //why are we using this?
        last_tick = now;

        //++ in back or front?
        frame_count++;
        if (frame_count >= FPSTargetFrames) {
            double actual_time =  std::chrono::duration<double>(now - last_test).count();
            logger.LogDebug("FPS: " + std::to_string(frame_count / actual_time));
            //It will take a lot of time for loading at the first time so could get a error for that part!
            frame_count = 0;
            last_test = now;
        }
        gamestatemanager.Update(dt);
        input.Update();
        window.Update();
    }
    //Update other services
}

bool Engine::HasGameEnded() {
    if (gamestatemanager.HasGameEnded() || window.IsClosed()) {
        return true;
        //Will type about stopping at error(:
    }
    else {
        return false;
    }
}