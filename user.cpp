
#include <stdio.h>
#include <iostream>
#include "user.hpp"

void user::set_username(){
    cout << "Придумайте новое имя пользователя: "; cin >> username;
    cout << "Имя пользователя успешно изменено" << endl;
}

string user::get_username(){
    return username;
}

void user::sign_up(){ //регистрация
    string passwd, passwd2;
    cout << "Придумайте имя пользователя: "; cin >> username;
    cout << "Придумайте пароль: "; cin >> passwd;
    cout << "Повторите пароль: "; cin >> passwd2;
    if(passwd == passwd2){
        password = passwd;
    }
}

int user::get_tag(){
    return access_tag;
}

int user::get_count(){
    return count; // мб это не надо
}

int user::get_id(){
    return id;
}


