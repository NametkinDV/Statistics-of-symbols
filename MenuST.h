#ifndef MenuST_h
#define MenuST_h

#include "StatTable.h"

typedef struct
{
  struct Table table;
  
} Menu;

int menuCreate(Menu *m); // Создание меню
int menuClose(Menu *m); // Удаление меню

int tableFromKeyboard(Menu *m); // Создание таблицы с клавиатуры
int tableFromFile(Menu *m); // Создание таблицы из файла
void settingsView(Menu *m); // Настройка вида отображения

#endif
