#pragma once
#include<string>
#include <ostream>
#include<SFML/Graphics.hpp>

class Karta {
	std::string kolor;		//kolor karty
	std::string wartosc;	//wartosc karty
	sf::Texture tekstura;	//tekstura karty
public:
	Karta() : kolor("bez_atu"), wartosc("2") {}						  
	Karta(std::string k, std::string w) : kolor(k), wartosc(w) {
		std::string nazwa_karty = kolor + wartosc + ".png";			//utworzenie stringu ze ścieżką do nazwy pliku z teksturą karty
		tekstura.loadFromFile( "Photos/Karty/" + nazwa_karty);		//załadowanie tekstury
	}
	friend std::ostream& operator<<(std::ostream& out, Karta karta) {
		out << karta.kolor+" " << karta.wartosc;
		return out;
	}
	std::string get_kolor() {
		return kolor;
	}
	std::string get_wartosc() {
		return wartosc;
	}
	void set_wartosci(std::string w, std::string k) {
		kolor = k;
		wartosc = w;
		if (kolor != "bez_atu") {
			std::string nazwa_karty = kolor + wartosc + ".png";
			tekstura.loadFromFile("Photos/Karty/" + nazwa_karty);
		}
	}
	sf::Texture getTexture() {
		return tekstura;
	}
};

bool operator==( Karta& k1, Karta& k2) {
	return k1.get_kolor() == k2.get_kolor() || k1.get_wartosc() == k2.get_wartosc();
}


