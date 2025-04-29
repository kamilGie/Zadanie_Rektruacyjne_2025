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
