//
//  main.cpp
//  CRUD-application
//
//  Created on 29.03.2018.
//  Copyright © 2018 Oreysoft. All rights reserved.
//
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "json.hpp"
#include "user.hpp"
#include "synlist.hpp"
#include <stdlib.h>
#include <vector>
#include <time.h>
#include "log.hpp"
using namespace std;
////////////////////////////////////////////////////////////
const int COMDS = 7; // количество команд
int synlist::count = 0;
int user::count = 0;
synlist* synarr[SIZE]; // массив указателей на объекты для удобства работы программы
json js; // основной объект
unsigned long jcount; // количество списков слов в файле
long int inx; // индекс используемый после поиска
class log logger;
class user* currUser = new class user;
string operation, opword;
string opList[COMDS] = {"поиск", "добавить группу", "удалить группу", "закончить работу", "добавить слово",
    "изменить слово", "удалить слово"}; // список дейстивий
//////////////////////////////////////////////////////////////

int main(int argc, const char * argv[]) {
    
    long int search();
    void add_group();
    void delete_group();
    
    void read_json();
    void write_json();
    
    void display_comds();
    void decor(int=50, char='-');
    //////////////////////////////////////////////////////////
    char choice; // выбор при регистрации
    cin.unsetf(std::ios_base::skipws);
   
    read_json();
   
    while(true) // вход в систему
    {
        decor();
        cout << "Пропустить этот шаг(s)" << endl;
        cout << "Войдите или зарегестрируйтесь (l/r): ";
        cin >> choice;
   //     cin.ignore(-1,'\n');
        if(choice == 'l'){
            // log in
            // reads user file to an array
            // searches for username
            // compares password
            // class user us(username, password);
            // currUser = &us;
            cerr << "В данный момент регистрация невозможна" << endl;
            break;
        } else if(choice == 'r'){
            currUser->sign_up();
            //write a new user to a file
            break;
        } else if(choice == 's'){
            break;
        }
        if(choice != 'l' || choice != 'r' || choice != 's')
            cerr << "Ошибка ввода, повторите попытку" << endl;
    }
    
    cout << "Добро пожаловать, " << currUser->get_username();
    cout << endl;
    logger.write(currUser->get_username(), "Выполнен вход");
    
    display_comds();
    
    // надо это как-то упростить
    inx = -2; // чтобы невозможно было сразу вводить сложные команды
    
    while(true) // начало работы
    {
        while(true)
        {
            decor();
            cout << "Введите желаемую операцию: "; // выдаёт два раза?
         //   cin.ignore(100,'\n');
            int ch;
            do{
                ch = getchar();
                operation += ch;
            } while (ch != '\n');
  //          getline(cin, operation); // ввод с пробелами
            cout <<"Operation is " << operation << endl;
             // приведение к маленьким буквам
            transform(operation.begin(), operation.end(), operation.begin(), ::tolower);
            bool exists = std::find(std::begin(opList), std::end(opList), operation) != std::end(opList);
            // проверить есть ли команда в массиве
            if(!exists){
                cout << "Выбранное действие недоступно, повторите попытку" << endl;
            } else
                break;
        }
        
        // желаемое действие
        // может упростить команды??
        if(operation == "поиск"){ //поиск
            
            inx = search();
            
            if(inx != -1){
                synarr[inx]->display(); cout << endl;
            } else{
                cout << "Слово отсутствует в базе данных" << endl;
            }
            string qline = "Поиск: " + opword;
            logger.write(currUser->get_username(), qline);
            
        }else if(operation == "добавить слово"){ //добавить слово к группе
            
             if(inx != -1 && inx != -2){
                 cout << "Добавить слово: "; cin >> noskipws >> opword;
             //   cin.ignore(100,'\n');
                // проверка на добавление того же слова
                 if(!synarr[inx]->is_in_arr(opword)){
                     synarr[inx]->add_word(opword); // если поиска не было?
                     synarr[inx]->display(); cout << endl;
                 } else
                     cout << "Слово уже существует" << endl;
             } else
                 cout << "Сначала нужно выполнить поиск" << endl;
            
            string qline = "Добавлено слово: " + opword;
            logger.write(currUser->get_username(), qline);
            
        }else if(operation == "добавить группу"){ //добавить группу
            add_group();
            // лог внутри
            
        }else if(operation == "изменить слово"){
            if(inx == -1 || inx == -2){
                cout << "Сначала нужно выполнить поиск" << endl;
                inx = search();
            } else {
                 cout << "Изменить слово: "; cin >> opword;
              //   cin.ignore(100,'\n');
            }
            synarr[inx]->update_word(opword);
            synarr[inx]->display(); cout << endl;
            
            string qline = "Изменено слово " + opword;
            logger.write(currUser->get_username(), qline);
            
        }else if(operation == "удалить слово"){ //удалить слово из группы
            if(inx == -1 || inx == -2){
                cout << "Сначала нужно выполнить поиск" << endl;
                inx = search();
            } else {
                cout << "Удалить слово: "; cin >> opword;
            //     cin.ignore(100,'\n');
            }
            synarr[inx]->delete_word(opword);
            synarr[inx]->display(); cout << endl;
            cout << "Слово успешно удалено" << endl;
            
            string qline = "Удалено слово " + opword;
            logger.write(currUser->get_username(), qline);
            
        }else if(operation == "удалить группу"){ //удалить группу синонимов
            delete_group();
            // лог внутри
            
        }else if(operation == "закончить работу"){ //закончить работу с программой
            logger.write(currUser->get_username(), "Работа завершена");
            write_json();
            break;
        }
    }
    return 0;
}

