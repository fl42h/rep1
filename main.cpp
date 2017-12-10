///============================================================================
/// Name        : newmain.cpp
/// Author      : Tomáš Jedlička
/// Version     : 10.69
/// Copyright   : Free 4 All
/// Description :
///============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
#include <iomanip>


using namespace std;
///inicializace funkci
char overeni_menu(char);                 ///overeni vyberu z menu (volba "r" nebo "v"
bool overeni_den_proti_mesici(int, int); //overení jestli má mesíc 30 nebo 31 a jestli je datum správně
bool overeni_rok(int); ///rozmezí 1800 až 2200 let našeho letopočtu
bool overeni_mesic(int); /// rozmenzí 1 až 12
bool overeni_kapacita(int); /// rozmezí 1 až 100
bool overeni_cena(int); ///rozmezi 1 až 30 mil.
bool overeni_id(int); /// rozmezí 1 až 100
int chyb_hlaska(string); /// nový vstup


int main() {
   ///pomocne globalni promenne
    string radek;
    char menu;
    const char separator    = ' ';


    ///uvitani
    cout << "Vita vas program Rezervace mistnosti" << endl;

	cout << "------SEZNAM MISTNOSTI--------" <<  endl;

    /// otevření souboru pro cteni
    ifstream read_stream("pokoje.csv", ios::in);
    ///overeni jestli je soubor otevren
    if(read_stream.fail()) {
        cout << "Soubor pokoje.csv nelze otevrít" <<endl;
        exit(1);
    }

    ///vypsani legendy tabulky
    cout << right << setw(5) << setfill(separator) << "ID" << right << setw(6) << setfill(separator) << "Patro" << right << setw(15) << setfill(separator)  << "Cislo pokoje" <<  right << setw(15) << setfill(separator) << "Kapacita " << right << setw(15) << setfill(separator) << "Cena" << endl;
    ///cyklus na parsovani
    while (getline(read_stream, radek)) {
        ///lokalní promenne
        int id;
        int patro;
        int cislo_pokoje;
        int kapacita;
        int cena;
            ///vlozeni retezce
            istringstream iss(radek);
            ///overeni formatu radku
            if (!(iss >> id >> patro >> cislo_pokoje >> kapacita >> cena)) { break; }
            ///vyspani dat do tabulky
            cout << right << setw(5) << setfill(separator) << id << right << setw(6) << setfill(separator) << patro << right << setw(15) << setfill(separator)  << cislo_pokoje <<  right << setw(15) << setfill(separator) << kapacita << right << setw(15) << setfill(separator) << cena << "Kc" << endl;
    }
            /// Ukončení  čtení
            read_stream.close();

    cout << "-----------------------------------------" << endl;
    cout << "Pro  Vyhledavac napiste v " << endl;
    cout << "Pro  Rezervace napiste r " << endl;
    cout << "Pro export nejblizich rezervaci dane mistnosti napiste e " << endl;
    cin >> menu;

    ///volba v menu
	if(overeni_menu(menu) == 'v')  {
           ///label pro goto
            hledej:
                        int hledej_cena;
                        int hledej_kapacita;
                        int datum_d;
                        int datum_m;
                        int datum_r;
                        string radek;
                        string carka;

                        ///VYHLEDÁVANÍ

                         cout << "-------VYHLEDAVANI-------" <<  endl;

                         cout << "-- Zadej maximalni cenu: ";
                         cin >> hledej_cena;
                         ///overeni ceny
                         while(!(overeni_cena(hledej_cena))) {
                             string druh = "cena";
                             ///funkce pro chybovou hlasku, vrati novou hodnotu
                             hledej_cena = chyb_hlaska(druh);
                         }

                         cout << "-- Zadej kapacitu (pocet osob): ";
                         cin >> hledej_kapacita;
                         ///overeni kapacity
                         while(!(overeni_kapacita(hledej_kapacita))) {
                             string druh = "kapacita";
                             hledej_kapacita = chyb_hlaska(druh);
                         }

                         cout << " -- Zadej pozadovany den (dd.mm.rrrr postupne s mezerou): ";
                         cin >> datum_d >> datum_m >> datum_r;
                         /*! overeni data */
                         while(!(overeni_rok(datum_r))) {
                             string druh = "rok";
                             datum_r = chyb_hlaska(druh);
                         }
                         while(!(overeni_mesic(datum_m))) {
                             string druh = "mesic";
                             datum_m = chyb_hlaska(druh);
                         }
                         while(!(overeni_den_proti_mesici(datum_m, datum_d))) {
                             string druh = "den";
                             datum_d = chyb_hlaska(druh);
                         }




     /*! otevreni pro ctení ze souboru */
                        /*! cteni ze souboru */
                         ifstream pokoje_hled("pokoje.csv", ios::in);
                         /*! overeni otevreni souboru */
                         if(pokoje_hled.fail()) {
                             cout << "soubor 'pokoje.csv' nelze otevrit" << endl;
                             exit(1);
                         }
                         /*! cteni ze souboru */
                         ifstream rezervace_hled("rezervace_data.csv", ios::in);
                         /*! overeni otevreni souboru */
                         if(rezervace_hled.fail()) {
                             cout << "soubor 'rezervace_data.csv' nelze otevrit" << endl;
                             exit(1);
                         }

                         cout << right << setw(5) << setfill(separator) << "ID" << right << setw(6) << setfill(separator) << "Patro" << right << setw(14) << setfill(separator)  << "Cislo pokoje" <<  right << setw(11) << setfill(separator) << "Kapacita " << right << setw(12) << setfill(separator) << "Cena" << endl;
                                /*! cyklus na cteni radku */
                                 while(getline(pokoje_hled, radek)) {
                                        /*! lokalni promenne */
                                        int id;
                                        int patro;
                                        int cislo_pokoje;
                                        int kapacita;
                                        int cena;
                                        /*! parsovani retezce */
                                        istringstream iss2(radek);
                                        if (!(iss2 >> id >> patro >> cislo_pokoje >> kapacita >> cena)) { break; }
                                        if(cena <= hledej_cena and kapacita >= hledej_kapacita) {
                                                cout << right << setw(5) << setfill(separator) << id << right << setw(6) << setfill(separator) << patro << right << setw(15) << setfill(separator)  << cislo_pokoje <<  right << setw(15) << setfill(separator) << kapacita << right << setw(15) << setfill(separator) << cena << "Kc" << endl;
                                        }

                                 }
                                /*! ukonceni cteni */
                                rezervace_hled.close();
                                pokoje_hled.close();

                              cout << "------------------------------------------" << endl;
                              cout << "pokud chces hledat znovu napis v " << endl;
                              cout << "pro pokracovani v rezervaci r " << endl;
                              cout << "pro export rezervací dané mistnosti e " << endl;
                              cout << "pro konec napis k " << endl;
                              cin >> menu;
                              /*! overeni prubehu menu */
                              if(overeni_menu(menu) == 'v') {
                                  goto hledej;
                              }
                              /*! ukonceni programu */
                              if(overeni_menu(menu) == 'k') {
                                  exit(0);
                              }
        }

                             /*! rezervace */
                             if(overeni_menu(menu) == 'r') {
                             /*! label pro goto */
                             rezerv:
                             int rez_id;
                             int datum_d;
                             int datum_m;
                             int datum_r;
                             string line;
                             int id, patro, cislo_pokoje, cena, kapacita;


                                 cout << "-------REZERVACE-------" <<  endl;

                                 cout << "Zadejte ID mistnosti: ";
                                 cin >> rez_id;
                                             while(!(overeni_id(rez_id))){
                                                 string druh = "id";
                                                 rez_id = chyb_hlaska(druh);
                                             }

                                              cout << " -- Zadej datum  (dd.mm.rr postupne): ";
                                 cin >> datum_d >> datum_m >> datum_r;
                                             while(!(overeni_rok(datum_r))) {
                                                 string druh = "rok";
                                                 datum_r = chyb_hlaska(druh);
                                             }
                                             while(!(overeni_mesic(datum_m))) {
                                                 string druh = "mesic";
                                                 datum_m = chyb_hlaska(druh);
                                             }
                                             while(!(overeni_den_proti_mesici(datum_m, datum_d))) {
                                                 string druh = "den";
                                                 datum_d = chyb_hlaska(druh);
                                             }


                                             /*!otevreni cteni*/
                                             ifstream rezervace_dostupnost("rezervace_data.csv", ios::in);
                                             if(rezervace_dostupnost.fail()) {
                                                 cout << "soubor nelze otevrit" << endl;
                                                 exit(1);
                                             }
                                             while(getline(rezervace_dostupnost, line)){
                                                 istringstream iss3(line);
                                                 int id, dd, mm, rrrr;
                                                 if(!(iss3 >> id >> dd >> mm >> rrrr)){break;}
                                                 if(id == rez_id and dd == datum_d and mm == datum_m and rrrr == datum_r){
                                                     cout << "tento pokoje je na toto datum obsazen zvolte jine datum nebo pokoj" << endl;
                                                     iss3.clear();
                                                     goto rezerv;
                                                 }
                                             }


                                             rezervace_dostupnost.close();


                                             ifstream pokoje_info("pokoje.csv");
                                             if(pokoje_info.fail()) {
                                                 cout << "soubor 'pokoje.csv' nelze otevřít" << endl;
                                                 exit(1);
                                             }
                                                       while(getline(pokoje_info, line)){
                                                            istringstream iss(line);
                                                            if(!(iss >> id >> patro >> cislo_pokoje >> kapacita >> cena)) {break;}
                                                            if(id == rez_id) {

                                 cout << "Vase rezervace " << endl;
                                 cout << "ID místnosti: " << id << endl;
                                 cout << "Patro: "<< patro << endl;
                                             cout << "Cislo pokoje. " << cislo_pokoje << endl;
                                 cout << "Konecna cena: " << cena << "Kc" << endl;
                                 cout << "Datum: " << datum_d << "/" << datum_m << "/" << datum_r << endl;

                                     pokoje_info.close();
                                ofstream rezervace_data ("rezervace_data.csv", ios::out | ios::app);
                                            if(rezervace_data.fail()) {
                                                cout << "Do souboru nelze 'rezervace_data.csv' zapsat" <<endl;
                                                /*! ukonceni s chybou */
                                                exit(1);
                                            }
                                rezervace_data << rez_id << " " << datum_d << " " << datum_m << " " << datum_r << endl;
                                rezervace_data.close();
                                cout << "Rezervace vytvorena" << endl;
                                            /*! vymazani string streamu */
                                            iss.clear();
                                                            }
                                                       }
                                                  cout << "-------------------------------------" << endl;
                                                  cout << "pokud chces rezervovat znovu napis r " << endl;
                                                  cout << "pokud chces hledat znovu napis v " << endl;
                                                  cout << "pro export rezervací dané mistnosti e " << endl;
                                                  cout << "pro konec napis k " << endl;
                                                  cin >> menu;
                                                  if(overeni_menu(menu) == 'r') {
                                                      goto rezerv;
                                                  }
                                                  if(overeni_menu(menu) == 'v') {
                                                      goto hledej;
                                                  }
                                                  if(overeni_menu(menu) == 'k') {
                                                      exit(0);
                                                  }
                        }


                        /*! export do HTML */
                        if(overeni_menu(menu) == 'e') {
                            /*! label pro export */
                            expo:

                            string cest;
                            int get_id;
                            string line;
                            cout << "----------------------------" << endl;
                            cout << "Export rezervaci do HTML" << endl;
                            cout << "zadejte umístěni souboru(př. c:/cesta/nazev.html  ): ";
                            cin >> cest;
                            cout << "Zadejte id místnosti: ";
                            cin >> get_id;
                            while(!(overeni_id(get_id))) {
                                string druh = "id";
                                get_id = chyb_hlaska(druh);
                            }

                            ifstream rezervace("rezervace_data.csv", ios::in);
                            if(rezervace.fail()) {
                                cout << "soubor 'rezervace_data.csv' nelze otevrít" << endl;
                                exit(1);
                            }
                            /*! vytvoreni a vypis do HTML */
                            ofstream html(cest, ios::out);
                            /*! hlavicka html */
                            html << "<html><head><title>Rezervace mistnosti ID: " << get_id << "</title></head><body>" << endl;
                            html << "<p>Tabulka Rezervaci</p>" << endl;
                            html << "<table>" << endl;
                            html << "<tr><th><b>ID</b></th><th><b>Den</b></th><th><b>Mesic</b></th><th><b>Rok</b></th></tr>" << endl;
                            /*! format v html */
                            while(getline(rezervace, line)) {
                                int id, dd, mm, rrrr;
                                istringstream iss(line);
                                if(!(iss >> id >> dd >> mm >> rrrr)) {break;}
                                if(id == get_id) {
                                    /*! export */
                                    html << "<tr><td>" << id << "</td><td>" << dd << "</td><td>" << mm << "</td><td>" << rrrr << "</td></tr>" << endl;
                                }
                            /*! hlaska o usmesnem vytvoreni */
                            }   cout << "soubor uspesne vytvoren v: " << cesta << endl;

                            html << "</table>" << endl;
                            html << "</body></html>" << endl;
                            /*! konec tela html souboru */
                            /*! ukonceni cteni */
                            html.close();

                                                  cout << "-------------------------------------" << endl;
                                                  cout << "pokud chces rezervovat znovu napis r " << endl;
                                                  cout << "pokud chces hledat znovu napis v " << endl;
                                                  cout << "pokud chces exportovat znovu napis e " << endl;
                                                  cout << "pokud chces ukoncit program napis k " << endl;
                                                  cin >> menu;
                                                  /*!volba*/
                                                  if(overeni_menu(menu) == 'r') {
                                                      goto rezerv;
                                                  }
                                                  if(overeni_menu(menu) == 'v') {
                                                      goto hledej;
                                                  }
                                                  if(overeni_menu(menu) == 'e') {
                                                      goto expo;
                                                  }
                                                  if(overeni_menu(menu) == 'k') {
                                                      exit(1);
                                                  }

                        }

	return 0;
}

