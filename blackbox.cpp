#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
using namespace std;

struct punkt
{
    int x;
    int y;
};

void wyswietlWzor();
void wyswietlNazwa();
void wyswietlGlowneMenu();
void wyswietlInformacje();
void plansza(int maxPol, int maxAtom);
void stanGry(int maxPol, punkt aktualnaPozycjaKursora, char** tabLaser[], int* tabAtom[], int liczbaZaznaczonychAtomow, int maxAtom);
void powrotDoMain(char sterowanie);
void losowanieAtomow(int maxAtom, int* tabAtom[], int maxPol);
void losAtomu(int* tabAtom[], int maxPol);
void sterowanieKursorem(int maxPol, punkt kierunek, punkt& aktualnaPozycja);
void strzelanie(int maxPol, punkt aktualnaPozycjaKursora, int* tabAtom[], char** tabLaser[], int& numerStrzalu);
int lotLaseru(int maxPol, punkt aktualnaPozycjaKursora, int* tabAtom[], char** tabLaser[], punkt kierunek, int& numerStrzalu);
int trafioneAtomy(int maxPol, int maxAtom, int* tabAtom[], char** tabLaser[]);
void zapisStanuGry(int maxPol, char** tabLaser[], int& numerRuchu, int& aktulanyRuchPoUndo);
void usuwanieRuchowPoUndo(int maxPol, int& numerRuchu, int& aktulanyRuchPoUndo);
void undo(int maxPol, char** tabLaser[], int& numerRuchu, int& numerStrzalu, int& aktulanyRuchPoUndo, int& liczbaZaznaczonychAtomow);
void redo(int maxPol, char** tabLaser[], int& numerRuchu, int& numerStrzalu, int& aktulanyRuchPoUndo, int& liczbaZaznaczonychAtomow);
void zaznaczanieAtomu(int maxPol, int maxAtom, punkt aktualnaPozycjaKursora, char** tabLaser[], int& liczbaZaznaczonychAtomow);
void wypisywaniePlanszy(int maxPol, punkt aktualnaPozycjaKursora, char** tabLaser[]);
void pokazywaniePlanszy(int maxPol, int* tabAtom[]);
void planszaKoncowa(int maxPol, char** tabLaser[], int* tabAtom[]);

int main()
{
    ofstream wyczyscPlik;
    wyczyscPlik.open("zapisStanuGry.txt", ios::trunc);
    wyczyscPlik.close();
    char przypadek;
    int rozmiarPlanszy;
    int iloscAtomow;
    wyswietlNazwa();
    wyswietlGlowneMenu();
    while (cin >> przypadek)
    {
        switch (przypadek)
        {
        case 'i':
        case 'I':
            system("cls");
            wyswietlInformacje();
            while (cin >> przypadek)
            {
                if (przypadek == 'z' || przypadek == 'Z')
                {
                    system("cls");
                    main();
                    break;
                }
                else
                {
                    cout << "Podano niepoprawne dane!" << endl;
                }
            }
            break;
        case 'x':
        case 'X':
            cout << "Program zostal zamkniety!" << endl;
            exit(0);
            break;
        case '1':
            system("cls");
            plansza(5, 3);
            break;
        case '2':
            system("cls");
            plansza(8, 5);
            break;
        case '3':
            system("cls");
            plansza(10, 8);
            break;
        case '4':
            cout << "Podaj wymiary planszy (min 3): ";
            cin >> rozmiarPlanszy;
            while (!cin.good() or rozmiarPlanszy < 3)
            {
                cin.clear();
                cin.ignore();
                cout << "Podano nieprawidlowe dane, wprowadz dane ponownie: " << endl;
                cout << "Podaj wymiary planszy (min 3): ";
                cin >> rozmiarPlanszy;
            }
            cout << "Podaj ilosc atomow (min 1, oraz mniej niz rozmiar planszy - 2 pola): ";
            cin >> iloscAtomow;
            while (!cin.good() or iloscAtomow < 1 or iloscAtomow > rozmiarPlanszy - 2)
            {
                cin.clear();
                cin.ignore();
                cout << "Podano nieprawidlowe dane, wprowadz dane ponownie: " << endl;
                cout << "Podaj ilosc atomow (min 1, oraz mniej niz rozmiar planszy - 2 pola): ";
                cin >> iloscAtomow;
            }
            system("cls");
            plansza(rozmiarPlanszy, iloscAtomow);
            break;
        default:
            cout << "Podano nieprawidlowe dane!" << endl;
            break;
        }
    }
    return 0;
}

