/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Engine.h
Project:    



Engine
Author:     Jonathan Holmes, Seunghyeon Song
Created:    March 8, 2023
Updated:    March 18, 2024
*/

#ifndef ENGINE_H
#define ENGINE_H

#include <chrono>
#include "Logger.h"
#include "Window.h"
#include "GameStateManager.h"
#include "Input.h"
#include "TextureManager.h"
#include "Font.h"

class Engine {
public:
    static Engine& Instance() {
        static Engine instance;
        return instance;
    }

    static Gam150::Logger& GetLogger() {
        return Instance().logger;
    }

    static Gam150::Window& GetWindow() {
        return Instance().window;
    }

    static Gam150::GameStateManager& GetGameStateManager() {
        return Instance().gamestatemanager;
    }

    static Gam150::Input& GetInput() {
        return Instance().input;
    }

    static Gam150::TextureManager& GetTextureManager() {
        return Instance().texturemanager;
    }

    static Gam150::Font& GetFont(int index) {
        return Instance().fonts[index];
    }

    void AddFont(const std::filesystem::path& file_name);

    //this things make possible to use private instance of class!!!!!!

    void Start(std::string window_title);
    void Stop();
    void Update();
    bool HasGameEnded();

private:
    Engine();

    std::chrono::system_clock::time_point last_tick;
    //maybe = now? not sure about this ting
    std::chrono::system_clock::time_point last_test;

    int frame_count = 0;

    static constexpr double TargetFPS = 30.0;
    static constexpr int FPSDuration = 5;
    static constexpr int FPSTargetFrames = static_cast<int>(FPSDuration * TargetFPS);

    Gam150::Logger logger; //like this?
    Gam150::Window window;
    Gam150::GameStateManager gamestatemanager;
    Gam150::Input input;
    Gam150::TextureManager texturemanager;

    std::vector<Gam150::Font> fonts;
};

#endif

