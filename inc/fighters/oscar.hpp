#pragma once

#include "../fighter.hpp"

class Oscar : public Fighter {
    public:

    private:

        static constexpr float ACCELERATION = 0.5;
        static constexpr float DECCELERATION = ACCELERATION / 2.0;
        static constexpr float MAX_SPEED = 5.0;

    public:

        Oscar(int32_t leftKey, int32_t rightKey, int32_t jumpKey);

        void update(const Stage& stage) override;

        void draw() const override;
};