void wyswietlWzor()
{
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl << endl;
}

void wyswietlNazwa()
{
    wyswietlWzor();
    cout << "  |********|_   |**|             |**|         |*******|  |**|  |**|         |********|_     |********|    |**|   |**| " << endl;
    cout << " |**|     |**|  |**|           |**__**|      |**|        |**| |**|         |**|     |**|   |**|    |**|    |**| |**|  " << endl;
    cout << " |**|     |**|  |**|          |**|  |**|    |**|         |** **|           |**|     |**|  |**|      |**|    |** **|   " << endl;
    cout << " |**|   |***|   |**|          |**|__|**|    |**|         |***|             |**|   |***|   |**|      |**|     |***|    " << endl;
    cout << " |**|     |**|  |**|         |**********|   |**|         |** **|           |**|     |**|  |**|      |**|    |** **|   " << endl;
    cout << " |**|     |**|  |**|____     |**|    |**|   |**|         |**| |**|         |**|     |**|  |**|      |**|   |**| |**|  " << endl;
    cout << " |**|     |**|  |*******|_  |**|      |**|   |**|        |**|  |**|        |**|     |**|   |**|    |**|   |**|   |**| " << endl;
    cout << "  |********|    |********|  |**|      |**|    |*******|  |**|  |**|         |********|      |********|   |**|     |**|" << endl << endl;
    wyswietlWzor();
    cout << setw(72) << "Witaj w grze Black box!" << endl;
    cout << setw(89) << "Gra zostala wykonana przez: Kewina Kisiela, ACiR, s197866" << endl << endl;
}

void wyswietlGlowneMenu()
{
    wyswietlWzor();
    cout << setw(62) << "MENU" << endl << endl;
    cout << "Wpisz '1', aby wybrac plansze 5x5 z 3 ukrytymi atomami." << endl << endl;
    cout << "Wpisz '2', aby wybrac plansze 8x8 z 5 ukrytymi atomami." << endl << endl;
    cout << "Wpisz '3', aby wybrac plansze 10x10 z 8 ukrytymi atomami." << endl << endl;
    cout << "Wpisz '4', aby wybrac rozmiar planszy oraz ilosc ukrytych atomow." << endl << endl;
    cout << "Wpisz 'I' lub 'i', aby wyswietlic informacje dotyczace gry." << endl << endl;
    cout << "Wpisz 'X' lub 'x', aby wyjsc z gry." << endl << endl;
    wyswietlWzor();
}

void wyswietlInformacje()
{
    wyswietlWzor();
    cout << setw(65) << "Informacje" << endl << endl;
    cout << "Ruch po planszy:" << endl;
    cout << "W/w = w gore" << endl;
    cout << "A/a = w lewo" << endl;
    cout << "S/s = w dol" << endl;
    cout << "D/d = w prawo" << endl << endl;
    cout << "Q/q - powoduje wyjscie do menu glownego" << endl << endl;
    cout << "U/u = undo, cofa ruch" << endl << endl;
    cout << "R/r = redo, powtarza cofniety ruch" << endl << endl;
    cout << "o - umozliwia zaznaczenie przypuszczalnego polozenia atomu" << endl << endl;
    cout << "k - konczy rozgrywke, wyswietla rozwiazanie i liczbe zdobytych punktow" << endl << endl;
    cout << "p - wyswietla rozwiazanie, bez mozliwosci kontynuowania gry" << endl << endl;
    cout << "H = Pomoc/Help - pokazuje umieszczenie atomow na planszy" << endl << endl;
    wyswietlWzor();
    cout << "Wpisz 'Z' lub 'z', aby wrocic do menu gry." << endl << endl;
    wyswietlWzor();
}

