#include <stdio.h>
#include <locale.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <windows.h>
#include <typeinfo>
using namespace std;

string dataArr[50] = {};

bool KEY[256];
void GetKEY(){
    int i = 0;
    while (i < 256){
        if (GetAsyncKeyState(i)) KEY[i] = 1; else KEY[i] = 0;
        i++;
    }

}
void clrscr(){
    system("CLS");
}

void exitFunction(){
    cout << "Выйти в главное меню" << "\n";
    while(true){
        GetKEY();
        if(KEY[27]){
            break;
        }
    }
}

void addFunction(){

    string newMineralName;

    cout << "Добавить минерал" << "\n";
    cout << "Введите название нового минерала: ";
    cin >> newMineralName;

     for(int i = 0; i <= 50; i++){
        if(dataArr[i].find(newMineralName) != -1){
            cout << "Данный минерал уже есть в базе: " << "\n";
            cout << dataArr[i];
            addFunction();
        }
        else{
            continue;
        }
    }
    string buffNewMineralCharact;
    cout << "Введите характеристику минерала: ";
    cin >> buffNewMineralCharact;
    string newMineralCharact = ". Характеристика: " + buffNewMineralCharact;

    string buffNewMineralProperty;
    cout << "Введите свойства минерала: ";
    cin >> buffNewMineralProperty;
    string newMineralProperty = ". Свойства: " + buffNewMineralProperty;

    string buffNewMineralContain;
    cout << "Введите состав: ";
    cin >> buffNewMineralContain;
    string newMineralContain = ". Состав: " + buffNewMineralContain;

    int newMineralIndex = 0;
    for(int i = 0; i <= 50; i++){
        if(dataArr[i] != ""){
            newMineralIndex+=1;
        }
    }

    newMineralIndex+=1;
    string newMineralRowToDataArr;
    newMineralRowToDataArr = "\n" + newMineralName + newMineralCharact + newMineralProperty + newMineralContain + "\n";
    cout << newMineralRowToDataArr << "\n";
    cout << newMineralIndex << "\n";
    dataArr[newMineralIndex] = newMineralRowToDataArr;
    for (int i = 0; i <= 50; i++){
        cout << dataArr[i];
    }

    ofstream fout;
    fout.open("data.txt");
    for(int i = 0; i <= 50; i++){
        fout << dataArr[i];
    }
    fout.close();
    cout << "Данные сохранены" << "\n";

    while(true){
        GetKEY();
        if(KEY[27]){
            break;
        }
    }
}

void changeFunction(){
    cout << "Изменить" << "\n";
    while(true){
        GetKEY();
        if(KEY[27]){
            break;
        }
    }
}

void findFunction(){

    string MineralSearch;
    cout << "Найти" << "\n";
    cout << "Введите название минерала: ";
    cin >> MineralSearch;

    for(int i = 0; i <= 50; i++){
        if(dataArr[i].find(MineralSearch) != -1){
            cout << dataArr[i];
            break;
        }
    }


    while(true){
        GetKEY();
        if(KEY[27]){
            break;
        }
    }

}

void deleteFunction(){
    cout << "Удалить" << "\n";
    while (true) {
        GetKEY();
        if (KEY[27]) {
            return;
        }
    }
}


void menuDrawing3(int c){
    cout << "       \n\n\n\t\t\t\t Меню.                               " << "\n\n";
    printf("        \t\t%s    Добавление.         \n", c == 1 ? "=>" : " ");
    printf("        \t\t%s    Поиск.              \n", c == 2 ? "=>" : " ");
    printf("        \t\t%s    Изменение.      \n", c == 3 ? "=>" : " ");
    printf("        \t\t%s    Удаление.             \n", c == 4 ? "=>" : " ");
    printf("        \t\t%s    Выйти.             \n", c == 5 ? "=>" : " ");
}

void menuSwitcher3(int menuNumber){
    switch(menuNumber){
        case 1: { // добавление
                clrscr();
                addFunction();
            break;
        }
        case 2: { //Поиск
                clrscr();
                findFunction();
            break;
        }
        case 3: { // Изменение
                clrscr();
                changeFunction();
            break;
        }
        case 4: { // Удаление
                clrscr();
                deleteFunction();
            break;
        }

        case 5: { // Выйти
                clrscr();
                exitFunction();
            break;
        }
    }
}

void menuSelector3(){
    clrscr();
    int input = 1;
    menuDrawing3(input);
    bool running = true;
    while (running) {
        GetKEY();
        if (KEY[13]) { //pressed enter
            Sleep(30);
            menuSwitcher3(input);
            clrscr();
            Sleep(100);
            break;
        }
        if (KEY[38]) { // pressed down
            input--;
            if (input == 0) {
                input = 5;
            }
            clrscr();
            menuDrawing3(input);
            Sleep(60);
        }
        if (KEY[40]) { // pressed up

            input++;
            if (input == 6) {
                input = 1;
            }
            clrscr();
            menuDrawing3(input);
            Sleep(60);

        }
    }
}

int main(){
    setlocale(LC_ALL, "RUS");
    char row[1024] = {};
    ifstream fin;
    fin.open("data.txt");
    char ch;
    int rowCounter = 0;
    int arrayCounter = 1;
    bool running = true;
    while(running){
        if(!(fin.get(ch))){
            break;
            running = false;
        }

        else if(ch == '#'){
            rowCounter = 0;
            dataArr[arrayCounter] = string(row);
            arrayCounter++;
            for(int i=0;i<=1024;i++)row[i]=0;

            continue;
        }

        row[rowCounter] = ch;
        rowCounter++;
    }

    int input = 1;
    menuDrawing3(input);
    bool running2 = true;
    while(running2){
        menuSelector3();
    }
    return 1;

}
