#include "Wall_Floor.h"

Wall_Floor::Wall_Floor(Math::vec3 start_position) : Gam150::GameObject(start_position)
{
    collision_type = Block;
    AddGOComponentSide(new Gam150::Sprite("Assets/Side_wall_Floor.spt", "Assets/Top_Wall_Floor.spt", this));
}
Wall_Floor2::Wall_Floor2(Math::vec3 start_position) : Gam150::GameObject(start_position)
{
    collision_type = Block;
    AddGOComponentSide(new Gam150::Sprite("Assets/Side_wall_Floor.spt", "Assets/Top_Wall_Floor2.spt", this));
}