void plansza(int maxPol, int maxAtom)
{
    int numerStrzalu = 1;
    int numerRuchu = 0;
    int aktulanyRuchPoUndo = 0;
    int liczbaZaznaczonychAtomow = 0;
    char sterowanie;
    char spacja[2] = " ";
    punkt aktualnaPozycjaKursora = { 0, 0 };
    int** tabAtom = new int* [maxPol + 2];
    char*** tabLaser = new char** [maxPol + 2];

    for (int i = 0; i < maxPol + 2; i++)
    {
        tabAtom[i] = new int[maxPol + 2];
        tabLaser[i] = new char* [maxPol + 2];
    }
    for (int i = 0; i < maxPol + 2; i++)
    {
        for (int j = 0; j < maxPol + 2; j++)
        {
            tabLaser[i][j] = spacja;
        }
    }

    losowanieAtomow(maxAtom, tabAtom, maxPol);
    zapisStanuGry(maxPol, tabLaser, numerRuchu, aktulanyRuchPoUndo);
    wypisywaniePlanszy(maxPol, aktualnaPozycjaKursora, tabLaser);

    while (sterowanie = cin.get())
    {
        switch (sterowanie)
        {
        case 'w':
            sterowanieKursorem(maxPol, { 0, -1 }, aktualnaPozycjaKursora);
            stanGry(maxPol, aktualnaPozycjaKursora, tabLaser, tabAtom, liczbaZaznaczonychAtomow, maxAtom);
            break;
        case 's':
            sterowanieKursorem(maxPol, { 0, 1 }, aktualnaPozycjaKursora);
            stanGry(maxPol, aktualnaPozycjaKursora, tabLaser, tabAtom, liczbaZaznaczonychAtomow, maxAtom);
            break;
        case 'a':
            sterowanieKursorem(maxPol, { -1, 0 }, aktualnaPozycjaKursora);
            stanGry(maxPol, aktualnaPozycjaKursora, tabLaser, tabAtom, liczbaZaznaczonychAtomow, maxAtom);
            break;
        case 'd':
            sterowanieKursorem(maxPol, { 1, 0 }, aktualnaPozycjaKursora);
            stanGry(maxPol, aktualnaPozycjaKursora, tabLaser, tabAtom, liczbaZaznaczonychAtomow, maxAtom);
            break;
        case ' ':
            strzelanie(maxPol, aktualnaPozycjaKursora, tabAtom, tabLaser, numerStrzalu);
            zapisStanuGry(maxPol, tabLaser, numerRuchu, aktulanyRuchPoUndo);
            stanGry(maxPol, aktualnaPozycjaKursora, tabLaser, tabAtom, liczbaZaznaczonychAtomow, maxAtom);
            break;
        case 'o':
            zaznaczanieAtomu(maxPol, maxAtom, aktualnaPozycjaKursora, tabLaser, liczbaZaznaczonychAtomow);
            zapisStanuGry(maxPol, tabLaser, numerRuchu, aktulanyRuchPoUndo);
            stanGry(maxPol, aktualnaPozycjaKursora, tabLaser, tabAtom, liczbaZaznaczonychAtomow, maxAtom);
            break;
        case 'k':
            system("cls");
            cout << "Rozwiazanie:" << endl << endl;
            planszaKoncowa(maxPol, tabLaser, tabAtom);
            cout << endl << endl << "Ilosc dobrze zaznaczonych atomow: " << trafioneAtomy(maxPol, maxAtom, tabAtom, tabLaser) << "/" << maxAtom;
            cout << endl;
            powrotDoMain(sterowanie);
            break;
        case 'p':
            system("cls");
            cout << "Rozwiazanie:" << endl << endl;
            pokazywaniePlanszy(maxPol, tabAtom);
            cout << endl;
            powrotDoMain(sterowanie);
            break;
        case 'u':
        case 'U':
            if (aktulanyRuchPoUndo > 1)
            {
                undo(maxPol, tabLaser, numerRuchu, numerStrzalu, aktulanyRuchPoUndo, liczbaZaznaczonychAtomow);
                stanGry(maxPol, aktualnaPozycjaKursora, tabLaser, tabAtom, liczbaZaznaczonychAtomow, maxAtom);
            }
            else
            {
                cout << "Nie mozna cofnac ruchu!" << endl;
            }
            break;
        case 'r':
        case 'R':
            if (aktulanyRuchPoUndo < numerRuchu)
            {
                redo(maxPol, tabLaser, numerRuchu, numerStrzalu, aktulanyRuchPoUndo, liczbaZaznaczonychAtomow);
                stanGry(maxPol, aktualnaPozycjaKursora, tabLaser, tabAtom, liczbaZaznaczonychAtomow, maxAtom);
            }
            else
            {
                cout << "Nie mozna przywrocic ruchu!" << endl;
            }
            break;
        case 'q':
        case 'Q':
            system("cls");
            main();
            break;
        case 'h':
        case 'H':
            pokazywaniePlanszy(maxPol, tabAtom);
            break;
        default:
            break;
        }
    }
    delete[] tabAtom;
    delete[] tabLaser;
}

