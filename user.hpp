
#ifndef user_h
#define user_h
// протестированно 22.04
// Сущестует три типа пользователей
// Обычный пользователь без регистрации
// Может только искать и просматривать
//
// Модератор
// Обладает некоторыми правами
//
// Администратор
// Обладает всеми правами
/////////////////////////////////
#include <string>
using namespace std;
enum tag{ admin, moderator, user};

class user
{
private:
    string username;
    tag access_tag;
    string password;
    static int count; // первый - админ
    int id;
 //   char* passwordHash[]; // попозже
//    void log(); // по ID и никнейму
//    void search();
public:
    user()
    {
        count++;
        if(count == 1){
            access_tag = admin;
        }
        id = count;
        username = "Гость";
    }
    user(string name, string pass) : username(name), password(pass)
    {
        count++;
        if(count == 1){
            access_tag = admin;
        }
        id = count;
    }
    int get_tag(); // доступ к действию
    int get_count(); // мб это не надо
    int get_id();
    void sign_up();
    void set_username();
    string get_username();
};

#endif /* user_h */
