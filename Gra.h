#pragma once
#include<vector>
#include<stack>
#include<random>
#include "Talia.h"
#include "Karta.h"
#include "Gracz.h"
#include "Walidator.h"
#include "Button.h"
class Gra {
	Talia talia;
	std::vector<Gracz> gracze; 
	std::stack<Karta> stos_rzuconych;		//stos kart rzuconych przez graczy
	std::queue<Karta> talia_do_ciagniecia;	//kolejka kart do ciągnięcia - można dokładać karty od dołu
	Walidator Walidator; 
	int index_gracza;						//indeks gracza definiujący, którego gracza kolej
	sf::RenderWindow window;				//okno z SFML
	Button button_wierzchnia_karta;			//przycisk przechowujący teksturę wierzchniej karty
	sf::Font arial;							//czcionka tekstu na przyciskach
	std::string label_text;					//string przechowujący tekst żądania
public:
	Gra(std::vector<std::string> _gracze) { //setup gry
		for (std::string& el : _gracze) {	//nazwanie graczy
			gracze.push_back(Gracz(el));
		}
		button_wierzchnia_karta.setButton({ 100,200 }, sf::Color::White);
		button_wierzchnia_karta.setPosition({ 300,100 });	//ustawienia przycisku wierzchniej karty
		arial.loadFromFile("arial.ttf");
		Restart();	//metoda przygotowująca grę
	}