long int search(){
    //проверка на ввод
    cout << "поиск: "; cin >> opword;
 //    cin.ignore(100,'\n');
    long int i = 0;
    while(!synarr[i]->is_in_arr(opword)){
        i++;
        if(i > jcount-1){
            i = -1;
            break;
        }
    }
    return i;
}

void add_group(){
    cout << "Вводите слова, введите \'@\', чтобы закончить: ";
    string word = "";
    json curjs;
    vector<string> opword;
    curjs["words"];
    
    while (cin >> word){
   //      cin.ignore(100,'\n');
        if(word == "@"){
            break;}
        opword.push_back(word);
        //  cout << "Word is " << word << endl;
    }
    /*
     for(int i=0; i < opword.size(); i++){
     cout << opword[i] << endl;
     } */
    
    curjs["words"] = opword;
    synarr[jcount] = new synlist(curjs);
    synarr[jcount]->display(); cout << endl;
    jcount++; //cout << jcount << endl;
    
    string qline = "Добавлены слова: ";
    for(int i=0; i < opword.size(); i++){
        qline += opword[i];
        qline += " ";
    }
    logger.write(currUser->get_username(), qline);
}

void delete_group(){
    char choice;
    cout << "Введите слово из группы, которую хотите удалить, ";
    inx = search();
    if(inx != -1){
        synarr[inx]->display(); cout << endl;
        cout << "Вы действительно хотите удалить группу? (y/n)";
        cin >> choice;
        
        if(choice == 'y'){
            delete synarr[inx];
            long int i;
            for(i=inx; i < jcount - inx; i++){
                synarr[i] = synarr[i+1];
            }
            // delete synarr[wordCount];
            jcount--;
        } else
            cout << "Операция отменена" << endl;
    } else{
        cout << "Слово отсутствует в базе данных" << endl;
    }
    string qline = "Удалены слова: ";
    for(int i=0; i < opword.size(); i++){
        qline += opword[i];
        qline += " ";
    }
    logger.write(currUser->get_username(), qline);
}

void read_json(){
    // надо проверить существование этого файла
    ifstream ifile("data.json");
    ifile >> js;
    cout << "js is " << js << endl;
    jcount = js["count"];
    
    for(int i =0; i < jcount; i++){
      //  cout << js["contents"][i]; cout << endl;
        // создаётся объект с помощью конструктора с json-массивом
        synarr[i] = new synlist(js["contents"][i]);
    //    synarr[i]->display(); cout << endl;
    }
    logger.write("sys", "файл прочитан");
}

void write_json(){
    //   исправить тут надо всё
    // запись в файл
    ofstream ofile("data.json");
    js["count"] = jcount; // поле счётчика
    js["contents"] = {};
    for(int i=0; i < jcount; i++){
        // вставляется каждый объект
        js["contents"].push_back(synarr[i]->get_json());
    }
    cout << "js is " << js << endl;
    fstream file;
    file.open("data.json", ios::trunc);
    ofile << js;
    logger.write("sys", "файл записан");
}

void display_comds(){
    cout << "Список доступных операций: ";
    for(int i=0; i < COMDS -2; i++){
        cout << opList[i] << ", "; // лишняя запятая
    }
    cout << opList[COMDS-1] << endl;
}

void decor(int q, char ch){
    for(int i=0; i < q; i++){
        cout << ch;
    }
    cout << endl;
}

