#include <stdio.h>
#include <stdlib.h>

#include "../library/main_menu.h"

// ini bstny bisa kamu edit propertynya terserah

typedef struct Item {
    int id;
    char name[15];
    int price;
} Item;

typedef struct ItemNode {
    Item data;
    struct ItemNode *left;
    struct ItemNode *right;
} ItemNode;

ItemNode* item_root = NULL;

ItemNode* create_item_node(Item item) {
    ItemNode* new_node = (ItemNode*)malloc(sizeof(ItemNode));
    new_node->data = item;
    new_node->left = new_node->right = NULL;
    return new_node;
}

void insert_item(ItemNode** root, Item item) {
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

ItemNode* find_item_min(ItemNode* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

void delete_item(ItemNode** root, int id) {
    if (*root == NULL) return;

    if (id < (*root)->data.id) {
        delete_item(&(*root)->left, id);
    } else if (id > (*root)->data.id) {
        delete_item(&(*root)->right, id);
    } else {
        if ((*root)->left == NULL) {
            ItemNode* temp = (*root)->right;
            free(*root);
            *root = temp;
        } else if ((*root)->right == NULL) {
            ItemNode* temp = (*root)->left;
            free(*root);
            *root = temp;
        } else {
            ItemNode* temp = find_item_min((*root)->right);
            (*root)->data = temp->data;
            delete_item(&(*root)->right, temp->data.id);
        }
    }
}

void in_order_items(ItemNode* root) {
    if (root == NULL) return;

    in_order_items(root->left);
    printf("| %-4d | %-14s | %-6d |\n", root->data.id, root->data.name, root->data.price);
    in_order_items(root->right);
}

// garap disini

void stock_menu(){
	// buat add stock
	// buat remove stock
	// edit item property (id,name,price)
	// dll
}

void view_stock(){
    // buat tabel display stock	
}
