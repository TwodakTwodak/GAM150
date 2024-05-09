/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObject.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
#include "Engine.h"
#include "Cube.h"
#include "Sprite.h"

namespace Gam150 { class Collision; }

//made with bool beacuse we have only two view!
enum View : bool {
    Side = true,
    Top = false
};


namespace CS230 {
    class GameObject {
    public:
        GameObject();
        GameObject(Math::vec3 position);
        GameObject(Math::vec3 position, double rotation, Math::vec3 scale);
        ~GameObject();

        virtual void Update(double dt);
        //Different in each view
        virtual void Draw(Math::TransformationMatrix camera_matrix);
        //For change view
        virtual void check_view();
        //For Collision
        void Collision(GameObject* compare);

        const Math::TransformationMatrix& GetMatrix();
        const Math::vec3& GetPosition() const;
        const Math::vec3& GetVelocity() const;
        const Math::vec3& GetScale() const;
        //double GetRotation() const;
        View GetView() const;
        void SetView(View view);
        Math::cube collision_cube;
        Gam150::Collision* collision;

    protected:
        class State {
        public:
            virtual void Enter(GameObject* object) = 0;
            virtual void Update(GameObject* object, double dt) = 0;
            virtual void CheckExit(GameObject* object) = 0;
            virtual std::string GetName() = 0;
        };
        State* current_state = nullptr;

        void change_state(State* new_state);

        void SetPosition(Math::vec3 new_position);
        void UpdatePosition(Math::vec3 delta);
        void SetVelocity(Math::vec3 new_velocity);
        void UpdateVelocity(Math::vec3 delta);
        //Different in each view but okay to use together
        void SetScale(Math::vec3 new_scale);
        void UpdateScale(Math::vec3 delta);
        //void SetRotation(double new_rotation);
        //void UpdateRotation(double delta);

        //should have each sprite
        Sprite side_sprite;
        Sprite top_sprite;
        Sprite* view_sprite = &side_sprite;

    private:

        //none 
        class State_None : public State {
        public:
            void Enter(GameObject*) override {}
            void Update(GameObject*, double) override {}
            void CheckExit(GameObject*) override {}
            std::string GetName() { return ""; }
        };
        State_None state_none;

        Math::TransformationMatrix object_matrix;

        bool matrix_outdated = false;

        double rotation;
        Math::vec3 scale;
        Math::vec3 position;
        Math::vec3 velocity;

        //this change by current view
        double* view_position = &(position.y);
        double* view_scale = &(scale.y);

        View current_view = View::Side;
    };
}