#include "attack.hpp"

#include "raylib.h"

Attack::Attack(Color color1, Color color2, int32_t attackKey) : color1(color1), color2(color2), attackKey(attackKey) {

}

void Attack::update(const Player& p) {
    checkAttackKey(p);
}

void Attack::moveWithPlayer(const Player& p) {
     Rectangle playerBody = p.get_body();
     hurtbox.x = playerBody.x;
     hurtbox.y = playerBody.y;
     hurtbox.height = playerBody.height;
     hurtbox.width = playerBody.width;

     hitbox.x = playerBody.x + 40;
     hitbox.y = playerBody.y;
     hitbox.height = H;
     hitbox.width = W;
}

void Attack::checkAttackKey(const Player& p) {
    if (IsKeyDown(attackKey)) {
        moveWithPlayer(p);
        collideWithHurtbox(hurtbox);
        draw();
    }
}

void Attack::draw() {
    DrawRectangleRec(hitbox, color1);
    DrawRectangleRec(hurtbox, color2);
}

void Attack::collideWithHurtbox(const Rectangle& hurtbox) {
    
}