/*! funkcece pro overeni a chybove hlasky */
char overeni_menu(char menu) {
    if(menu != 'v' and menu != 'r' and menu != 'e' and menu != 'k') {
        cout << "Zadali jste spatne" << endl;
        cin >> menu;
        return(menu);
    }
    else return(menu);
};
bool overeni_den_proti_mesici(int mesic, int den) {
   if((!cin.fail())) {
    if(overeni_mesic(mesic)) {
            if(den <= 31 and den >= 1) {
                return(true);
            }
            if((den == 31) and (mesic == 1 or 3 or 5 or 7 or 8 or 10 or 12)) {
                return(true);
            }
            if((den > 28) and (mesic == 2)) {
                return(true);
            }}
        cin.clear();
        cin.ignore();
        return(false);
        }
};

bool overeni_rok(int rok) {
    if(!(cin.fail())) {
    if(rok <= 2200 and rok >= 1800) {
        return(true);
    }}
    cin.clear();
    cin.ignore();
    return(false);
};

bool overeni_mesic(int mesic) {
    if(!(cin.fail())) {
    if(mesic <= 12 and mesic >= 1) {
        return(true);
    }}
    cin.clear();
    cin.ignore();
    return(false);
};

bool overeni_kapacita(int kapacita) {
    if(!(cin.fail())) {
    if(kapacita <= 100 and kapacita >= 1){
        return(true);
    }}
    cin.clear();
    cin.ignore();
    return(false);
};

bool overeni_cena(int cena) {
    if(!(cin.fail())) {
    if(cena <= 30000000 and cena >= 1) {
        return(true);
    }}
    cin.clear();
    cin.ignore();
    return(false);
};

bool overeni_id(int id) {
    if(!(cin.fail())) {
    if(id <= 100 and id >= 1){
        return(true);
    }}
    cin.clear();
    cin.ignore();
    return(false);
};

int chyb_hlaska(string druh) {
    int nove_data;
    cout << "zadali jste spatne" << " " << druh << " " << "prosim zadejte znovu : ";
    cin >> nove_data;
    return(nove_data);
};


