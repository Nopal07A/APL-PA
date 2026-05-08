#include <iostream>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <atomic>
using namespace std;

#define MAX 100
struct Login{
    string username;
    string password;
};
struct DetailHero{
    string role;
    string kesulitan;
    int level;
    string patch;
};
struct Hero{
    int id;
    string nama;
    bool meta;
    DetailHero detail;
};
struct Spell{
    int id;
    string nama;
};
struct Emblem{
    int id;
    string nama;
};
struct Map{
    int id;
    string nama;
};
struct Favorit{
    string nama;
    string role;
    int level;
    int match;
    float winrate;
};

Hero hero[MAX] = {
    {1,"Ling",true,{"Assassin","Hard",15,"Buff"}},
    {2,"Tigreal",false,{"Tank","Easy",10,"Normal"}},
    {3,"Kagura",true,{"Mage","Hard",14,"Buff"}},
    {4,"Beatrix",false,{"Marksman","Medium",13,"Nerf"}}
};

Spell spell[MAX] = {
    {1,"Flicker"},
    {2,"Retribution"}
};

Emblem emblem[MAX] = {
    {1,"Assassin"},
    {2,"Tank"}
};

Map mapGame[MAX] = {
    {1,"Broken Wall"},
    {2,"Flying Clouds"}
};

// Overloading
string pesan(string nama) {
    string msg = " Anda Keluar Dari Menu : " + nama;
    cout << msg << endl;
    return msg;
}

string pesan(string nama, string status) {
    string msg = " Anda Keluar Dari Menu : " + nama + " , " + status;
    cout << msg << endl;
    return msg;
}

Favorit favorit[MAX];

int jumlahHero = 4;
int jumlahSpell = 2;
int jumlahEmblem = 2;
int jumlahMap = 2;
int jumlahFavorit = 0;