void stanGry(int maxPol, punkt aktualnaPozycjaKursora, char** tabLaser[], int* tabAtom[], int liczbaZaznaczonychAtomow, int maxAtom)
{
    system("cls");
    wypisywaniePlanszy(maxPol, aktualnaPozycjaKursora, tabLaser);
    cout << endl << "Zaznaczone Atomy: " << liczbaZaznaczonychAtomow << "/" << maxAtom << endl;
}

void powrotDoMain(char sterowanie)
{
    while (cin >> sterowanie)
    {
        if (sterowanie == 'q' || sterowanie == 'Q')
        {
            system("cls");
            main();
            break;
        }
        else
        {
            cout << "Podano niepoprawne dane!" << endl << "Wpisz 'q' lub 'Q' aby wyjsc do menu glownego" << endl;
        }
    }
}

void losowanieAtomow(int maxAtom, int* tabAtom[], int maxPol)
{
    srand(time(NULL));
    for (int i = 0; i < maxAtom; i++)
    {
        losAtomu(tabAtom, maxPol);
    }
}

void losAtomu(int* tabAtom[], int maxPol)
{
    int x = rand() % (maxPol - 1) + 1;
    int y = rand() % (maxPol - 1) + 1;
    if (tabAtom[x][y] == 1)
    {
        losAtomu(tabAtom, maxPol);
    }
    else
    {
        tabAtom[x][y] = 1;
    }
}

void sterowanieKursorem(int maxPol, punkt kierunek, punkt& aktualnaPozycja)
{
    if (aktualnaPozycja.x + kierunek.x >= 0 and aktualnaPozycja.x + kierunek.x < maxPol + 2)
    {
        aktualnaPozycja.x += kierunek.x;
    }
    if (aktualnaPozycja.y + kierunek.y >= 0 and aktualnaPozycja.y + kierunek.y < maxPol + 2)
    {
        aktualnaPozycja.y += kierunek.y;
    }
}

void strzelanie(int maxPol, punkt aktualnaPozycjaKursora, int* tabAtom[], char** tabLaser[], int& numerStrzalu)
{
    if (!(aktualnaPozycjaKursora.x >= 1 and aktualnaPozycjaKursora.y >= 1 and aktualnaPozycjaKursora.x <= maxPol and aktualnaPozycjaKursora.y <= maxPol))
    {
        if (!(aktualnaPozycjaKursora.x == 0 and aktualnaPozycjaKursora.y == 0) and !(aktualnaPozycjaKursora.x == 0 and aktualnaPozycjaKursora.y == (maxPol + 1)) and !(aktualnaPozycjaKursora.x == (maxPol + 1) and aktualnaPozycjaKursora.y == 0) and !(aktualnaPozycjaKursora.x == (maxPol + 1) and aktualnaPozycjaKursora.y == (maxPol + 1)))
        {
            if ((*(tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y]) == ' '))
            {
                if (aktualnaPozycjaKursora.x == 0)
                {
                    lotLaseru(maxPol, aktualnaPozycjaKursora, tabAtom, tabLaser, { 1, 0 }, numerStrzalu);
                }
                if (aktualnaPozycjaKursora.x == (maxPol + 1))
                {
                    lotLaseru(maxPol, aktualnaPozycjaKursora, tabAtom, tabLaser, { -1, 0 }, numerStrzalu);
                }
                if (aktualnaPozycjaKursora.y == 0)
                {
                    lotLaseru(maxPol, aktualnaPozycjaKursora, tabAtom, tabLaser, { 0, 1 }, numerStrzalu);
                }
                if (aktualnaPozycjaKursora.y == (maxPol + 1))
                {
                    lotLaseru(maxPol, aktualnaPozycjaKursora, tabAtom, tabLaser, { 0, -1 }, numerStrzalu);
                }
            }
        }
    }
}

