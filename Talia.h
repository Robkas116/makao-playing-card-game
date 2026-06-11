#pragma once
#include "Karta.h"
#include<vector>
#include<stack>
#include<random>
#include<queue>
class Talia {
	std::vector<Karta> stos_kart;
	std::vector<std::string> wielkosci = { "AS", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	void Insert_color(std::string kolor) {
		for (const auto el : wielkosci) {
			Karta K(kolor, el);
			stos_kart.push_back(K);
		}
	}
	std::queue<Karta> potasowane;
public:
	Talia() {	
		Insert_color("trefl");
		Insert_color("karo");
		Insert_color("kier");
		Insert_color("pik");
	}
		
	std::queue<Karta> get_potasowane() {
		return potasowane;
	}
	
	void Rozloz() {
		for (const auto el : stos_kart) {
			std::cout << el << std::endl;
		}
	}
	void Tasuj_talie() {
		wyczysc_stos();
		std::random_device rd;  // sprzętowe losowe źródło
		std::default_random_engine rng(rd());  // inicjalizacja seedem
		std::shuffle(std::begin(stos_kart), std::end(stos_kart), rng);
		for (int i = 0; i < stos_kart.size(); i++) {
			potasowane.push(stos_kart[i]);
		}
	}
	void wyczysc_stos() {
		while (!potasowane.empty()) {
			potasowane.pop();
		}
	}
	

};