	void Rozgrywka() {
		window.create(sf::VideoMode(1000, 1000), "Makao", sf::Style::Titlebar | sf::Style::Close); //utworzenie okna gry
		window.setKeyRepeatEnabled(true);
		while (window.isOpen()) {
			Karta wybor_gracza;
			Karta wierzchnia_karta;
			
			auto& obecny_gracz = gracze[index_gracza];	//przypisanie obecnego gracza wzgledem indeksu
			wierzchnia_karta = stos_rzuconych.top();	//przypisanie wierzchniej karty
			button_wierzchnia_karta.LoadCardTexture(wierzchnia_karta);	//załadowanie tekstury wierzchniej karty
			if (Walidator.get_akcja()) {	//sprawdzenie czy rzucona została karta akcyjna
				if (wierzchnia_karta.get_wartosc() == "2" || wierzchnia_karta.get_wartosc() == "3") {
					Dotasuj_talie(std::stoi(wierzchnia_karta.get_wartosc()));
					for (int i = 0; i < std::stoi(wierzchnia_karta.get_wartosc()); i++) {
						obecny_gracz.ciagnij(talia_do_ciagniecia);	//pociągnięcie przez gracza odpowiedniej liczby kart
					}
					InkrementujIndexGracza();
					Walidator.set_akcja(0);
					continue;
				}

				else if (wierzchnia_karta.get_wartosc() == "4") { //kolejka gracza jest pominięta
					InkrementujIndexGracza();
					Walidator.set_akcja(0);
					continue;
				}
				if(Walidator.get_czy_J()) {
					label_text = "Uwaga wymagana karta: " + Walidator.get_J_zadanie();
				}
				else {
					label_text = "Uwaga kolor: " + Walidator.get_A_kolor();
				}			

			}	
			int zagranie_czy_pass = 0;
			obecny_gracz.set_czy_akcja(Walidator.get_akcja());		
			while (zagranie_czy_pass == 0) {
				wybor_gracza = obecny_gracz.Wybor_karty(window, button_wierzchnia_karta, label_text);
				zagranie_czy_pass = Walidator.Waliduj(stos_rzuconych.top(), wybor_gracza);
			}
				
				
			if (wybor_gracza.get_kolor() != "bez_atu") {
				Walidator.set_akcja(0);
				obecny_gracz.Usun_rzucona();
				//std::cout << "Udalo sie " << std::endl;
				if (wybor_gracza.get_wartosc() == "2" || wybor_gracza.get_wartosc() == "3" || wybor_gracza.get_wartosc() == "4" ||
					wybor_gracza.get_wartosc() == "AS" || wybor_gracza.get_wartosc() == "J") {
					Walidator.set_akcja(1);
					std::string warunek;

					if (wybor_gracza.get_wartosc() == "AS") {
						window.clear();
						bool wybrany_kolor = 0;
						std::vector<Button> kolory;
						Button btrefl("trefl", { 100,100 }, 40, sf::Color::Black, sf::Color::White);
						Button bkaro("karo", { 100,100 }, 40, sf::Color::Black, sf::Color::White);
						Button bkier("kier", { 100,100 }, 40, sf::Color::Black, sf::Color::White);
						Button bpik("pik", { 100,100 }, 40, sf::Color::Black, sf::Color::White);
						Button label("Wybierz kolor", { 300, 100 }, 60, sf::Color::Black, sf::Color::Red);
						label.setPosition({ 100, 50 });
						label.setFont(arial);
						label.drawTo(window);
						kolory.push_back(btrefl);
						kolory.push_back(bkaro);
						kolory.push_back(bkier);
						kolory.push_back(bpik);

						for (float i = 0; i < 4; i++) {
							kolory[i].setPosition({ 200, (200 + i * 150) });
							kolory[i].setFont(arial);
							kolory[i].drawTo(window);
						}
								
						window.display();

						sf::Event Event;
						while (!wybrany_kolor) {
							while (window.pollEvent(Event))
							{
								switch (Event.type) {
								case sf::Event::Closed:
									window.close();
									break;
											

								case sf::Event::MouseButtonPressed:
									for (auto& el : kolory) {
										if (el.isMouseOver1(window)) {
											Walidator.set_A_kolor(el.get_text());
											wybrany_kolor = 1;										
											break;
										}
									}
								}
							}
						}
						Walidator.set_czy_J(0);
					}
					if (wybor_gracza.get_wartosc() == "J") {
						window.clear();
						bool wybrane_zadanie = 0;
						std::vector<Button> demands;
						Button zadanie5("5", { 50, 50 }, 40, sf::Color::Black, sf::Color::White);
						Button zadanie6("6", { 50, 50 }, 40, sf::Color::Black, sf::Color::White);
						Button zadanie7("7", { 50, 50 }, 40, sf::Color::Black, sf::Color::White);
						Button zadanie8("8", { 50, 50 }, 40, sf::Color::Black, sf::Color::White);
						Button zadanie9("9", { 50, 50 }, 40, sf::Color::Black, sf::Color::White);
						Button zadanie10("10", { 50, 50 }, 40, sf::Color::Black, sf::Color::White);
						Button zadanieQ("Q", { 50, 50 }, 40, sf::Color::Black, sf::Color::White);
						Button zadanieK("K", { 50, 50 }, 40, sf::Color::Black, sf::Color::White);
						Button label("Wybierz wymagana karte", { 300, 100 }, 60, sf::Color::Black, sf::Color::Red);
						label.setPosition({ 100, 50 });
						label.setFont(arial);
						label.drawTo(window);
						demands.push_back(zadanie5);
						demands.push_back(zadanie6);
						demands.push_back(zadanie7);
						demands.push_back(zadanie8);
						demands.push_back(zadanie9);
						demands.push_back(zadanie10);
						demands.push_back(zadanieQ);
						demands.push_back(zadanieK);

						for (float i = 0; i < 4; i++) {
							demands[i].setPosition({ 100+i*70, 200 });
							demands[i].setFont(arial);
							demands[i].drawTo(window);
						}


						for (float i = 4; i < 8; i++) {
							demands[i].setPosition({ 100 + (i-4) * 70, 300 });
							demands[i].setFont(arial);
							demands[i].drawTo(window);
						}

						window.display();

						sf::Event Event;
						while (!wybrane_zadanie) {
							while (window.pollEvent(Event)) {				
								switch (Event.type) {
								case sf::Event::Closed:
									window.close();
									break;


								case sf::Event::MouseButtonPressed:
									//std::cout << "Wcisnieto przycisk \n";
									for (auto& el : demands) {
										if (el.isMouseOver1(window)) {
											Walidator.set_J_zadanie(el.get_text());
											wybrane_zadanie = 1;
											break;
										}
									}
								}
							}
						}
						Walidator.set_czy_J(1);
					}
				}
				InkrementujIndexGracza();
				stos_rzuconych.push(wybor_gracza);
				WinCondition(obecny_gracz);
			}
			else {
				Dotasuj_talie(1);
				obecny_gracz.ciagnij(talia_do_ciagniecia);
				InkrementujIndexGracza();
			}
			
		}

	}
	void Dotasuj_talie(int liczba) {
		int rozmiar = talia_do_ciagniecia.size();
		if (rozmiar < liczba) {
			Karta pom = stos_rzuconych.top();
			stos_rzuconych.pop();
			std::vector<Karta> tasowane;
			while (!stos_rzuconych.empty()) {
				tasowane.push_back(stos_rzuconych.top());
				stos_rzuconych.pop();
			}
			stos_rzuconych.push(pom);
			std::random_device rd;  
			std::default_random_engine rng(rd());
			std::shuffle(std::begin(tasowane), std::end(tasowane), rng);
			for (int i = 0; i < tasowane.size(); i++) {
				talia_do_ciagniecia.push(tasowane[i]);
			}
		}
	}
	
