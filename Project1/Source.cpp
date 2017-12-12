#include<iostream>
#include<fstream>
using namespace std;


struct WspolrzednePola {

public:
	WspolrzednePola()
	{
		this->x = -1;
		this->y = -1;
	}
	WspolrzednePola(int x, int y)
	{
		this->x = x;
		this->y = y;
	}
	int x;
	int y;
	int index() {
		return this->y * 20 + this->x;
	}
};

class Pole {
public:
	int rodzaj;
	int koszt = 0;
	WspolrzednePola poleRodzica;
	WspolrzednePola wspolrzedne;
	double heurystyka = 0.0;

	Pole() {

	};
};

int main() {

	WspolrzednePola start = WspolrzednePola(0, 6);
	WspolrzednePola koniec = WspolrzednePola(16, 14);



	static const int kosztRuchu = 1;

	Pole Pola[400] = {};

	ifstream infile;
	infile.open("grid.txt");

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			WspolrzednePola wspolrzedna = WspolrzednePola(j, i);
			int index = wspolrzedna.index();

			infile >> Pola[index].rodzaj;
			Pola[index].wspolrzedne = wspolrzedna;
			Pola[index].heurystyka = sqrt((wspolrzedna.x - koniec.x)*(wspolrzedna.x - koniec.x) + (wspolrzedna.y - koniec.y)*(wspolrzedna.y - koniec.y));
		}
	}

	Pola[start.index()].rodzaj = 1;
	Pola[start.index()].koszt = 0;

	while (true) {
		double min = 50.0;
		WspolrzednePola minWsp;
		for (int i = 400; i >= 0; i--) {
			if (Pola[i].rodzaj == 1) {
				if (min > (Pola[i].heurystyka + Pola[i].koszt)) {
					min = (Pola[i].heurystyka + Pola[i].koszt);
					minWsp = Pola[i].wspolrzedne; // poprawiæ warunek

				}
			}
		}

		if (min == 50.0) {
			cout << "Nie ma drogi z punktu start do punktu koniec" << endl;
			system("PAUSE");
			return 0;
		}

		if (minWsp.x == koniec.x && minWsp.y == koniec.y) {
			cout << "Znaleziono droge do konca" << endl;

			while (!(minWsp.x == start.x && minWsp.y == start.y)) {
				Pola[minWsp.index()].rodzaj = 3;
				minWsp = Pola[minWsp.index()].poleRodzica;
			}

			Pola[minWsp.index()].rodzaj = 3;

			for (int i = 0; i < 20; i++)
			{
				for (int j = 0; j < 20; j++)
				{
					if (Pola[WspolrzednePola(j, i).index()].rodzaj == 3 || Pola[WspolrzednePola(j, i).index()].rodzaj == 5) {
						cout << Pola[WspolrzednePola(j, i).index()].rodzaj << " ";
					}
					else {
						cout << "  ";
					}
				/*	cout << Pola[WspolrzednePola(j, i).index()].rodzaj << " ";*/
				}
				cout << endl;
			}

			system("PAUSE");
			return 0;
		}

		Pola[minWsp.index()].rodzaj = 2;

		if (minWsp.y + 1 <= 19) {
			WspolrzednePola dol = WspolrzednePola(minWsp.x, minWsp.y + 1);
			if (Pola[dol.index()].rodzaj == 0 || (Pola[dol.index()].rodzaj == 1 && Pola[dol.index()].koszt > Pola[minWsp.index()].koszt + kosztRuchu)) {
				Pola[dol.index()].rodzaj = 1;
				Pola[dol.index()].poleRodzica = minWsp;
				Pola[dol.index()].koszt = Pola[minWsp.index()].koszt + kosztRuchu;
			}
		}
		if (minWsp.x - 1 >= 0) {
			WspolrzednePola lewo = WspolrzednePola(minWsp.x - 1, minWsp.y);
			if (Pola[lewo.index()].rodzaj == 0 || (Pola[lewo.index()].rodzaj == 1 && Pola[lewo.index()].koszt > Pola[minWsp.index()].koszt + kosztRuchu)) {
				Pola[lewo.index()].rodzaj = 1;
				Pola[lewo.index()].poleRodzica = minWsp;
				Pola[lewo.index()].koszt = Pola[minWsp.index()].koszt + kosztRuchu;
			}
		}
		if (minWsp.y - 1 >= 0) {
			WspolrzednePola gora = WspolrzednePola(minWsp.x, minWsp.y - 1);
			if (Pola[gora.index()].rodzaj == 0 || (Pola[gora.index()].rodzaj == 1 && Pola[gora.index()].koszt > Pola[minWsp.index()].koszt + kosztRuchu)) {
				Pola[gora.index()].rodzaj = 1;
				Pola[gora.index()].poleRodzica = minWsp;
				Pola[gora.index()].koszt = Pola[minWsp.index()].koszt + kosztRuchu;
			}
		}
		if (minWsp.x + 1 <= 19) {
			WspolrzednePola prawo = WspolrzednePola(minWsp.x + 1, minWsp.y);
			if (Pola[prawo.index()].rodzaj == 0 || (Pola[prawo.index()].rodzaj == 1 && Pola[prawo.index()].koszt > Pola[minWsp.index()].koszt + kosztRuchu)) {
				Pola[prawo.index()].rodzaj = 1;
				Pola[prawo.index()].poleRodzica = minWsp;
				Pola[prawo.index()].koszt = Pola[minWsp.index()].koszt + kosztRuchu;
			}
		}


	}

}




