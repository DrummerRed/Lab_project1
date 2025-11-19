#include <iostream>
#include <cstdlib>
#include <ncurses.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include <limits.h>


using namespace std;

void file_creater();
void interface(int choice);
void Menu_for_record();
void interface_for_record(int choice);
void files_info();

// void choose(string* mark_ptr, int* serial_number_ptr, int* cathedra_ptr, int* terminals_ptr, int* storage_device_ptr);
void choose_1(string* mark_ptr, string* serial_number_ptr, string* cathedra_ptr);
void choose_2(string* mark_ptr, string* terminals_ptr, string* storage_device_ptr);
// void record();
void record_1();
void record_2();
void Menu();
void Help();
int mark_symb(string mark);
string scan_mark();
int serial_number_symb(string serial_number);
string scan_serial_number();
int cathedra_symb(string cathedra);
string scan_cathedra();