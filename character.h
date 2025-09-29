
#ifndef CHARACTER_H
#define CHARACTER_H

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <string>

using namespace std;

// Clase base abstracta para todos los personajes
class Character {
protected:
    string name;     // Nombre del personaje
    int health;      // Salud
    int mana;        // Mana
    int strength;    // Fuerza de ataque
    int shield;      // Escudo

public:
    // Constructores
    Character() : name(""), health(0), mana(0), strength(0), shield(0) {} // Constructor por defecto
    Character(string name, int health, int mana, int strength, int shield) : // Constructor con parametros
        name(name), health(health), mana(mana), strength(strength), shield(shield) {}
    Character(const Character& other) : // COnstructor de copia
        name(other.name), health(other.health), mana(other.mana), 
        strength(other.strength), shield(other.shield) {}
    
    // Destructor virtual
    virtual ~Character() {}

    // Metodos de acceso
    string getName() const {
        return name;
    }
    int getHealth() const {
        return health;
    }
    int getMana() const {
        return mana;
    }
    int getStrength() const {
       return strength;
    }
    int getShield() const {
        return shield;
    }

    // Verifica si el personaje está vivo
    bool isAlive() const { 
        return health > 0; 
    }
    
    // Recibe daño
    void takeDamage(int damage) {
        int actualDamage = damage - shield; // Reduce daño por el escudo
        if (actualDamage > 0) {
            health -= actualDamage;
            if (health < 0) health = 0; 
        }
    }
    
    // Metodos de ataque 
    virtual void attack(Character& target) = 0;          // Ataque fuerte
    virtual void normalAttack(Character& target) = 0;    // Ataque normal
    virtual void ultimateAttack(Character& target) = 0;  // Ataque ultimate

    
    virtual void recover(int amount) = 0;            // Recupera salud y mana
    virtual string toString() const = 0;             // Cambia a string

    // Operador de igualdad (compara estado de vida)
    bool operator==(const Character& other) const {
        return this->isAlive() == other.isAlive();
    }
};

// Clase Guerrero
class Warrior : public Character {
public:
    // Constructores
    Warrior() : Character("Warrior", 80, 30, 40, 20) {} // Constructor por defecto
    Warrior(string name) : Character(name, 80, 30, 40, 20) {} // Constructor con parametros
    Warrior(const Warrior& other) : Character(other) {} // Constructor de copia

    // Ataque normal - no gasta mana
    void normalAttack(Character& target) override {
        int damage = strength;
        target.takeDamage(damage);
        cout << name << " performs a basic attack (" << damage << " damage)" << endl;
    }

    // Ataque ultimate - mayor daño, cuesta toda la mana
    void ultimateAttack(Character& target) override {
        if (mana >= 30) {  
            target.takeDamage(120);
            mana -= 30;
            cout << name << " performs ultimate attack (120 damage, -30 MP)" << endl;
        } else {
            cout << name << " lacks mana for ultimate attack! Uses normal attack instead." << endl;
            normalAttack(target);
        }
    }

    // Ataque fuerte - daño doble, costo bajo de mana
    void attack(Character& target) override {
        if (mana >= 10) {
            int damage = strength * 2;
            target.takeDamage(damage);
            mana -= 10;
            cout << name << " performs a heavy attack (" << damage << ") damage, -10 MP" << endl;
        } else {
            cout << name << " lacks mana for a heavy attack! Uses normal attack instead." << endl;
            normalAttack(target);
        }
    }

    // Recupera salud y mana
    void recover(int amount) override {
        health += amount;
        if (health > 80) health = 80; // Limite de salud
        
        mana += amount;
        if (mana > 30) mana = 30; // Limte de mana
        
        cout << name << " Recovers (+" << amount << " HP/MP)" << endl;
    }

    // Representación en string
    string toString() const override {
        stringstream ss;
        ss << "Warrior [" << name << "] - HP: " << health << "/80 | Mana: " << mana << "/30 | " 
           << "Strength: " << strength << " | Shield: " << shield;
        return ss.str();
    }
};

// Clase Arquero
class Archer : public Character {
public:
    // Constructores
    Archer() : Character("Archer", 60, 50, 30, 15) {} // Constructor por defecto
    Archer(string name) : Character(name, 60, 50, 30, 15) {} // Constructor con parametros
    Archer(const Archer& other) : Character(other) {} // Constructor de copia

    // Ataque normal
    void normalAttack(Character& target) override {
        int damage = strength;
        target.takeDamage(damage);
        cout << name << " performs basic attack (" << damage << " damage)" << endl;
    }

