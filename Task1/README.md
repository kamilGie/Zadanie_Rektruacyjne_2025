# Szukajka.pl — Moduł Podpowiedzi

<details>
  <summary>  Treść Zadania </summary>
  
  ## Zadanie 1: Administrator wyszukiwarki szukajka.pl
  Jesteś administratorem wyszukiwarki szukajka.pl w roku 1997. Twoim zadaniem jest
  implementacja modułu wypisującego podpowiedzi do inputu użytkownika.
  ### Podstawowe wymagania:
  - Możliwość dodania nowego zapytania
  - Wyszukiwarka ma zwrócić najbardziej zbliżone zapytania do danego (np. najdłuższy
  prefiks)
  ### Przykładowy scenariusz użycia:

  (linie rozpoczynające się od ‘>’ zostały wprowadzone przez użytkownika programu)
```yaml
  > add: Kiedy jest nowy rok w Chinach?
  > add: Kiedy jest nowy rok w Tajlandii?
  > ask: Kiedy jest nowy rok
  result: Kiedy jest nowy rok w Chinach?
  result: Kiedy jest nowy rok w Tajlandii?
```

--- 
</details>

## Opis rozwiązania

Skupiłem się na normalizacji zapytań oraz ich przechowywaniu w stałej strukturze.

- Każde zapytanie jest normalizowane poprzez zamianę wszystkich liter na małe oraz usunięcie zbędnych spacji.
- Dodawanie zapytań polega na wstawieniu nowego zapytania do posortowanego wektora.
- Wyszukiwanie zapytań polega na pobraniu ich rankingu — od pierwszego pasującego do danego prefiksu do ostatniego.
- Na koniec zapytania są zapisywane do pliku, z którego można je później ponownie wczytać.


## Instalacja oraz budowanie

Aby zbudować projekt, użyj poniższego polecenia:

```bash
conan build . --build=missing
```

Na systemie Linux: Wymagany jest GCC w wersji 13 lub nowszej. Jeśli nie posiadasz tej wersji, cmake sprawdzi, czy jest zainstalowana, i poda odpowiednią komendę do jej instalacji.

## Uruchamianie
Aby uruchomić program:
```perl
./build/Release/Task1
```

Aby uruchomić testy:

```perl
./build/Release/Task1-ut
```
