
#pragma once
#define MAX_CART 100

typedef struct {
    char name[50];
    int quantity;
    int price;
} Cart_Item;

extern Cart_Item cart[MAX_CART];   // Hanya deklarasi, bukan definisi
extern int cart_size;

void cashier_menu(const char *username);
