#ifndef MYGAME_MISSION_H
#define MYGAME_MISSION_H

int getCurrentMission(int x)//X is a current coordinate
{
    int mission = 0;
    if(x >= 0 && x < 600)
        mission = 0;
    if(x > 400)
    {
        mission = 1;
    }
    if(x > 700)
    {
        mission = 2;
    }
    if(x > 2200)
    {
        mission = 3;
    }

    return mission;
}

std::string getTextMission(int currentMission)
{
    std::string missionText = "";
    switch(currentMission)
    {
        case 0:
            missionText = "Welcome!\n";
            break;
        case 1:
            missionText = "The first level mission\n";
            break;
        case 2:
            missionText = "Second level mission\n";
            break;
        case 3:
            missionText = "Third level mission\n";
            break;
    }
    return missionText;
}

#endif //MYGAME_MISSION_H
