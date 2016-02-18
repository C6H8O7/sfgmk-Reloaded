////////////////////////////////////////////////////////////////////////////////////
//
//	Reseau neuronnal
//	http://inkdrop.net/dave/docs/neural-net-tutorial.cpp
//
////////////////////////////////////////////////////////////////////////////////////

#ifndef _NEURONNETWORK_HPP_
#define _NEURONNETWORK_HPP_

#include <vector>

#define NEURON_ETA 0.15					// [0.0..1.0]	Frequence d'entrainement generale
#define NEURON_ALPHA 0.5				// [0.0..n]		Multiplicateur du dernier changement de poids (momentum)

#define NEURON_SMOOTH_FACTOR 100.0		// Nombre d'echantillons sur lequel est calcule la moyenne

class Neuron;

struct NeuronConnexion
{
	double weight;
	double delta_weight;
};

typedef std::vector<Neuron>				NeuronLayer;
typedef std::vector<NeuronLayer>		NeuronLayers;
typedef std::vector<NeuronConnexion>	NeuronConnexions;

typedef std::vector<unsigned int>		NetworkStructure;
typedef std::vector<double>				NeuronNetworkValues;

class Neuron
{
	////////////////////////////////////////////////////////////////////////////////////
	// Classe Neuron

public:

	////////////////////////////////////////////////////////////////////////////////////
	// Constructeur

	Neuron(unsigned int _n, unsigned int _i) : n(_n), index(_i) {
		init();
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Destructeur

	~Neuron() {
		deinit();
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Initialisation neuronne

	inline void init() {
		connexions.resize(n);
		for (unsigned int i = 0; i < n; i++)
			connexions[i].weight = rand() / double(RAND_MAX);
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Deinitialisation neuronne

	inline void deinit() {
		connexions.clear();
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Force une sortie

	inline void setOutput(double _output) {
		output = _output;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Retourne la sortie

	inline double getOutput() {
		return output;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Calcule le gradient

	inline void computeGradient(double _v) {
		gradient = (_v - output) * function_d(output);
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Ajuste le gradient

	inline void correctGradient(const NeuronLayer& _layer) {
		gradient = sumGradients(_layer) * function_d(output);
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Fait la somme des gradients

	inline double sumGradients(const NeuronLayer& _nextLayer) {
		double sum = 0.0;

		// On fait la somme de nos contributions sur les erreurs que l'on envoie 

		for (unsigned int i = 0; i < _nextLayer.size() - 1; i++) {
			sum += connexions[i].weight * _nextLayer[i].gradient;
		}

		return sum;
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Mise a jour des poids en entree

	inline void compute(NeuronLayer& _previousLayer) {
		for (unsigned int i = 0; i < _previousLayer.size(); i++) {
			Neuron& neuron = _previousLayer[i];
			double oldW = neuron.connexions[index].delta_weight;

			double newW =
				// Notre sortie multiplie par le training rate et le gradient
				NEURON_ETA * neuron.output * gradient
				// On y ajoute le momentum : une fraction du precedent delta weight
				+ NEURON_ALPHA * oldW;

			neuron.connexions[index].delta_weight = newW;
			neuron.connexions[index].weight += newW;
		}
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Processus de calcul avec valeur attendue

	inline void process(const NeuronLayer& _layer) {
		double sum = 0.0;
		for (unsigned int i = 0; i < _layer.size(); i++)
			sum += _layer[i].output * _layer[i].connexions[index].weight;
		output = function(sum);
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Fonction de transfert

	inline double function(double _v) {
		return tanh(_v);
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Derivee de la fonction de transfert

	inline double function_d(double _v) {
		return 1.0 - _v * _v;
	}

protected:

	double output;

	double gradient;

	NeuronConnexions connexions;

	unsigned int n;
	unsigned int index;
};

class NeuronNetwork
{
	////////////////////////////////////////////////////////////////////////////////////
	// Classe NeuronNetwork

public:

	////////////////////////////////////////////////////////////////////////////////////
	// Constructeur

	NeuronNetwork() {

	}

	////////////////////////////////////////////////////////////////////////////////////
	// Init

	inline void init(const NetworkStructure& _structure) {
		unsigned int nbLayers = _structure.size();
		for (unsigned int i = 0; i < nbLayers; i++) {
			layers.push_back(NeuronLayer());
			unsigned int nbOutputs = i == (nbLayers - 1) ? 0 : _structure[i + 1];

			// On ajoute une nouvelle couche qu'on remplit
			// En ajoutant une neuronne "dummy"
			for (unsigned int j = 0; j <= _structure[i]; j++) {
				layers.back().push_back(Neuron(nbOutputs, j));
			}

			// On set la sortie des neuronnes "dummy" a 1
			layers.back().back().setOutput(1.0);
		}
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Stocke les resultats dans un vecteur

	inline void getOutputs(NeuronNetworkValues& _outputs) {
		_outputs.clear();
		for (unsigned int i = 0; i < layers.back().size() - 1; i++) {
			_outputs.push_back(layers.back()[i].getOutput());
		}
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Applique la retropropagation

	inline void retropropagate(const NeuronNetworkValues& _values) {
		NeuronLayer& outputLayer = layers.back();
		currentError = 0.0;

		for (unsigned int i = 0; i < outputLayer.size() - 1; i++) {
			double delta = _values[i] - outputLayer[i].getOutput();
			currentError += delta * delta;
		}

		currentError /= outputLayer.size() - 1;
		currentError = sqrt(currentError);
		averageError = (averageError * NEURON_SMOOTH_FACTOR + currentError) / (NEURON_SMOOTH_FACTOR + 1.0);

		for (unsigned int i = 0; i < outputLayer.size() - 1; i++) {
			outputLayer[i].computeGradient(_values[i]);
		}

		for (unsigned int i = layers.size() - 2; i > 0; i--) {
			NeuronLayer& hiddenLayer = layers[i];
			NeuronLayer& nextLayer = layers[i + 1];
			for (unsigned int j = 0; j < hiddenLayer.size(); j++) {
				hiddenLayer[i].correctGradient(nextLayer);
			}
		}

		for (unsigned int i = layers.size() - 1; i > 0; i--) {
			NeuronLayer& layer = layers[i];
			NeuronLayer& previousLayer = layers[i - 1];
			for (unsigned int j = 0; j < layer.size() - 1; j++) {
				layer[j].compute(previousLayer);
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Passe les valeurs a calculer dans le reseau

	inline void process(const NeuronNetworkValues& _values) {
		for (unsigned int i = 0; i < _values.size(); i++) {
			layers[0][i].setOutput(_values[i]);
		}

		for (unsigned int i = 1; i < layers.size(); i++) {
			NeuronLayer& previous = layers[i - 1];
			for (unsigned int j = 0; j < layers[i].size() - 1; j++) {
				layers[i][j].process(previous);
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////
	// Retourne l'erreur moyenne

	inline double getAverageError() {
		return averageError;
	}

private:

	NeuronLayers layers;

	double currentError;
	double averageError;
};

#endif