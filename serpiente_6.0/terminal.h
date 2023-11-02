/*
 * terminal.h
 * ccatalan (7/2018)
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#if defined linux || MAC
#include <sys/select.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <stropts.h>
#elif defined _WIN32
#include <windows.h>
#include <conio.h>
#endif

#ifndef TERMINAL_H_INCLUDED
#define TERMINAL_H_INCLUDED

#if defined linux || MAC
#define CABECERA "\x1B["
#define BORRAR CABECERA "2J"
#define CURSOR_VISIBLE CABECERA "?25h"
#define CURSOR_INVISIBLE CABECERA "?25l"
struct termios orig_termios;
#endif

/*
 * Habilita modo crudo: sin echo, sin enter, sin espera
 */
void habilitar_modo_crudo_terminal() {
#if defined linux || MAC
  tcgetattr(STDIN_FILENO, &orig_termios);
  struct termios raw = orig_termios;
  raw.c_lflag &= ~(ECHO | ICANON);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 0;  // en 1/10 seg, e.g. 1 = 100 ms
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
#endif
}

/*
 * Deshabilita modo crudo
 */
void deshabilitar_modo_crudo_terminal() {
#if defined linux || MAC
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
#endif
}

/*
 *  Borra terminal
 */
void borrar_terminal() {
#if defined linux || MAC
  printf("%s", BORRAR);
  fflush(stdout);
#elif defined _WIN32
  system("cls");
#endif
}

/*
 * Hace cursor visible o invisible
 */
void cursor_visible(bool habilitacion) {
#if defined linux || MAC
  if (habilitacion) {
    printf("%s", CURSOR_VISIBLE);
  } else {
    printf("%s", CURSOR_INVISIBLE);
  }
  fflush(stdout);
#elif defined _WIN32
  HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursor;
  cursor.dwSize = 1;
  cursor.bVisible = habilitacion ? TRUE : FALSE;
  SetConsoleCursorInfo(handle, &cursor);
#endif
}

/*
 *  Pone cursor en x,y
 */
void poner_cursor(int x,int y) {
#if defined linux || MAC
  printf("%s%d;%df", CABECERA, y, x);
  fflush(stdout);
#elif defined _WIN32
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#endif
}

/*
 *  Retardo ejecución en milisegundos
 */
void retardo(int ms) {
#if defined linux || MAC
  usleep(ms * 1000);
  fflush(stdout);
#elif defined _WIN32
  Sleep(ms);
#endif
}

/*
 *  Lee tecla
 *  Retorna tecla pulsada o cero en caso contrario
 */
char leer_tecla() {
#if defined linux || MAC
  char tecla = 0;
  read(STDIN_FILENO, &tecla, 1);
  return tecla;
#elif defined _WIN32
  if (kbhit()) {
    return getch();
  }
  return 0;
#endif
}

#endif // TERMINAL_H_INCLUDED
