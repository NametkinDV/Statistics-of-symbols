// Программа Statistics of Symbols v1.0
// Данная программа предоставляет пользователю возможность ввести данные
// с клавиатуры, либо из файла пользователя, подводит статистику
// введённых символов\цифр и выводит их на экран в виде таблицы.
// Настройки предоставляют пользователю возможность выбрать вид отображения.
// Автор: Намёткин Дмитрий

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

int getSymbolsFromKeyboard(char ***arr,int **arr_size) // Получение символов с клавиатуры и запись в массив arr
{
  char **arr1;
  **arr_size = 0;
  arr1 = (char**)malloc(sizeof(char*));
  char char_choice; // Символ вводимый пользователем

  printf("Введите точку '.', чтобы окончить ввод новых символов\n");

  for(;;)
    {
      printf("Введите символ: ");
      scanf("%1s", &char_choice);
      
      if(char_choice == '.') break;

      *arr1 = (char*)realloc(*arr1, **arr_size + 1);
      arr1[0][arr_size[0][0]++] = char_choice;
     }
  printf("\n");

    if (*arr1 == NULL)
    {
      free(*arr);
      *arr = NULL;
      }
  *arr = arr1;
  return 1;
}


int getSymbolsFromFile(char ***arr, int **arr_size) // Получение символов из файла и запись в массив arr1
{
  char some_char;
   *arr = (char**)malloc(sizeof(char*));
  **arr_size = 0;
  char name_file[31];

  printf("Внимание: Строка принимает не более 30 символов\nВведите названия файла: ");
  scanf("%30s", name_file);

  FILE *file = fopen(name_file, "r");
  if (file == NULL)
    {
      free(*arr);
      *arr = NULL;
      printf("Ошибка: Не удалось открыть файл!\n");
      return 0;
    }

  while (fgetc(file) != EOF)
    {
      ++**arr_size;
    }
  
  rewind(file);
  **arr = malloc(sizeof(char) * **arr_size - 1);
  
  for (int i = 0; (some_char = fgetc(file)) != EOF;)
    {
      arr[0][0][i] = some_char;
      ++i;
    }

  fclose(file);
  file = NULL;
  --**arr_size;
  printf("\n");
 
  return 1;
}


int sortingSymbols(char ***arr1, int **arr_size1, int **all_char, int **max_number_char) // Сортировка и деление на элементы массива arr1
{                                                                                          // с записью в массив arr2
  if (*arr1 == NULL)
    {
      printf("Ошибка: Нет элементов для сортировки!\n");
      return 0;
    }
  
  char **arr2 = NULL;
  arr2 = (char**)malloc(sizeof(char*));

  int arr_size2 = 0;

  **all_char = 0; // Количество одиночных символов(ширина таблицы)
  **max_number_char = 0; // Самое большое количество одиночного символа(высота таблицы)
  char temp = ' ';

  for (int i = 0; i < **arr_size1; ++i)
    {
      if (arr1[0][0][i] == ' ') continue;

      int many_char = 0;
      int sector_size = 0;

      temp = arr1[0][0][i];
      ++**all_char;
      ++**all_char;
      arr2 = (char**)realloc(arr2, sizeof(char*) * (**all_char));
      arr2[arr_size2] = (char*)malloc(sizeof(char));

      for(int j = 0; j < **arr_size1; ++j)
	{
	  if (arr1[0][0][j] == temp)
	    {
	      arr2[arr_size2] = (char*)realloc(arr2[arr_size2], sizeof(char) * (sector_size + 1));
	      arr2[arr_size2][sector_size++] = arr1[0][0][j];
	      arr1[0][0][j] = ' ';
	      ++many_char;
	    }
	  else continue;
	}

      arr2[arr_size2] = (char*)realloc(arr2[arr_size2], sizeof(char) * sector_size);
      arr2[arr_size2][sector_size] = '0';
      ++arr_size2;
      
      arr2[arr_size2] = (char*)malloc(sizeof(char) * 1);
      arr2[arr_size2][0] = '0';
      ++arr_size2;
      
      if (**max_number_char < many_char) **max_number_char = many_char;
    }

  printf("Количество символов: %d\n", **all_char / 2);
  printf("Самая большая величина: %d\n", **max_number_char);

  free(**arr1);
  **arr_size1 = 0;
  *arr1 = arr2;
  arr2 = NULL;
  
  return 1;
}


int createTable(char ***arr2, int **all_char, int **max_number_char, int view) // Отрисовка таблицы в arr1 с переносом элементов из arr2
{
  if (*arr2 == NULL)
    {
      printf("Ошибка: Нет элементов для создания таблицы!\n");
      return 0;
    }
  
  char **arr1 = NULL;
  
  int var_switch = 0; // Переключатель сигнализирующий что символы закончились
  all_char[0][0] += 3;        // Прибавление 2 символа к ширине для отрисовки таблицы
  max_number_char[0][0] += 2; // Прибавление 2 символа к высоте для отрисовки таблицы
  
  arr1 = (char**)calloc(**all_char, sizeof(char*)); // Выделение памяти под ширину таблицы

  for (int i = 0; i < **all_char; ++i)
    arr1[i] = (char*)calloc(**max_number_char, sizeof(char)); // Выделение памяти под высоту таблицы
  
  for(int i = 0; i < **all_char; ++i) // Отрисовка самой таблицы
    {
      for(int j = 0; j < **max_number_char; ++j)
	{
	  if (i < 2 && j > 1) {if (j < 11) arr1[i][j] = ' '; else continue;}

	   else  if (j == 0 && i > 2)
	     {
	       if(arr2[0][i-3][0] == '0')
		 arr1[i][j] = ' ';
	       else
		 arr1[i][j] = arr2[0][i-3][0];
	     }
	   
	  else if(j == 1 && i == 2)
	    arr1[i][j] = '+';

	  else if (i == 2)
	    arr1[i][j] = '|';

	  else if (j == 1)
	    arr1[i][j] = '-';
	  
	  else
	    arr1[i][j] = ' ';
	}
    }

  
  for (int i = 3; i < **all_char; ++i) // Отрисовка символов в таблице
    {
      var_switch = 0;

      for (int j = 2; j < **max_number_char; ++j)
	{
	  if (var_switch == 1 || arr2[0][i-3][j-2] == '0')
	    {
	      var_switch = 1;
	      arr1[i][j] = ' ';
	    }

	  else
	    {
	      if (view == 1) arr1[i][j] = arr2[0][i-3][j-2];
	      else if (view == 2) arr1[i][j] = '+';
	    }
	  
	}
    }

  for (int i = 0; i < **all_char - 3; ++i)
    free(arr2[0][i]);
  
  free(*arr2);
  *arr2 = arr1;
  arr1 = NULL;
    
  return 1;
}


