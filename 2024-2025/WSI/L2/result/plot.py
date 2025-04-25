import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

# Lista plików do przetworzenia
files = {
    "3x3": "result3x3",
    "4x4": "result4x4"
}

# Stałe
column_names = ["size", "heuristic", "steps", "visited", "time"]
sns.set(style="whitegrid")

for size, file_path in files.items():
    # Wczytaj dane
    df = pd.read_csv(file_path, sep=r"\s+", names=column_names, engine="python")

    # WYKRES 1: Odwiedzone vs Kroki
    plt.figure(figsize=(8, 6))
    sns.scatterplot(data=df, x="steps", y="visited", hue="heuristic", palette="Set1")
    plt.title(f"Plansza {size} - Odwiedzone vs Kroki")
    plt.xlabel("Liczba kroków")
    plt.ylabel("Liczba odwiedzonych")
    plt.legend(title="Heurystyka")
    plt.tight_layout()
    plt.savefig(f"visited_vs_steps_{size}.png")
    plt.clf()

    # WYKRES 2: Czas vs Kroki
    plt.figure(figsize=(8, 6))
    sns.scatterplot(data=df, x="steps", y="time", hue="heuristic", palette="Set1")
    plt.title(f"Plansza {size} - Czas vs Kroki")
    plt.xlabel("Liczba kroków")
    plt.ylabel("Czas [s]")
    plt.legend(title="Heurystyka")
    plt.tight_layout()
    plt.savefig(f"time_vs_steps_{size}.png")
    plt.clf()

