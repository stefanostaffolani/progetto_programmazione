/* implementazione di alcune classi che ereditano cose: citta-capoluogo-capitale*/

#include <iostream>
using namespace std;


class Citta {
protected:
	char nome[30];
	int numAbitanti;
public:
	Citta(char name[], int abitanti = 0) {
		strcpy_s(nome, name);
		numAbitanti = abitanti;
	}
	void descrizione() { // stampa informazioni sulla città
		cout << "\n" << nome << ":";
		cout << "\nil numero di abitanti e': " << numAbitanti << endl;
	}
	void cambiaAbitanti(int num) {
		numAbitanti = num;
	}
};


class Capoluogo : public Citta {
protected:
	char regione[30];
public:
	Capoluogo(char name[], char region[], int abitanti = 0) : Citta(name, abitanti) {
		strcpy_s(regione, region);
	}
	void descrizione() {
		Citta::descrizione();
		cout << "capoluogo della regione: " << regione << endl;
	}
};

class Capitale : public Capoluogo {
protected:
	char nazione[30];
public:
	Capitale(char nation[], char name[], char region[], int abitanti = 0) : Capoluogo(name, region, abitanti) {
		strcpy_s(nazione, nation);
	}
	void descrizione() {
		Capoluogo::descrizione();
		cout << "Capitale della nazione: " << nazione << endl;
	}
};


int main() {
	char città[30] = "Bologna";
	char regione[30] = "Emilia-Romagna";
	char capitale[30] = "Italia";
	Capitale bolo = Capitale(capitale, città, regione, 1000);
	bolo.descrizione();
	return 0;
}