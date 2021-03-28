//Agnieszka_Talik_2020
#include <iostream>
#include <cctype>
#include <stdlib.h>
#include <bitset>
#include <math.h>
#include <fstream>

using namespace std;

struct Cztery8 {
	bitset<8> b1;
	bitset<8> b2;
	bitset<8> b3;
	bitset<8> b4;
};

Cztery8 convers32to8(const bitset<32>& input) {
	auto tmp = input.to_ulong();
	Cztery8 result;
	result.b4 = bitset<8>(tmp & 0xFF);
	tmp >>= 8;
	result.b3 = bitset<8>(tmp & 0xFF);
	tmp >>= 8;
	result.b2 = bitset<8>(tmp & 0xFF);
	tmp >>= 8;
	result.b1 = bitset<8>(tmp & 0xFF);
	return result;
}
unsigned conversion(int* decIp)//Konwersja adresu IP na jedni liczbe dziesietni
{
	uint32_t ip = decIp[0] << 24u | decIp[1] << 16u | decIp[2] << 8u | decIp[3];
	return ip;
}

void check(int* decIp, int msk) //Sprawdzanie poprawno?ci IP i maski
{
	for (int i=0; i<4; i++)
	{
		if (decIp[i] >= 0 && decIp[i] <= 255)
			i++;
		else
		{
			cout << "Nieprawidlowy IP" << endl;
			exit(EXIT_FAILURE);
		}
	}
	if (msk < 0 || msk > 32)
	{
		cout << "Nieprawidlowa maska";
		exit(EXIT_FAILURE);
	}
}

unsigned mask(int msk) //Zmiana maski ze skróconej na pe3ni
{	
	int mk[32];

	for (int i = 0; i < msk; i++)
		mk[i] = 1;

	for (int i = msk; i<=32; i++)
		mk[i] = 0;

	uint32_t m = mk[0] << 32u | mk[1] << 31u | mk[2] << 30u | mk[3] << 29u | mk[4] << 28u | mk[5] << 27u
		| mk[6] << 26u | mk[7] << 25u;

	return m;
}
bitset<32> Adr_sieci(unsigned ip, unsigned mask) // Adres sieciowy, iloczyn binarny AND (wynik binarnie)
{
	unsigned x = ip & mask;
	bitset<32> b = x;
	
	return b;
}
bitset<32> And_p1(unsigned ip, unsigned msk) // Adres sieci + 1 (obliczanie pierwszego hosta)
{
	unsigned x = (ip & msk);
	bitset<32> b = x|1;

	return b;
}

bitset<32> broadcast_min1(bitset<32> broadcast) // Adres sieci - 1 (obliczanie ostatniego hosta)
{
	bitset<32> b = (broadcast)^(bitset <32> (1));

	return b;
}

bitset<32> Not(unsigned msk) // NOT na postaci binarnej maski (do adresu rozg3oszeniowego)
{
	unsigned x = ~msk ;
	bitset<32> b = x;

	return b;
}
int l_host(int msk) // Maksymalna liczba hostów
{
	int max = pow(2, (32-msk))-2;
	return max;
}
string klasa(int* ip)
{
		bitset<1> a = ip[0] >> 7;
	if (a == 0)
		return "A";

		bitset<2> b = ip[0] >> 6;
	if (b.to_ullong() == 2) // bin: 10
		return "B";

		bitset<3> c = ip[0] >> 5;
	if (c.to_ullong() == 6) // bin: 110
		return "C";

		bitset<4U> de = ip[0] >> 4;
	if (de.to_ullong() == 14) // bin: 1110
		return "D";

	if (de.to_ullong() == 15) // bin: 1111
		return "E";
	else
		return "0";
}
	
