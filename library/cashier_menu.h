#pragma once
#define MAX_CART 100

typedef struct {
    char name[30];
    int quantity;
} Cart_Item;

extern Cart_Item cart[MAX_CART];
extern int cart_size;
void cashier_menu();
