#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int decrypt(int a, int b, int input);

int encrypt(int a, int b, int input);

int main(){

    string filename;
    char letter;

    cout << "Please enter a file to open: ";
    cin >> filename;

    ifstream readFile;

    readFile.open(filename);

    if (!readFile.is_open()){

        cout << "Error! " << filename << "could not be opened!\n";
        exit(0);
    }

    ofstream writeFile;
    char selection;

    cout << "Encrypt (e) or decrypt (d)?\n";

    cin >> selection;

    if (selection == 'e'){

        writeFile.open("EC_"+ filename);

        while (readFile.get(letter)){

            if (letter < 32 || letter > 127) writeFile << letter;

            else writeFile << char(encrypt(7,24,(letter - 32)) + 32);
        }
        writeFile.close();
    }
    else {

        writeFile.open("DC_"+ filename);

        while (readFile.get(letter)){

            if (letter < 32 || letter > 127) writeFile << letter;

            else writeFile << char(decrypt(68,-24,(letter - 32)) + 32);
        }
        writeFile.close();
    }

}

int decrypt(int a, int b, int input){

    int c = (a * (input + b));

    while (c < 0){

        c += 95;
    }

    return c % 95;
}

int encrypt(int a, int b, int input){

    return ((a * input) + b) % 95;
}