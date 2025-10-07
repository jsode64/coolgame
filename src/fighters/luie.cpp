#include "fighters/luie.hpp"

Luie::Luie(int32_t leftKey, int32_t rightKey, int32_t jumpKey, int32_t attackKey)
    : Fighter(Rectangle({ 0.0f, 0.0f, 10.0f, 30.0f }), 15.0f, ACCELERATION, DECCELERATION, MAX_SPEED, leftKey, rightKey, jumpKey, attackKey) {
    respawn();
}

void Luie::update(const Stage& stage, std::vector<Attack>& attacks) {
    handle_movement();
    handle_oob();
    handle_collision(stage);
    handle_attacks(attacks);
}

void Luie::draw() const {
    DrawRectangleRec(body, GREEN);
}

Attack Luie::ground_attack() {
    return Attack(this, body, Vector2(0.0f, -5.0f),
        [this](Attack& atk, std::vector<std::unique_ptr<Fighter>>& fighters) {
            atk.set_hitbox(body);
            return atk.get_ticks() > 60;
        },
        [](const Attack& atk){

        }
    );
}

Attack Luie::air_attack() {
    return Attack(this, body, Vector2(0.0f, -5.0f),
        [this](Attack& atk, std::vector<std::unique_ptr<Fighter>>& fighters) {
            return true;
        },
        [](const Attack& atk){

        }
    );
}