void clearBuffer(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pause(){
    system("pause");
}

void headerHero(){
    cout << "\n========================================================================================================\n";
    cout << "|" << setw(3) << "ID"
         << "|" << setw(20) << "Hero"
         << "|" << setw(15) << "Role"
         << "|" << setw(15) << "Kesulitan"
         << "|" << setw(8) << "Level"
         << "|" << setw(12) << "Patch"
         << "|" << setw(10) << "Meta"
         << " |\n";

    cout << "========================================================================================================\n";
}

bool loginAdmin(Login admin){
    string username, password;
    int kesempatan = 0;
    while(kesempatan < 3){
        cout << "Username : ";
        cin >> username;
        cout << "Password : ";
        cin >> password;
        if(username == admin.username && password == admin.password){
            cout << "\nLogin berhasil!\n";
            return true;
        }
        kesempatan++;
        cout << "Login gagal (" << kesempatan << "/3)\n";
    }
    return false;
}

void lihatHero(){
    if(jumlahHero == 0){
        cout << "Belum ada data hero\n";
        return;
    }

    headerHero();

    for(int i = 0; i < jumlahHero; i++){
        cout << "|"
             << setw(3) << hero[i].id
             << "|" << setw(20) << hero[i].nama
             << "|" << setw(15) << hero[i].detail.role
             << "|" << setw(15) << hero[i].detail.kesulitan
             << "|" << setw(8) << hero[i].detail.level
             << "|" << setw(12) << hero[i].detail.patch
             << "|" << setw(10) << (hero[i].meta ? "Yes" : "No")
             << " |\n";
    }

    cout << "========================================================================================================\n";
}

void tambahHero(){
    Hero baru;
    baru.id = jumlahHero + 1;
    cout << "Nama Hero        : ";
    getline(cin, baru.nama);
    cout << "Role Hero        : ";
    getline(cin, baru.detail.role);
    cout << "Kesulitan Hero   : ";
    getline(cin, baru.detail.kesulitan);
    cout << "Level Hero (1-15): ";
    cin >> baru.detail.level;
    if(cin.fail()){
        clearBuffer();
        throw invalid_argument("Level harus angka!");
    }
    if(baru.detail.level < 1 || baru.detail.level > 15){
        throw out_of_range("Level harus 1-15!");
    }
    clearBuffer();
    baru.detail.patch = "Normal";
    baru.meta = false;
    hero[jumlahHero] = baru;
    jumlahHero++;
    cout << "\nHero berhasil ditambahkan!\n";
}

void updateHero(){
    lihatHero();
    int id;
    cout << "\nMasukkan ID Hero : ";
    cin >> id;
    clearBuffer();
    int index = id - 1;
    if(index < 0 || index >= jumlahHero){
        throw out_of_range("ID tidak ditemukan!");
    }
    cout << "\n1. Nama\n";
    cout << "2. Role\n";
    cout << "3. Kesulitan\n";
    cout << "4. Level\n";
    cout << "5. Patch\n";
    cout << "Pilih : ";
    int pilih;
    cin >> pilih;
    clearBuffer();
    switch(pilih){
        case 1:
            cout << "Nama baru : ";
            getline(cin, hero[index].nama);
            break;
        case 2:
            cout << "Role baru : ";
            getline(cin, hero[index].detail.role);
            break;
        case 3:
            cout << "Kesulitan baru : ";
            getline(cin, hero[index].detail.kesulitan);
            break;
        case 4:
            cout << "Level baru : ";
            cin >> hero[index].detail.level;
            break;
        case 5:
            cout << "Patch baru : ";
            getline(cin, hero[index].detail.patch);

            if(hero[index].detail.patch == "Buff"){
                hero[index].meta = true;
            }
            else{
                hero[index].meta = false;
            }
            break;
    }
    cout << "\nData berhasil diupdate!\n";
}

void hapusHero(){
    lihatHero();
    int id;
    cout << "\nMasukkan ID Hero : ";
    cin >> id;
    int index = id - 1;
    for(int i = index; i < jumlahHero - 1; i++){
        hero[i] = hero[i + 1];
        hero[i].id = i + 1;
    }
    jumlahHero--;
    cout << "\nData berhasil dihapus!\n";
}

void lihatSpell(){
    cout << "===========================\n";
    cout << "|         DATA SPELL      |\n";
    cout << "===========================\n";
    for(int i = 0; i < jumlahSpell; i++){
        cout << spell[i].id << ". "
             << spell[i].nama << endl;
    }
}

void tambahSpell(){
    spell[jumlahSpell].id = jumlahSpell + 1;
    cout << "Nama Spell : ";
    getline(cin, spell[jumlahSpell].nama);
    jumlahSpell++;
    cout << "Spell berhasil ditambahkan!\n";
}

void lihatEmblem(){
    cout << "===========================\n";
    cout << "|       DATA EMBLEM       |\n";
    cout << "===========================\n";
    for(int i = 0; i < jumlahEmblem; i++){
        cout << emblem[i].id << ". "
             << emblem[i].nama << endl;
    }
}

void tambahEmblem(){
    emblem[jumlahEmblem].id = jumlahEmblem + 1;
    cout << "Nama Emblem : ";
    getline(cin, emblem[jumlahEmblem].nama);
    jumlahEmblem++;
    cout << "Emblem berhasil ditambahkan!\n";
}

void lihatMap(){
    cout << "===========================\n";
    cout << "|          DATA MAP       |\n";
    cout << "===========================\n";
    for(int i = 0; i < jumlahMap; i++){
        cout << mapGame[i].id << ". "
             << mapGame[i].nama << endl;
    }
}

void tambahMap(){
    mapGame[jumlahMap].id = jumlahMap + 1;
    cout << "Nama Map : ";
    getline(cin, mapGame[jumlahMap].nama);
    jumlahMap++;
    cout << "Map berhasil ditambahkan!\n";
}

void sortingNama(){
    for(int i = 0; i < jumlahHero - 1; i++){
        for(int j = 0; j < jumlahHero - i - 1; j++){
            if(hero[j].nama > hero[j + 1].nama){
                swap(hero[j], hero[j + 1]);
            }
        }
    }
    cout << "\nSorting nama berhasil!\n";
}

void sortingLevel(){
    for(int i = 0; i < jumlahHero - 1; i++){
        int minIdx = i;
        for(int j = i + 1; j < jumlahHero; j++){
            if(hero[j].detail.level < hero[minIdx].detail.level){
                minIdx = j;
            }
        }
        swap(hero[i], hero[minIdx]);
    }
    cout << "\nSorting level berhasil!\n";
}

void menuSorting(){
    int pilih;
    do{
        system("cls");
        cout << "=============================================\n";
        cout << "|                MENU SORTING               |\n";
        cout << "=============================================\n";
        cout << "|1. Sorting Nama Hero                       |\n";
        cout << "|2. Sorting Level Hero                      |\n";
        cout << "|3. Kembali                                 |\n";
        cout << "=============================================\n";
        cout << "Pilih : ";
        cin >> pilih;
        clearBuffer();
        switch(pilih){
            case 1:
                sortingNama();
                lihatHero();
                pause();
                break;
            case 2:
                sortingLevel();
                lihatHero();
                pause();
                break;
            case 3:
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                pause();
        }
    }while(pilih != 3);
}

int binarySearchNama(string target){
    sortingNama();
    int low = 0;
    int high = jumlahHero - 1;
    while(low <= high){
        int mid = (low + high) / 2;
        if(hero[mid].nama == target){
            return mid;
        }
        else if(hero[mid].nama < target){
            low = mid + 1;
        }
        else{
            high = mid - 1;
        }
    }
    return -1;
}

void cariRole(){
    string role;
    cout << "Masukkan role : ";
    getline(cin, role);
    bool ditemukan = false;
    for(int i = 0; i < jumlahHero; i++){
        if(hero[i].detail.role == role){
            cout << hero[i].nama << endl;
            ditemukan = true;
        }
    }
    if(!ditemukan){
        cout << "Role tidak ditemukan\n";
    }
}

void menuSearching(){
    int pilih;
    do{
        system("cls");
        cout << "=============================================\n";
        cout << "|               MENU SEARCHING              |\n";
        cout << "=============================================\n";
        cout << "|1. Search Hero Nama                        |\n";
        cout << "|2. Search Hero Role                        |\n";
        cout << "|3. Kembali                                 |\n";
        cout << "=============================================\n";
        cout << "Pilih : ";
        cin >> pilih;
        clearBuffer();
        switch(pilih){
            case 1:{
                string cari;
                cout << "Masukkan nama hero : ";
                getline(cin, cari);
                int hasil = binarySearchNama(cari);
                if(hasil != -1){
                    cout << "\nHero ditemukan : "
                         << hero[hasil].nama
                         << endl;
                }
                else{
                    cout << "\nHero tidak ditemukan\n";
                }
                pause();
                break;
            }
            case 2:
                cariRole();
                pause();
                break;
            case 3:
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                pause();
        }
    }while(pilih != 3);
}

void heroMeta(){
    cout << "=============================\n";
    cout << "|           HERO META       |\n";
    cout << "=============================\n";
    for(int i = 0; i < jumlahHero; i++){
        if(hero[i].meta){
            cout << hero[i].nama
                 << " | "
                 << hero[i].detail.patch
                 << endl;
        }
    }
}

void compareHero(){
    lihatHero();
    int a,b;
    cout << "\nPilih Hero 1 : ";
    cin >> a;
    cout << "Pilih Hero 2 : ";
    cin >> b;
    a--;
    b--;
    int powerA = hero[a].detail.level;
    int powerB = hero[b].detail.level;
    if(hero[a].detail.patch == "Buff") powerA += 5;
    if(hero[b].detail.patch == "Buff") powerB += 5;
    if(hero[a].detail.patch == "Nerf") powerA -= 5;
    if(hero[b].detail.patch == "Nerf") powerB -= 5;
    system("cls");
    cout << "=============================\n";
    cout << "|           HASIL           |\n";
    cout << "=============================\n";
    cout << "=== BERDASARKAN HERO POWER ===\n";
    cout << hero[a].nama
         << " Power : "
         << powerA
         << endl;
    cout << hero[b].nama
         << " Power : "
         << powerB
         << endl;
    if(powerA > powerB){
        cout << "Hero lebih kuat : "
             << hero[a].nama
             << endl;
    }
    else if(powerB > powerA){
        cout << "Hero lebih kuat : "
             << hero[b].nama
             << endl;
    }
    else{
        cout << "Kedua hero seimbang\n";
    }
    cout << "\n=== BERDASARKAN TINGKAT KESULITAN ===\n";
    cout << hero[a].nama
         << ", Kesulitan : "
         << hero[a].detail.kesulitan
         << endl;
    cout << hero[b].nama
         << ", Kesulitan : "
         << hero[b].detail.kesulitan
         << endl;
    if(hero[a].detail.kesulitan == "Hard" && hero[b].detail.kesulitan != "Hard"){
        cout << "Hero lebih sulit : "
            << hero[a].nama
            << endl;
    }
    if(hero[b].detail.kesulitan == "Hard" && hero[a].detail.kesulitan != "Hard"){
        cout << "Hero lebih sulit : "
            << hero[b].nama
            << endl;
    }
    if(hero[a].detail.kesulitan == "Medium" && hero[b].detail.kesulitan == "Easy"){
        cout << "Hero lebih sulit : "
             << hero[a].nama
             << endl;
    }
    if(hero[b].detail.kesulitan == "Medium" && hero[a].detail.kesulitan == "Easy"){
        cout << "Hero lebih sulit : "
             << hero[b].nama
             << endl;
    }
    if(hero[a].detail.kesulitan == hero[b].detail.kesulitan){
        cout << "Kedua hero memiliki tingkat kesulitan yang sama\n";
    }
}

void tambahFavorit(){
    lihatHero();
    int pilih;
    cout << "\nPilih Hero Favorit : ";
    cin >> pilih;
    pilih--;
    favorit[jumlahFavorit].nama = hero[pilih].nama;
    favorit[jumlahFavorit].role = hero[pilih].detail.role;
    favorit[jumlahFavorit].level = hero[pilih].detail.level;
    favorit[jumlahFavorit].match = rand() % 100;
    favorit[jumlahFavorit].winrate = rand() % 100;
    jumlahFavorit++;
    cout << "\nFavorit berhasil ditambahkan!\n";
}

void updateRealtimeFavorit(){
    for(int i = 0; i < jumlahFavorit; i++){
        favorit[i].match += rand() % 5;
        favorit[i].winrate += (rand() % 11 - 5);
        if(favorit[i].winrate < 0)
            favorit[i].winrate = 0;
        if(favorit[i].winrate > 100)
            favorit[i].winrate = 100;
    }
}

void datafavorit() {
    cout << "====================================\n";
        cout << "|            HERO FAVORIT          |\n";
        cout << "====================================\n";
        for(int i = 0; i < jumlahFavorit; i++){
            cout << i + 1 << ". "
                 << favorit[i].nama
                 << " | "
                 << favorit[i].role
                 << " | Match : "
                 << favorit[i].match
                 << " | WR : "
                 << favorit[i].winrate
                 << "%\n";
        }
}

void lihatFavorit(){
    atomic<bool> keluar(false);
    thread inputThread([&](){
        string cmd;
        while(getline(cin, cmd)){
            if(cmd == "e"){
                keluar = true;
                break;
            }
        }
    });

    while(!keluar){
        system("cls");
        datafavorit();
        cout << "\nKetik e lalu Enter untuk kembali ke Menu User.\n";
        cout << "Update setiap 10 detik...\n";
        for(int t = 0; t < 100 && !keluar; t++){
            this_thread::sleep_for(chrono::milliseconds(100));
        }
        if(!keluar){
            updateRealtimeFavorit();
        }
    }
    if(inputThread.joinable()) inputThread.join();
}

void hapusFavorit(){
    int no;
    datafavorit();
    cout << "Pilih favorit yang dihapus : ";
    cin >> no;
    for(int i = no - 1; i < jumlahFavorit - 1; i++){
        favorit[i] = favorit[i + 1];
    }
    jumlahFavorit--;
    cout << "\nHero favorit berhasil dihapus!\n";
}

void menuCreate(){
    int pilih;
    do{
        system("cls");
        cout << "==================================\n";
        cout << "|            MENU CREATE         |\n";
        cout << "==================================\n";
        cout << "|1. Create Hero                  |\n";
        cout << "|2. Create Spell                 |\n";
        cout << "|3. Create Emblem                |\n";
        cout << "|4. Create Map                   |\n";
        cout << "|5. Kembali                      |\n";
        cout << "==================================\n";
        cout << "Pilih : ";
        cin >> pilih;
        clearBuffer();
        switch(pilih){
            case 1:
                tambahHero();
                pause();
                break;
            case 2:
                tambahSpell();
                pause();
                break;
            case 3:
                tambahEmblem();
                pause();
                break;
            case 4:
                tambahMap();
                pause();
                break;
        }
    }while(pilih != 5);
}

void menuHero(){
    int pilih;
    do{
        system("cls");
        cout << "================================================\n";
        cout << "|                 MENU HERO                    |\n";
        cout << "================================================\n";
        cout << "|1. Lihat Hero                                 |\n";
        cout << "|2. Fitur Sorting                              |\n";
        cout << "|3. Fitur Searching                            |\n";
        cout << "|4. Kembali                                    |\n";
        cout << "================================================\n";
        cout << "Pilih : ";
        cin >> pilih;
        clearBuffer();
        switch(pilih){
            case 1:
                lihatHero();
                pause();
                break;
            case 2:
                menuSorting();
                break;
            case 3:
                menuSearching();
                break;
            case 4:
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                pause();
        }
    }while(pilih != 4);
}

void menuRead(){
    int pilih;
    do{
        system("cls");
        cout << "================================\n";
        cout << "|            MENU READ         |\n";
        cout << "================================\n";
        cout << "|1. Read Hero                  |\n";
        cout << "|2. Read Spell                 |\n";
        cout << "|3. Read Emblem                |\n";
        cout << "|4. Read Map                   |\n";
        cout << "|5. Kembali                    |\n";
        cout << "================================\n";
        cout << "Pilih : ";
        cin >> pilih;
        clearBuffer();
        switch(pilih){
            case 1:
                menuHero();
                pause();
                break;
            case 2:
                lihatSpell();
                pause();
                break;
            case 3:
                lihatEmblem();
                pause();
                break;
            case 4:
                lihatMap();
                pause();
                break;
        }
    }while(pilih != 5);
}

void menuFav() {
    int pilih;
    do {
        system("cls");
        cout << "=============================================\n";
        cout << "|              MENU FAVORIT                 |\n";
        cout << "=============================================\n";
        cout << "|1. Buat Hero Favorit                       |\n";
        cout << "|2. Lihat Hero Favorit                      |\n";
        cout << "|3. Hapus Hero Favorit                      |\n";
        cout << "|4. Kembali                                 |\n";
        cout << "=============================================\n";
        cout << "Pilih : ";
        cin >> pilih;
        clearBuffer();
        switch(pilih){
            case 1:
                system("cls");
                tambahFavorit();
                pause();
                break;
            case 2:
                system("cls"); 
                lihatFavorit();
                break;
            case 3:
                system("cls");
                hapusFavorit();
                pause();
                break;
            case 4:
                system("cls");  
                pesan("favorit", "Kembali ke Menu User");
                pause();
                break;
            default:
                cout << "Pilihan tidak valid!\n";
                pause();
        }
    } while(pilih != 4);
}

void menuAdmin(){
    int pilih;
    do{
        system("cls");
        cout << "=============================================\n";
        cout << "|                   MENU ADMIN              |\n";
        cout << "=============================================\n";
        cout << "|1. Create Data                             |\n";
        cout << "|2. Read Data                               |\n";
        cout << "|3. Update Hero                             |\n";
        cout << "|4. Delete Hero                             |\n";
        cout << "|5. Keluar                                  |\n";
        cout << "=============================================\n";
        cout << "Pilih : ";
        cin >> pilih;
        clearBuffer();
        switch(pilih){
            case 1:
                menuCreate();
                break;
            case 2:
                menuRead();
                break;
            case 3:
                updateHero();
                pause();
                break;
            case 4:
                hapusHero();
                pause();
                break;
            case 5:
                pesan("admin");
                pause();
                break;
        }
    }while(pilih != 5);
}

void menuUser(){
    int pilih;
    do{
        system("cls");
        cout << "=============================================\n";
        cout << "|                  MENU USER                |\n";
        cout << "=============================================\n";
        cout << "|1. Lihat Hero                              |\n";
        cout << "|2. Hero Meta                               |\n";
        cout << "|3. Cari Berdasarkan Role                   |\n";
        cout << "|4. Compare Hero                            |\n";
        cout << "|5. Hero Favorit                            |\n";
        cout << "|6. Keluar                                  |\n";
        cout << "=============================================\n";
        cout << "Pilih : ";
        cin >> pilih;
        clearBuffer();
        switch(pilih){
            case 1:
                system("cls");
                lihatHero();
                pause();
                break;
            case 2:
                system("cls");
                heroMeta();
                pause();
                break;
            case 3:
                system("cls");
                cariRole();
                pause();
                break;
            case 4:
                system("cls");
                compareHero();
                pause();
                break;
            case 5:
                system("cls");
                menuFav();
                pause();
                break;
            case 6:
                system("cls");
                pesan("user");
                pause();
                break;
        }
    }while(pilih != 6);
}


struct User{
    string username;
    string password;
};
User userList[MAX];
int jumlahUser = 0;
void registrasiUser(){
    User baru;
    cout << "=== REGISTRASI USER ===\n";
    cout << "Username : ";
    cin >> baru.username;
    cout << "Password : ";
    cin >> baru.password;

    for(int i = 0; i < jumlahUser; i++){
        if(userList[i].username == baru.username){
            cout << "Username sudah digunakan!\n";
            return;
        }
    }
    userList[jumlahUser++] = baru;
    cout << "Registrasi berhasil!\n";
}

bool loginUser(){
    string username, password;
    int kesempatan = 0;
    while(kesempatan < 3){
        cout << "=== LOGIN USER ===\n";
        cout << "Username : ";
        cin >> username;
        cout << "Password : ";
        cin >> password;

        for(int i = 0; i < jumlahUser; i++){
            if(userList[i].username == username &&
               userList[i].password == password){
                cout << "Login berhasil!\n";
                return true;
            }
        }
        kesempatan++;
        cout << "Username atau Password salah! ("
             << kesempatan << "/3)\n";
        pause();
        system("cls");
    }
    cout << "Gagal login 3 kali!\n";
    pause();
    return false;
}

int main(){
    srand(time(0));
    Login admin = {"admin","01123"};
    int pilih;
    do {
        system("cls");
        cout << "====================================================\n";
        cout << "|  SISTEM MANAJEMEN HERO META PATCH UPDATE MOBILE  |\n";
        cout << "|            MOBILE LEGENDS : BANG BANG            |\n";
        cout << "====================================================\n";
        cout << "|1. Admin                                          |\n";
        cout << "|2. Login User                                     |\n";
        cout << "|3. Registrasi User                                |\n";
        cout << "|4. Keluar                                         |\n";
        cout << "====================================================\n";
        cout << "Pilih : ";
        cin >> pilih;
        clearBuffer();
        switch(pilih){
            case 1:
                if(loginAdmin(admin)){
                    menuAdmin();
                }
                break;
            case 2:
                if(loginUser()){
                    menuUser();
                }
                break;
            case 3:
                registrasiUser();
                pause();
                break;
            case 4:
                system("cls");
                cout << "Terima kasih telah menggunakan sistem ini.\n";
                break;
            default:
                cout << "\n==System massage==\n";
                cout << "Pilihan gk ada.\n";
                pause();
        }
    } while(pilih != 4);

    return 0;
}