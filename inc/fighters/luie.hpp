#pragma once

#include "../fighter.hpp"

class Luie : public Fighter {
public:
private:
  static constexpr float ACCELERATION = 1.0;
  static constexpr float DECCELERATION = ACCELERATION * 0.85;
  static constexpr float MAX_SPEED = 8.0;
  static constexpr bool controllerFlag = true;

public:
  Luie(int32_t leftKey, int32_t rightKey, int32_t jumpKey, int32_t attackKey, int32_t leftKeyController, int32_t rightKeyController, 
          int32_t jumpKeyController, int32_t attackKeyController);

  std::unique_ptr<Attack> ground_attack() override;

  std::unique_ptr<Attack> air_attack() override;

  void controllerFlagReturn();

  void draw() const override;
};
