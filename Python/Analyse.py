import numpy as np
from matplotlib import pyplot as plt

nbr_coups = 875000
e_min = 0.0  # 0.0
e_max = 2.93  # 2.916
nbr_c = 503  # 1204
range_canaux = e_max - e_min
pas = (range_canaux * 1000) / nbr_c  # en keV
pas_calc = range_canaux / nbr_c  # en MeV

data = []
with open('G4_Co60_10M_fusion.txt') as f:
    i = 0
    for line in f:
        if i < 2:
            i += 1
            pass
        elif 2 <= i <= nbr_coups + 1:
            data.append(float(line))
            i += 1

for x in range(0, int(nbr_coups)):
    e = data[x] * 1000
    sigma = ((273.28 * (e ** -0.651)) / 100) * data[x]
    a = np.random.normal(data[x], sigma)
    data[x] = abs(a)

canaux = []
for x in range(0, nbr_c):
    canaux.append(0)

for x in range(0, len(data)):
    a = int(data[x] // pas_calc)
    try:
        canaux[a] += 1
    except:
        pass


energies = []
for x in range(len(canaux)):
    energies.append(x * ((e_max * 1000) / nbr_c))

derrien = []
with open("data_NaI.txt") as g:
    for line in g:
        derrien.append(float(line))

difference = []
for x in range(len(canaux)):
    if derrien[x] == 0:
        a = (canaux[x] - derrien[x]) * 100
    else:
        a = ((canaux[x] - derrien[x]) / derrien[x]) * 100
    difference.append(a)

font = {'family': 'serif',
        'color':  'darkred',
        'weight': 'normal',
        'size': 16,
        }

font1 = {'family': 'serif',
        'color':  'darkred',
        'weight': 'normal',
        'size': 8,
        }

bornesup = 100
borneinf = -100

plt.figure(figsize=(12, 5), dpi=150)
plt.plot(energies, derrien, linewidth=0.8, label="Détecteur", color='k')
plt.plot(energies, canaux, linewidth=0.8, label="Geant4", color='r')
plt.title('Comparaison Geant4 - détecteur réel', fontdict=font)
plt.xlabel('Energie (keV)', fontdict=font)
plt.ylabel('Nombre de coups', fontdict=font)
plt.yscale('linear')
plt.legend()
plt.savefig("NaI-G4-lin.png", dpi=150)
plt.show()

plt.figure(figsize=(12, 5), dpi=150)
plt.plot(energies, derrien, linewidth=0.8, label="Détecteur", color='k')
plt.plot(energies, canaux, linewidth=0.8, label="Geant4", color='r')
plt.title('Comparaison Geant4 - détecteur réel', fontdict=font)
plt.xlabel('Energie (keV)', fontdict=font)
plt.ylabel('Log du nombre de coups', fontdict=font)
plt.yscale('log')
plt.legend()
plt.savefig("NaI-G4-log.png", dpi=150)
plt.show()

plt.figure(figsize=(12, 5), dpi=150)
plt.plot(energies, difference, 'kx', markersize=1.5, label="Geant4")
plt.plot([0, 2930], [0, 0], linewidth=2, label="Détecteur", color='r')
plt.axvline(1173, borneinf, bornesup, linewidth=1, label='1.17 MeV Cobalt', color='k')
plt.axvline(1332, borneinf, bornesup, linewidth=1, label='1.33 MeV Cobalt', color='g')
plt.title('Projection des écarts sur le spectre réel', fontdict=font)
plt.xlabel('Energie (keV)', fontdict=font)
plt.ylabel('Ecart en %', fontdict=font)
plt.ylim((borneinf, bornesup))
plt.yscale('symlog')
plt.legend()
plt.savefig("NaI-G4-compsym.png", dpi=300)
plt.show()

plt.figure(figsize=(12, 5), dpi=150)
plt.plot(energies, difference, 'kx', markersize=1.5, label="Geant4")
plt.plot([0, 2930], [0, 0], linewidth=2, label="Détecteur", color='r')
plt.axvline(1173, borneinf, bornesup, linewidth=1, label='1.17 MeV Cobalt', color='k')
plt.axvline(1332, borneinf, bornesup, linewidth=1, label='1.33 MeV Cobalt', color='g')
plt.title('Projection des écarts sur le spectre réel', fontdict=font)
plt.xlabel('Energie (keV)', fontdict=font)
plt.ylabel('Ecart en %', fontdict=font)
plt.ylim((borneinf, bornesup))
plt.yscale('linear')
plt.legend()
plt.savefig("NaI-G4-complin.png", dpi=300)
plt.show()
