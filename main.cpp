#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
using namespace std;

float wczytajSrednia(string przedmiot)
{
    float srednia;
    cout << "Podaj srednia z " << przedmiot << ": ";
    cin >> srednia;
    cout << endl;
    return srednia;
}
bool znajdzPoczatekWymienianiaPrzedmiotow(fstream &plik, short klasa)
{
    string wierszPoczatkowy;
    switch(klasa)
    {
    case 0:
        wierszPoczatkowy = "WSZYSTKIE KLASY";
        break;
    case 1:
        wierszPoczatkowy = "KLASA 1";
        break;
    case 2:
        wierszPoczatkowy = "KLASA 2";
        break;
    case 3:
        wierszPoczatkowy = "KLASA 3";
        break;
    default:
        cout << "ERROR (Nie wiem o takiej klasie)" << endl;
        break;
    }
    while(true)
    {
        if(!plik.good())
            return false;
        string linia;
        getline(plik, linia);
        if(linia == wierszPoczatkowy)
            return true;
    }
}
void pobierzDane(short klasa, bool wczytanoPrzedmiotyDlaWszystkich, float &sumaSrednich, short &iloscPrzedmiotow)
{
    fstream plik;
    plik.open("Przedmioty.txt");
    if(!plik.good())
    {
        cout << "Nie znalazlem pliku Przedmioty.txt" << endl;
        exit(0);
    }
    if(!wczytanoPrzedmiotyDlaWszystkich && znajdzPoczatekWymienianiaPrzedmiotow(plik, 0))
    {
        string przedmiot;
        while(true)
        {
            getline(plik, przedmiot);
            if(przedmiot == "KONIEC")
                break;
            sumaSrednich += wczytajSrednia(przedmiot);
            iloscPrzedmiotow++;
        }
    }
    if(znajdzPoczatekWymienianiaPrzedmiotow(plik, klasa))
    {
        string przedmiot;
        while(true)
        {
            getline(plik, przedmiot);
            if(przedmiot == "KONIEC")
                break;
            sumaSrednich += wczytajSrednia(przedmiot);
            iloscPrzedmiotow++;
        }
    }
    plik.close();
}
int main()
{
    short klasa = 0;
    float sumaSrednich = 0;
    short iloscPrzedmiotow = 0;
    cout << "==== KALKULATOR SREDNIEJ ====" << endl;
    cout << "W ktorej jestes klasie?" << endl;
    cin >> klasa;
    while(cin.fail() || klasa < 1 || klasa > 3)
    {
        cin.clear();
        cin.ignore();
        cout << "Wprowadziles bledne dane. Sprobuj ponownie" << endl;
        cin >> klasa;
    }
    if(klasa == 1 || klasa == 2)
    {
        pobierzDane(klasa, false, sumaSrednich, iloscPrzedmiotow);
        cout << "Twoja srednia wynosi: " << setprecision(3) << sumaSrednich / iloscPrzedmiotow << endl;
    }
    else
    {
        pobierzDane(1, false, sumaSrednich, iloscPrzedmiotow);
        pobierzDane(2, true, sumaSrednich, iloscPrzedmiotow);
        pobierzDane(3, true, sumaSrednich, iloscPrzedmiotow);
        cout << "Twoja srednia wynosi: " << setprecision(3) << sumaSrednich / iloscPrzedmiotow << endl;
    }
    return 0;
}
