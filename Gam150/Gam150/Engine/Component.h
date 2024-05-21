#pragma once

namespace Gam150 {
    class Component {
    public:
        virtual ~Component() {};
        virtual void Update([[maybe_unused]] double dt) {};
    };
}