int lotLaseru(int maxPol, punkt aktualnaPozycjaKursora, int* tabAtom[], char** tabLaser[], punkt kierunek, int& numerStrzalu)
{
    punkt kierunek2 = kierunek;
    punkt pozycjaLasera = { aktualnaPozycjaKursora.x, aktualnaPozycjaKursora.y };
    char numerStrzaluChar[3];
    sprintf_s(numerStrzaluChar, "%d", numerStrzalu);

    if (tabAtom[pozycjaLasera.x + kierunek2.x][pozycjaLasera.y + kierunek2.y] == 1)
    {
        tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y] = new char[3];
        tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y][0] = 'H';
        return 0;
    }
    if (kierunek2.x != 0)
    {
        if (tabAtom[pozycjaLasera.x + kierunek2.x][pozycjaLasera.y + 1] == 1 or tabAtom[pozycjaLasera.x + kierunek2.x][pozycjaLasera.y - 1] == 1)
        {
            tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y] = new char[3 + sizeof(char)];
            tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y][0] = 'R';
            return 0;
        }
    }
    if (kierunek2.y != 0)
    {
        if (tabAtom[pozycjaLasera.x + 1][pozycjaLasera.y + kierunek2.y] == 1 or tabAtom[pozycjaLasera.x - 1][pozycjaLasera.y + kierunek2.y] == 1)
        {
            tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y] = new char[3 + sizeof(char)];
            tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y][0] = 'R';
            return 0;
        }
    }

    pozycjaLasera.x = pozycjaLasera.x + kierunek2.x;
    pozycjaLasera.y = pozycjaLasera.y + kierunek2.y;

    while ((pozycjaLasera.x > 0 and pozycjaLasera.y > 0 and pozycjaLasera.x < maxPol + 1 and pozycjaLasera.y < maxPol + 1))
    {
        if (tabAtom[pozycjaLasera.x + kierunek2.x][pozycjaLasera.y + kierunek2.y] == 1)
        {
            tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y] = new char[3 + sizeof(char)];
            tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y][0] = 'H';
            return 0;
        }
        if (kierunek2.x != 0)
        {
            if (tabAtom[pozycjaLasera.x + kierunek2.x][pozycjaLasera.y + 1] == 1 and tabAtom[pozycjaLasera.x + kierunek2.x][pozycjaLasera.y - 1] == 1)
            {
                tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y] = new char[3 + sizeof(char)];
                tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y][0] = 'R';
                return 0;
            }
            if (tabAtom[pozycjaLasera.x + kierunek2.x][pozycjaLasera.y + 1] == 1)
            {
                kierunek2.x = 0;
                kierunek2.y = -1;
            }
            else if (tabAtom[pozycjaLasera.x + kierunek2.x][pozycjaLasera.y - 1] == 1)
            {
                kierunek2.x = 0;
                kierunek2.y = 1;
            }
        }
        if (kierunek2.y != 0)
        {
            if (tabAtom[pozycjaLasera.x + 1][pozycjaLasera.y + kierunek2.y] == 1 and tabAtom[pozycjaLasera.x - 1][pozycjaLasera.y + kierunek2.y] == 1)
            {
                tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y] = new char[3 + sizeof(char)];
                tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y][0] = 'R';
                return 0;
            }
            if (tabAtom[pozycjaLasera.x + 1][pozycjaLasera.y + kierunek2.y] == 1)
            {
                kierunek2.x = -1;
                kierunek2.y = 0;
            }
            else if (tabAtom[pozycjaLasera.x - 1][pozycjaLasera.y + kierunek2.y] == 1)
            {
                kierunek2.x = 1;
                kierunek2.y = 0;
            }
        }
        pozycjaLasera.x += kierunek2.x;
        pozycjaLasera.y += kierunek2.y;
    }
    tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y] = new char[3 + sizeof(char)];
    tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y][0] = numerStrzaluChar[0];
    tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y][1] = numerStrzaluChar[1];
    tabLaser[pozycjaLasera.x][pozycjaLasera.y] = new char[3 + sizeof(char)];
    tabLaser[pozycjaLasera.x][pozycjaLasera.y][0] = numerStrzaluChar[0];
    tabLaser[pozycjaLasera.x][pozycjaLasera.y][1] = numerStrzaluChar[1];
    numerStrzalu++;
    return 0;
}

