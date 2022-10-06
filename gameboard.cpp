#include "gameboard.hh"

Gameboard::Gameboard() {
}

// init ilman parametrejä kehittää satunnaisen pelilaudan
void Gameboard::init() {
    vector<uint> unformattedGameboard = { };

    string seedAsString;
    cout << "Enter seed value: ";
    getline(cin, seedAsString);
    uint seed = stoi_with_check(seedAsString);

    default_random_engine gen(seed);
    uniform_int_distribution<unsigned int> distr(1, 5);

    for (unsigned int i = 0; i < BOARD_SIDE * 5; i++) {
        unformattedGameboard.push_back(distr(gen));
    }

    gameboard = formatGameboard(unformattedGameboard);
}

// init parametrin kanssa tekee käyttäjän syötteestä pelilaudan
void Gameboard::init(const vector<uint> &manualInput) {
    gameboard = formatGameboard(manualInput);
}

// Tulostaa pelilaudan rivi- ja sarakenumeroineen.
void Gameboard::print() {
    cout << "=================" << endl;
    cout << "|   | 1 2 3 4 5 |" << endl;
    cout << "-----------------" << endl;
    for (uint i = 0; i < BOARD_SIDE; ++i) {
        cout << "| " << i + 1 << " | ";
        for (uint j = 0; j < BOARD_SIDE; ++j) {
            if (gameboard.at(i).at(j) == 0) {
                cout << EMPTY << " ";
            } else {
                cout << gameboard.at(i).at(j) << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << "=================" << endl;
}

// ottaa 25 pituuden 1-ulotteisen vectorin ja tekee siitä 5 x 5 2-ulotteisen vectorin
vector<vector<uint>> Gameboard::formatGameboard(const vector<uint>& unformattedGameboard) {
    vector<vector<unsigned int>> formattedGameboard = { };

    for (unsigned int i = 0; i < BOARD_SIDE; i++) {
        vector<unsigned int> row = { };

        // menee unformattedGameboardissa aina 5 alkioita kerrallaan ja tallentaa ne rivittäin pelilaudalle
        for (unsigned int j = BOARD_SIDE * i; j < BOARD_SIDE * (i + 1); j++) {
            row.push_back(unformattedGameboard.at(j));
        }

        formattedGameboard.push_back(row);
    }
    return formattedGameboard;
}

// katsoo, onko koordinaatit oikeita
bool Gameboard::checkInput(vector<uint> coordinates) {
    // jos jost coordinates.size() ei ole 2, niin tiedetään, että käyttäjä joko kirjoitti liikaa tai liian vähän numeroita
    if (coordinates.size() != 2
            or coordinates.at(0) < 1 or BOARD_SIDE < coordinates.at(0)
            or coordinates.at(1) < 1 or BOARD_SIDE < coordinates.at(1)) {
        cout << "Out of board" << endl;
        return false;
    }
    else if (gameboard.at(coordinates.at(1) - 1).at(coordinates.at(0) - 1) == 0) {
        cout << "Already removed" << endl;
        return false;
    }

    return true;
}

// katsoo, onko jokaisella numerolla ainakin 1 naapuri
bool Gameboard::checkNeighbours() {
    // kulmat
    if (gameboard.at(0).at(0) != 0 && gameboard.at(1).at(0) == 0 && gameboard.at(0).at(1) == 0)
        return true;
    else if (gameboard.at(4).at(0) != 0 && gameboard.at(3).at(0) == 0 && gameboard.at(4).at(1) == 0)
        return true;
    else if (gameboard.at(0).at(4) != 0 && gameboard.at(0).at(3) == 0 && gameboard.at(1).at(4) == 0)
        return true;
    else if (gameboard.at(4).at(4) != 0 && gameboard.at(3).at(4) == 0 && gameboard.at(4).at(3) == 0)
        return true;

    // reunojen tarkistus
    for (uint i = 1; i < BOARD_SIDE - 1; i++) {
        //yläreuna
        if (gameboard.at(0).at(i) != 0
                && gameboard.at(0).at(i-1) == 0 && gameboard.at(0).at(i+1) == 0
                && gameboard.at(1).at(i) == 0)
            return true;

        // alareuna
        if (gameboard.at(4).at(i) != 0
                && gameboard.at(4).at(i-1) == 0 && gameboard.at(4).at(i+1) == 0
                && gameboard.at(3).at(i) == 0)
            return true;

        // vasen reuna
        if (gameboard.at(i).at(0) != 0
                && gameboard.at(i-1).at(0) == 0 && gameboard.at(i+1).at(0) == 0
                 && gameboard.at(i).at(1) == 0)
            return true;

        // oikea reauna
        if (gameboard.at(i).at(4) != 0
                 && gameboard.at(i-1).at(4) == 0 && gameboard.at(i+1).at(4) == 0
                 && gameboard.at(i).at(3) == 0)
            return true;
    }

    // sisäisten numeroitten tarkistus
    for (uint i = 1; i < BOARD_SIDE - 1; i++) {
        for (uint j = 1; j < BOARD_SIDE - 1; j++) {

             if (gameboard.at(i).at(j) != 0
                    && gameboard.at(i-1).at(j) == 0 && gameboard.at(i+1).at(j) == 0
                    && gameboard.at(i).at(j-1) == 0 && gameboard.at(i).at(j+1) == 0)
                return true;
        }
    }
    return false;
}

// poistaa numeron pelilaudalta
bool Gameboard::removeNumber(vector<uint> coordinates) {
    if (checkInput(coordinates)) {
        uint x = coordinates.at(0) - 1;
        uint y = coordinates.at(1) - 1;
        gameboard.at(y).at(x) = 0;
        return true;
    }
    return false;
}

// katsoo, onko pelaaja voittanut
bool Gameboard::hasWon() {
    //Alustetaan numeroiden maara.
    int numberCount = 0;

    /*ekalla for silmukalla kaydaan lapi 1-5 ja sen jalkeen
    kaydaan lapi rivit ja tarkistaaan onko
    jotain numero kaksi tai yli rivilla.*/

    for (uint i = 1; i <= BOARD_SIDE; i++) {
        for (uint j = 0; j < BOARD_SIDE; j++) {
            for (uint k = 0;k<BOARD_SIDE; k++) {

                if (i == gameboard.at(j).at(k)) {
                     numberCount++;
                  }
              }

              if (numberCount >= 2) {
                  return false;
              } else {
                  numberCount=0;
              }

          }

      }

    /*ekalla for silmukalla kaydaan lapi 1-5 ja sen jalkeen
    *kaydaan lapi sarakkeet ja tarkistaaan onko
    *jotain numero kaksi tai yli sarakkeessa.*/

    for( uint i = 1; i <= 5; i++) {
          numberCount = 0;

          for (uint j = 0; j < BOARD_SIDE; j++) {

            for (uint k = 0; k < BOARD_SIDE; k++){

                if(i == gameboard.at(k).at(j)){
                    numberCount++;
                }
            }

            if (numberCount >= 2) {
                return false;
            } else {
                numberCount = 0;
            }
        }
    }
    return true;
}

// katsoo, onko pelaaja hävinnyt
bool Gameboard::hasLost() {

    //kay pelilaudan lapi ja tarkistaa onko kaksi vierrekkain tai onko numero eristyksissä
    for (uint i = 0; i < BOARD_SIDE - 1; i++) {

        for (uint j = 0; j < BOARD_SIDE - 1; j++) {

            if ((gameboard.at(i).at(j) == 0 && (gameboard.at(i + 1).at(j) == 0 || gameboard.at(i).at(j + 1) == 0))
                    || checkNeighbours())
                return true;
        }

        // viimeiset sarakkeet ja rivi pienella erikoiskasittelylla
        if ((gameboard.at(4).at(i) == 0 && gameboard.at(4).at(i + 1) == 0)
                || (gameboard.at(i).at(4) == 0 && gameboard.at(i + 1).at(4) == 0))
            return true;
    }

    return false;
}

// Muuttaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan.
//
// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns zero.
uint Gameboard::stoi_with_check(const string& str) {
    bool is_numeric = true;
    for (unsigned int i = 0; i < str.length(); ++i) {
        if (not isdigit(str.at(i))) {
            is_numeric = false;
            break;
        }
    }
    if (is_numeric) {
        return stoi(str);
    } else {
        return 0;
    }
}
