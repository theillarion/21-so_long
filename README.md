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
