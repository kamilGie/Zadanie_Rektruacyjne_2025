# Kolizje

<details>
  <summary>  Treść Zadania </summary>
  
Zaimplementuj funkcję `isColliding` zwracającą `true` jeśli dwa trójkąty w przestrzeni
2D kolidują ze sobą. Następnie napisz wizualizator tej kolizji. Trójkąty powinny być widoczne
na ekranie i co najmniej jeden z nich możliwy do sterowania przez użytkownika. Kolizja
powinna być w jakiś sposób zasygnalizowana użytkownikowi.
```cpp
struct vec2
{
 float x, y;
};
struct triangle
{
 std::array<vec2, 3> points;
};
bool isColliding(const& triangle1, const& triangle2);
```

--- 
</details>

## Opis rozwiązania


<table>
  <tr>
    <td>
      <img src="https://github.com/user-attachments/assets/839a373f-7717-40bf-ba44-f9c7df07e0f5" alt="triangles" width=100% />
    </td>
    <td style="vertical-align: top; padding-left: 20px;">
      <h2>🎮 Sterowanie trójkątem</h2>
      <ul>
        <li>🖱️ <strong>LPM (lewy przycisk myszy)</strong> – kliknij na trójkąt, aby go poruszyć.</li>
        <li>🔲 <strong>LPM + przeciągnięcie w rogu</strong> – zmienia rozmiar trójkąta.</li>
        <li>🖱️ <strong>PPM (prawy przycisk myszy)</strong> – przesuwanie całej planszy.</li>
        <li>🔍 <strong>Scroll myszki</strong> – zoomowanie (przybliżenie / oddalenie planszy).</li>
      </ul>
    </td>
  </tr>
</table>

Funckja sprawdzająca kolizje polega na szukaniu **osi separacji** 2 trójkątów.
1. Dla każdej krawędzi obu trójkątów wyznaczana jest prosta prostopadła (potencjalna oś separacji).
2. Następnie wszystkie wierzchołki obu trójkatów są **rzutowane na tę prostą**, i dla każdego wyznaczany jest **minimalny i maksymalny rzut**.
3. Jeśli **minimalny rzut jedego trójkąta jest większy niż maksymalny rzut drugiego** (lub odwrotnie), to pomiędzy trójkątami znajduje się oś sepracji

> Jeśli nie znajdziemy żadnej osi separacji — trójkąty **nachodzą na siebie**, więc kolizja istnieje.


---

## instalacja oraz budowanie
```perl
conan build . --build=missing 
```

na linuxie w przypadku problemu z pakietami systemowymi podczas budowania projektu, nalezy odpalic 

```perl
conan build . --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True
```

## Uruchamianie
Aby uruchomić program:
```perl
./build/Release/Task2 
```
Aby uruchomić testy:


```perl
./build/Release/Task2-ut
```

