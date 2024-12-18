#ifndef ROOM_H
#define ROOM_H

#define MAX_NAME_LEN 50
#define MAX_ROOMS 5

typedef struct {
    char name[MAX_NAME_LEN];
    char description[200];
    int hasItem;  // 1 if item exists
    char itemName[MAX_NAME_LEN];
    int hasMonster;
    char monsterName[MAX_NAME_LEN];
    int monsterHealth;
    int monsterStrength;
    int north, south, east, west; // Connected rooms
} Room;

void initializeRooms(Room rooms[]);
void look(Room *room);
void move(Room rooms[], int *currentRoom, char direction[10]);
void displayMap();


#endif
