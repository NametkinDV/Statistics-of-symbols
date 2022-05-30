#ifndef StatTable_h
#define StatTable_h

struct Table
{
  char **arr;
  int *arr_size;
  int *width_Table;
  int *height_Table;

  int *view;
};

int addTable(struct Table *t); // Создание таблицы
int deleteTable(struct Table*t); // Удаление таблицы

int getSymbolsFromKeyboard(struct Table *t); // Получение символов с клавиатуры и запись в массив arr
int getSymbolsFromFile(struct Table *t); // Получение символов из файла и запись в массив arr
int sortingSymbols(struct Table *t); // Сортировка и деление массива arr1 в arr2
int createTable(struct Table *t); // Отрисовка таблицы с занесением элементов
int drawTable(struct Table *t); // Отрисовка таблицы на экране
int clearTable(struct Table *t); // Очистка таблицы
  
#endif
