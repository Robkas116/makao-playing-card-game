#pragma once
#include<vector>
#include "Talia.h"
#include<iostream>
#include<queue>
#include<string>
#include "Button.h"
#include "Label.h"
class Gracz {
	std::string nazwa;				//nazwa gracza
	std::vector<Karta> reka;		//wektor przechowujący karty gracza
	int index_rzuconej;				//indeks poruszania się po ręce
	std::vector<Button> przyciski;	//wektor przycisków do wyboru karty
	bool czy_akcja;					//warunek czy obecna karta jest akcyjna
	sf::Font arial;					//czcionka tekstu przycisków
public:
	Gracz(std::string _nazwa) : nazwa(_nazwa) {
		arial.loadFromFile("arial.ttf");									//załadowanie czcionki		
		Button b1("", { 100, 200 }, 0, sf::Color::White, sf::Color::White);	//przycisk bazowy
		for (int i = 0; i < 5; i++) {										//przypisanie parametrów każdego przycisku wyboru karty
			float posX = 50 + i * 150;
			b1.setPosition({ posX, 400.0f });
			przyciski.push_back(b1);
		}

	}

	void ciagnij(std::queue<Karta>& talia) {
		if (!talia.empty()) {
			reka.push_back(talia.front());
			talia.pop();
		}
	}

	Karta Wybor_karty(sf::RenderWindow& window, Button b, std::string label_text) {
		int i_reki = 0;
		int i_wyboru = 0;
		int wybor;
		Karta pom;
		Button label_warunek(label_text, { 400, 50 }, 50, sf::Color::Black, sf::Color::White);
		label_warunek.setPosition({ 150,300 });
		label_warunek.setFont(arial);
		Button przycisk_ciagnij("Ciagnij", { 200,100 }, 50, sf::Color::Black, sf::Color::White);
		przycisk_ciagnij.setPosition({ 450, 700 });
		przycisk_ciagnij.setFont(arial);
		Button przycisk_reroll("Wiecej", { 200,100 }, 50, sf::Color::Black, sf::Color::White);
		przycisk_reroll.setPosition({ 200, 700 });
		przycisk_reroll.setFont(arial);

		while (true) {
			std::string zagrywa_str = "Zagrywa gracz: " + nazwa;
			Button zagrywa_gracz(zagrywa_str, { 300,50 }, 50, sf::Color::Black, sf::Color::Red);
			zagrywa_gracz.setFont(arial);
			zagrywa_gracz.setPosition({ 125,10 });
			bool klikniete = 0;
			window.clear();
			if ((reka.size() - i_reki) > 5) {
				for (i_wyboru = 0; i_wyboru < 5; i_wyboru++) {
					przyciski[i_wyboru].LoadCardTexture(reka[i_reki + i_wyboru]);
					przyciski[i_wyboru].drawTo(window);
					//std::cout << reka[i_reki + i_wyboru].get_wartosc() << " " << reka[i_reki + i_wyboru].get_kolor() << "\t";
				}
				
				przycisk_reroll.drawTo(window);
				przycisk_ciagnij.drawTo(window);
				b.drawTo(window);
				if (czy_akcja) {
					label_warunek.drawTo(window);
				}
				zagrywa_gracz.drawTo(window);
				window.display();
				
				sf::Event Event;
				while (!klikniete) {	
					while (window.pollEvent(Event))
					{
						switch (Event.type) {
						case sf::Event::Closed:
							window.close();
							break;
							
							
						case sf::Event::MouseButtonPressed:		//wychwycono wciśnięcie przycisku
							for (int i = 0; i < 5; i++) {		//pętla przechodząca po wszystkich wyświetlonych przyciskach
								Button przycisk = przyciski[i];
								if (przycisk.isMouseOver1(window)) {	//sprawdza czy w momencie wciśnięcia myszka była na przycisku
									index_rzuconej = i_reki + i;
									pom = reka[index_rzuconej];			//przypisanie wciśniętej karty do karty pomocniczej
									klikniete = 1;						//warunek wyjścia z pętli
									return pom;							//zwrócenie pomocniczej karty
								}
							}
							if (przycisk_ciagnij.isMouseOver1(window)) {	//sprawdzenie czy nie wciśnięto przycisku Ciągnij
								pom.set_wartosci("AS", "bez_atu");
								klikniete = 1;
								return pom;		//zwrócenie bazowej karty
							}

							if (przycisk_reroll.isMouseOver1(window)) {		//sprawdzenie czy nie wciśnięto przycisku Więcej
								i_reki += 5;								//zwiększenie indeksu ręki
								klikniete = 1;
							}


							
						}
					}
				}
			}
			else {
				int j = 0;
				for (i_wyboru = 0; i_reki + i_wyboru < reka.size(); i_wyboru++) {
					przyciski[i_wyboru].LoadCardTexture(reka[i_reki + i_wyboru]);
					przyciski[i_wyboru].drawTo(window);
					//std::cout << reka[i_reki + i_wyboru].get_wartosc() << " " << reka[i_reki + i_wyboru].get_kolor() << "\t";
					j++;
				}
				
				for (j; j < 5; j++) {
					przyciski[j].LoadBlack();
					przyciski[j].drawTo(window);
				}
				przycisk_reroll.drawTo(window);
				przycisk_ciagnij.drawTo(window);
				b.drawTo(window);
				
				if (czy_akcja) {
					label_warunek.drawTo(window);
				}
				zagrywa_gracz.drawTo(window);
				window.display();
				
				sf::Event Event;
				bool klikniete = 0;
				while (!klikniete) {
					while (window.pollEvent(Event))
					{
						switch (Event.type) {
						case sf::Event::Closed:
							window.close();
							break;
						
						case sf::Event::MouseButtonPressed:
							//std::cout << "Wcisnieto przycisk \n";
							for (int i = 0; i < 5; i++) {
								Button przycisk = przyciski[i];
								if (przycisk.isMouseOver1(window)) {
									index_rzuconej = i_reki + i;
									pom = reka[index_rzuconej];
									klikniete = 1;
									
									return pom;
								}
							}
							if (przycisk_ciagnij.isMouseOver1(window)) {
								pom.set_wartosci("AS", "bez_atu");
								klikniete = 1;
								
								return pom;
							}

							if (przycisk_reroll.isMouseOver1(window)) {
								i_reki = 0;
								klikniete = 1;
							}


							
						}
					}
				}
			}
		}
	}
	void Usun_rzucona() {
		reka.erase(reka.begin() + index_rzuconej);
	}
	int get_liczba_kart() {
		return reka.size();
	}
	std::string get_nazwa_gracza() {
		return nazwa;
	}

	friend std::ostream& operator<<(std::ostream& out, Gracz karta) {
		out << karta.nazwa;
		return out;
	}
	
	void zerujReke() {
		reka.clear();
	}
	void set_czy_akcja(bool b) {
		czy_akcja = b;
	}

};