#include "stdafx.h"

using namespace std;


//==============================================================================
double C_NEURONE::eta = 0.15;    //  [0.0..1.0]
double C_NEURONE::alpha = 0.5;   //  [0.0..1.0]
//==============================================================================

void C_NEURONE::Mise_A_Jour_Poids(T_COUCHE &P_Couche)
{
    for (unsigned L_Index = 0; L_Index < P_Couche.size(); ++L_Index) {
        C_NEURONE &L_Neurone = P_Couche[L_Index];
        double L_Ancien_Poids = L_Neurone.Les_Connexions[Numero_Neurone].Delta_Poids;
        double L_Nouveau_Poids =eta* L_Neurone.Get_Sortie()* Gradient+ alpha* L_Ancien_Poids;
        L_Neurone.Les_Connexions[Numero_Neurone].Delta_Poids = L_Nouveau_Poids;
        L_Neurone.Les_Connexions[Numero_Neurone].Poids += L_Nouveau_Poids;
    }
}
//------------------------------------------------------------------------------
double C_NEURONE::Sommer_Gradients(const T_COUCHE &P_Couche) const
{
    double L_Somme = 0.0;
    for (unsigned n = 0; n < P_Couche.size() - 1; ++n) {
        L_Somme += Les_Connexions[n].Poids * P_Couche[n].Gradient;
    }

    return L_Somme;
}
//------------------------------------------------------------------------------
void C_NEURONE::Ajuste_Gradient(const T_COUCHE &P_Couche)
{
    double L_Somme_Gradients = Sommer_Gradients(P_Couche);
    Gradient = L_Somme_Gradients * C_NEURONE::Fonction_Transfert_Derivee(Sortie);
}
//------------------------------------------------------------------------------
void C_NEURONE::Calcul_Gradient(double P_Valeur)
{
    double delta = P_Valeur - Sortie;
    Gradient = delta * C_NEURONE::Fonction_Transfert_Derivee(Sortie);
}
//------------------------------------------------------------------------------
double C_NEURONE::Fonction_Transfert(double P_X)
{
    return tanh(P_X);
}
//------------------------------------------------------------------------------
double C_NEURONE::Fonction_Transfert_Derivee(double P_X)
{
    return 1.0 - P_X* P_X;
}
//------------------------------------------------------------------------------
void C_NEURONE::Run(const T_COUCHE &P_Couche)
{
    double L_Somme = 0.0;
    for (unsigned L_Index = 0; L_Index < P_Couche.size(); ++L_Index) {
        L_Somme += P_Couche[L_Index].Get_Sortie() * P_Couche[L_Index].Les_Connexions[Numero_Neurone].Poids;
    }
    Sortie = C_NEURONE::Fonction_Transfert(L_Somme);
}
//------------------------------------------------------------------------------
C_NEURONE::C_NEURONE(unsigned P_Nombre_Sorties, unsigned P_Index)
{
    for (unsigned L_Index = 0; L_Index < P_Nombre_Sorties; ++L_Index) {
        Les_Connexions.push_back(T_CONNEXION());
        Les_Connexions.back().Poids = Poids_Aleatoires();
    }
    Numero_Neurone = P_Index;
}
//------------------------------------------------------------------------------

//==============================================================================


//==============================================================================
double C_RESEAU::Facteur_Moyenne = 100.0; 
//==============================================================================

