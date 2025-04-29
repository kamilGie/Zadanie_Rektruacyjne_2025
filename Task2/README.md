<p align="center">
  <img src="https://github.com/user-attachments/assets/839a373f-7717-40bf-ba44-f9c7df07e0f5" alt="triangles" />
</p>

## 🎮 Sterowanie trójkątem

- 🖱️ **LPM (lewy przycisk myszy)** – kliknij na trójkąt, aby go poruszyć.
- 🔲 **LPM + przeciągnięcie w rogu** – zmienia rozmiar trójkąta.
- 🖱️ **PPM (prawy przycisk myszy)** – przesuwanie całej planszy.
- 🔍 **Scroll myszki** – zoomowanie (przybliżenie / oddalenie planszy).

## instalacja oraz budowanie
```perl
conan build . --build=missing 
```

na linuxie w przypadku problemu z pakietami systemowymi podczas budowania projektu, nalezy odpalic 

```perl
conan build . --build=missing -c tools.system.package_manager:mode=install -c tools.system.package_manager:sudo=True -s
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

