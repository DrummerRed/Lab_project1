#include <iostream>
#include <cstdlib>
#include <ncurses.h>
#include <string>
#include <fstream>
#include <unistd.h>
#include <limits.h>

using namespace std;

struct cathedra_counts;
struct data_from_file;

void interface(int choice);
void Menu(char* argv[]);
void Help();
void file_checker(bool* file_ECM_exist, bool* file_ECM_CONF_exist);
void files_info(bool* files_ECM_exist, bool* file_ECM_CONF_exist, char* argv[]);
void files_is_found();
void Menu_for_viewing(bool* files_ECM_exist, bool* file_ECM_CONF_exist);
void interface_for_viewing(int choice);

void file_viewer_to_screen();               // Режим вывода данных на экран
int string_counter(string file_name);        // Функция подсчета строк в файле
bool files_warning(int counter, string filename);            // Предупреждение при ошибке чтения файла
void file_reader(data_from_file* array, int SIZE, string filename);      // Функция считывания файлов

void test_func(data_from_file* data_ECM, int SIZE);      // Удалить тестовую функцию отладки