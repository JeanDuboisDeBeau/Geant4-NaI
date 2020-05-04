#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <random>
using namespace std;

int main()
{
    std::vector<double> energie1;
    std::vector<double> energie2;
    std::vector<double> energieTot;
    std::vector<double> energieNormal;

    ifstream monFlux("D:/ISIB/MA1/Geant4/NEW/G4_Co60_10M.txt");  //Ouverture d'un fichier en lecture

    if (monFlux)
    {
        string line;
        bool HHH = false;
        bool BREAK = false;
        bool END = false;
        while (getline(monFlux, line))
        {
            if (line == "HHH"){
                HHH = !HHH;
            }
            else if (line == "BREAK"){
                BREAK = true;
            }
            else if (line == "END") {
                END = !END;
                BREAK = false;
            }
            else if (HHH && !BREAK && !END) {
                energie1.push_back(stod(line));
            }
            else if (HHH && !BREAK && END) {
                energie2.push_back(stod(line));
            }
            else {
            }
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
    monFlux.close();

    int taille1 = energie1.size();
    int taille2 = energie2.size();

    for (int i(0); i < taille1; ++i) {
        energieTot.push_back(energie1[i] + energie2[i]);
    }

    energieTot.erase(std::remove(begin(energieTot), end(energieTot), 0), end(energieTot));

    double nbrCoups = energieTot.size();
    double efficiency = nbrCoups / (double)taille1;

    ofstream myFile;
    myFile.open("D:/ISIB/MA1/Geant4/NEW/G4_Co60_10M_fusion.txt");
    myFile << "Nombre de coups max : " << (int)nbrCoups << endl;
    myFile << "Efficience : " << efficiency << endl;
    for (int i(0); i < nbrCoups; ++i) {
        myFile << energieTot[i] << endl;
    }
    myFile.close();
}