void C_RESEAU::Get_Sorties(vector<double> &P_Sorties) const
{
    P_Sorties.clear();
    for (unsigned L_Index = 0; L_Index < Les_Couches.back().size() - 1; ++L_Index) {
        P_Sorties.push_back(Les_Couches.back()[L_Index].Get_Sortie());
    }
}
//------------------------------------------------------------------------------
void C_RESEAU::Retropropagation(const vector<double> &P_Valeurs)
{
    T_COUCHE &L_Couche_Sortie = Les_Couches.back();
    Erreur_Actuelle = 0.0;

    for (unsigned L_Index = 0; L_Index < L_Couche_Sortie.size() - 1; ++L_Index) {
        double L_Delta = P_Valeurs[L_Index] - L_Couche_Sortie[L_Index].Get_Sortie();
        Erreur_Actuelle += L_Delta * L_Delta;
    }
    Erreur_Actuelle /= L_Couche_Sortie.size() - 1; // get average error squared
    Erreur_Actuelle = sqrt(Erreur_Actuelle); // RMS
    Erreur_Moyenne =(Erreur_Moyenne * Facteur_Moyenne + Erreur_Actuelle)/ (Facteur_Moyenne + 1.0);
   for (unsigned L_Index = 0; L_Index < L_Couche_Sortie.size() - 1; ++L_Index) {
        L_Couche_Sortie[L_Index].Calcul_Gradient(P_Valeurs[L_Index]);
    }
    for (unsigned L_Numero_Couche = Les_Couches.size() - 2; L_Numero_Couche > 0; --L_Numero_Couche) {
        T_COUCHE &L_Couche_Cachee = Les_Couches[L_Numero_Couche];
        T_COUCHE &L_Suivante = Les_Couches[L_Numero_Couche + 1];
        for (unsigned L_Index = 0; L_Index < L_Couche_Cachee.size(); ++L_Index) {
            L_Couche_Cachee[L_Index].Ajuste_Gradient(L_Suivante);
        }
    }
    for (unsigned L_Numero_Couche = Les_Couches.size() - 1; L_Numero_Couche > 0; --L_Numero_Couche) {
        T_COUCHE &L_Couche = Les_Couches[L_Numero_Couche];
        T_COUCHE &L_Precedente = Les_Couches[L_Numero_Couche - 1];
        for (unsigned L_Index = 0; L_Index < L_Couche.size() - 1; ++L_Index) {
            L_Couche[L_Index].Mise_A_Jour_Poids(L_Precedente);
        }
    }
}
//------------------------------------------------------------------------------
void C_RESEAU::Run(const vector<double> &P_Valeurs)
{
    assert(P_Valeurs.size() == Les_Couches[0].size() - 1);
    for (unsigned L_Index = 0; L_Index < P_Valeurs.size(); ++L_Index) {
        Les_Couches[0][L_Index].Set_Sortie(P_Valeurs[L_Index]);
    }
    for (unsigned L_Numero_Couche = 1; L_Numero_Couche < Les_Couches.size(); ++L_Numero_Couche) {
        T_COUCHE &L_Precedente = Les_Couches[L_Numero_Couche - 1];
        for (unsigned L_Index = 0; L_Index < Les_Couches[L_Numero_Couche].size() - 1; ++L_Index) {
            Les_Couches[L_Numero_Couche][L_Index].Run(L_Precedente);
        }
    }
}
//------------------------------------------------------------------------------
C_RESEAU::C_RESEAU(const vector<unsigned> &P_Topologie)
{
    unsigned L_Nombre_Couches = P_Topologie.size();
    for (unsigned L_Numero_Couche = 0; L_Numero_Couche < L_Nombre_Couches; ++L_Numero_Couche) {
        Les_Couches.push_back(T_COUCHE());
        unsigned L_Nombre_Sorties = L_Numero_Couche == P_Topologie.size() - 1 ? 0 : P_Topologie[L_Numero_Couche + 1];
        for (unsigned L_Index = 0; L_Index <= P_Topologie[L_Numero_Couche]; ++L_Index) {
            Les_Couches.back().push_back(C_NEURONE(L_Nombre_Sorties, L_Index));
            cout << "Made a Neuron!" << endl;
        }
        Les_Couches.back().back().Set_Sortie(1.0);
    }
}
//------------------------------------------------------------------------------

void Affiche_Vecteur(string label, vector<double> &v)
{
    cout << label << " ";
    for (unsigned i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }

    cout << endl;
}
//------------------------------------------------------------------------------