//
// Created by henry on 2021-12-09.
//

#ifndef FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_HEALTH_H_
#define FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_HEALTH_H_

namespace SpaceInvader::CustomCS {

class Health {
    int health;
    int total;
  public:
    explicit Health(int health, int total) : health(health), total(total) {};
    [[nodiscard]] int getHealth() const { return health; }
    [[nodiscard]] int getTotal() const { return total; }
    void setHealth(int newHealth) { this->health = std::clamp(newHealth, 0, total); }
};

}

#endif //FINAL_PROJECT_EXAMPLES_SPACEINVADER_COMPONENTS_HEALTH_H_
