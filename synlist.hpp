

#ifndef synlist_hpp
#define synlist_hpp

#include <stdio.h>
#include <string>
#include "json.hpp"
#include <vector>
#include <iostream>
using namespace std;
using namespace nlohmann;

const int SIZE = 100;

class synlist
{
private:
    static int count;
    int id, wordCount;
    string synarr[SIZE]; // главный массив слов
     // скорее всего не пригодится
    string eoarr = "\0"; // обозначает конец массива
    int search_for_index(string);
public:
    synlist() // конструктор без аргументов
    {
        id = ++count;
        wordCount = 0;
    }
    synlist(string arr[]) // инициализация массивом
    {
        wordCount =0;
        id = ++count;
        int i=0;
        for(; i < SIZE; i++){
            synarr[i] = arr[i];// а если массив меньше или больше?
            // что делать с пустыми значениями?
            wordCount++;
        }
      //  synarr[++i] = eoarr;
    }
    // предпочтительнее
    synlist(json jobj) // конструктор с json
    {
        wordCount =0;
        id = ++count;
        for(int i=0; i < jobj["words"].size(); i++){
            synarr[i] = jobj["words"][i];
            wordCount++;
        }
    }
    void get_info()const; // для проверок
    void add_word(string);
    void update_word(string);
    void delete_word(string);
    void display() const;
    bool is_in_arr(string);
    void sort(); // мб не надо
    string get_word(); // не уверен, что понадобится
    //////////////
    json get_json(); // получить объект в формате json
    // для записи в файл (json)
    void diskIn();
    void diskOut();
};

#endif /* synlist_hpp */
