/*
    CSCE1011 - Battle Arena Game
    Bavly Attallah - (write your id)
    Moataz Badawy - 900244214
*/

#include "Character.h"
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <string>

using namespace std;

// simple text menu and instructions without emojis
void displayInstructions() {
    cout << "\n\n==== GAME INSTRUCTIONS ====" << endl;
    cout << "1. Create 4-6 characters." << endl;
    cout << "   - Name each character." << endl;
    cout << "   - Choose a class: Warrior, Mage, or Archer." << endl;
    cout << "2. Battle rules:" << endl;
    cout << "   - Each round two random alive characters fight." << endl;
    cout << "   - 50% chance to use normal attack or special ability." << endl;
    cout << "3. Win by being the last character alive." << endl;
    cout << "   - If more than one survives you may choose a tie-breaker." << endl;
    cout << "4. Statistics are tracked and shown at the end." << endl;
    cout << "===========================\n" << endl;
}

bool showWelcomeMenu() {
    cout << "\n==========================================" << endl;
    cout << "       WELCOME TO CSCE1011 BATTLE ARENA     " << endl;
    cout << "==========================================" << endl;
    cout << "1. Start game" << endl;
    cout << "2. View instructions" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter choice (1-3): ";

    int choice;
    cin >> choice;
    cin.ignore();
    switch(choice) {
        case 1:
            return true;
        case 2:
            displayInstructions();
            return showWelcomeMenu();
        case 3:
            exit(0);    // Exit the program
        default:
            cout << "Invalid choice.\n" << endl;
            return showWelcomeMenu();
    }
}

void displayCharacterInfo(Character* c);
bool compareCharacters(Character* a, Character* b);

