/* Hitori
 *
 * Kuvaus:
 *   Ohjelma toteuttaa Hitori-pelin. Pelissä on peliruudukko kooltaan
 * 5 x 5. Kukin ruutu sisältää jonkin numeroista 1-5. Vaaka- ja
 * pystyriveillä voi aluksi olla useita samoja numeroita, mutta
 * tarkoituksena on poistaa numeroita niin, että kullakin vaaka- ja
 * pystyrivillä on kutakin numeroa vain yksi tai ei yhtään. Kuitenkaan
 * vierekkäisten ruutujen numeroita ei saa poistaa, eikä mikään jäljelle
 * jäävä numero (ruutu) saa jäädä irralleen muista, eli sen ympäriltä
 * (yläpuolelta, alapuolelta, vasemmalta, oikealta) ei saa poistaa
 * kaikkia numeroita.
 *   Aluksi käyttäjältä kysytään, täytetäänkö peliruudukko satunnaisesti
 * arvottavilla luvuilla 1-5 vai käyttäjän valitsemilla 25 luvulla.
 * Ensimmäisessä vaihtoehdossa käyttäjältä kysytään satunnaisluku-
 * generaattorin siemenlukua ja jälkimmäisessä häntä pyydetään syöttämään
 * 25 lukua.
 *   Joka kierroksella käyttäjältä kysytään poistettavan numeron
 * koordinaatteja eli kahta lukua. Peli päättyy pelaajan voittoon,
 * jos peliruudukon kaikilla vaaka- ja pystyriveillä esiintyy kukin
 * numero 1-5 korkeintaan kerran. Peli päättyy pelaajan häviöön,
 * jos hän poistaa jo poistetun numeron viereisen numeron tai jos
 * jokin numero jää irralleen muista.
 *   Ohjelma tarkistaa annetut koordinaatit. Koordinaattien pitää olla
 * peliruudukon sisällä, ja niiden osoittaman ruudun pitää sisältää
 * numero, eli jo poistettua numeroa ei voi poistaa toiseen kertaan.
 *   Pelin päättyessä kerrotaan, voittiko vai hävisikö pelaaja.
 *
 * Ohjelman kirjoittajat
 * Nimi: Mikko Rajakorpi
 * Opiskelijanumero: 150464570
 * Käyttäjätunnus: pnmira
 * E-Mail: mikko.rajakorpi@tuni.fi
 *
 * Nimi: Santeri Virtanen
 * Opiskelijanumero: 427639
 * Käyttäjätunnus: sv427639
 * E-Mail: santeri.t.virtanen@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 *
 * */

#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <gameboard.hh>

using namespace std;


// splittaa merkkijonon numerot vectoriin
vector<uint> split(const string& input) {
    vector<uint> unformattedGameboard = { };

    for (char currentChar: input) {
        if (isdigit(currentChar)) {

            // tekee merkista intin ottamalla sen ASCII numeron ja vähentämällä 0 merkin ASCII numeron
            uint currentNumber = currentChar - '0';
            unformattedGameboard.push_back(currentNumber);
        }
    }

    return unformattedGameboard;
}

// katsoo, onko syöte oikea
bool correctInput(const string& input) {
    if (input.length() == 1
            && (toupper(input.at(0)) == 'R'
                or toupper(input.at(0)) == 'I'
                or toupper(input.at(0)) == 'Q'))
        return true;
    else
        return false;
}

int main()
{

    // kysyy käyttäjältä, miten hän haluaa täyttää pelilaudan
    string type;
    do {
        cout << "Select start (R for random, I for input): ";
        getline(cin, type);
    }
    while (!correctInput(type));

    Gameboard gameboard;

    // tyypin tarkastelu
    if (toupper(type.at(0)) == 'R')
        gameboard.init();
    else if (toupper(type.at(0)) == 'Q') {
        cout << "Quitting" << endl;
        return EXIT_SUCCESS;
    }
    else {
        string input = "";
        cout << "Input: ";
        getline(cin, input);

        vector<uint> unformattedGameboard = split(input);

        gameboard.init(unformattedGameboard);
    }

    gameboard.print();

    // pelin logiikka

    do {
        cout << "Enter removable element (x, y): ";
        string coordinates;
        getline(cin, coordinates);

        if (toupper(coordinates.at(0)) == 'Q') {
            cout << "Quitting" << endl;
            return EXIT_SUCCESS;
        }

        vector<uint> coordinatesVector = split(coordinates);

        if (gameboard.removeNumber(coordinatesVector))
            gameboard.print();
    }
    while(!gameboard.hasLost() && !gameboard.hasWon());

    // oikean loppuviestin näyttäminen
    if (gameboard.hasLost())
       cout << "You lost" << endl;
    else if (gameboard.hasWon())
        cout << "You won" << endl;

    return 0;
}
