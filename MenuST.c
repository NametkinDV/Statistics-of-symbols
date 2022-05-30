#include <stdio.h>
#include <stdlib.h>
#include "StatTable.h"
#include "MenuST.h"


int menuCreate(Menu *m) // Создание меню
{
  if (addTable(&m->table) == 0) return 0;
  else return 1;
}


int menuClose(Menu *m) // Удаление меню
{
  if (deleteTable(&m->table) == 0) return 0;
  return 1;
}


int tableFromKeyboard(Menu *m) // Создание таблицы с клавиатуры
{
  getSymbolsFromKeyboard(&m->table);
  if (*m->table.arr_size != 0)
    {
      sortingSymbols(&m->table);
      createTable(&m->table);
      drawTable(&m->table);
      clearTable(&m->table);
    }
  else return 0;
  return 1;
}


int tableFromFile(Menu *m) // Создание таблицы из файла
{
  getSymbolsFromFile(&m->table);
  if (*m->table.arr_size != 0)
    {
      sortingSymbols(&m->table);
      createTable(&m->table);
      drawTable(&m->table);
      clearTable(&m->table);
    }
  else return 0;
  return 1;
}


void settingsView(Menu *m) // Настройка вида отображения
{
  char choise = '.';
  while (choise != '0' && choise != '1' && choise != '2')
    {
      printf("\nНастройка отображения символов:\n1.Отображение в виде введённых символов(ABC) (по умолчанию)\n2.Отображение в виде одного символа(+++)\n0.Вернуться назад\n");
      
      scanf(" %c", &choise);
	    
      switch(choise)
	{
	case '0': // Возврат назад из настройки символов
	  {
	    break;
	  }
	  
	case '1': // Отображение в виде символов
	  {
	    *m->table.view = 1;
	    printf("\nСохранено: Отображение в виде введённых символов(ABC).\n");
	    break;
	  }
	  
	case '2': // Отображение в виде плюсов
	  {
	    *m->table.view = 2;
	    printf("\nСохранено: Отображение в виде одного символа(+++).\n");
	    break;
	  }
	}
      
    }
  
}
