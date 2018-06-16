
#include <stdio.h>
#include <string>
#include "synlist.hpp"
#include <iostream>
#include "json.hpp"
#include <fstream>
#include <stdlib.h>

int synlist::search_for_index(string str){
    int i=0;
 //   cout << *str << endl;
    while(synarr[i] != str){
        i++;
     //   cout << i;
        if(i > wordCount){
            i = -1; // для ошибок
            break;
        }
    }
    return i;
}

void synlist::display() const{ // показать слова
    for(int i=0; i < wordCount - 1; i++){
        cout << synarr[i] << ", ";
    }
    cout << synarr[wordCount-1];
}

void synlist::add_word(string str){// добавить слово
    synarr[wordCount++] = str;
}

void synlist::update_word(string str){
    int i = search_for_index(str);
   // cout << i << endl;
    if(i != -1){
        string newWord;
        cout << "Введите новое слово: "; cin >> newWord;
        synarr[i] = newWord;
        cout << "Слово успешно изменено" << endl;
    }
    else
        cerr << "Слова не существует" << endl;
}

void synlist::delete_word(string str){
    int inx = search_for_index(str);
    if(inx != -1){
        for(int i=inx; i < wordCount - inx; i++){
            synarr[i] = synarr[i+1];
        }
        // delete synarr[wordCount];
        wordCount--;
    }
    else
        cerr << "Слова не существует" << endl;
}

bool synlist::is_in_arr(string word){
    bool exists;
    int inx = search_for_index(word); // ищет индекс
    // возвращает -1, если не находит
    exists = (inx != -1) ? true : false;
    return exists;
}

void synlist::sort(){ // мб не надо
}

json synlist::get_json(){
    json js;
    js["id"] = id;
    for(int i=0; i < wordCount; i++){
        js["words"].push_back(synarr[i]);
    }
    return js;
}

void synlist::get_info() const{
    cout << "ID is " << id << endl;
    cout << "Word count is " << wordCount;
}


