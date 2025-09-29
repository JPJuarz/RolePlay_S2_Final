
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "character.h"
#include "level.h"

using namespace std;

// Vector  que almacena los niveles del juego
vector<Level*> levels(4);
// Puntero al personaje héroe
Character *hero;

// Funcion para crear el heroe del juego
void createHero() {
    string name;
    int option;

    // Solicita nombre 
    cout << "What is your hero's name? \n";
    cin >> name;
    cin.ignore();

    // Muestra opciones de clase
    cout << "0. Warrior\n";
    cout << "1. Archer\n";
    cout << "2. Mage\n";
    cout << "What kind of hero do you want to be? \n";
    cin >> option;

    // Asegurarse que la opción este en el rango
    option %= 3;

    // Crea el heroe segun la clase seleccionada
    switch(option) {
        case 0 : hero = new Warrior(name); break;
        case 1 : hero = new Archer(name); break;
        case 2 : hero = new Mage(name); break;
    }
}

// Funcion para crear los niveles del juego
void createLevels() {
    // Nivel 1: Goblin
    levels[0] = new Level("The Duel in the Goblin's Lair");
    levels[0]->addPrologue("The hero entered a foggy forest. Twisted trees whispered secrets. In a moonlit clearing, a mighty goblin appeared, ready to battle.");
    levels[0]->addEpilogue("The hero bravely defeated the goblin. Exhausted but victorious, he looked at the sunrise, ready for future challenges. \n\n");
    levels[0]->addEnemy(new Enemy("Goblin", 25, 15, 5, 0));
    levels[0]->addHero(hero);

    // Nivel 2: Orc
    levels[1] = new Level("The Battle of the Shadow Cave");
    levels[1]->addPrologue("The cave was dark and damp, with stalactites, bats, and an oppressive atmosphere. An orc awaited the hero by a fire.");
    levels[1]->addEpilogue("The hero, bleeding but victorious, defeated the orc. Exhausted, he picked up his sword and set out for new adventures. \n\n");
    levels[1]->addEnemy(new Enemy("Orc", 75, 45, 15, 0));
    levels[1]->addHero(hero);

    // Nivel 3: Dragon
    levels[2] = new Level("The Confrontation at the Frosty Peak");
    levels[2]->addPrologue("On the snowy mountaintop, the hero faced the red dragon. Icy wind whipped as the dragon roared, its scales glistening. Battle imminent.");
    levels[2]->addEpilogue("The hero stood over the fallen dragon. Wind scattered ashes. Sword smoking, he looked out over the snowy landscape, triumphant. \n\n");
    levels[2]->addEnemy(new Enemy("Dragon", 100, 60, 30, 0));
    levels[2]->addHero(hero);

    // Nivel final: Sarvok
    levels[3] = new Level("The Final Battle against the Necromancer");
    levels[3]->addPrologue("The hero stepped into the heart of the Dark Fortress, as crimson light shun upon he spotted the necromancer Sarvok prepared to face him. Shadows danced as dark magic filled the air.");
    levels[3]->addEpilogue("The hero, victorious, sealed the Eternity Stone. The Dark Fortress crumbled, and the hero emerged into the light, ready for new adventures. \n\n");
    levels[3]->addEnemy(new Enemy("Sarvok", 150, 100, 50, 0));
    levels[3]->addHero(hero);
}

// Funcion para liberar la memoria
void deleteAll() {
    // Elimina todos los niveles
    for (Level *lvl : levels) {
        if(lvl != nullptr) {
            delete lvl;
        }
    }
    // Elimina el héroe
    if(hero != nullptr) {
        delete hero;
    }
}

int main(int argc, char* argv[]) {
    int option, i = 0; 
    bool finished = false;

    // Crea el heroe y los niveles
    createHero();
    createLevels();

    // Introducción del juego
    cout << "\nIn the Kingdom of Eldoria, peace is shattered when the "
         << "necromancer Sarvok seeks the Stone of Eternity to gain "
         << "unlimited power. Guided by a prophecy, three heroes—a "
         << "Warrior, an Archer, and a Mage—set out on a journey to stop "
         << "Sarvok from achieving his goal, facing many dangers along the way.\n";
         cout << "----------------------------------------------------\n\n";

    while (!finished && i < levels.size()) {
        // Ejecuta el nivel actual
        levels[i]->execute();
        
        // Verifica si el jugador gano o perdio
        if (!levels[i]->hasWon()) {
            finished = true;
        } else {
            // Muestra datos del heroe y opciion de descansar
            cout << hero->toString() << "\n";
            cout << "Do you want to rest? (0 = No, 1 = Yes) \n ";
            cin >> option;

            if (option == 1) {
                hero->recover(20); // Recupera salud y maná
            }
        }
        i++; // Pasa al siguiente nivel
    }

    // Mensaje de victoria si se completaron todos los niveles
    if (i >= levels.size() && levels[i-1]->hasWon()) {
        cout << "\nAfter the defeat of Sarvok and the sealing of the Eternity Stone, "
             << "Eldoria flourished and the heroes were celebrated. Their legacy continues "
             << "to inspire to this day, maintaining peace and justice in the realm.\n"
             << "----------------------------------------------------\n\n"
             << "Congratulations! You have completed the game!\n";
    }

    // Libera memoria
    deleteAll();

    return 0;
};