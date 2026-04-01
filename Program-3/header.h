#include <iostream>
#include <cstdlib>          // Для использования некоторых системных функций: system(), exit()
#include <ncurses.h>        // Для реализации интерактивного меню
#include <string>
#include <fstream>
#include <unistd.h>         /////
#include <limits.h>         // Для константы максимальной длины пути
#include <iomanip>          // Для вывода информации в табличном виде

#include <wchar.h>

using namespace std;

struct columns; 

void Menu(char* argv[]);        // Главное меню программы
void interface(int choice);     // Отрисовка интерфейса главного меню программы

void Help();                    // Функция работы пункта меню "Помощь"

void Menu_for_sorting();
void choose_file_interface();
int file_parser(columns* array, int SIZE, string file_name);
int string_counter(string file_name);
string del_space(string str);
string inverse_del_space(string str);

int choose_field(columns* array, int SIZE);
int type_sort();
void regroup_array(int field, columns* array, int SIZE);

void debug_print(columns* array, int SIZE);          // удалить