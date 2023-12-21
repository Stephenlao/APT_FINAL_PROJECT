#ifndef SKILL_H
#define SKILL_H

#include <string>

class Skill
{
private:
    std::string name;
    float creditPerHour;
    

public:
    Skill(std::string skillName = "", float creditPerHour = 0);
    void getSkillName();
    float getCreditPerHour();

    bool createSkill(std::string skillName, float creditPerHour);
   
};

#endif // SKILL_H
