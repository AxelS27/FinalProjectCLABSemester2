//=====[[ C Library ]]=====
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//=====[[ Custom Library ]]=====
#include "../library/stock_menu.h"
#include "../library/main_menu.h"

//=====[[ BST's Code ]]=====
typedef struct Item {
    int id;
    char name[15];
    int price;
    int stock;
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
        return;
    }

    if (item.id < (*root)->data.id) {
        insert_item(&(*root)->left, item);
    } else if (item.id > (*root)->data.id) {
        insert_item(&(*root)->right, item);
    } else {
        printf("-> Item with ID %d already exists!\n\n", item.id);
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
    printf("| %-4d | %-14s | %-8d | %-11d |\n", root->data.id, root->data.name, root->data.price, root->data.stock);
    in_order_items(root->right);
}

Item_Node* search_item(Item_Node* root, int id) {
    if (!root) return NULL;
    if (id == root->data.id) return root;
    if (id < root->data.id) return search_item(root->left, id);
    return search_item(root->right, id);
}

bool is_duplicate_name(const char *name) {
    Item_Node *curr = item_root;
    while (curr) {
        int cmp = strcmp(name, curr->data.name);
        if (cmp == 0) return true;
        curr = (cmp < 0) ? curr->left : curr->right;
    }
    return false;
}

void free_bst(Item_Node* root) {
    if (!root) return;
    free_bst(root->left);
    free_bst(root->right);
    free(root);
}

//=====[[ Save/Load Stock ]]=====
void save_stock_recursive(FILE* fp, Item_Node* root) {
    if (!root) return;
    save_stock_recursive(fp, root->left);
    fprintf(fp, "%d,%s,%d,%d\n", root->data.id, root->data.name, root->data.stock, root->data.price);
    save_stock_recursive(fp, root->right);
}

void save_stock_to_file(const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("-> Failed to save stock to file.\n");
        return;
    }
    save_stock_recursive(fp, item_root);
    fclose(fp);
}

void load_stock_from_file(const char* filename) {
    free_bst(item_root);
    item_root = NULL;

    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("-> No stock file found, starting with empty data.\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), fp)) {
        Item item;
        sscanf(line, "%d,%14[^,],%d,%d", &item.id, item.name, &item.stock, &item.price);
        insert_item(&item_root, item);
    }
    fclose(fp);
}

