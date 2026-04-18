//#include path 
   // <nlohmann/json.hpp>
#include<iostream>
#include<ctime>
#include<vector>
#include<string>
#include<map>
#include<fstream>
#include"nlohmann/json.hpp"
using json = nlohmann::json;
using namespace std;
//1Человек 2Эльф 3Полу-орк 4Дварф 5Хафлинг 6Гоблин
//1боец 2Жрец 3Вор 4Маг 5Рыц свят ид 6Варлок 7Ведьма 8Гладиатор 9Самурай 10Видящий

struct Character{
    int hp=0;
    string name;
    int Strength=0;
    int Dexterity=0;
    int Constit=0;
    int Intelligence=0;
    int Wisdom=0;
    int Charisma=0;

    int race=0;
    int clase=0;
    int God = 0;

    string ClassTal;
    vector<string> ClassDop;
    string ClassName;

    string RaceName;
    string RaceBonus;

    vector<string> GodTal;

    Character(string name){
        this->name = name;
    }

};

struct Race{
    string Name;
    string Bonus;
};

struct Class{
    string Name;
    vector<string> dop;//присваевается все
    vector<string> tal;//выбираешь что выпадет
};

struct GodTal{
    int NumTal;
    vector<string> GodTal;
};
//1Человек 2Эльф 3Полу-орк 4Дварф 5Хафлинг 6Гоблин
map<int, Race> RACES = {
    {1,{"Человек","Амбици: Получаешь один доп ролл талантов на первом уровне"}},
    {2,{"Эльф","+1 к попаданию дальнобойным оружием/сотворением заклинания"}},
    {3,{"Полуорк","+1 на попадание и урон с ближнибойным оружием"}},
    {4,{"Дварф","Крепкий: Каждый раз поднимая уровень перебрасываешь хп  с премуществом"}},
    {5,{"Хафлинг","Скрытность: один раз в отдых можешь на 3 раунда становитья невидимым "}},
    {6,{"Гоблин","Обостренные чувства: нельзя застать в расплох"}}

};
//1боец 2Жрец 3Вор 4Маг 5Рыц свят ид 6Варлок 7Ведьма 8Гладиатор 9Самурай 10Видящий
map<int, Class> CLASSES = {//сделать плюсы из допов (10 total)
    {1,{"Боец",{"Мул: Если твое значение конституции >0 это значение прибаляется к слотам в сумке 2",
                "Мастер: владения оружием: в начале выбиратся оружие к которому +1 к попаданию и урону + половина уровня (округлять вниз)",
                "Упорство: Выберите Силу или Ловкость. Делай броски с премуществом с этим показателем (не боевые)"},
                    {"Увеличьте мастерство владения оружием, добавив один дополнительный тип оружия",
                    "+1 к урону от оружий ближнего и дальнего боя",
                    "+2 к силе, ловкости или конституции",
                    "Выберите один вид брони. Вы получаете +1 к ЗЩ от этих доспехов"}}},
    {2,{"Жрец",{"Знание заклинания Изгнание нежити",
                "Служение божеству: выбери божество, которому хочешь служить, у тебя будет иметься его символика",
                "Каждый раз поднимая уровень ты можешь выбрать еще одно заклинание жреца",
                "Сотворение заклинаний: чтобы сотворить заклинание нужно выкинуть >10+тир заклинания. Кидаяется 1d20 + Мудрость"},
                    {"Получите преимущество при сотворении одного известного вам заклинания",
                    "+1 к попаданию атакам ближнего или дальнего боя",
                    "+1 к проверкам на каст заклинаний жреца",
                    "+2 к характеристике Силы или Мудрости"}}},
    {3,{"Вор",{"Удар из под тишка: Если ты бьешь врага который тебя не заметил, то ты кидаешь ещ еодин кубик урона типа оружия",
                "Воровство. Вы искусны в воровских навыках и имеете необходимые инструменты спрятанные при себе (они не занимают слоты снаряжения)",
                "Вы обучены следующим заданиям и имеете преимущество на любые связанные проверки:Лазание,Подкрадывание и прятки,Применение маскировки,Поиск и обезвреживание ловушек,Деликатные задачи, такие как чисткакарманов и вскрытие замков"},
                    {"Получите преимущество при бросках инициативы (перебросьте, если есть дубликат)",
                    "Ваш Удар в спину наносит +1 кубик урона",
                    "2 к характеристикам Силы, Ловкости или Харизмы",
                    "+1 к попаданию атакам ближнего и дальнего боя"}}},
};

map<int, GodTal> GODTAL = {

};

int roll1d6(){
    return rand()%6+1;
}

int choose(const vector<string>& items) {
    for (int i=0; i<items.size(); i++){
        cout << i+1 << ". " << items[i] << endl;
    }
    cout<<items.size()+1<<". "<<"Рандом"<<endl;
    int x;
    cin >> x;
    if (x == items.size()+1){
        x = rand() % items.size()+1;
    }
    return x-1;
}

void chooseRace(Character &c) {
    cout << "\nВыберите расу:\n";
    vector<string> list;
    for (auto &r : RACES) list.push_back(r.second.Name);
    int r = choose(list) + 1;

    c.race = r;

    c.RaceName = RACES[r].Name;
    c.RaceBonus = RACES[r].Bonus;
}

void chooseClass(Character &c) {
    cout << "\nВыберите класс:\n";
    vector<string> list;
    for (auto &cl : CLASSES) list.push_back(cl.second.Name);

    int k = choose(list) + 1;
    c.clase = k;

    c.ClassName = CLASSES[k].Name;
    c.ClassDop = CLASSES[k].dop;
}

