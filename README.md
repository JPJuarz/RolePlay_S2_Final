RPG Adventure
Project Overview

This is a text-based role-playing game (RPG) written in C++. Players create a hero and progress through multiple levels, battling enemies such as goblins, orcs, dragons, and ultimately the necromancer Sarvok. The game focuses on turn-based combat, character management, and simple decision-making.
The project was developed as a practice in object-oriented programming, pointers, dynamic memory, and class inheritance in C++. It allows users to understand game loops, battles, and hero progression in a small-scale RPG environment.

How to Play

Create Your Hero:
Choose a hero name and select a class:

Warrior: High health and strong physical attacks
Archer: Balanced health and ranged attacks
Mage: Lower health but high mana and powerful magic

Progress Through Levels:

Each level introduces a unique enemy and story prologue.
Battle enemies using three types of attacks:
Normal Attack: Costs no mana
Strong Attack: Costs some mana, deals more damage
Ultimate Attack: Costs maximum mana, deals massive damage

Recover Between Levels:
Players can choose to rest to regain health and mana before moving to the next challenge.

Victory Condition:
Defeat all enemies and ultimately Sarvok to complete the game and save the kingdom.

Project Structure

main.cpp – Entry point, manages game flow and user interactions.
character.h – Abstract Character class and derived classes: Warrior, Archer, Mage, Enemy.
level.h – Level class, manages enemies, prologues, epilogues, and battle execution.

Key Features

Object-oriented design with inheritance and polymorphism.
Dynamic memory management for hero and levels.
Turn-based combat system with multiple attack types.
Simple text-based storytelling with prologues and epilogues.

Learning Outcomes

Through this project, I improved my understanding of -
Class inheritance and polymorphism in C++
Managing dynamic memory with pointers
Designing and executing turn-based combat logic
Structuring a small game with levels and progression
