#pragma once

typedef struct {
    char name[50];
    int quantity;
    int price;
} Cart_Item;

extern Cart_Item cart[100];
extern int cart_size;

void cashier_menu(const char *username);
