#include "Skill.h"
#include <iostream>

Skill::Skill(std::string skillName, float creditPerHour)
    : name(skillName), creditPerHour(creditPerHour) {}

void Skill::getSkillName() {
    std::cout << "Name: " << name << std::endl;
}

float Skill::getCreditPerHour() {
    return creditPerHour;
}

bool Skill::createSkill(std::string skillName, float creditPerHour) {
    if (creditPerHour > 0) {
        this->name = skillName;
        this->creditPerHour = creditPerHour;
        return true;
    }
    return false;
}


