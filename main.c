#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "StatTable.h"
#include "MenuST.h"

int main()
{
  printf("Программа получает данные из файла или с клавиатуры и выводит статистистику\nих количества на экран.\n");

  Menu menu;
  menuCreate(&menu);
  
  char choise1 = '.';

  for(;;)
    {
      printf("\nМеню программы.\n1.Ввод данных\n2.Настройка отображения символов\n0.Выход из программы\n");
      scanf(" %c", &choise1);
      
      switch(choise1)
	{
	case '0': return 0; // Выход из программы
	  
	case '1': // Ввод данных
	  {
	    choise1 = '.';
	    char choise2 = '.';
	    
	    while (choise2 != '0' && choise2 != '1' && choise2 != '2')
	      {
		printf("\nВыберите вид ввода данных:\n1.Ввод с клавиатуры\n2.Ввод из файла\n0.Вернуться назад\n"); 

		scanf(" %c", &choise2);
		
		switch(choise2)
		  {
		  case '0': // Возврат из ввода данных
		    {
		      break;
		    }
		    
		  case '1': // Ввод с клавиатуры
		    {
		      tableFromKeyboard(&menu);
		      break;
		    }
		    
		  case '2': // Ввод из файла
		    {
		      tableFromFile(&menu);
		      break;
		    }
		    
		  }
		
	      }
	    break;
	  }
	  
	case '2': // Настройка отображения символов
	  {
	    settingsView(&menu);
	    break;
	  }
	}
      
    }
  menuClose(&menu);
  return 0;
}