int main()
{
		int decIp[4];
		int msk;

		ofstream zapis("Kalkulator_podsieci.txt");

		cout << "Podaj adres IP rozdzielajac oktety spacja: ";
		cin >> decIp[0] >> decIp[1] >> decIp[2] >> decIp[3];
		cout << "Podaj skrocony zapis maski: ";
		cin >> msk;
		
		zapis << "Adres IP: " << decIp[0] << "." << decIp[1] << "." << decIp[2] << "." << decIp[3] << endl << "Skrocona maska: " << msk << endl << endl;
		cout << endl;

		check(decIp, msk);
		{
			bitset<32> b(Adr_sieci(conversion(decIp), mask(msk)));
			auto x4 = convers32to8(b);
			zapis << "Adres sieci: " << (x4.b1).to_ullong() << "." << (x4.b2).to_ullong() << "." << (x4.b3).to_ullong() << "." << (x4.b4).to_ullong() << endl
				<< "Adres sieci binarnie: " << (x4.b1) << "." << (x4.b2) << "." << (x4.b3) << "." << (x4.b4) << endl << endl;
			cout << "Adres sieci: " << (x4.b1).to_ullong() << "." << (x4.b2).to_ullong() << "." << (x4.b3).to_ullong() << "." << (x4.b4).to_ullong() << endl;
			cout << "Adres sieci binarnie: " << (x4.b1) << "." << (x4.b2) << "." << (x4.b3) << "." << (x4.b4) << endl << endl;
		}
		{
			bitset<32> b(And_p1(conversion(decIp), mask(msk)));
			auto x4 = convers32to8(b);
			zapis << "Host minimalny: " << (x4.b1).to_ullong() << "." << (x4.b2).to_ullong() << "." << (x4.b3).to_ullong() << "." << (x4.b4).to_ullong() << endl
				<< "Host minimalny binarnie: " << (x4.b1) << "." << (x4.b2) << "." << (x4.b3) << "." << (x4.b4) << endl << endl;
			cout << "Host minimalny: " << (x4.b1).to_ullong() << "." << (x4.b2).to_ullong() << "." << (x4.b3).to_ullong() << "." << (x4.b4).to_ullong() << endl;
			cout << "Host minimalny binarnie: " << (x4.b1) << "." << (x4.b2) << "." << (x4.b3) << "." << (x4.b4) << endl << endl;
		}
		bitset<32> adres_sieci(Adr_sieci(conversion(decIp), mask(msk)));
		bitset<32> broadcast = (Not(mask(msk)) | adres_sieci);
		{
			bitset<32> b(broadcast);
			auto x4 = convers32to8(b);
			zapis << "Broadcast: " << (x4.b1).to_ullong() << "." << (x4.b2).to_ullong() << "." << (x4.b3).to_ullong() << "." << (x4.b4).to_ullong() << endl
				<< "Broadcast binarnie: " << (x4.b1) << "." << (x4.b2) << "." << (x4.b3) << "." << (x4.b4) << endl << endl;
			cout << "Broadcast: " << (x4.b1).to_ullong() << "." << (x4.b2).to_ullong() << "." << (x4.b3).to_ullong() << "." << (x4.b4).to_ullong() << endl;
			cout << "Broadcast binarnie: " << (x4.b1) << "." << (x4.b2) << "." << (x4.b3) << "." << (x4.b4) << endl << endl;
		}
		{	
			bitset<32> b(broadcast_min1(broadcast));
			auto x4 = convers32to8(b);
			zapis << "Host maksymalny: " << (x4.b1).to_ullong() << "." << (x4.b2).to_ullong() << "." << (x4.b3).to_ullong() << "." << (x4.b4).to_ullong() << endl
				<< "Host maksymalny binarnie: " << (x4.b1) << "." << (x4.b2) << "." << (x4.b3) << "." << (x4.b4) << endl << endl;
			cout << "Host maksymalny: " << (x4.b1).to_ullong() << "." << (x4.b2).to_ullong() << "." << (x4.b3).to_ullong() << "." << (x4.b4).to_ullong() << endl;
			cout << "Host maksymalny binarnie: " << (x4.b1) << "." << (x4.b2) << "." << (x4.b3) << "." << (x4.b4) << endl << endl;
		}
		{
			bitset<32> b(mask(msk));
			auto x4 = convers32to8(b);
			zapis << "Maska: " << (x4.b1).to_ullong() << "." << (x4.b2).to_ullong() << "." << (x4.b3).to_ullong() << "." << (x4.b4).to_ullong() << endl
				<< "Maska binarnie: " << (x4.b1) << "." << (x4.b2) << "." << (x4.b3) << "." << (x4.b4) << endl << endl;
			cout << "Maska: " << (x4.b1).to_ullong() << "." << (x4.b2).to_ullong() << "." << (x4.b3).to_ullong() << "." << (x4.b4).to_ullong() << endl;
			cout << "Maska binarnie: " << (x4.b1) << "." << (x4.b2) << "." << (x4.b3) << "." << (x4.b4) << endl << endl;
		}
		zapis << "Maksymalna liczba hostow: " << l_host(msk) << endl << endl;
		cout << "Maksymalna liczba hostow: " << l_host(msk) << endl << endl;

		zapis << "Klasa sieci: " << klasa(decIp) << endl;
		cout << "Klasa sieci: " << klasa(decIp) << endl;

		zapis.close();
		
	return 0;
}