#pragma once
#include<iostream>
#include<vector>
#include "Gracz.h"
class Komputer : Gracz {
	static int liczba_komputerow;
public:
	Komputer() {
		liczba_komputerow++;
	}
	static void ile_komputerow() {
		std::cout << liczba_komputerow;
	}
};