	void Restart() {
		talia.Tasuj_talie();
		talia_do_ciagniecia = talia.get_potasowane();
		for (auto& el : gracze) {	//rozdanie kart graczom
			el.zerujReke();
			for (int i = 0; i < 5; i++) {
				el.ciagnij(talia_do_ciagniecia);
			}
		}

		if (!talia_do_ciagniecia.empty()) {
			stos_rzuconych.push(talia_do_ciagniecia.front()); //wystawienie wierzchniej karty
			talia_do_ciagniecia.pop();
		}
		index_gracza = 0;
		Walidator.set_akcja(0);
	}

	void InkrementujIndexGracza() {
		if (index_gracza != gracze.size() - 1)
			index_gracza++;
		else
			index_gracza = 0;
	}

	void WinCondition(Gracz obecny_gracz) {
		if (obecny_gracz.get_liczba_kart() == 0) {
			window.clear();
			std::string zwycieski_string = "WYGRAL GRACZ " + obecny_gracz.get_nazwa_gracza() + "\nGRATULACJE\n";
			Button winner_btn(zwycieski_string, { 500, 150 }, 50, sf::Color::Black, sf::Color::White);
			Button czy_grasz_dalej("Czy chcesz zagrac jeszcze raz?", { 600,100 }, 40, sf::Color::Black, sf::Color::White);
			Button tak("TAK", { 100, 100 }, 40, sf::Color::Black, sf::Color::White);
			Button nie("NIE", { 100,100 }, 40, sf::Color::Black, sf::Color::White);
			winner_btn.setFont(arial);
			winner_btn.setPosition({ 50, 50 });
			winner_btn.drawTo(window);
			czy_grasz_dalej.setFont(arial);
			czy_grasz_dalej.setPosition({ 50, 250 });
			czy_grasz_dalej.drawTo(window);
			tak.setFont(arial);
			tak.setPosition({ 225, 400 });
			tak.drawTo(window);
			nie.setFont(arial);
			nie.setPosition({ 375, 400 });
			nie.drawTo(window);
			window.display();
			sf::Event Event;
			bool gra_dalej = 0;
			while (!gra_dalej) {
				while (window.pollEvent(Event))
				{
					switch (Event.type) {
					case sf::Event::Closed:
						window.close();
						break;
					case sf::Event::MouseButtonPressed:
						//std::cout << "Wcisnieto przycisk \n";
						if (nie.isMouseOver1(window)) {
							window.close();
							break;
						}
						if (tak.isMouseOver1(window)) {
							Restart();
						}
					}
				}
			}
		}
	}
};