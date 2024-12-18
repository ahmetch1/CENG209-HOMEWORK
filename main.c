#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Constants
#define MAX_INVENTORY 10
#define MAX_NAME_LEN 50
#define MAX_ROOMS 5

typedef struct {
    char name[MAX_NAME_LEN];
    int health;
    int strength;
    int inventoryCapacity;
    int inventorySize;
    char inventory[MAX_INVENTORY][MAX_NAME_LEN];
} Player;

typedef struct {
    char name[MAX_NAME_LEN];
    char description[200];
    int hasItem;  // Flag for item in room
    char itemName[MAX_NAME_LEN];
    int hasMonster;  // Flag for monster in room
    char monsterName[MAX_NAME_LEN];
    int monsterHealth;
    int monsterStrength;
    int north, south, east, west; // Connected rooms
} Room;



// Function Prototypes
void initializePlayer(Player *player);
void initializeRooms(Room rooms[]);
void displayRoom(Room *room);
void look(Room *room);
void pickItem(Player *player, Room *room);
void inventory(Player *player);
void move(Room rooms[], int *currentRoom, char direction[10]);
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
    
    printf("Would you like to load a saved game? (yes/no): ");
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

// Initialize Player
void initializePlayer(Player *player) {
    strcpy(player->name, "Hero");
    player->health = 100;
    player->strength = 20;
    player->inventoryCapacity = MAX_INVENTORY;
    player->inventorySize = 0;
}

// Initialize 5 Rooms
void initializeRooms(Room rooms[]) {
    // Room 0
    strcpy(rooms[0].name, "Dungeon Entrance");
    strcpy(rooms[0].description, "A dark, gloomy entrance.");
    rooms[0].hasItem = 1; strcpy(rooms[0].itemName, "Torch");
    rooms[0].hasMonster = 1; strcpy(rooms[0].monsterName, "Goblin");
    rooms[0].monsterHealth = 30; rooms[0].monsterStrength = 10;
    rooms[0].north = 1; rooms[0].south = -1; rooms[0].east = 2; rooms[0].west = -1;

    // Room 1
    strcpy(rooms[1].name, "Hall of Bones");
    strcpy(rooms[1].description, "A chilling hall filled with skeleton remains.");
    rooms[1].hasItem = 1; strcpy(rooms[1].itemName, "Sword");
    rooms[1].hasMonster = 1; strcpy(rooms[1].monsterName, "Skeleton Warrior");
    rooms[1].monsterHealth = 40; rooms[1].monsterStrength = 15;
    rooms[1].north = -1; rooms[1].south = 0; rooms[1].east = -1; rooms[1].west = -1;

    // Room 2
    strcpy(rooms[2].name, "Treasure Room");
    strcpy(rooms[2].description, "A room glittering with treasure and Health Poison.");
    rooms[2].hasItem = 1; strcpy(rooms[2].itemName, "Health Poison");
    rooms[2].hasMonster = 1; strcpy(rooms[2].monsterName, "Mimic");
    rooms[2].monsterHealth = 35; rooms[2].monsterStrength = 12;
    rooms[2].north = 3; rooms[2].south = -1; rooms[2].east = -1; rooms[2].west = 0;

    // Room 3
    strcpy(rooms[3].name, "Armory");
    strcpy(rooms[3].description, "An abandoned armory with rusted weapons.");
    rooms[3].hasItem = 1; strcpy(rooms[3].itemName, "Shield");
    rooms[3].hasMonster = 1; strcpy(rooms[3].monsterName, "Orc");
    rooms[3].monsterHealth = 50; rooms[3].monsterStrength = 18;
    rooms[3].north = -1; rooms[3].south = 2; rooms[3].east = -1; rooms[3].west = 4;

    // Room 4
    strcpy(rooms[4].name, "Dark Cave");
    strcpy(rooms[4].description, "A pitch-black cave where danger lurks.");
    rooms[4].hasItem = 0;
    rooms[4].hasMonster = 1; strcpy(rooms[4].monsterName, "Giant Spider(Final Boss)");
    rooms[4].monsterHealth = 110; rooms[4].monsterStrength = 50;
    rooms[4].north = -1; rooms[4].south = -1; rooms[4].east = 3; rooms[4].west = -1;
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

void look(Room *room) {
    printf("You look around: %s\n", room->description);
    if (room->hasItem) {
        printf("You see a %s here.\n", room->itemName);
    }
    if (room->hasMonster) {
        printf("A %s is here! It looks hostile!\n", room->monsterName);
    }
}

void inventory(Player *player) {
    printf("Your inventory:\n");
    if (player->inventorySize == 0) {
        printf(" - Empty\n");
    } else {
        for (int i = 0; i < player->inventorySize; i++) {
            printf(" - %s\n", player->inventory[i]);
        }
    }
}

// Move to Another Room
void move(Room rooms[], int *currentRoom, char direction[10]) {
    int nextRoom = -1;

    if (strcmp(direction, "north") == 0) {
        nextRoom = rooms[*currentRoom].north;
    } else if (strcmp(direction, "south") == 0) {
        nextRoom = rooms[*currentRoom].south;
    } else if (strcmp(direction, "east") == 0) {
        nextRoom = rooms[*currentRoom].east;
    } else if (strcmp(direction, "west") == 0) {
        nextRoom = rooms[*currentRoom].west;
    } else {
        printf("Invalid direction.\n");
        return;
    }

    if (nextRoom != -1) {
        *currentRoom = nextRoom;
        printf("You moved to %s.\n", rooms[*currentRoom].name);
    } else {
        printf("You cannot move in that direction.\n");
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

// Display Map
void displayMap(){
	
	printf("\n|Hall of Bones|         |Dark Cave|-------|Armory|                     N   \n");
	printf("       |                                   |                           |   \n");
	printf("       |                                   |                      W---------E \n");
	printf("       |                                   |                           |    \n");
	printf("       |                                   |                           S   \n");
	printf("|Dungeon Entrance|------------------|Treasure Room|                \n");
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

