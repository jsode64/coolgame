#pragma once

#include "../fighter.hpp"

class Luie : public Fighter {
    public:

    private:

        static constexpr float ACCELERATION = 1.0;
        static constexpr float DECCELERATION = ACCELERATION * 0.85;
        static constexpr float MAX_SPEED = 8.0;

    public:

        Luie(int32_t leftKey, int32_t rightKey, int32_t jumpKey, int32_t attackKey);

        Attack ground_attack() override;

        Attack air_attack() override;

        void update(const Stage& stage, std::vector<Attack>& attacks) override;

        void draw() const override;
};
