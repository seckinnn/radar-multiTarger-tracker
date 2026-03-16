import matplotlib.pyplot as plt
import time
import os

LOG_FILE = "sample_output.txt"

plt.ion()  
fig, ax = plt.subplots(figsize=(8,6))

HEDEF_SAYISI = 3  # kaç hedef 
hedefler = {i: {"x": [], "y": []} for i in range(HEDEF_SAYISI)}
olcumler = {i: {"x": [], "y": []} for i in range(HEDEF_SAYISI)}

while True:
    if not os.path.exists(LOG_FILE):
        time.sleep(0.5)
        continue

    with open(LOG_FILE, "r") as f:
        lines = f.readlines()

    tracks = {}
    hedef_index = 0
    for line in lines:
        line = line.strip()
        # Trackler
        if line.startswith("Track ") and "->" in line and "silindi" not in line:
            parts = line.split("->")
            track_id_str = parts[0].split()[1]
            try:
                track_id = int(track_id_str)
            except ValueError:
                continue
            pos_part = parts[1].split("|")[0].strip()
            x, y = pos_part.strip("()").split(",")
            x = float(x)
            y = float(y)
            if track_id not in tracks:
                tracks[track_id] = {"x": [], "y": []}
            tracks[track_id]["x"].append(x)
            tracks[track_id]["y"].append(y)

        # Hedef konumlarını oku
        elif line.startswith("Konum ->"):
            pos_str = line.split("->")[1].strip()
            x, y = pos_str.strip("()").split(",")
            x = float(x)
            y = float(y)
            if hedef_index < HEDEF_SAYISI:
                hedefler[hedef_index]["x"].append(x)
                hedefler[hedef_index]["y"].append(y)
                hedef_index += 1

    # Grafik temizle
    ax.clear()

    # Trackleri çiz
    for tid, data in tracks.items():
        ax.plot(data["x"], data["y"], marker='o', label=f"Track {tid}")

    # Hedefleri çiz 
    for hid, data in hedefler.items():
        ax.plot(data["x"], data["y"], marker='x', linestyle='--', label=f"Hedef {hid}")

    ax.set_xlabel("X")
    ax.set_ylabel("Y")
    ax.set_title("Radar Trackleri ve Hedefler - Canlı")
    ax.grid(True)
    ax.legend()
    plt.pause(0.5)  