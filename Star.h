#pragma once
class star {
public:
    int id;
    float x;
    float y;
    float z;
    int octant;

    //Functions
    star() {
        id = -1;
        x = 0;
        y = 0;
        z = 0;
        octant = getOctant();
    }
    star(int ID, float X, float Y, float Z) {
        id = ID;
        x = X;
        y = Y;
        z = Z;
        octant = getOctant();
    }
    int getOctant();
};