void zaznaczanieAtomu(int maxPol, int maxAtom, punkt aktualnaPozycjaKursora, char** tabLaser[], int& liczbaZaznaczonychAtomow)
{
    char znakO[2] = { "o" };
    if (aktualnaPozycjaKursora.x >= 1 and aktualnaPozycjaKursora.y >= 1 and aktualnaPozycjaKursora.x <= maxPol and aktualnaPozycjaKursora.y <= maxPol)
    {
        if (*(tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y]) != *znakO)
        {
            if (liczbaZaznaczonychAtomow < maxAtom) 
            {
                tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y] = new char[3 + sizeof(char)];
                *(tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y]) = *znakO;
                liczbaZaznaczonychAtomow += 1;
            }
        }
        else
        {
            *(tabLaser[aktualnaPozycjaKursora.x][aktualnaPozycjaKursora.y]) = ' ';
            liczbaZaznaczonychAtomow -= 1;
        }
    }
}

int trafioneAtomy(int maxPol, int maxAtom, int* tabAtom[], char** tabLaser[])
{
    int trafioneAtomy = 0;
    for (int i = 1; i <= maxPol; i++)
    {
        for (int j = 1; j <= maxPol; j++)
        {
            if (tabAtom[i][j] == 1 and *(tabLaser[i][j]) == 'o')
            {
                trafioneAtomy++;
            }
        }
    }
    return trafioneAtomy;
}

void zapisStanuGry(int maxPol, char** tabLaser[], int& numerRuchu, int& aktulanyRuchPoUndo)
{
    ofstream plik;
    if (aktulanyRuchPoUndo != numerRuchu)
    {
        usuwanieRuchowPoUndo(maxPol, numerRuchu, aktulanyRuchPoUndo);
    }
    plik.open("zapisStanuGry.txt", ios::app);
    for (int i = 0; i < (maxPol + 2); i++)
    {
        for (int j = 0; j < (maxPol + 2); j++)
        {
            if (tabLaser[j][i][0] == ' ')
            {
                plik << "#" << " ";
            }
            else if (!tabLaser[j][i][1] or tabLaser[j][i][0] == 'H' or tabLaser[j][i][0] == 'R' or tabLaser[j][i][0] == 'o')
            {
                plik << tabLaser[j][i][0] << " ";
            }
            else
            {
                plik << tabLaser[j][i][0] << tabLaser[j][i][1] << " ";
            }
        }
        plik << "\n";
    }
    plik << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= \n";
    plik.close();
    numerRuchu++;
    aktulanyRuchPoUndo++;
}

void undo(int maxPol, char** tabLaser[], int& numerRuchu, int& numerStrzalu, int& aktulanyRuchPoUndo, int& liczbaZaznaczonychAtomow)
{
    int zaznaczoneAtomyWPliku = 0;
    fstream plik2;
    plik2.open("zapisStanuGry.txt", ios::in | ios::out);
    for (int i = 0; i < (maxPol + 3) * (aktulanyRuchPoUndo - 2); i++)
    {
        plik2.ignore(256, '\n');
    }

    int maxWczytanaLiczba = 0;
    for (int i = 0; i < (maxPol + 2); i++)
    {
        for (int j = 0; j < (maxPol + 2); j++)
        {
            char wczytanyZnak[3];
            int wczytanaLiczba;
            plik2 >> wczytanyZnak;
            if (wczytanyZnak[0] == '#')
            {
                tabLaser[j][i][0] = ' ';
                tabLaser[j][i][1] = ' ';
            }
            else if (!wczytanyZnak[1] or wczytanyZnak[0] == 'H' or wczytanyZnak[0] == 'R')
            {
                tabLaser[j][i][0] = wczytanyZnak[0];
            }
            else
            {
                tabLaser[j][i][0] = wczytanyZnak[0];
                tabLaser[j][i][1] = wczytanyZnak[1];
            }
            wczytanaLiczba = atoi(wczytanyZnak);
            if (wczytanaLiczba > maxWczytanaLiczba)
            {
                maxWczytanaLiczba = wczytanaLiczba;
            }
            if (wczytanyZnak[0] == 'o')
            {
                zaznaczoneAtomyWPliku++;
            }
        }
        plik2.ignore(256, '\n');
    }
    numerStrzalu = maxWczytanaLiczba + 1;
    liczbaZaznaczonychAtomow = zaznaczoneAtomyWPliku;
    aktulanyRuchPoUndo--;
    plik2.close();
}

