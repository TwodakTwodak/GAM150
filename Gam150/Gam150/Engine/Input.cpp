/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Input.c
Project:    



Engine
Author:     Jonathan Holmes, Seunghyeon Song
Created:    March 8, 2023
Updated:    March 18, 2024
*/

#include "Input.h"
#include "Engine.h"
#include <raylib.h>

Gam150::Input::Input() {
    keys_down.resize(static_cast<int>(Keys::Count));
    previous_keys_down.resize(static_cast<int>(Keys::Count));
}

constexpr int Gam150_to_rl(Gam150::Input::Keys Gam150_key) noexcept {
    switch (Gam150_key) {
    case Gam150::Input::Keys::A:
        return KEY_A;
    case Gam150::Input::Keys::B:
        return KEY_B;
    case Gam150::Input::Keys::C:
        return KEY_C;
    case Gam150::Input::Keys::D:
        return KEY_D;
    case Gam150::Input::Keys::E:
        return KEY_E;
    case Gam150::Input::Keys::F:
        return KEY_F;
    case Gam150::Input::Keys::G:
        return KEY_G;
    case Gam150::Input::Keys::H:
        return KEY_H;
    case Gam150::Input::Keys::I:
        return KEY_I;
    case Gam150::Input::Keys::J:
        return KEY_J;
    case Gam150::Input::Keys::K:
        return KEY_K;
    case Gam150::Input::Keys::L:
        return KEY_L;
    case Gam150::Input::Keys::M:
        return KEY_M;
    case Gam150::Input::Keys::N:
        return KEY_N;
    case Gam150::Input::Keys::O:
        return KEY_O;
    case Gam150::Input::Keys::P:
        return KEY_P;
    case Gam150::Input::Keys::Q:
        return KEY_Q;
    case Gam150::Input::Keys::R:
        return KEY_R;
    case Gam150::Input::Keys::S:
        return KEY_S;
    case Gam150::Input::Keys::T:
        return KEY_T;
    case Gam150::Input::Keys::U:
        return KEY_U;
    case Gam150::Input::Keys::V:
        return KEY_V;
    case Gam150::Input::Keys::W:
        return KEY_W;
    case Gam150::Input::Keys::X:
        return KEY_X;
    case Gam150::Input::Keys::Y:
        return KEY_Y;
    case Gam150::Input::Keys::Z:
        return KEY_Z;
    case Gam150::Input::Keys::Space:
        return KEY_SPACE;
    case Gam150::Input::Keys::Enter:
        return KEY_ENTER;
    case Gam150::Input::Keys::Left:
        return KEY_LEFT;
    case Gam150::Input::Keys::Up:
        return KEY_UP;
    case Gam150::Input::Keys::Right:
        return KEY_RIGHT;
    case Gam150::Input::Keys::Down:
        return KEY_DOWN;
    case Gam150::Input::Keys::One:
        return KEY_ONE;
    case Gam150::Input::Keys::Two:
        return KEY_TWO;
    case Gam150::Input::Keys::Three:
        return KEY_THREE;
    case Gam150::Input::Keys::Four:
        return KEY_FOUR;
    case Gam150::Input::Keys::Five:
        return KEY_FIVE;
    case Gam150::Input::Keys::Six:
        return KEY_SIX;
    case Gam150::Input::Keys::Seven:
        return KEY_SEVEN;
    case Gam150::Input::Keys::Eight:
        return KEY_EIGHT;
    case Gam150::Input::Keys::Nine:
        return KEY_NINE;
    case Gam150::Input::Keys::Zero:
        return KEY_ZERO;
    case Gam150::Input::Keys::Escape:
        return KEY_ESCAPE;
    case Gam150::Input::Keys::Left_Shift:
        return KEY_LEFT_SHIFT;
        //is this right to add this thing here?
    default:
        return -1;
    }
}

constexpr Gam150::Input::Keys& operator++(Gam150::Input::Keys& key) noexcept {
    //int??
    //adding int?
    key = static_cast<Gam150::Input::Keys>(static_cast<unsigned>(key) + 1);
    return key;
    //needs bridge?
    //why error occured? (maybe casting pointer?) or & in declar part?
}


void Gam150::Input::SetKeyDown(Keys key, bool value) {
    keys_down[static_cast<int>(key)] = value;
}

void Gam150::Input::Update() {
    previous_keys_down = keys_down;
    //which place to put, ++i or i++
    for (Keys key = Keys::A; key < Keys::Count; ++key) {
        const auto rl_key = Gam150_to_rl(static_cast<Keys>(key));
        SetKeyDown(key, IsKeyDown(rl_key));
        if (KeyJustPressed(key)) {
            Engine::GetLogger().LogDebug("Key Pressed");
        }
        else if (KeyJustReleased(key)) {
            Engine::GetLogger().LogDebug("Key Released");
        }
    }
}

bool Gam150::Input::KeyDown(Keys key) {
    return keys_down[static_cast<int>(key)];
}

bool Gam150::Input::KeyJustPressed(Keys key) {
    return keys_down[static_cast<int>(key)] == true && previous_keys_down[static_cast<int>(key)] == false;
}

bool Gam150::Input::KeyJustReleased(Keys key) {
    return keys_down[static_cast<int>(key)] == false && previous_keys_down[static_cast<int>(key)] == true;
}

