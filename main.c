#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "player.c"
#include "room.c"


// Function Prototypes
void pickItem(Player *player, Room *room);
void attack(Player *player, Room *room);
void displayCommands();
void saveGame(Player *player, Room rooms[], int currentRoom);
void loadGame(Player *player, Room rooms[], int *currentRoom);

// Main Function
int main() {
    Player player;
    Room rooms[MAX_ROOMS];
    int currentRoom = 0;
    char command[20];
    char direction[10];

    // Initialization
    initializePlayer(&player);
    initializeRooms(rooms);
    
    printf("Would you like to load a saved gsame? (yes/no): ");
    char choice[10];
    scanf("%s", choice);
    if (strcmp(choice, "yes") == 0) {
        loadGame(&player, rooms, &currentRoom);
    } else {
        printf("Starting a new game!\n");
    }
    
    printf("Welcome to the Dungeon Adventure Game!\n");
    displayCommands();
    displayMap();

    // Main Game Loop
    while (1) {
        printf("\n[Player Health: %d | Strength: %d]\n", player.health, player.strength);
        printf("You are in %s.\n", rooms[currentRoom].name);
        printf("Enter command: ");
        scanf("%s", command);

        if (strcmp(command, "look") == 0) {
            look(&rooms[currentRoom]);
        } else if (strcmp(command, "pick") == 0) {
            pickItem(&player, &rooms[currentRoom]);
        } else if (strcmp(command, "inventory") == 0) {
            inventory(&player);
        } else if (strcmp(command, "move") == 0) {
            printf("Enter direction (north, south, east, west): ");
            scanf("%s", direction);
            move(rooms, &currentRoom, direction);
        } else if (strcmp(command, "attack") == 0) {
            attack(&player, &rooms[currentRoom]);
        } else if (strcmp(command, "exit") == 0) {
            printf("Thanks for playing! Goodbye!\n");
            break;
        } else if (strcmp(command, "save") == 0) {
            saveGame(&player, rooms, currentRoom);
        } else {
            printf("Invalid command. Try again.\n");
            displayCommands();
        }
        	if (strcmp(rooms[currentRoom].name, "Dark Cave") == 0) {
        			if(rooms[currentRoom].hasMonster==0){
        			printf("You finished the game! Thanks for playing! Goodbye!\n");
        			break;}
		}

        // Check if player is dead
        if (player.health <= 0) {
            printf("You have been defeated! Game over.\n");
            break;
        }
    }
    return 0;
}


// Pick up Item
void pickItem(Player *player, Room *room) {
    if (room->hasItem) {
        if (player->inventorySize < player->inventoryCapacity) {
            strcpy(player->inventory[player->inventorySize], room->itemName);
            player->inventorySize++;
            room->hasItem = 0;
            printf("You picked up the %s.\n", room->itemName);
            if(strcmp(room->itemName,"Health Poison")==0){
            	player->health =100;
			}
			else if(strcmp(room->itemName,"Sword")==0){
            	player->strength +=20;
			}
        } else {
            printf("Your inventory is full!\n");
        }
    } else {
        printf("There is nothing to pick up here.\n");
    }
}



// Attack Command
void attack(Player *player, Room *room) {
    if (room->hasMonster) {
        printf("You engage in combat with the %s!\n", room->monsterName);
        while (player->health > 0 && room->monsterHealth > 0) {
            // Player attack
            room->monsterHealth -= player->strength;
            printf("You hit the %s for %d damage. Monster Health: %d\n", room->monsterName, player->strength, room->monsterHealth);

            if (room->monsterHealth <= 0) {
                printf("You defeated the %s!\n", room->monsterName);
                room->hasMonster = 0;
                return;
            }

            // Monster attack
            player->health -= room->monsterStrength;
            printf("The %s hits you for %d damage. Your Health: %d\n", room->monsterName, room->monsterStrength, player->health);
        }
    } else {
        printf("There is no monster to attack here.\n");
    }
}
// Save Game to File
void saveGame(Player *player, Room rooms[], int currentRoom) {
    FILE *file = fopen("savegame.dat", "wb");
    if (file == NULL) {
        printf("Error saving game.\n");
        return;
    }

    fwrite(player, sizeof(Player), 1, file);
    fwrite(rooms, sizeof(Room), MAX_ROOMS, file);
    fwrite(&currentRoom, sizeof(int), 1, file);

    fclose(file);
    printf("Game saved successfully!\n");
}

// Load Game from File
void loadGame(Player *player, Room rooms[], int *currentRoom) {
    FILE *file = fopen("savegame.dat", "rb");
    if (file == NULL) {
        printf("No saved game found. Starting a new game.\n");
        return;
    }

    fread(player, sizeof(Player), 1, file);
    fread(rooms, sizeof(Room), MAX_ROOMS, file);
    fread(currentRoom, sizeof(int), 1, file);

    fclose(file);
    printf("Game loaded successfully! Welcome back, %s.\n", player->name);
}

// Display Commands
void displayCommands() {
    printf("Available commands:\n");
    printf(" - look          : Display room description\n");
    printf(" - pick          : Pick up an item in the room\n");
    printf(" - inventory     : Show your inventory\n");
    printf(" - move          : Move to another room\n");
    printf(" - attack        : Attack a monster in the room\n");
    printf(" - exit          : Quit the game\n");
    printf(" - save          : Save the current game\n");
}
