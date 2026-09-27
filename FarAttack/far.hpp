#include "../Interface/interface.hpp"

class Far: public Ability {
private:
    int radius;
    int damage;
    int usedEnergy;
public:
    Far(int dam, int rad, int e);

    std::string getName() override;
    int getUsedEnergy() override;
    void use(Player &robot, Map &map, Enemy* target) override;
};