#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <string.h>

// Constants
#define MAX_INVENTORY 10
#define MAX_NAME_LEN 50

// Player Structure
typedef struct {
    char name[MAX_NAME_LEN];
    int health;
    int strength;
    int inventoryCapacity;
    int inventorySize;
    char inventory[MAX_INVENTORY][MAX_NAME_LEN];
} Player;

// Function Prototypes
void initializePlayer(Player *player);
void inventory(Player *player);

#endif // PLAYER_H

