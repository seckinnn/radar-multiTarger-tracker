#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <iomanip>
#include <fstream>   
#include "Hedef.hpp"
#include "Track.hpp"

using namespace std;
double mesafe(double x1,double y1,double x2,double y2)
{
    double dx = x1 - x2;
    double dy = y1 - y2;
    return sqrt(dx*dx + dy*dy);
}

int main()
{
    default_random_engine rastgeleUretici;
    normal_distribution<double> gurultu(0.0, 0.5);

    vector<Hedef> hedefler =
    {
        {0,0,1,0.5},
        {10,5,-0.3,0.8},
        {5,15,0.2,-0.4}
    };

    vector<Track> trackler;
    int sonraki_track_id = 0;

    const double ESIG_MESAFE = 5.0;
    const int MAX_KAYIP_KARE = 3;

    ofstream logdosya("sample_output.txt");
    if(!logdosya.is_open())
    {
        cerr << "Dosya açılamadı!" << endl;
        return 1;
    }

    for(int zaman=0; zaman<20; zaman++)
    {
        cout << fixed << setprecision(4);
        logdosya << fixed << setprecision(4);

        cout << "Zaman: " << zaman << endl;
        logdosya << "Zaman: " << zaman << endl;

        vector<pair<double,double>> olcumler;
        for(auto &hedef : hedefler)
        {
            hedef.hareketEt();
            double olcum_x = hedef.x + gurultu(rastgeleUretici);
            double olcum_y = hedef.y + gurultu(rastgeleUretici);
            olcumler.push_back({olcum_x, olcum_y});

            cout << "Konum -> (" << hedef.x << "," << hedef.y << ")" << endl;
            logdosya << "Konum -> (" << hedef.x << "," << hedef.y << ")" << endl;
        }

        for(auto &t : trackler)
            t.predict();

        vector<bool> olcum_kullanildi(olcumler.size(), false);
        for(auto &t : trackler) t.kayip_kare++;

        for(size_t i=0;i<olcumler.size();i++)
        {
            double x = olcumler[i].first;
            double y = olcumler[i].second;

            double en_kucuk_mesafe = 999999;
            int en_yakin_track = -1;

            for(size_t j=0;j<trackler.size();j++)
            {
                double d = mesafe(x,y,trackler[j].x,trackler[j].y);
                if(d < en_kucuk_mesafe)
                {
                    en_kucuk_mesafe = d;
                    en_yakin_track = j;
                }
            }

            if(en_kucuk_mesafe < ESIG_MESAFE && en_yakin_track != -1)
            {
                trackler[en_yakin_track].guncelle(x,y);
                olcum_kullanildi[i] = true;
            }
        }
        for(size_t i=0;i<olcumler.size();i++)
        {
            if(!olcum_kullanildi[i])
            {
                Track yeni_track(sonraki_track_id, olcumler[i].first, olcumler[i].second);
                trackler.push_back(yeni_track);
                sonraki_track_id++;
            }
        }

        for(auto it = trackler.begin(); it != trackler.end(); )
        {
            if(it->kayip_kare > MAX_KAYIP_KARE)
            {
                cout << "Track silindi -> Track " << it->id << endl;
                logdosya << "Track silindi -> Track " << it->id << endl;
                it = trackler.erase(it);
            }
            else
                ++it;
        }

        cout << "Track Durumu:" << endl;
        logdosya << "Track Durumu:" << endl;
        for(const auto &t : trackler)
        {
            cout << "Track " << t.id << " -> (" << t.x << "," << t.y << ")"
                 << " | Hiz: (" << t.vx << "," << t.vy << ")" << endl;
            logdosya << "Track " << t.id << " -> (" << t.x << "," << t.y << ")"
                     << " | Hiz: (" << t.vx << "," << t.vy << ")" << endl;
        }
        cout << "-------------------------" << endl;
        logdosya << "-------------------------" << endl;
    }

    logdosya.close();
    cout << "Log dosyasi olusturuldu: sample_output.txt" << endl;

    return 0;
}