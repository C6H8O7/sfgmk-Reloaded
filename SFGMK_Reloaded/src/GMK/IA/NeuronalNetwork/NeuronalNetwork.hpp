#ifndef NEURONAL_NETWORK_HPP
#define NEURONAL_NETWORK_HPP

#include "stdafx.h"

using namespace std;


struct T_CONNEXION
{
	double Poids;
	double Delta_Poids;
};


class C_NEURONE;

typedef vector<C_NEURONE> T_COUCHE;

//==============================================================================
class C_NEURONE
{
	public:
		C_NEURONE(unsigned P_Nombre_Sorties, unsigned P_Numero);
		void Set_Sortie(double P_Valeur) { Sortie = P_Valeur; }
		double Get_Sortie(void) const { return Sortie; }
		void Run(const T_COUCHE &P_Couche);
		void Calcul_Gradient(double P_Valeur);
		void Ajuste_Gradient(const T_COUCHE &P_Couche);
		void Mise_A_Jour_Poids(T_COUCHE &P_Couche);

	protected:
		static double eta;   // [0.0..1.0] 
		static double alpha; // [0.0..n] 
		static double Fonction_Transfert(double P_X);
		static double Fonction_Transfert_Derivee(double P_X);
		static double Poids_Aleatoires(void) { return rand() / double(RAND_MAX); }
		double Sommer_Gradients(const T_COUCHE &P_Couche) const;
		double Sortie;
		vector<T_CONNEXION> Les_Connexions;
		unsigned Numero_Neurone;
		double Gradient;
};


class C_RESEAU
{
	public:
		C_RESEAU(const vector<unsigned>& P_Topologie);
		void Run(const vector<double>& P_Valeurs);
		void Retropropagation(const vector<double>& P_Valeurs);
		void Get_Sorties(vector<double>& P_Liste) const;
		double Get_Erreur_Moyenne(void) const { return Erreur_Moyenne; }

	private:
		vector<T_COUCHE> Les_Couches;
		double Erreur_Actuelle;
		double Erreur_Moyenne;
		static double Facteur_Moyenne;
};


#endif