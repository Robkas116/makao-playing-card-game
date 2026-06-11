#pragma once
#include "Karta.h"

class Walidator {
	bool akcja;		//okresla czy zagrana byla wczesniej karta akcji
	bool czy_J;		//okresla czy rzucony zostal walet, przeciwnie rzucony byl as
	std::string A_kolor; //kolor zadany asem
	std::string J_zadanie; //zadanie ustanowione waletem
public:
	Walidator() : akcja(0) {};

	bool get_akcja() {
		return akcja;
	}
	void set_akcja(bool b) {
		akcja = b;
	}
	bool get_czy_J() {
		return czy_J;
	}
	void set_czy_J(bool b) {
		czy_J = b;
	}
	std::string get_A_kolor() {
		return A_kolor;
	}
	void set_A_kolor(std::string s) {
		A_kolor = s;
	}
	std::string get_J_zadanie() {
		return J_zadanie;
	}
	void set_J_zadanie(std::string s) {
		J_zadanie = s;
	}
	bool Waliduj(Karta k1, Karta k2) { //k1 karta wierzchnia, k2 karta rzucona
		if (!akcja) {
			if (k2.get_wartosc() == "AS") {
				return 1;
			}
			if (k2.get_kolor() == "bez_atu") {
				return 1;
			}
			return k1 == k2;
		}
		else {
			if (k1.get_wartosc() == "J") {
				if (k2.get_wartosc() == J_zadanie) {
					return 1;
				}
				else if (k2.get_kolor() == "bez_atu") {
					return 1;
				}
				else
					return 0;
			
			}
			if (k2.get_wartosc() == "AS") {
				return 1;
			}
			if (k1.get_wartosc() == "AS") {
				return k2.get_kolor() == A_kolor;
			}
			if (k2.get_wartosc() == "AS") {
				return 1;
			}
		}
	}
};