    // Ataque ultimate
    void ultimateAttack(Character& target) override {
        if (mana >= 50) { 
            target.takeDamage(130);
            mana -= 50;
            cout << name << " performs ultimate attack (130 damage, -50 MP)" << endl;
        } else {
            cout << name << " not enough mana for ultimate attack! Uses normal attack instead." << endl;
            normalAttack(target);
        }
    }

    // Ataque fuerte
    void attack(Character& target) override {
        if (mana >= 20) {
            int damage = strength * 3;
            target.takeDamage(damage);
            mana -= 20;
            cout << name << " performs a heavy attack (" << damage << ") damage, -20 MP" << endl;
        } else {
            cout << name << " not enough mana for heavy attack! Uses normal attack instead." << endl;
            normalAttack(target);
        }
    }

    // Recupera salud y mana
    void recover(int amount) override {
        health += amount;
        if (health > 60) health = 60;
        
        mana += amount;
        if (mana > 50) mana = 50;
        
        cout << name << " Recovers (+" << amount << " HP/MP)" << endl;
    }

    // Representación en string
    string toString() const override {
        stringstream ss;
        ss << "Archer [" << name << "] - HP: " << health << "/60 | Mana: " << mana << "/50 | " 
           << "Strength: " << strength << " | Shield: " << shield;
        return ss.str();
    }
};

// Clase Mago
class Mage : public Character {
public:
    // Constructores
    Mage() : Character("Mage", 65, 100, 20, 10) {} // Constructor por defecto
    Mage(string name) : Character(name, 65, 100, 20, 10) {} // Constructor con parametros
    Mage(const Mage& other) : Character(other) {} // Constructor de copia

    // Ataque normal
    void normalAttack(Character& target) override {
        int damage = strength;
        target.takeDamage(damage);
        cout << name << " performs a basic attack (" << damage << " damage)" << endl;
    }

    // Ataque ultimate
    void ultimateAttack(Character& target) override {
        if (mana >= 100) {  
            target.takeDamage(140);
            mana -= 100;
            cout << name << " performs ultimate attack (140 damage, -100 MP)" << endl;
        } else {
            cout << name << " lacks mana for ultimate attack! Uses normal attack instead." << endl;
            normalAttack(target);
        }
    }

    // Ataque fuerte
    void attack(Character& target) override {
        if (mana >= 30) {
            int damage = strength * 4;
            target.takeDamage(damage);
            mana -= 30;
            cout << name << " Performs a heavy attack (" << damage << ") damage, -30 MP" << endl;
        } else {
            cout << name << " lacks mana for heavy attack! Uses basic attack instead." << endl;
            normalAttack(target);
        }
    }
    
    // Recupera salud y mana
    void recover(int amount) override {
        health += amount;
        if (health > 65) health = 65;
        
        mana += amount;
        if (mana > 100) mana = 100;
        
        cout << name << " Recovers (+" << amount << " HP/MP)" << endl;
    }
    
    // Representación en string
    string toString() const override {
        stringstream ss;
        ss << "Mage [" << name << "] - HP: " << health << "/65 | Mana: " << mana << "/100 | " 
           << "Strength: " << strength << " | Shield: " << shield;
        return ss.str();
    }
};

// Clase Enemigo
class Enemy : public Character {
public:
    // Constructores
    Enemy() : Character("Enemy", 30, 0, 15, 5) {} // Constructor por defecto
    Enemy(string name, int health, int mana, int strength, int shield) // Constructor con parametros
        : Character(name, health, mana, strength, shield) {} 
    Enemy(const Enemy& other) : Character(other) {} // Constructor de copia

    // Ataque normal
    void normalAttack(Character& target) override {
        int damage = strength;
        target.takeDamage(damage);
        cout << name << " performs a basic attack (" << damage << " damage)" << endl;
    }

    // Ataque ultimate (los enemigos no lo usan pero es necesario porque es abstracta la clase character)
    void ultimateAttack(Character& target) override {
        normalAttack(target);
    }

    // Ataque fuerte (usa normal por defecto por misma razón)
    void attack(Character& target) override {
        normalAttack(target);
    }

    // Recupera salud (tampoco lo usan los enemigos pero es necesario)
    void recover(int amount) override {
        health += amount;
        if (health > 30) health = 30;
        
        cout << name << " Recovers (+" << amount << " HP)" << endl;
    }
    
    // Representación en string
    string toString() const override {
        stringstream ss;
        ss << "Enemy [" << name << "] - HP: " << health;
        return ss.str();
    }
};

#endif CHARACTER_H