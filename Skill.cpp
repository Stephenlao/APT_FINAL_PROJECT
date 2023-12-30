#include "Skill.h"
#include <iostream>
#include <string>
using std::string;

Skill::Skill(std::string skillName, float creditPerHour)
    : name(skillName), creditPerHour(creditPerHour) {}



string Skill::getSkillName() const {
    return name;
}

float Skill::getCreditPerHour() const {
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

void Skill::setSkillName(string skillName) {
    this->name = skillName;
}