void usuwanieRuchowPoUndo(int maxPol, int& numerRuchu, int& aktulanyRuchPoUndo)
{
    numerRuchu = aktulanyRuchPoUndo;
    fstream plik3;
    plik3.open("zapisStanuGry.txt", ios::in | ios::out);
    ofstream plik4;
    plik4.open("tymczasowy.txt");
    string wczytanyTekst;
    for (int i = 0; i < aktulanyRuchPoUndo; i++)
    {
        for (int j = 0; j < (maxPol + 2); j++)
        {
            for (int k = 0; k < (maxPol + 2); k++)
            {
                plik3 >> wczytanyTekst;
                plik4 << wczytanyTekst << " ";
            }
            plik4 << "\n";
        }
        plik3 >> wczytanyTekst;
        plik4 << wczytanyTekst << "\n";
    }
    plik3.close();
    plik4.close();
    remove("zapisStanuGry.txt");
    rename("tymczasowy.txt", "zapisStanuGry.txt");
}

void redo(int maxPol, char** tabLaser[], int& numerRuchu, int& numerStrzalu, int& aktulanyRuchPoUndo, int& liczbaZaznaczonychAtomow)
{
    int zaznaczoneAtomyWPliku = 0;
    fstream plik5;
    plik5.open("zapisStanuGry.txt", ios::in | ios::out);
    for (int i = 0; i < (maxPol + 3) * (aktulanyRuchPoUndo); i++)
    {
        plik5.ignore(256, '\n');
    }
    int maxWczytanaLiczba = 0;
    for (int i = 0; i < (maxPol + 2); i++)
    {
        for (int j = 0; j < (maxPol + 2); j++)
        {
            char wczytanyZnak[5];
            int wczytanaLiczba;
            plik5 >> wczytanyZnak;
            if (wczytanyZnak[0] == '#')
            {
                tabLaser[j][i][0] = ' ';
                tabLaser[j][i][1] = ' ';
            }
            else if (!wczytanyZnak[1] or wczytanyZnak[0] == 'H' or wczytanyZnak[0] == 'R')
            {
                tabLaser[j][i][0] = wczytanyZnak[0];
            }
            else
            {
                tabLaser[j][i][0] = wczytanyZnak[0];
                tabLaser[j][i][1] = wczytanyZnak[1];
            }
            wczytanaLiczba = atoi(wczytanyZnak);
            if (wczytanaLiczba > maxWczytanaLiczba)
            {
                maxWczytanaLiczba = wczytanaLiczba;
            }
            if (wczytanyZnak[0] == 'o')
            {
                zaznaczoneAtomyWPliku++;
            }
        }
        plik5.ignore(256, '\n');
    }
    numerStrzalu = maxWczytanaLiczba + 1;
    liczbaZaznaczonychAtomow = zaznaczoneAtomyWPliku;
    aktulanyRuchPoUndo++;
    plik5.close();
}

