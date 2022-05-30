#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "StatTable.h"

int addTable(struct Table *t) // Создание таблицы
{
  t->arr = (char**)malloc(sizeof(char*));
  *t->arr = (char*)malloc(sizeof(char));
  t->arr_size = (int*)malloc(sizeof(int));
  t->width_Table = (int*)malloc(sizeof(int));;
  t->height_Table = (int*)malloc(sizeof(int));;

  t->view = (int*)malloc(sizeof(int));
  *t->view = 1;

  return 1;
}


int deleteTable(struct Table *t) // Удаление таблицы
{
  if (*t->arr_size != 0)
    {
       free(*t->arr);
    }

  else if (*t->width_Table != 0 && *t->height_Table != 0)
    {
      for (int i = 0; i < *t->width_Table; ++i)
	{
	  free(t->arr[i]);
	}
    }
  else free(*t->arr);

  free(t->arr);
  free(t->arr_size);
  free(t->width_Table);
  free(t->height_Table);
  free(t->view);

  return 1;
}


int getSymbolsFromKeyboard(struct Table *t) // Получение символов с клавиатуры и запись в массив arr
{
  *t->arr_size = 0;
  char char_choice; // Символ вводимый пользователем

  printf("Введите точку '.', чтобы окончить ввод новых символов\n");

  for(;;)
    {
      printf("Введите символ: ");
      scanf(" %c", &char_choice);

      if(char_choice == '.') break;

      *t->arr = (char*)realloc(*t->arr, *t->arr_size + 1);
      t->arr[0][t->arr_size[0]++] = char_choice;
     }

  return 1;
}


int getSymbolsFromFile(struct Table *t) // Получение символов из файла и запись в массив arr
{
  *t->arr_size = 0;

  char name_file[31];
  char some_char;

  printf("Внимание: Строка принимает не более 30 символов\nВведите названия файла: ");
  scanf("%30s", name_file);

  FILE *file = fopen(name_file, "r");
  if (file == NULL)
    {
      printf("\nОшибка: Не удалось открыть файл!\n");
      return 0;
    }

  while (fgetc(file) != EOF) // Проход для подсчёта общего количества символов
    {
      ++*t->arr_size;
    }

  rewind(file);
  *t->arr = (char*)realloc(*t->arr, sizeof(char) * *t->arr_size - 1); // Выделение памяти под символы файла

  for (int i = 0; (some_char = fgetc(file)) != EOF;) // Запись символов из файла в массив
    {
      t->arr[0][i] = some_char;
      ++i;
    }

  fclose(file);
  file = NULL;
  --*t->arr_size;

  return 1;
}


int sortingSymbols(struct Table *t) // Сортировка и деление массива arr1 в arr2
{
  if (t->arr == NULL)
    {
      printf("\nОшибка: Нет элементов для сортировки!\n");
      return 0;
    }

  *t->width_Table = 0; // Количество одиночных символов(ширина таблицы)
  *t->height_Table = 0; // Самое большое количество одиночного символа(высота таблицы)

  char **arr2 = NULL;
  arr2 = (char**)malloc(sizeof(char*));

  int arr_size2 = 0;
  char temp = ' '; // Опорный символ

  for (int i = 0; i < *t->arr_size; ++i)
    {
      if (t->arr[0][i] == ' ') continue;

      int many_char = 0;
      int sector_size = 0;

      temp = t->arr[0][i];
      ++*t->width_Table;
      ++*t->width_Table;
      arr2 = (char**)realloc(arr2, sizeof(char*) * (*t->width_Table));
      arr2[arr_size2] = (char*)malloc(sizeof(char));

      for(int j = 0; j < *t->arr_size; ++j)
	{
	  if (t->arr[0][j] == temp)
	    {
	      arr2[arr_size2] = (char*)realloc(arr2[arr_size2], sizeof(char) * (sector_size + 1));
	      arr2[arr_size2][sector_size++] = t->arr[0][j];
	      t->arr[0][j] = ' ';
	      ++many_char;
	    }
	  else continue;
	}

      arr2[arr_size2] = (char*)realloc(arr2[arr_size2], sizeof(char) * sector_size); // Запись завершающего нуля в конце
      arr2[arr_size2][sector_size] = '0';
      ++arr_size2;

      arr2[arr_size2] = (char*)malloc(sizeof(char) * 1); // Разделение между массивами символов
      arr2[arr_size2][0] = '0';
      ++arr_size2;

      if (*t->height_Table < many_char) *t->height_Table = many_char; // Проверка на самое большое повторение символа
    }

  printf("\nКоличество символов: %d\n", *t->width_Table / 2);
  printf("Самая большая величина: %d\n", *t->height_Table);

  free(*t->arr);
  free(t->arr);
  *t->arr_size = 0;
  t->arr = arr2;
  arr2 = NULL;

  return 1;
}