int main()
{
    // Seed random number generator
    srand(time(0));

    if (!showWelcomeMenu())
        return 0;

    // Create characters using base class pointers
    vector<Character*> characters;

    int numCharacters;
    cout << "How many brave warriors will enter the arena? (4-6 recommended): ";
    cin >> numCharacters;
    cin.ignore();

    cout << "\nTell us about your fighters:\n";
    for (int i = 0; i < numCharacters; i++) {
        string name, type;
        cout << "\nFighter " << i + 1 << " Name: ";
        getline(cin, name);
        cout << "Fighter " << i + 1 << " Class (Warrior/Mage/Archer): ";
        getline(cin, type);

        if (type == "Warrior") {
            characters.push_back(new Warrior(name));
        } else if (type == "Mage") {
            characters.push_back(new Mage(name));
        } else if (type == "Archer") {
            characters.push_back(new Archer(name));
        } else {
            cout << "Unknown class! " << name << " enters as a Warrior." << endl;
            characters.push_back(new Warrior(name));
        }
    }

    cout << "\nTotal active warriors in the arena: " << Character::getCharacterCount() << endl;
    cout << "==========================================" << endl;

    // Display intial lineup
    cout << "\nTHE ARENA LINEUP:\n";
    cout << left << setw(15) << "Name" 
            << left << setw(15) << "Health" 
            << left << setw(15) << "Attack Power" << endl;
    cout << "------------------------------------------" << endl;
    for (Character* c : characters) {
        displayCharacterInfo(c);
        cout << endl;
    }

    // Battle Simulation
    int numRounds;
    cout << "\nHow many rounds of combat will occur? (5 recommended): ";
    cin >> numRounds;

    // Battle Statistics
    struct Stats {
        string name;
        int attackesPerformed = 0;
        int specialUsed = 0;
        int damageDealt = 0;
        int damageTaken = 0;
    };

    vector<Stats> stats(characters.size());
    for (size_t i = 0; i < characters.size(); i++) { 
        stats[i].name = characters[i]->getName();
    }

    for (int round = 1; round <= numRounds; round++) {
        cout << "\n" << string(50, '=') << endl;
        cout << "                    ROUND " << round << "                    " << endl;
        cout << string(50, '=') << endl;

        // Get alive characters
        vector<Character*> alive;
        vector<int> aliveIndices;
        for (size_t i = 0; i < characters.size(); i++) {
            if (characters[i]->isAlive()) {
                alive.push_back(characters[i]);
                aliveIndices.push_back(i);
            }
        }

        // If less than 2 alive, end tournament
        if (alive.size() < 2) {
            cout << "\nNot enough fighters remaining! The tournament ends here." << endl;
            break;
        }

        // Randomly select two different characters
        int index1 = rand() % alive.size();
        int index2;
        do {
            index2 = rand() % alive.size();
        } while (index2 == index1);

        Character* attacker = alive[index1];
        Character* defender = alive[index2];

        // Get original indices for stats tracking
        int attackerIndex = aliveIndices[index1];
        int defenderIndex = aliveIndices[index2];

        cout << "\nCLASH IN THE ARENA:\n";
        cout << attacker->getName() << " faces off against " << defender->getName() << "!\n" << endl;
        
        // Decide whether to use regular attack or special ability (50% chance)
        int damage;
        bool usedSpecial = (rand() % 2 == 0);
        
        if (!usedSpecial) {
            damage = attacker->attack();
            stats[attackerIndex].attackesPerformed++;
            cout << attacker->getName() << " launches a powerful strike!" << endl;
        } else {
            damage = attacker->specialAbility();
            stats[attackerIndex].specialUsed++;
            cout << attacker->getName() << " unleashes their special ability!" << endl;
        }

        // Store defender's health before attack for stats
        int healthBefore = defender->getHealth();

        // Apply damage to defender
        defender->takeDamage(damage);

        // update stats
        stats[attackerIndex].damageDealt += damage;
        stats[defenderIndex].damageTaken += (healthBefore - defender->getHealth());

        // Check if defender is defeated
        if (!defender->isAlive()) {
            cout << "\n*** " << defender->getName() << " has been DEFEATED! ***" << endl;
        }

        // Show current stats health status
        cout << "\nCURRENT HEALTH STATUS:\n";
        cout << "  " << attacker->getName() << ": " << attacker->getHealth() << " HP" << endl;
        cout << "  " << defender->getName() << ": " << defender->getHealth() << " HP" << endl;
    }
    
    // Display Final Scoreboard
    cout << "\n" << string(105, '=') << endl;
    cout << "                                 FINAL BATTLE SCOREBOARD                                  " << endl;
    cout << string(105, '=') << endl;

    cout << left << setw(15) << "Name" 
            << setw(20) << "Attacks" 
            << setw(20) << "Special Moves" 
            << setw(20) << "Damage Dealt" 
            << setw(20) << "Damage Taken" 
            << "Status" << endl;
    cout << string(105, '-') << endl;

    for (Character* c : characters) {
        int idx = distance(characters.data(), find(characters.data(), characters.data() + characters.size(), c));
        cout << left << setw(15) << c->getName()
                << setw(20) << stats[idx].attackesPerformed
                << setw(20) << stats[idx].specialUsed
                << setw(20) << stats[idx].damageDealt
                << setw(20) << stats[idx].damageTaken
                << (c->isAlive() ? "Alive" : "Defeated") << endl;
    }

    // Announce tournament Winner
    cout << "\n==========================================" << endl;
    cout << "          TOURNAMENT CONCLUSION          " << endl;
    cout << "==========================================" << endl;

    vector<Character*> alive;
    for (Character* c : characters) {
        if (c->isAlive()) {
            alive.push_back(c);
        }
    }

    if (alive.size() == 1) {
        cout << "\nTHE CHAMPION: " << alive[0]->getName() << "!" << endl;
        cout << "Victory is yours, mighty warrior!" << endl;
    } 
    else if (alive.size() > 1) {
        cout << "\nMultiple warriors remain standing in the arena!" << endl;
        cout << "Survivors: ";
        for (size_t i = 0; i < alive.size(); i++) {
            cout << alive[i]->getName();
            if (i < alive.size() - 1) cout << ", ";
        }
        cout << endl;
        
        // Ask user if they want a tie-breaker round
        char choice;
        cout << "\nDo you want a final tie-breaker clash? (y/n): ";
        cin >> choice;
        
        if (choice == 'y' || choice == 'Y') {
            cout << "\n" << string(50, '=') << endl;
            cout << "            ULTIMATE TIE-BREAKER BATTLE           " << endl;
            cout << string(50, '=') << endl;
            
            // Continue battling until only one remains or user gives up
            int tieRound = 1;
            while (alive.size() > 1) {
                cout << "\n--- Final Round " << tieRound++ << " ---" << endl;
                
                // Get current alive characters
                alive.clear();
                for (Character* c : characters) {
                    if (c->isAlive()) {
                        alive.push_back(c);
                    }
                }
                
                if (alive.size() < 2) break;
                
                // Randomly select two different characters
                int index1 = rand() % alive.size();
                int index2;
                do {
                    index2 = rand() % alive.size();
                } while (index2 == index1);
                
                Character* attacker = alive[index1];
                Character* defender = alive[index2];
                
                cout << "\nBattle: " << attacker->getName() << " clashes with " << defender->getName() << endl;
                
                // Decide whether to use regular attack or special ability (50% chance)
                int damage;
                if (rand() % 2 == 0) {
                    damage = attacker->attack();
                    cout << attacker->getName() << " strikes with devastating force!" << endl;
                } else {
                    damage = attacker->specialAbility();
                    cout << attacker->getName() << " channels their ultimate power!" << endl;
                }
                
                // Apply damage to defender
                defender->takeDamage(damage);
                
                // Check if defender is defeated
                if (!defender->isAlive()) {
                    cout << "*** " << defender->getName() << " has been DEFEATED! ***" << endl;
                }
                
                // Show current health status
                cout << "\nRemaining fighters in the arena:\n";
                for (Character* c : alive) {
                    if (c->isAlive()) {
                        cout << "  " << c->getName() << ": " << c->getHealth() << " HP" << endl;
                    }
                }
                
                // After each battle, ask if user wants to continue
                if (alive.size() > 1) {
                    char continueChoice;
                    cout << "\nContinue the battle? (y/n): ";
                    cin >> continueChoice;
                    if (continueChoice != 'y' && continueChoice != 'Y') {
                        break;
                    }
                }
            }
            
            // Check final winner after tie-breaker
            alive.clear();
            for (Character* c : characters) {
                if (c->isAlive()) {
                    alive.push_back(c);
                }
            }
            
            cout << "\n" << string(50, '=') << endl;
            cout << "          THE ULTIMATE CHAMPION EMERGES         " << endl;
            cout << string(50, '=') << endl;
            
            if (alive.size() == 1) {
                cout << "\nALL HAIL THE VICTOR: " << alive[0]->getName() << "!" << endl;
                cout << "You have proven yourself the ultimate warrior!" << endl;
            } else if (alive.size() > 1) {
                cout << "\nStill no clear winner exists! Final survivors: ";

                for (size_t i = 0; i < alive.size(); i++) {
                    cout << alive[i]->getName();
                    if (i < alive.size() - 1) cout << ", ";
                }

                cout << endl;
                cout << "The battle ends in an legendary stalemate!" << endl;
            } else {
                cout << "\nTotal annihilation! Every warrior has fallen in combat!" << endl;
            }
        } else {
            cout << "\nThe tournament concludes in an honorable tie!" << endl;
        }
    } 
    else {
        cout << "\nTotal annihilation! Every warrior has been defeated!" << endl;
    }

    // Memory cleanup
    cout << "\n==========================================" << endl;
    cout << "      The Arena is being cleared...       " << endl;
    cout << "==========================================" << endl;

    for (Character* c : characters) {
        delete c;
    }
    characters.clear();

    cout << "\nTournament complete! Until next time, warriors!" << endl;

    return 0;
}

void displayCharacterInfo(Character* c) {
    cout << left << setw(15) << c->getName();
    cout << left << setw(15) << c->getHealth();
    cout << left << setw(15) << c->attack();
}

bool compareCharacters(Character* a, Character* b) {
    if (a->isAlive() && !b->isAlive()) return true; 
    if (!a->isAlive() && b->isAlive()) return false; 

    return a->getName() < b->getName(); 
}