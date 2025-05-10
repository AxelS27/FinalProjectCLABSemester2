#include <stdio.h>
#include <stdlib.h>

#include "../library/stock_menu.h"
#include "../library/main_menu.h"

// ini bstny bisa kamu edit propertynya terserah

typedef struct Item {
    int id;
    char name[15];
    int price;
} Item;

typedef struct Item_Node {
    Item data;
    struct Item_Node *left;
    struct Item_Node *right;
} Item_Node;

Item_Node* item_root = NULL;

Item_Node* create_item_node(Item item) {
    Item_Node* new_node = (Item_Node*)malloc(sizeof(Item_Node));
    new_node->data = item;
    new_node->left = new_node->right = NULL;
    return new_node;
}

void insert_item(Item_Node** root, Item item) {
    if (*root == NULL) {
        *root = create_item_node(item);
        printf("Item added successfully!\n");
        return;
    }

    if (item.id < (*root)->data.id) {
        insert_item(&(*root)->left, item);
    } else if (item.id > (*root)->data.id) {
        insert_item(&(*root)->right, item);
    } else {
        printf("Item with ID %d already exists!\n", item.id);
    }
}

Item_Node* find_item_min(Item_Node* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

void delete_item(Item_Node** root, int id) {
    if (*root == NULL) return;

    if (id < (*root)->data.id) {
        delete_item(&(*root)->left, id);
    } else if (id > (*root)->data.id) {
        delete_item(&(*root)->right, id);
    } else {
        if ((*root)->left == NULL) {
            Item_Node* temp = (*root)->right;
            free(*root);
            *root = temp;
        } else if ((*root)->right == NULL) {
            Item_Node* temp = (*root)->left;
            free(*root);
            *root = temp;
        } else {
            Item_Node* temp = find_item_min((*root)->right);
            (*root)->data = temp->data;
            delete_item(&(*root)->right, temp->data.id);
        }
    }
}

void in_order_items(Item_Node* root) {
    if (root == NULL) return;

    in_order_items(root->left);
    printf("| %-4d | %-14s | %-6d |\n", root->data.id, root->data.name, root->data.price);
    in_order_items(root->right);
}

// garap disini
void stock_menu(){
    int choice;

    while (1) {
        system("clear");
        printf("+------------------------------------------------+\n");
        printf("|                 STOCK UP CAFFEE                |\n");
        printf("|              Stock Management Menu             |\n");
        printf("|------------------------------------------------|\n");
        printf("|                                                |\n");
        printf("| [1] Add stock                                  |\n"); // nanti file stockny bisa di edit di database/stock.txt stylenya tar csv
        printf("| [2] Remove Stock                               |\n"); // contoh 001,americano,15,15000
        printf("|                                                |\n"); // (id,name,stock,price)
        printf("| [3] Edit item's property                       |\n"); // editny properti dari item (name,price bisa diganti)
        printf("|                                                |\n");
        printf("| [0] Back                                       |\n");
    	printf("|                                                |\n");
        printf("+------------------------------------------------+\n");
        printf(">> ");

        while (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
        }

        switch (choice) {
        	case 1:
        		// add_stock()
        		break;
        	case 2:
        		// remove_stock();
        		break;
        	case 3:
        		// edit_stock();
        		break;
        	case 0:
        		printf("Loading main menu...\n\n");
        		system("pause");
        		main_menu();
        		break;
        }
    }
}

void view_stock(){
    // buat tabel display stock	
}
