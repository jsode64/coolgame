#pragma once

#include "../fighter.hpp"

class Stabby : public Fighter {
public:
private:
  static constexpr float ACCELERATION = 1.0;
  static constexpr float DECCELERATION = ACCELERATION * 0.85;
  static constexpr float MAX_SPEED = 8.0;
  static constexpr bool controllerFlag = true;

public:
  Stabby(int32_t leftKey, int32_t rightKey, int32_t jumpKey, int32_t attackKey, Gamepad controller);

  std::unique_ptr<Attack> ground_attack() override;

  std::unique_ptr<Attack> air_attack() override;

  void controllerFlagReturn();

  void draw() const override;

  /**
   * Handles the fighter using an attack.
   */
  void handle_attacks(std::list<std::unique_ptr<Attack>> &attacks);

  
  void default_update(Game &game);

};
