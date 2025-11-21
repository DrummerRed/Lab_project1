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
void Menu_for_cleaning();
void interface_for_cleaning(int choice);
void choose_1(string* mark_ptr, string* serial_number_ptr, string* cathedra_ptr);
void choose_2(string* mark_ptr, string* terminals_ptr, string* storage_device_ptr);
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
int terminals_and_storage_device_symb(string str);
string scan_terminals();
string scan_storage_device();

void Menu_are_you_sure_cleaning(string file_1, string file_2 = "");
void are_you_sure_interface(int choice, string file_1, string file_2);
void file_ECM_cleaning();
void file_ECM_CONF_cleaning();

string upper_symb(string str);