void wypisywaniePlanszy(int maxPol, punkt aktualnaPozycjaKursora, char** tabLaser[])
{
    if (aktualnaPozycjaKursora.x == 0 and aktualnaPozycjaKursora.y == 0)
    {
        cout << " *";
    }
    else
    {
        cout << "  ";
    }
    for (int i = 1; i <= maxPol + 1; i++)
    {
        if (aktualnaPozycjaKursora.x == i and aktualnaPozycjaKursora.y == 0)
        {
            cout << "   *";
        }
        else
        {
            if (!tabLaser[i][0][1] or tabLaser[i][0][1] == ' ' or tabLaser[i][0][0] == 'H' or tabLaser[i][0][0] == 'R')
            {
                cout << "   " << tabLaser[i][0][0];
            }
            else
            {
                cout << "  " << tabLaser[i][0][0] << tabLaser[i][0][1];
            }
        }
    }
    cout << endl;
    for (int i = 1; i <= maxPol; i++)
    {
        cout << "  " << char(196);
        for (int j = 0; j < maxPol; j++)
        {
            cout << char(197);
            for (int k = 0; k < 3; k++)
            {
                cout << char(196);
            }
        }
        cout << char(197) << char(196) << endl;
        if (aktualnaPozycjaKursora.x == 0 and aktualnaPozycjaKursora.y == i)
        {
            cout << "  *";
        }
        else
        {
            if (!tabLaser[0][i][1] or tabLaser[0][i][1] == ' ' or tabLaser[0][i][0] == 'H' or tabLaser[0][i][0] == 'R')
            {
                cout << "  " << tabLaser[0][i][0];
            }
            else
            {
                cout << " " << tabLaser[0][i][0] << tabLaser[0][i][1];
            }
        }
        for (int j = 1; j <= maxPol; j++)
        {
            if (aktualnaPozycjaKursora.x == j and aktualnaPozycjaKursora.y == i)
            {
                cout << char(179) << " * ";
            }
            else
            {
                cout << char(179) << " " << *(tabLaser[j][i]) << " ";
            }
        }
        cout << char(179);
        if (aktualnaPozycjaKursora.x == maxPol + 1 and aktualnaPozycjaKursora.y == i)
        {
            cout << "* ";
        }
        else
        {
            if (!tabLaser[maxPol + 1][i][1] or tabLaser[maxPol + 1][i][1] == ' ' or tabLaser[maxPol + 1][i][0] == 'H' or tabLaser[maxPol + 1][i][0] == 'R')
            {
                cout << tabLaser[maxPol + 1][i][0];
            }
            else
            {
                cout << tabLaser[maxPol + 1][i][0] << tabLaser[maxPol + 1][i][1] << " ";
            }
        }
        cout << endl;
    }
    cout << "  " << char(196);
    for (int i = 1; i <= maxPol; i++)
    {
        cout << char(197);
        for (int j = 0; j < 3; j++)
        {
            cout << char(196);
        }
    }
    cout << char(197) << char(196) << endl;
    for (int i = 0; i <= maxPol + 1; i++)
    {
        if (aktualnaPozycjaKursora.x == i and aktualnaPozycjaKursora.y == maxPol + 1)
        {
            cout << " *  ";
        }
        else
        {
            if (!tabLaser[i][maxPol + 1][1] or tabLaser[i][maxPol + 1][1] == ' ' or tabLaser[i][maxPol + 1][0] == 'H' or tabLaser[i][maxPol + 1][0] == 'R')
            {
                cout << " " << tabLaser[i][maxPol + 1][0] << "  ";
            }
            else
            {
                cout << tabLaser[i][maxPol + 1][0] << tabLaser[i][maxPol + 1][1] << "  ";
            }
        }
    }
    cout << endl;
}

void pokazywaniePlanszy(int maxPol, int* tabAtom[])
{
    for (int i = 1; i <= maxPol; i++)
    {
        cout << "  " << char(196);
        for (int j = 0; j < maxPol; j++)
        {
            cout << char(197);
            for (int k = 0; k < 3; k++)
            {
                cout << char(196);
            }
        }
        cout << char(197) << char(196) << endl << "   ";
        for (int j = 1; j <= maxPol; j++)
        {
            if (tabAtom[j][i] == 1)
            {
                cout << char(179) << " O ";
            }
            else
            {
                cout << char(179) << "   ";
            }
        }
        cout << char(179) << endl;
    }
    cout << "  " << char(196);
    for (int j = 0; j < maxPol; j++)
    {
        cout << char(197);
        for (int k = 0; k < 3; k++)
        {
            cout << char(196);
        }
    }
    cout << char(197) << char(196);
}

void planszaKoncowa(int maxPol, char** tabLaser[], int* tabAtom[])
{
    cout << "  ";
    for (int i = 1; i <= maxPol + 1; i++)
    {
        cout << "   " << *(tabLaser[i][0]);
    }
    cout << endl;
    for (int i = 1; i <= maxPol; i++)
    {
        cout << "  " << char(196);
        for (int j = 0; j < maxPol; j++)
        {
            cout << char(197);
            for (int k = 0; k < 3; k++)
            {
                cout << char(196);
            }
        }
        cout << char(197) << char(196) << endl;
        cout << "  " << *(tabLaser[0][i]);
        for (int j = 1; j <= maxPol; j++)
        {
            if (tabAtom[j][i] == 1 and *(tabLaser[j][i]) == 'o')
            {
                cout << char(179) << " O ";
            }
            else if (*(tabLaser[j][i]) == 'o')
            {
                cout << char(179) << " X ";
            }
            else
            {
                cout << char(179) << "   ";
            }
        }
        cout << char(179);
        cout << *(tabLaser[maxPol + 1][i]) << " ";
        cout << endl;
    }
    cout << "  " << char(196);
    for (int i = 1; i <= maxPol; i++)
    {
        cout << char(197);
        for (int j = 0; j < 3; j++)
        {
            cout << char(196);
        }
    }
    cout << char(197) << char(196) << endl;
    for (int i = 0; i <= maxPol + 1; i++)
    {
        cout << " " << *(tabLaser[i][maxPol + 1]) << "  ";
    }
    cout << endl;
}