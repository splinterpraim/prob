#include <iostream>
#include  <windows.h>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Ticket.h"
#include "Train.h"
#include "Plane.h"
using namespace std;

bool srvn_date(int day, int month, int year);
int main()
{
        setlocale(LC_ALL, "Rus");
        SetConsoleCP(1251);
        SetConsoleOutputCP(1251);




    int c;
    int exi=1;
    int proverka=1;
    string username;


    do
    {
        try
        {
            system("cls");
            cout<<"\n                       Добро пожаловать в программу \"Электронная касса\"\n";
            cout<<"                      -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --\n";
            cout<<"                            -- -- -- -- -- -- -- -- -- -- -- -- --  \n";
            cout<<"\nВведите имя\n(Имя может содержать кирилицу, латинские буквы или числа)\n(Не допускаются символы: ? \ | / * \" : ) \n";
            cout<<"Имя: ";
            getline(cin,username);
           if((username.find('?') != string::npos)||(username.find('\\') != string::npos)||(username.find('|') != string::npos)||
              (username.find('/') != string::npos)||(username.find('*') != string::npos)||(username.find('\"') != string::npos)||(username.find(':') != string::npos)||(cin.fail()))
                throw runtime_error("Errore INPUT! (Не допускаются символы: ? \ | / * \" : )");
                proverka=0;
        }
        catch(const runtime_error &ex)
        {
            cout <<  ex.what() << endl;
            cout<<"\nPress Enter to enter again. . .";
            cin.get();
        }
    }while(proverka);


    ///Создание файла пользователя
    int prov=0;
    fstream creat_T("users/"+username+"_Train"+".txt");
    if(!(creat_T.is_open()))
    {
        creat_T.open("users/"+username+"_Train"+".txt", ios::out);
        creat_T<<0<<endl;
    }
    creat_T.close();

    fstream creat_P("users/"+username+"_Plane"+".txt");
    if(!(creat_P.is_open()))
    {
        creat_P.open("users/"+username+"_Plane"+".txt", ios::out);
        creat_P<<0<<endl;
    }
    creat_P.close();
    ///





    Ticket *first= new Train();
    first->setNext(new Plane());


    do
     {
        system("cls");
        cout<<"Выберите что вы хотите сделать!\n";
        cout<<"1.Найти билет\n2.Посмотреть купленные билеты на Поезд\n3.Посмотреть купленные билеты на Самолет\n4.Выход\n";

        try
        {
            cin>>c;
           if((c<1)||(c>4)||(cin.fail())||(cin.peek()!='\n'))
                throw runtime_error("Errore INPUT! Нельзя вводить буквы или цифры больше 4 и меньше 1");

        }
        catch(const runtime_error &ex)
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout <<  ex.what() << endl;
            cout<<"\nНажмите Enter чтобы ввести еще раз. . .";
            cin.get();
            c=0;

        }

        switch(c)
        {
        case 1:{system("cls");
                stringstream sstreambuf;
                int day=0,month=0,year=0;
                float cost=0;
                string direction="";
                string buf="";
                string panel="Введите данные для поиска билета\n (если вы не знаете что написать или не хотите вводить какое-то поле, то просто нажмите Enter)\n";
                cin.ignore(10000, '\n');
                do
                {
                    system("cls");
                    cout<<panel<<"Введите дату\n";
                    cout<<"День: ";
                    getline(cin,buf,'\n');
                        if(buf==""){  day=0; proverka=0;}
                        else {
                                try
                                {sstreambuf.clear();  sstreambuf<<buf;buf="";  sstreambuf>>day;
                                    if((sstreambuf.fail())||(day>31)||(day<1)||(sstreambuf.peek()!=EOF))
                                        throw runtime_error("Errore INPUT! Нельзя вводить буквы или цифры больше 31 и меньше 1");
                                    proverka=0;
                                }
                                catch(const runtime_error &ex)
                                {
                                    sstreambuf.clear();   sstreambuf.ignore(1000,'\n');
                                    cout <<  ex.what() << endl;
                                    cout<<"\nНажмите Enter чтобы ввести еще раз. . .";cin.get();
                                    proverka=1;  day=0;
                                }
                            }
                }while(proverka);

                do
                {
                    system("cls");
                    cout<<panel<<"Введите дату\n";
                    cout<<"День: "<<day<<endl;
                    cout<<"Месяц: ";
                    getline(cin,buf,'\n');
                        if(buf==""){  month=0; proverka=0;}
                        else {
                                try
                                {sstreambuf.clear();   sstreambuf<<buf;buf="";   sstreambuf>>month;
                                    if((sstreambuf.fail())||(month>12)||(month<1)||(sstreambuf.peek()!=EOF))
                                        throw runtime_error("Errore INPUT! Нельзя вводить буквы или цифры больше 12 и меньше 1");
                                    proverka=0;
                                }
                                catch(const runtime_error &ex)
                                {
                                    sstreambuf.clear();  sstreambuf.ignore(1000,'\n');
                                    cout <<  ex.what() << endl;
                                    cout<<"\nНажмите Enter чтобы ввести еще раз. . .";cin.get();
                                    proverka=1;  month=0;
                                }
                            }
                }while(proverka);

                do
                {
                    system("cls");
                    cout<<panel<<"Введите дату\n";
                    cout<<"День: "<<day<<endl;
                    cout<<"Месяц: "<<month<<endl;
                    cout<<"Год:   ";
                    getline(cin,buf,'\n');
                        if(buf==""){  year=0; proverka=0;}
                        else {
                                try
                                {sstreambuf.clear();   sstreambuf<<buf;buf="";   sstreambuf>>year;
                                    if((sstreambuf.fail())||(srvn_date(day,month,year))||(sstreambuf.peek()!=EOF))
                                        throw runtime_error("Errore INPUT! Нельзя вводить буквы и нельзя вводить дату, которая находится в прошлом");
                                    proverka=0;
                                }
                                catch(const runtime_error &ex)
                                {
                                    sstreambuf.clear();  sstreambuf.ignore(1000,'\n');
                                    cout <<  ex.what() << endl;
                                    cout<<"\nНажмите Enter чтобы ввести еще раз. . .";cin.get();
                                    proverka=1;  year=0;
                                }
                            }
                }while(proverka);

                do
                {
                    system("cls");
                    cout<<panel<<"Введите дату\n";
                    cout<<"День: "<<day<<endl;
                    cout<<"Месяц: "<<month<<endl;
                    cout<<"Год:   "<<year<<endl;
                    cout<<"Введите стоимость: ";
                    getline(cin,buf,'\n');
                        if(buf==""){  cost=0; proverka=0;}
                        else {
                                try
                                {sstreambuf.clear();   sstreambuf<<buf;buf="";   sstreambuf>>cost;
                                    if((sstreambuf.fail())||(cost<0)||(sstreambuf.peek()!=EOF))
                                        throw runtime_error("Errore INPUT! Нельзя вводить буквы и цифры меньше 1, также при вводе используйте \'.\' (1226.56) ");
                                    proverka=0;
                                }
                                catch(const runtime_error &ex)
                                {
                                    sstreambuf.clear();  sstreambuf.ignore(1000,'\n');
                                    cout <<  ex.what() << endl;
                                    cout<<"\nНажмите Enter чтобы ввести еще раз. . .";cin.get();
                                    proverka=1;  cost=0;
                                }
                            }
                }while(proverka);

                system("cls");
                cout<<panel<<"Введите дату\n";
                cout<<"День: "<<day<<endl;
                cout<<"Месяц: "<<month<<endl;
                cout<<"Год:   "<<year<<endl;
                cout<<"Введите стоимость: "<<cost<<endl;



                cout<<"Введите Пункт назначения: ";getline(cin,direction,'\n');

                system("cls");
                cout<<panel<<"Введите дату\n";
                cout<<"День: "<<day<<endl;
                cout<<"Месяц: "<<month<<endl;
                cout<<"Год:   "<<year<<endl;
                cout<<"Введите стоимость: "<<cost<<endl;
                cout<<"Введите Пункт назначения: ";
                if(direction=="")cout<<"-"<<endl;
                else cout<<direction<<endl;


                first->buy(day, month,year, cost, direction,username);
                cout<<"\nНажмите Enter чтобы вернуться в меню. . .";
                cin.get();
                break;}
        case 2:{system("cls");
                first->Show_user_s_ticket(username,1);
                cout<<"\nНажмите Enter чтобы вернуться в меню. . .";
                cin.get();cin.get();
                break;}
        case 3:{system("cls");
                first->Show_user_s_ticket(username,2);
                cout<<"\nНажмите Enter чтобы вернуться в меню. . .";
                cin.get();cin.get();
                break;}
        case 4:{system("cls");
                exi=0;
                break;}
        default:
                break;
        }
    }while(exi);

   delete first;

    return 0;
}

bool srvn_date(int day, int month, int year)
{
     SYSTEMTIME lt;
    GetLocalTime(&lt);


    if(((day==0)&&(month==0))||((day!=0)&&(month==0)))
    {
        if(year<lt.wYear) return 1;
        else return 0;
    }

    if((day==0)&&(month!=0))
    {
        if(year<lt.wYear) return 1;
        else if(year>lt.wYear) return 0;
        else
        {
            if(month<lt.wMonth) return 1;
            else if(month>lt.wMonth) return 0;
        }
     }

     if((day!=0)&&(month!=0))
     {

        if(year<lt.wYear) return 1;
        else if(year>lt.wYear) return 0;
        else
        {
            if(month<lt.wMonth) return 1;
            else if(month>lt.wMonth) return 0;
            else
            {
                if(day<lt.wDay) return 1;
                else return 0;
            }
        }
     }

}
