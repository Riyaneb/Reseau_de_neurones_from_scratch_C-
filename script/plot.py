import pandas as pd
import matplotlib.pyplot as plt
import os

path_csv = '../data/training_snake_log.csv'

if(not os.path.exists(path_csv)):
    print(f"Fichier {path_csv} introuvable")
    exit(1)

df = pd.read_csv(path_csv)

fig, (ax1,ax2,ax3) = plt.subplots(3, 1, figsize=(10, 12))

fig.suptitle("Évolution de l'entrainement de l'agent snake en diminuant le taux d'apprentissage",fontsize=16,fontweight='bold')

ax1.plot(df['episode'], df['score'], label='Score de l\'epoch', color='blue')
ax1.plot(df['episode'], df['mean_score'], label='Moyenne_roulante du score (100 epochs)', color='red')
ax1.set_xlabel('Epoch')
ax1.set_ylabel('Score')
ax1.set_title('Évolution du score réalisé par l\'agent')
ax1.legend()
ax1.grid(True)

ax2.plot(df['episode'], df['epsilon'], label='Epsilon', color='green')
ax2.set_xlabel('Epoch')
ax2.set_ylabel('Epsilon')
ax2.set_title('Évolution de l\'exploration (epsilon)')
ax2.legend()
ax2.grid(True)

ax3.plot(df['episode'], df['loss'], label='Loss', color='orange')
ax3.set_xlabel('Epoch')
ax3.set_ylabel('Loss')
ax3.set_title('Évolution de la perte (loss)')
ax3.legend()
ax3.grid(True)

plt.tight_layout()

plt.savefig('../data/plot/training_snake_log_learning_rate.png')
print("Graphique sauvegardé dans le dossier plot")

