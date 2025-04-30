# Operacja binarna

<details>
  <summary>  Treść Zadania </summary>
  
Zakładając, że operacja binarna `f` nie wywołuje żadnych “efektów ubocznych”,
zaimplementuj funkcję `calculate` tak, że jej rezultat będzie odpowiadał n-krotnej aplikacji
funkcji `f` na argumencie `value`.
```cpp
template <class T, class Op>
concept IsSupported = requires(T first, T second, Op operation)
{
 { operation(first, second) } -> std::convertible_to<T>;
 { T::identity() } -> std::convertible_to<T>;
};
template <class BinaryOp, class ValueType>
 requires IsSupported<ValueType, BinaryOp>
ValueType calculate(int n, ValueType value, const BinaryOp& f);
```

### Przykładowo dla zmiennych x, y i z (z klasy `T`) oraz funkcji `f`:
`calculate(3, x, f)`
powinno zwrócić taki sam wynik jak wywołanie: `f(f(x, x), x)`

Dodatkowo możemy założyć że:
  - `f(x, T::identity()) == f(T::identity(), x) == x`
  - `f(f(x, y), z) == f(x, f(y, z))`
  - oraz `f` nie wywołuje żadnych “efektów ubocznych”.

--- 
</details>

## Opis rozwiązania
Dzięki temu, że kolejność działań nie ma znaczenia, możemy wykorzystać zapis binarny liczby `n`. Dla każdego bitu o wartości 1 w tym zapisie dodajemy odpowiednią potęgę wyniku, aplikując funkcję `f`.

## Instalacja oraz budowanie

Aby zbudować projekt, użyj poniższego polecenia:

```bash
conan build . --build=missing
```

## Uruchamianie
Aby uruchomić program:
```perl
./build/Release/Task3
```

Aby uruchomić testy:

```perl
./build/Release/Task3-ut
```
