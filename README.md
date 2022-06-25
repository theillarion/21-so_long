# 21-so_long
## Установка
> `git clone --recurse-submodules https://github.com/theillarion/21-so_long.git`
* или
> `git clone https://github.com/theillarion/21-so_long.git` \
> `git submodule update --init --recursive`
## Требования
### Mac OS
* framework **AppKit** and **OpenGL**
### Linux
* xorg
* x11
* zlib \
`sudo apt install xorg libxext-dev zlib1g-dev libbsd-dev`
## Использование
* `make`
  * `all` / `debug` / `so_long` / `so_long_bonus` 
  * `debug` / `so_long_debug`
  * `clean`
  * `fclean`
  * `re`
* `./so_long` *path_to_map_dot_ber*
## Особенности проекта
* Работоспособность на двух ОС: Mac OS (Darwin) и Linux (Debian systems).
* Библиотеки/функции/перечисления используются в зависимости от ОС.
* Динамическая подборка размера пикселей в зависимости от разрешения экрана (от 8 пикселей до 128).
## Карта
* Файл должен быть с расширением .ber
* Символы:
  * **1** - стена *(неограниченное количество, но карта должна быть закрыта стеной)*
  * **E** - выход *(только один, доступен только тогда, когда все предметы коллекции собраны)*
  * **0** - пусто пространство *(неограниченное количество)*
  * **C** - предмет коллекции *(неограниченное количество, необходимо собрать все)*
  * **F** - вражеский патруль *(неограниченное количество, при столкновение с игроком игра заканчивается)*
