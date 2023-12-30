#ifndef SKILL_H
#define SKILL_H

#include <iostream>
#include <string>
using std::string;

class Skill
{
private:
    std::string name;
    float creditPerHour;
    

public:
    Skill(std::string skillName = "", float creditPerHour = 0);
    string getSkillName() const;
    float getCreditPerHour() const;
    void setSkillName(string skillName);
    bool createSkill(std::string skillName, float creditPerHour);
   
};

#endif // SKILL_H
