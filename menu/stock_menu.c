//=====[[ C Library ]]=====
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    printf("| %-4d | %-14s | %-6d | %-6d |\n", root->data.id, root->data.name, root->data.price, root->data.stock);
    in_order_items(root->right);
}

Item_Node* search_item(Item_Node* root, int id) {
    if (!root) return NULL;
    if (id == root->data.id) return root;
    if (id < root->data.id) return search_item(root->left, id);
    return search_item(root->right, id);
}

//=====[[ Procedure/Function ]]=====
void save_stock_recursive(FILE* fp, Item_Node* root) {
    if (!root) return;
    save_stock_recursive(fp, root->left);
    fprintf(fp, "%d,%s,%d,%d\n", root->data.id, root->data.name, root->data.stock, root->data.price);
    save_stock_recursive(fp, root->right);
}

void save_stock_to_file(const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Failed to save stock to file.\n");
        return;
    }
    save_stock_recursive(fp, item_root);
    fclose(fp);
    printf("Stock saved successfully to %s.\n", filename);
}

void load_stock_from_file(const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("No stock file found, starting with empty data.\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), fp)) {
        Item item;
        sscanf(line, "%d,%14[^,],%d,%d", &item.id, item.name, &item.stock, &item.price);
        insert_item(&item_root, item);
    }
    fclose(fp);
    printf("Stock loaded from %s.\n", filename);
    system("pause");
}

void add_stock(){
	system("cls");
    Item newItem;
  	printf("Enter item ID: ");
   	scanf("%d", &newItem.id);
	getchar();
	printf("Enter item name: ");
    scanf(" %[^\n]", newItem.name);
    newItem.name[strcspn(newItem.name, "\n")] = '\0';
    printf("Enter item price: ");
    scanf("%d", &newItem.price);
    printf("Enter item stock: ");
    scanf("%d", &newItem.stock);

	insert_item(&item_root, newItem);
	save_stock_to_file("database/item_stock.txt");
	system("pause");
	
}

void remove_stock(){
	system("cls");
	load_stock_from_file("dataStock.txt");
    int id;
   	printf("Enter ID to remove: ");
   	scanf("%d", &id);
   	Item_Node* node = search_item(item_root, id);
  	if (!node) {
  	printf("Item not found.\n");
   	} else{
   		delete_item(&item_root, id);
   		printf("Item removed.\n");
	}
	
	save_stock_to_file("item_tock.txt");
   	system("pause");	   	
}

void edit_stock(){
	system("cls");
	load_stock_from_file("item_stock.txt");
	int id;
    printf("Enter ID to edit: ");
    scanf("%d", &id);

    Item_Node* node = search_item(item_root, id);
    if (!node) {
       	printf("Item not found.\n");
	} else {
	    printf("Current Name: %s | Price: %d   |  Stock: %d\n", node->data.name, node->data.price, node->data.stock);
	    printf("Enter new name (press enter to skip): ");
	    getchar();
	    char new_name[15];
	    fgets(new_name, sizeof(new_name), stdin);
	    if (strcmp(new_name, "\n") != 0) {
		    new_name[strcspn(new_name, "\n")] = '\0';
	        strcpy(node->data.name, new_name);
	    }
			
		printf("Enter new price (-1 to skip): ");
	    int new_price;
	    scanf("%d", &new_price);
	    if (new_price != -1) node->data.price = new_price;
			        
	    printf("Enter new stock (-1 to skip): ");
	    int new_stock;
	    scanf("%d", &new_stock);
	    if (new_price != -1) node->data.stock = new_stock;
			
		save_stock_to_file("database/item_stock.txt");
		printf("Item updated successfully.\n");
	}
	system("pause");
}

void view_stock(const char *username) {
    system("cls");
    load_stock_from_file("database/item_stock.txt");
    printf("+------------------------------------------------+\n");
    printf("| User: %-10s                               |\n", username); 
    printf("|                   STOCK LIST                   |\n");
    printf("+------------------------------------------------+\n");
    printf("| ID   | Name           | Stock | Price  |\n");
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
        printf("|                                                |\n");
        printf("| [1] Add stock                                  |\n");
        printf("| [2] Remove Stock                               |\n");
        printf("|                                                |\n");
        printf("| [3] Edit item's property                       |\n");
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
        		add_stock();
        		break;
        	case 2:
				remove_stock();
        		break;
        	case 3:
        		edit_stock();
        		break;
        	case 0:
        		printf("Loading main menu...\n\n");
        		system("pause");
        		main_menu(username);
        		break;
        }
    }
}
