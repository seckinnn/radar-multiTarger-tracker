#pragma once
#include <cmath>
#include <iostream>

class Track
{
public:
    int id;
    double x;
    double y;
    double vx = 0;
    double vy = 0;
    int kayip_kare = 0;

    
    double P[2][2]; 
    double R[2][2]; 

    Track(int id_, double baslangic_x, double baslangic_y)
    {
        id = id_;
        x = baslangic_x;
        y = baslangic_y;

        P[0][0] = P[1][1] = 1;
        P[0][1] = P[1][0] = 0;

        R[0][0] = R[1][1] = 0.25;
        R[0][1] = R[1][0] = 0;
    }

    void predict()
    {
        x += vx;
        y += vy;
    }

    void guncelle(double olcum_x, double olcum_y)
    {
        double S[2][2];
        S[0][0] = P[0][0] + R[0][0];
        S[0][1] = P[0][1] + R[0][1];
        S[1][0] = P[1][0] + R[1][0];
        S[1][1] = P[1][1] + R[1][1];

        double K[2][2];
        K[0][0] = P[0][0]/S[0][0];
        K[0][1] = P[0][1]/S[1][1];
        K[1][0] = P[1][0]/S[0][0];
        K[1][1] = P[1][1]/S[1][1];

        double dx = olcum_x - x;
        double dy = olcum_y - y;

        x += K[0][0]*dx + K[0][1]*dy;
        y += K[1][0]*dx + K[1][1]*dy;

        vx = K[0][0]*dx;
        vy = K[1][1]*dy;

        P[0][0] = (1 - K[0][0])*P[0][0];
        P[0][1] = (1 - K[0][1])*P[0][1];
        P[1][0] = (1 - K[1][0])*P[1][0];
        P[1][1] = (1 - K[1][1])*P[1][1];

        kayip_kare = 0;
    }
};