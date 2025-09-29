#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>
#include <vector>
#include "character.h"

using namespace std;

class Level {
protected:
    string name, prologue, epilogue; // Nombre del nivel, prólogo y epílogo
    Character* hero;                 // Puntero al heroe 
    Character* enemy;                // Puntero al enemigo del nivel
    bool won;                        // Indica si el nivel fue ganado

public:
    // Constructores
    Level() : name(""), prologue(""), epilogue(""), hero(nullptr), enemy(nullptr), won(false) {} // Constructor por defecto
    Level(string name) : name(name), prologue(""), epilogue(""), hero(nullptr),  // Constructor con parametros
        enemy(nullptr), won(false) {}
    Level(const Level& other) // Constructor de copia
        : name(other.name), prologue(other.prologue), epilogue(other.epilogue), 
          hero(other.hero), enemy(other.enemy), won(other.won) {}
    
    // Destructor
    virtual ~Level() {
        if(enemy != nullptr) {
            delete enemy;
        }
    }

    // Verifica si el nivel fue ganado
    bool hasWon() const {
        return won;
    }

    // Metodos para agregar texto
    void addPrologue(const string& text) {
        prologue = text;
    }
    void addEpilogue(const string& text) {
        epilogue = text;
    }
    
    // Metodos para asignar personajes
    void addHero(Character* h) {
        hero = h;
    }
    void addEnemy(Character* e) {
        enemy = e;
    }

    // Metodo para ejecutar el nivel
    void execute() {
        // Verificaa que hay personajes asignados
        if (hero == nullptr || enemy == nullptr) {
            cout << "Error: Hero or enemy not set for the level." << endl;
            return;
        }

        // Muestra la información del nivel
        cout << "Prologue: " << prologue << endl;
        cout << "Hero: " << hero->toString() << endl;
        cout << "Enemy: " << enemy->toString() << endl;

        // Bucle de la batalla
        while (hero->isAlive() && enemy->isAlive()) {
            int attackChoice;
            // Muestra las multiples opciones de ataque
            cout << "\nChoose attack:\n";
            cout << "(1) Normal Attack (No mana cost)\n";
            cout << "(2) Strong Attack (Costs mana)\n";
            cout << "(3) Ultimate Attack (Costs max mana)\n";  
            cout << "Your choice: ";
            cin >> attackChoice;

            // Ejecuta ataque segun la opción seleccionada
            if (attackChoice == 1) {
                hero->normalAttack(*enemy); 
            } 
            else if (attackChoice == 2) {
                hero->attack(*enemy);  
            }
            else if (attackChoice == 3) {
                hero->ultimateAttack(*enemy);  
            }
            else {
                cout << "Invalid choice. Using normal attack.\n";
                hero->normalAttack(*enemy);
            }

            // Enemigo contraataca si sigue vivo
            if (enemy->isAlive()) {
                enemy->attack(*hero);
                cout << enemy->getName() << " counterattacks!\n";
            }
        }

        // Determina resultado de la batalla
        if (hero->isAlive()) {
            won = true;
            cout << "Hero has won the battle!" << endl;
        } else {
            won = false;
            cout << "Hero has been defeated." << endl;
        }

        // Muestra epílogo
        cout << "Epilogue: " << epilogue << endl;
    }
};

#endif LEVEL_H