//=====[[ Menu Functions ]]=====
void add_stock(const char *username) {
    system("cls");
    load_stock_from_file("database/item_stock.txt");

    Item newItem;
    printf("+------------------------------------------------+\n");
    printf("| User: %-40s |\n", username);                   
    printf("|                 STOCK UP CAFFEE                |\n");
    printf("|                 Add Stock Menu                 |\n");
    printf("+------------------------------------------------+\n");

    while (1) {
        printf("  Enter item ID: ");
        if (scanf("%d", &newItem.id) != 1) {
            printf("-> Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        if (search_item(item_root, newItem.id)) {
            printf("-> Error: ID already exists. Please enter a different ID.\n");
        } else {
            break;
        }
    }

    while (1) {
        printf("  Enter item name: ");
        fgets(newItem.name, sizeof(newItem.name), stdin);
        newItem.name[strcspn(newItem.name, "\n")] = '\0';

        if (is_duplicate_name(newItem.name)) {
            printf("-> Error: Name already exists. Please enter a different name.\n");
        } else {
            break;
        }
    }

    while (1) {
        printf("  Enter item price: ");
        if (scanf("%d", &newItem.price) != 1) {
            printf("-> Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        if (newItem.price < 0) {
            printf("-> Price cannot be negative!\n");
        } else break;
    }

    while (1) {
        printf("  Enter item stock: ");
        if (scanf("%d", &newItem.stock) != 1) {
            printf("-> Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }
        if (newItem.stock < 0) {
            printf("-> Stock cannot be negative!\n");
        } else break;
    }

    printf("+------------------------------------------------+\n");
    insert_item(&item_root, newItem);
    save_stock_to_file("database/item_stock.txt");
    system("pause");
}

void remove_stock(const char *username) {
    system("cls");
    load_stock_from_file("database/item_stock.txt");
    printf("+------------------------------------------------+\n");
    printf("| User: %-40s |\n", username);                   
    printf("|                 STOCK UP CAFFEE                |\n");
    printf("|               Remove Stock Menu                |\n");
    printf("+------------------------------------------------+\n");
    int id;
    while (1) {
        printf("  Enter ID to remove: ");
        if (scanf("%d", &id) != 1) {
            printf("-> Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        } else break;
    }

    printf("+------------------------------------------------+\n");
    Item_Node* node = search_item(item_root, id);
    if (!node) {
        printf("-> Item not found.\n");
    } else {
        delete_item(&item_root, id);
        printf("-> Item removed.\n\n");
    }

    save_stock_to_file("database/item_stock.txt");
    system("pause");
}

void edit_stock(const char *username) {
    system("cls");
    load_stock_from_file("database/item_stock.txt");
	
	printf("+------------------------------------------------+\n");
    printf("| User: %-40s |\n", username);                   
    printf("|                 STOCK UP CAFFEE                |\n");
    printf("|                 Edit Stock Menu                |\n");
    printf("+------------------------------------------------+\n");
	
    int id;
    while (1) {
        printf("  Enter ID to edit: ");
        if (scanf("%d", &id) != 1) {
            printf("-> Invalid input. Try again.\n");
            while (getchar() != '\n');
            continue;
        } else break;
    }

    Item_Node* node = search_item(item_root, id);



    if (!node) {
        printf("-> Item not found.\n");
    } else {
        printf("-> Current Name: %s | Price: %d | Stock: %d\n\n", node->data.name, node->data.price, node->data.stock);
        printf("  Enter new name (press enter to skip): ");
        while (getchar() != '\n');
        char new_name[15];
        fgets(new_name, sizeof(new_name), stdin);
        if (strcmp(new_name, "\n") != 0) {
            new_name[strcspn(new_name, "\n")] = '\0';

            if (strcmp(new_name, node->data.name) != 0 && is_duplicate_name(new_name)) {
                printf("-> Error: Item name already exists.\n");
                system("pause");
                return;
            }

            strcpy(node->data.name, new_name);
        }

        int new_price;
        printf("  Enter new price (-1 to skip): ");
        scanf("%d", &new_price);
        if (new_price >= 0) node->data.price = new_price;

        int new_stock;
        printf("  Enter new stock (-1 to skip): ");
        scanf("%d", &new_stock);
        if (new_stock >= 0) node->data.stock = new_stock;

        save_stock_to_file("database/item_stock.txt");
        printf("\n-> Item updated successfully.\n\n");
    }
    system("pause");
}

void view_stock(const char *username) {
    system("cls");
    load_stock_from_file("database/item_stock.txt");
    printf("+------------------------------------------------+\n");
    printf("| User: %-40s |\n", username);     
    printf("|                   STOCK LIST                   |\n");
    printf("+------------------------------------------------+\n");
    printf("| ID   | Name           | Stock    | Price       |\n");
    printf("+------------------------------------------------+\n");
    in_order_items(item_root);
    printf("+------------------------------------------------+\n");
    system("pause");
}

void stock_menu(const char *username){
    int choice;
    while (1) {
        system("cls");
        printf("+------------------------------------------------+\n");
        printf("| User: %-10s                               |\n", username); 
        printf("|                 STOCK UP CAFFEE                |\n");
        printf("|              Stock Management Menu             |\n");
        printf("|------------------------------------------------|\n");
        printf("| [1] Add stock                                  |\n");
        printf("| [2] Remove Stock                               |\n");
        printf("|                                                |\n");
        printf("| [3] Edit item's property                       |\n");
        printf("|                                                |\n");
        printf("| [0] Back                                       |\n");
        printf("+------------------------------------------------+\n");
        printf(">> ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: add_stock(username); break;
            case 2: remove_stock(username); break;
            case 3: edit_stock(username); break;
            case 0:
                printf("Loading main menu...\n\n");
                system("pause");
                main_menu(username);
                return;
        }
    }
}

