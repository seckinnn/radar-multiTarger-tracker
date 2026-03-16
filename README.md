Multi-Target Radar Tracking Simulator (MTT)
Bu proje, C++ kullanarak birden fazla hedefi (Multi-Target) simüle eden ve Nearest Neighbor (NN) veri ilişkilendirme algoritması ile takip eden bir radar sistemidir. Proje, gürültülü (noisy) ölçümler içerisinden gerçek hedefleri ayıklamak ve izlerini (track) yönetmek üzerine kurgulanmıştır.

🚀 Öne Çıkan Özellikler
Veri İlişkilendirme: Öklid mesafesi tabanlı En Yakın Komşu (Nearest Neighbor) algoritması.

Gating: Belirli bir eşik değerin (ESIG_MESAFE) üzerindeki hatalı ölçümleri reddetme.

Track Yönetimi: Aktif olmayan hedeflerin otomatik silinmesi (Track Deletion) ve yeni hedeflerin tespiti.

Hız Tahmini: Ölçüm farklarından yararlanarak dinamik hız vektörü hesaplama.

📦 Kurulum ve Çalıştırma
Projeyi yerelinizde çalıştırmak için:
git clone https://github.com/seckinnn/radar-MultiTarger-Tracker.git
cd radar-MultiTarger-Tracker/src
g++ main.cpp -o tracker
./tracker

Örnek Çıktı
Zaman: 0
Konum -> (1.0000,0.5000)
Konum -> (9.7000,5.8000)
Konum -> (5.2000,14.6000)
Track Durumu:
Track 0 -> (1.0000,0.5000) | Hiz: (1.0000,0.5000)
Track 1 -> (9.7000,5.8000) | Hiz: (-0.3000,0.8000)
Track 2 -> (5.2000,14.6000) | Hiz: (0.2000,-0.4000)
-------------------------