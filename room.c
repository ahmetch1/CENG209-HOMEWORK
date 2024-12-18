#include "room.h"

#define MAX_ROOMS 5
#define MAX_NAME_LEN 50


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
    rooms[4].monsterHealth = 110; rooms[4].monsterStrength = 40;
    rooms[4].north = -1; rooms[4].south = -1; rooms[4].east = 3; rooms[4].west = -1;
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

// Display Map
void displayMap(){
	
	printf("\n|Hall of Bones|         |Dark Cave|-------|Armory|                     N   \n");
	printf("       |                                   |                           |   \n");
	printf("       |                                   |                      W---------E \n");
	printf("       |                                   |                           |    \n");
	printf("       |                                   |                           S   \n");
	printf("|Dungeon Entrance|------------------|Treasure Room|                \n");
}
