# Gra Saper - README

## Spis treści

1. [Opis projektu](#opis-projektu)
2. [Podręcznik użytkownika](#podręcznik-użytkownika)
   - [Zasady gry](#zasady-gry)
   - [Sposób uruchomienia programu](#sposób-uruchomienia-programu)
   - [Opis poszczególnych opcji](#opis-poszczególnych-opcji)
3. [Szczegóły implementacji](#szczególy-implementacji)
   - [Podział programu na moduły](#podział-programu-na-moduły)
   - [Interfejs kluczowych funkcji](#interfejs-kluczowych-funkcji)
   - [Opis ważniejszych struktur](#opis-ważniejszych-struktur)
   - [Opis i wyniki testów](#opis-i-wyniki-testów)
4. [Podział pracy w zespole](#podział-pracy-w-zespole)
5. [Podsumowanie](#podsumowanie)

---

## Opis projektu

"Saper" to klasyczna gra komputerowa, w której celem gracza jest oznaczenie wszystkich min na planszy bez ich aktywowania. Gra została stworzona w celu nauki programowania zespołowego oraz praktycznego zastosowania różnych technologii i metodologii projektowania oprogramowania.

---

## Podręcznik użytkownika

### Zasady gry

1. Gracz rozpoczyna grę i wybiera rozmiar planszy z przedstawionych mu opcji.
2. Celem gry jest oznaczenie wszystkich min bez ich aktywacji.
3. Kliknięcie na pole:
   - Jeśli pole zawiera minę – gra kończy się przegraną.
   - Jeśli pole nie zawiera miny – odsłania liczbę określającą, ile min znajduje się w sąsiedztwie pola.
4. Gracz może oznaczać pola flagami, wpisując `f x y`, gdzie `x` i `y` to koordynaty.
5. Gra kończy się wygraną, gdy wszystkie pola, które nie są minami, zostaną odkryte.

### Sposób uruchomienia programu

1. Upewnij się, że masz zainstalowane wymagane oprogramowanie:
   - GCC
2. Pobierz projekt z repozytorium.
3. Uruchom plik MakeFile: `make game`.
4. Postępuj zgodnie z instrukcjami wyświetlanymi na ekranie.

### Opis poszczególnych opcji

Gra posiada 3 poziomy trudności (oraz możliwość definicji własnego poziomu):

- **Łatwy** – 9x9
- **Średni** – 16x16
- **Trudny** – 16x30 (gdzie 16 to liczba wierszy, a 30 to liczba kolumn)
- **Własna plansza** – użytkownik definiuje rozmiar planszy.

---

## Szczegóły implementacji

### Podział programu na moduły

1. **main.c** – Plik główny odpowiedzialny za uruchomienie gry.
2. **logic.c** – Logika gry, w tym generowanie planszy i obsługa zdarzeń.
3. **output.c** – Obsługa listy najlepszych graczy.
4. **test\_\*** – Moduły testujące poszczególne funkcjonalności gry (\* - poszczególne nazwy modułów testujących różne elementy).

### Interfejs kluczowych funkcji

#### Plik: `logic.h`

- `void initSize(int difLevel)` – Funkcja inicjalizująca wymiary planszy na podstawie poziomu trudności wybranego przez użytkownika.

- `int checkAround(char *map, int x, int y)` – Funkcja zliczająca liczbę min w sąsiedztwie podanego pola.

- `int checkFields(char *map, int x, int y)` – Funkcja zwracająca liczbę sąsiadujących pól, które nie zawierają min.

- `void setFields(char *map)` – Funkcja ustawiająca wartości pól na planszy, reprezentujące liczbę sąsiednich min.

- `int outsideBox(int tmp, int x, int y)` – Funkcja sprawdzająca, czy dane pole znajduje się poza obszarem gry.

- `char *getMap(int mines, int x, int y, int ifRand)` – Funkcja generująca planszę gry z określoną liczbą min.

- `char *initMap()` – Funkcja inicjalizująca planszę gry z zakrytymi polami.

- `char *getUserMap(char *map, int x, int y)` – Funkcja generująca planszę użytkownika, odkrywając wybrane pole i jego sąsiedztwo.

- `void show(char *map)` – Funkcja wyświetlająca aktualny stan planszy gry w konsoli.

- `void swapValues(char *map, char *userMap, int x, int y)` – Funkcja przenosząca wartość z planszy gry na planszę użytkownika.

- `void setValue(char *userMap, int x, int y, char value)` – Funkcja ustawiająca wartość danego pola na planszy użytkownika.

#### Plik: `output.h`

- `void updateBestPlayers(char *name, int score)` – Funkcja aktualizująca listę najlepszych graczy w pliku `leader_board.txt`. Odczytuje bieżące wyniki, porównuje je z wynikiem użytkownika i zapisuje zaktualizowaną listę, uwzględniając nowy wynik, jeśli jest lepszy od istniejących.

### Opis ważniejszych struktur

- **Plansza (map, userMap)** – Tablica dwuwymiarowa reprezentująca stan gry (pola zakryte, odkryte, miny).
- **Struktura gracza (board)** – Struktura zawierająca imię gracza oraz jego wynik:
  ```c
  typedef struct {
      char name[50];
      int points;
  } board;
  ```

# Opis i wyniki testów

Testy zostały zaimplementowane z użyciem funkcji testowych. Poniżej znajdują się szczegóły dotyczące testów:

## test_initSize()
Testuje funkcję `initSize()`, która ustawia rozmiar planszy na podstawie poziomu trudności. Testy sprawdzają, czy wymiary planszy są poprawnie ustawiane dla trzech poziomów trudności (1, 2, 3).

## test_checkAround()
Testuje funkcję `checkAround()`, która zlicza liczbę min w sąsiedztwie danego pola na planszy. Testy sprawdzają różne pozycje na planszy, aby upewnić się, że liczba min jest poprawnie obliczana.

## test_setFields()
Testuje funkcję `setFields()`, która ustawia liczbę min wokół danego pola. Sprawdzane jest, czy wartości są odpowiednio ustawione na planszy.

## test_outsideBox()
Testuje funkcję `outsideBox()`, która sprawdza, czy dane pole znajduje się w obrębie planszy.

## test_getMap()
Testuje funkcję `getMap()`, która generuje planszę z określoną liczbą min. Test sprawdza, czy liczba min jest zgodna z oczekiwaniami.

## Funkcja `assert()`

Funkcja `assert()` to mechanizm testowy, który służy do sprawdzania, czy wyrażenie logiczne jest prawdziwe. Jeśli wyrażenie jest fałszywe, program przerywa działanie i wyświetla błąd. Używa się jej do weryfikacji, czy funkcje działają zgodnie z oczekiwaniami.


#### Wyniki testów:

```
test_initSize passed!
test_checkAround passed!
test_setFields passed!
test_outsideBox passed!
test_getMap passed!
All tests passed!
```

---

## Podział pracy w zespole

1. **Michał Glinka** – Implementacja logiki gry oraz pisanie dokumentacji 
`logic.c, test_function.c`.

2. **Michał Muszyński** – Operacje na plikach i pisanie testów            
`MakeFile, test_leaderboard.c, output.c, main.c`.

---

## Podsumowanie

### Czy wszystkie funkcjonalności udało się zaimplementować?

Tak, wszystkie podstawowe funkcjonalności gry zostały zaimplementowane.

### Co sprawiało trudności?

Największym wyzwaniem była komunikacja i trzymanie sie orginalnej wizji projektu, oraz podział pracy.

### Jakie napotkaliście problemy i jak je rozwiązaliście?

- **Problem:** Sprawdzanie czy pola do okaoła punktu startowego nie są bombami w przypadku gdzie punkt startowy jest na granicy planszy. 

  **Rozwiązanie:** Napisanie oddzielnej funkcji do sprawdzania pustych pól do okoła punktu startowego.


### Wnioski

Projekt pozwolił nam zdobyć doświadczenie w pracy zespołowej oraz wspólne rozwiązywaniu problemów programistycznych. Zrozumieliśmy, jak ważne jest planowanie oraz odpowiedni podział zadań w zespole.

