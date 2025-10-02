#pragma once

#include "../fighter.hpp"

class Luie : public Fighter {
    public:

    private:

        static constexpr float ACCELERATION = 1.0;
        static constexpr float DECCELERATION = ACCELERATION * 0.85;
        static constexpr float MAX_SPEED = 8.0;

    public:

        Luie(int32_t leftKey, int32_t rightKey, int32_t jumpKey);

        void update(const Stage& stage) override;

    void draw() const override;
};
