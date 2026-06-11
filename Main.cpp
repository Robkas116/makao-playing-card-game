#include<iostream>
#include "Talia.h"
#include"Karta.h"
#include "Gracz.h"
#include "Gra.h"
int main() {
	std::vector<std::string> v = { "Gracz1", "Gracz2"};
	Gra gra1(v);
	gra1.Rozgrywka();
}



