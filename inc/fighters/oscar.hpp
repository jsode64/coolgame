#pragma once

#include "../fighter.hpp"

class Oscar : public Fighter {
private:
  static constexpr float ACCELERATION = 0.5;
  static constexpr float DECCELERATION = ACCELERATION / 2.0;
  static constexpr float MAX_SPEED = 5.0;

public:
  Oscar(int32_t leftKey, int32_t rightKey, int32_t jumpKey, int32_t attackKey, int32_t leftKeyController, int32_t rightKeyController, 
        int32_t jumpKeyController, int32_t attackKeyController);

  std::unique_ptr<Attack> ground_attack() override;

  std::unique_ptr<Attack> air_attack() override;

  void update(Game &game) override;

  void draw() const override;
};
