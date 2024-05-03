/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameStateManager.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Seunghyeon Song
Created:    March 8, 2023
Upated:     March 15, 2024
*/

#include "GameStateManager.h"
#include "Engine.h"

CS230::GameStateManager::GameStateManager() :
    current_gamestate(nullptr),
    next_gamestate(nullptr),
    status(Status::STARTING)
{ }

void CS230::GameStateManager::Update(double dt) {
    switch (status) {
    case Status::STARTING:
        next_gamestate = gamestates[0];
        status = Status::LOADING;
        if (gamestates.size() < 1) {
            status = Status::STOPPING;
        }
        break;
    case Status::LOADING:
        current_gamestate = next_gamestate;
        Engine::GetLogger().LogEvent("Load " + current_gamestate->GetName());
        current_gamestate->Load();
        Engine::GetLogger().LogEvent("Load Complete");
        status = Status::UPDATING;
        break;
    case Status::UPDATING:
        if (current_gamestate != next_gamestate) {
            status = Status::UNLOADING;
        }
        else {
            Engine::GetLogger().LogVerbose("Update " + current_gamestate->GetName());
            current_gamestate->Update(dt);
            current_gamestate->Draw();
            //new change
        }
        //Without else counter goes to 6!
        break;
    case Status::UNLOADING:
        Engine::GetLogger().LogEvent("Unload " + current_gamestate->GetName()); //Is this right there are no comment about this. Without this code just Name of State shows on screen.
        current_gamestate->Unload();
        Engine::GetTextureManager().Unload();
        Engine::GetLogger().LogEvent("Unload Complete");
        status = Status::LOADING;
        if(next_gamestate == nullptr){
            status = Status::STOPPING;
        }
        break;
    case Status::STOPPING:
        status = Status::EXIT;
        //Will type someday
        break;
    case Status::EXIT:
        break;
    }
}

void CS230::GameStateManager::AddGameState(GameState& gamestate) {
    gamestates.push_back(&gamestate); //&?
}

void CS230::GameStateManager::SetNextGameState(int index) {
    next_gamestate = gamestates[index]; //?
}

void CS230::GameStateManager::ReloadGameState() {
    status = Status::UNLOADING;//Where are we using this?
    //how the hack is this working!
}

void CS230::GameStateManager::ClearNextGameState() {
    next_gamestate = nullptr;
}

bool CS230::GameStateManager::HasGameEnded() {
    return status == Status::EXIT;
}
