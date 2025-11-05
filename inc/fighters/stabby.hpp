#pragma once

#include "../fighter.hpp"

class Stabby : public Fighter {
public:
private:
  static constexpr float ACCELERATION = 1.0;
  static constexpr float DECCELERATION = ACCELERATION * 0.85;
  static constexpr float MAX_SPEED = 8.0;

public:
  Stabby(int32_t leftKey, int32_t rightKey, int32_t jumpKey, int32_t attackKey);

  std::unique_ptr<Attack> ground_attack() override;

  std::unique_ptr<Attack> air_attack() override;

  void draw() const override;
};
