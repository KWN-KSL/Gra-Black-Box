# 🎮 Black Box Game 🎮
Black Box to gra logiczna inspirowana klasyczną planszówką z lat 70., stworzona w języku C++ jako projekt na 1. semestrze studiów. Celem gry jest odkrycie ukrytych atomów poprzez dedukcję i analizę zachowania promieni wprowadzanych do planszy z jej krawędzi.
## 🧭 Menu startowe:
![image](https://github.com/user-attachments/assets/3e7768a4-abaf-442c-bd71-e389a2cac0f8)
## ℹ️ Ekran informacyjny:
![image](https://github.com/user-attachments/assets/ccc68df8-788a-451f-bbae-9db8681b0d59)
## 🎲 Przykład rozgrywki:
![BlackBox-gif](https://github.com/user-attachments/assets/ff7d8c53-afb2-4d10-904d-aaaa17873183)
## 📜 Zasady gry:
Gracz symuluje strzały promieniami w czarną skrzynkę, próbując odgadnąć ukryte pozycje atomów. Promienie mogą:  
* Trafić w atom — znikają (oznaczenie H)
* Zostać odbite — zmieniają kierunek (R)
* Wylecieć z innej strony — ten sam numer strzału na wejściu i wyjściu  
Gracz zaznacza przypuszczalne pozycje atomów (o) i kończy grę (k), gdy jest pewien swoich typów. Program ocenia trafność.
## 🧠 Funkcje programu
* Interaktywna rozgrywka w konsoli
* Obsługa wielu etapów (np. plansza 5×5 z 3 atomami czy plansza 10×10 z 8 atomami)  
* Losowe rozmieszczenie atomów
* Undo/redo (min. 5 ruchów)
* Estetyczne obramowania planszy (rozszerzone znaki ASCII)
* Menu dostępne w dowolnym momencie
* Ocenianie poprawności po zakończeniu gry (k)