void generateTalent(Character &c) {
    auto &cls = CLASSES[c.clase];

    int roll = roll1d6()+roll1d6();
    int idx = 0;

    if (roll == 2) idx = 0;
    else if (roll >=3 && roll <=6) idx = 1;
    else if (roll >=7 && roll <=9) idx = 2;
    else if (roll >=10 && roll <=11) idx = 3;
    else if (roll == 12) {
        cout << "Выпало 12! Выберите талант вручную:\n";
        idx = choose(cls.tal);
    }

    c.ClassTal = cls.tal[idx];
}

void rollHp(Character &c){
    if (c.clase == 1 || 8){
        c.hp = rand()%8 + 1;
    } 
    else if (c.clase == 2 || 5 || 6 || 9 || 10){
        c.hp = rand()%6 + 1;
    } 
    else if (c.clase == 3 || 4 || 7){
        c.hp = rand()%4 + 1;
    }
    if (c.race == 4){c.hp+=2;}
}

void showStats(Character &c){
    cout<<"1.Str: "<<c.Strength<<"\t2.Dex: "<<c.Dexterity<<"\t3.Con: "<<c.Constit<<endl<<
    "4.Int: "<<c.Intelligence<<"\t5.Wis: "<<c.Wisdom<<"\t6.Char: "<<c.Charisma<<endl;
}

void RollStats(Character &c){
    vector<string> stat = {"Str","Dex","Con","Int","Wis","Char"};
    for (int i = 0;i<6;i++){
        int chois;
        int a = (rand()%6+1)+(rand()%6+1)+(rand()%6+1);
        cout<<"Вам выпала "<<a<<", куда хотите распределить"<<endl;
        for (int j = 0; j < stat.size(); j++){
            cout<<j+1<<"."<<stat[j]<<"\t";
        }
        cout<<endl;
        cin>>chois;

        if (chois < 1 || chois > stat.size()) {
        cout << "Неверный ввод!" << endl;
        i--;
        continue;
        }
        if (stat[chois-1] == "Str") c.Strength = a;
        else if (stat[chois-1] == "Dex") c.Dexterity = a;
        else if (stat[chois-1] == "Con") c.Constit = a;
        else if (stat[chois-1] == "Int") c.Intelligence = a;
        else if (stat[chois-1] == "Wis") c.Wisdom = a;
        else if (stat[chois-1] == "Char") c.Charisma = a;
        stat.erase(stat.begin() + chois-1);
    }
    showStats(c);
}

void ReRollStat(Character &c){
    cout<<"Что вы хотите изменить?(max 2 stat)"<<endl;
    int a;
    cin>>a;
    int b = (rand()%6+1)+(rand()%6+1)+(rand()%6+1);
    switch(a){
        case 1:
            cout<<"Str = "<<b<<endl;
            c.Strength = b;
            break;
        case 2:
            cout<<"Dex = "<<b<<endl;
            c.Dexterity = b;
            break;
        case 3:
            cout<<"Con = "<<b<<endl;
            c.Constit = b;
            break;
        case 4:
            cout<<"Int = "<<b<<endl;
            c.Intelligence = b;
            break;
        case 5:
            cout<<"Wis = "<<b<<endl;
            c.Wisdom = b;
            break;
        case 6:
            cout<<"Char = "<<b<<endl;
            c.Charisma = b;
            break;
        default:
            cout<<"Неверный ввод"<<endl;
            break;
    }
    cout<<endl;
}

int showHP(Character &c){
    return c.hp;
}

void showHero(Character &c){
    cout<<endl;
    cout<<c.name<<"\t"<<c.ClassName<<","<<c.RaceName<<"\tHP="<<c.hp<<endl;
    showStats(c);
    cout<<"Таланты: "<<c.ClassTal<<endl<<"----------"<<endl;
    for (int i = 0; i < sizeof(c.ClassDop);i++){
        cout<<c.ClassDop[i]<<endl;
    }
    cout<<"----------"<<endl;
    cout<<c.RaceBonus<<endl<<"----------"<<endl;
}

void getCharacter(){
    
}

void saveCharacter(const Character& c, const string& filename) {
    json j;
    j["name"] = c.name;
    j["hp"] = c.hp;
    j["Strength"] = c.Strength;
    j["Dexterity"] = c.Dexterity;
    j["Constit"] = c.Constit;
    j["Intelligence"] = c.Intelligence;
    j["Wisdom"] = c.Wisdom;
    j["Charisma"] = c.Charisma;
    j["race"] = c.race;
    j["clase"] = c.clase;
    j["God"] = c.God;
    j["ClassTal"] = c.ClassTal;
    j["ClassDop"] = c.ClassDop;
    j["RaceName"] = c.RaceName;
    j["RaceBonus"] = c.RaceBonus;

    ofstream out(filename);
    out << j.dump(4);
}

void Go(Character &c){
    RollStats(c);
    for (int i = 0; i<2;i++){
        char var = 'n';
        cout<<"Хотите что то изменить? y/n(def: n): ";
        cin>>var;
        if (var == 'y'){ReRollStat(c);}
        else {break;}
    }
    chooseClass(c);
    chooseRace(c);
    generateTalent(c);
    rollHp(c);
    showHero(c);
}


int main(){
    setlocale(LC_ALL,"ru");
    srand(time(NULL));
    int a;
    cout<<"Что вы хотите сделать?"<<endl<<
    "1.Создать персонажа"<<\t<<"2.Улучшить персонажа"
    cin>>a;
    if (a == 1){
        string b;
        cout<<"Введите имя персонажа"<<endl;
        getline(cin,b);
        Character hero(b);
        Go(hero);
    }
    if (a == 2){

    }
    else{cout<<"Неверный ввод"<<endl;}
    saveCharacter(hero,hero.name);

    return 0;
}