int createTable(struct Table *t) // Отрисовка таблицы с занесением элементов
{
  if (t->arr == NULL)
    {
      printf("\nОшибка: Нет элементов для создания таблицы!\n");
      return 0;
    }

  char **arr1 = NULL;

  int var_switch = 0; // Переключатель сигнализирующий что символы закончились
  *t->width_Table += 3;  // Прибавление 3 символа к ширине для отрисовки таблицы
  *t->height_Table += 2; // Прибавление 2 символа к высоте для отрисовки таблицы

  arr1 = (char**)calloc(*t->width_Table, sizeof(char*)); // Выделение памяти под ширину таблицы

  for (int i = 0; i < *t->width_Table; ++i)
    arr1[i] = (char*)calloc(*t->height_Table, sizeof(char)); // Выделение памяти под высоту таблицы

  
  for(int i = 0; i < *t->width_Table; ++i) // Отрисовка самой таблицы
    {
      for(int j = 0; j < *t->height_Table; ++j)
	{
	  if (i < 2 && j > 1) { if (j < 11) arr1[i][j] = ' '; else continue; } // Отрисовка пробелов для выравнивания счётчика от 1 до 9

	  else  if (j == 0 && i > 2) // Отрисовка нижней строки
	     {
	       if(t->arr[i-3][0] == '0') // Пробелы между символами
		 arr1[i][j] = ' ';
	       else
		 arr1[i][j] = t->arr[i-3][0]; // Отрисовка символов
	     }

	  else if(j == 1 && i == 2) // Пересечение полос
	    arr1[i][j] = '+';

	  else if (i == 2) // Вертикальные полосы
	    arr1[i][j] = '|';

	  else if (j == 1) // Горизонтальные полосы
	    arr1[i][j] = '-';

	  else // Заполнение остального пространства пробелами
	    arr1[i][j] = ' ';
	}
    }


  for (int i = 3; i < *t->width_Table; ++i) // Отрисовка символов в таблице
    {
      var_switch = 0;

      for (int j = 2; j < *t->height_Table; ++j)
	{
	  if (var_switch == 1 || t->arr[i-3][j-2] == '0') // Заполнение пустого пространства пробелами
	    {
	      var_switch = 1;
	      arr1[i][j] = ' ';
	    }

	  else // Отрисовка символов в таблице
	    {
	      if (*t->view == 1) arr1[i][j] = t->arr[i-3][j-2]; // Отрисовка символами
	      else if (*t->view == 2) arr1[i][j] = '+'; // Отрисовка плюсами
	    }

	}
    }

  for (int i = 0; i < *t->width_Table - 3; ++i)
    free(t->arr[i]);

  free(t->arr);
  t->arr = arr1;
  arr1 = NULL;

  return 1;
}


int drawTable(struct Table *t) // Отрисовка таблицы на экране
{
  if (t->arr == NULL)
    {
      printf("\nОшибка: Нет элементов для отображения!\n");
      return 0;
    }

  for(int j = *t->height_Table-1; j >= 0; --j)
    {
      printf("\n");
      for(int i = 0; i < *t->width_Table; ++i)
	{
	  if (i == 0 && j > 1) printf("%d", (j - 1));
	  else printf("%c", t->arr[i][j]);
	}
    }

  printf("\n");

  return 1;
}


int clearTable(struct Table *t) // Очистка таблицы
{
  if (t->arr == NULL)
    {
      printf("\nОшибка: Нет элементов для удаления!");
      return 0;
    }

    for (int i = 0; i < *t->width_Table; ++i)
      {
	free(t->arr[i]);
      }
    free(t->arr);

    t->arr = (char**)malloc(sizeof(char*));
    *t->arr = (char*)malloc(sizeof(char));
    *t->width_Table = 0;
    *t->height_Table = 0;

  return 1;
}
