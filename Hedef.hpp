#pragma once

struct Hedef
{
    double x;
    double y;
    double hiz_x;
    double hiz_y;

    void hareketEt()
    {
        x += hiz_x;
        y += hiz_y;
    }
};