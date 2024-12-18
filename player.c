#include "player.h"

#define MAX_INVENTORY 10
#define MAX_NAME_LEN 50



// Initialize Player
void initializePlayer(Player *player) {
    strcpy(player->name, "Hero");
    player->health = 100;
    player->strength = 20;
    player->inventoryCapacity = MAX_INVENTORY;
    player->inventorySize = 0;
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

