#pragma once

#include "../fighter.hpp"

class Oscar : public Fighter {
private:
  static constexpr float ACCELERATION = 0.5;
  static constexpr float DECCELERATION = ACCELERATION / 2.0;
  static constexpr float MAX_SPEED = 5.0;

public:
  Oscar(int32_t leftKey, int32_t rightKey, int32_t jumpKey, int32_t attackKey, Gamepad controller);

  std::unique_ptr<Attack> ground_attack() override;

  std::unique_ptr<Attack> air_attack() override;

  void update(Game &game) override;

  void draw() const override;


  /**
   * Handles the fighter using an attack.
   */
  void handle_attacks(std::list<std::unique_ptr<Attack>> &attacks);

  
  void default_update(Game &game);
};