int drawTable(char ***arr1, int **all_char, int **max_number_char) // Отрисовка таблицы на экране
{
  if (*arr1 == NULL) {printf("Ошибка: Нет элементов для отображения!\n"); return 0;}
  for(int j = **max_number_char-1; j >= 0; --j)
    {
      printf("\n");
      for(int i = 0; i < **all_char; ++i)
	{
	  if (i == 0 && j > 1) printf("%d", (j - 1));
	  else printf("%c", arr1[0][i][j]);
	}     
    }
  
  printf("\n");

  return 1;
}


int deleteTable(char ***arr, int **width_Table, int **height_Table)
{
  if (*arr == NULL)
    {
      printf("Ошибка: Нет элементов для удаления!");
      return 0;
    }

    for (int i = 0; i < **width_Table; ++i)
      {
	free(arr[0][i]);
      }
    free(*arr);
    *arr = NULL;
    **width_Table = 0;
    **height_Table = 0;
    
  return 1;
}


int main()
{
  printf("Программа получает данные из файла или с клавиатуры и выводит статистистику\nих количества на экран.\n\nМеню программы.\n1.Ввод данных\n2.Настройка отображения символов\n0.Выход из программы\n");

  char **arr = NULL;
  int *arr_size = (int*)malloc(sizeof(int));
  int *width_Table = (int*)malloc(sizeof(int));
  int *height_Table = (int*)malloc(sizeof(int));
  int view = 1;
  
  *arr_size = 0; // Ячейка для подсчёта введёных пользователем символов
  *width_Table = 0;
  *height_Table = 0;
  
  int var1;
  int var2;

  for(;;)
    {
      scanf("%d", &var1);
      
      switch(var1)
	{
	case 0: return 0;
	  
	case 1:
	  {
	    var1 = -1;
	    printf("\nВыберите вид ввода данных:\n1.Ввод с клавиатуры\n2.Ввод из файла\n0.Вернуться назад\n"); 
	    scanf("%d", &var2);
	    
	    switch(var2)
	      {
	      case 0:
		{
		  var2 = -1;
		  printf("\nМеню программы.\n1.Ввод данных\n2.Настройка отображения символов\n0.Выход из программы\n");
		  break;
		}
		
	      case 1:
		{
		  var2 = -1;
		  
		  getSymbolsFromKeyboard(&arr, &arr_size);
		  if (arr != NULL)
		    {
		  sortingSymbols(&arr, &arr_size, &width_Table, &height_Table);
		  createTable(&arr, &width_Table, &height_Table, view);
		  drawTable(&arr, &width_Table, &height_Table);
		  deleteTable(&arr, &width_Table, &height_Table);
		    }
		 
		  printf("\nМеню программы.\n1.Ввод данных\n2.Настройка отображения символов\n0.Выход из программы\n");
		  break;
		}
		
	      case 2:
		{
		  var2 = -1;
		  
		  getSymbolsFromFile(&arr, &arr_size);
		  if (arr != NULL)
		    {
		  sortingSymbols(&arr, &arr_size, &width_Table, &height_Table);
		  createTable(&arr, &width_Table, &height_Table, view);
		  drawTable(&arr, &width_Table, &height_Table);
		  deleteTable(&arr, &width_Table, &height_Table);
		    }
		  
		  printf("\nМеню программы.\n1.Ввод данных\n2.Настройка отображения символов\n0.Выход из программы\n");
		  break;
		}
	      }
	    break;
	  }
	  
	case 2:
	  {
	    var1 = -1;
	    printf("\nНастройка отображения символов:\n1.Отображение в виде введённых символов(ABC) (по умолчанию)\n2.Отображение в виде одного символа(+++)\n0.Вернуться назад\n");
	    scanf("%d", &var2);
	    
	    switch(var2)
	      {
	      case 0:
		{
		  printf("\nМеню программы.\n1.Ввод данных\n2.Настройка отображения символов\n0.Выход из программы\n");
		  var2 = -1;
		  break;
		}
		
	      case 1:
		{
		  var2 = -1;
		  view = 1;
		  printf("\nМеню программы.\n1.Ввод данных\n2.Настройка отображения символов\n0.Выход из программы\n");
		  break;
		}
		
	      case 2:
		{
		  var2 = -1;
		  view = 2;
		  printf("\nМеню программы.\n1.Ввод данных\n2.Настройка отображения символов\n0.Выход из программы\n");
		  break;
		}
	      }
	    
	  }
	  break;
	  
	}
      
    }
  return 0;
}
