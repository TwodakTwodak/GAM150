#pragma once

#include "../Engine/GameState.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Camera.h"

class Editor : public CS230::GameState {
public:
    Editor();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override {
        return "Editor";
    }

private:
    CS230::GameObjectManager gameobjectmanager;
    int room = 1;
    int max_room = 1;
    int load_object_number = 0;
    int room_object_memory[100] = { 0 };
    int memory = 1;
    bool adding_object = false;
    bool went_map = true;
    int object_place = 0;//0-non 1-side 2-top 
    int adding_objects[100] = { 0 };
    bool cant_move = true;
    bool move_check = false;
    std::string type;
};