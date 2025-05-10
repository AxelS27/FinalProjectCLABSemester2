#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../library/cashier_menu.h"
#include "../library/main_menu.h"

Cart_Item cart[MAX_CART];
int cart_size = 0;


void order();
void history();
void add_item();
void remove_item();
void member();
void confirm_order();
void already_member();
void create_member();

void cashier_menu(){
	int choice;
	while (1) {
        system("clear");
        printf("+------------------------------------------------+\n");
        printf("|                 STOCK UP CAFFEE                |\n");
        printf("|                  Cashier Menu                  |\n");
        printf("|------------------------------------------------|\n");
        printf("|                                                |\n");
        printf("| [1] Order                                      |\n");
        printf("| [2] History                                    |\n");
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
        		order();
        		break;
        	case 2:
        		history();
        		break;
        	case 3:
        		break;
        	case 0:
        		printf("Loading main menu...\n\n");
        		system("pause");
        		main_menu();
        		break;
        }
	}
}

void order(){
	int choice;
	while (1) {
        system("clear");
        printf("+------------------------------------------------+\n");
        printf("|                 STOCK UP CAFFEE                |\n");
        printf("|                   Order Menu                   |\n");
        printf("|------------------------------------------------|\n");
        printf("|                                                |\n");
        printf("| [1] Add item                                   |\n");
        printf("| [2] Remove item                                |\n");
        printf("|                                                |\n");
        printf("| [3] Member                                     |\n");
        printf("|                                                |\n");
        printf("| [4] Confirm order                              |\n");
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
        		add_item();
        		break;
        	case 2:
        		remove_item();
        		break;
        	case 3:
        		member();
        		break;
        	case 4:
        		confirm_order();
        		break;
        	case 0:
        		printf("Loading cashier menu...\n\n");
        		system("pause");
        		cashier_menu();
        		break;
        }
	}
}

void add_item() {
    char item_name[30];
    int quantity;

    system("clear");
    printf("+------------------------------------------------+\n");
    printf("|                 STOCK UP CAFFEE                |\n");
    printf("|                  Add Item Menu                 |\n");
    printf("|------------------------------------------------|\n");
    printf("  Item's name : ");
    scanf(" %[^\n]", item_name);
    printf("  Quantity    : ");
    scanf("%d", &quantity);

    // Validasi dari item_stock.txt
    FILE *file = fopen("database/item_stock.txt", "r");
    if (file == NULL) {
        printf("Failed to open item_stock.txt!\n");
        system("pause");
        return;
    }

    char line[100];
    int item_found = 0;
    while (fgets(line, sizeof(line), file)) {
        int id, stock, price;
        char name[30];

        sscanf(line, "%d,%[^,],%d,%d", &id, name, &stock, &price);
        if (strcmp(name, item_name) == 0) {
            item_found = 1;
            break;
        }
    }
    fclose(file);

    if (!item_found) {
        printf("Item not found in stock!\n");
        system("pause");
        return;
    }

    // Add to cart
    int found_in_cart = 0;
    for (int i = 0; i < cart_size; i++) {
        if (strcmp(cart[i].name, item_name) == 0) {
            cart[i].quantity += quantity;
            found_in_cart = 1;
            break;
        }
    }

    if (!found_in_cart && cart_size < MAX_CART) {
        strcpy(cart[cart_size].name, item_name);
        cart[cart_size].quantity = quantity;
        cart_size++;
    }

    printf("Item added to cart!\n");
    system("pause");
}



void remove_item() {
    char item_name[30];
    int quantity;

    system("clear");
    printf("+------------------------------------------------+\n");
    printf("|                 STOCK UP CAFFEE                |\n");
    printf("|                 Remove Item Menu               |\n");
    printf("|------------------------------------------------|\n");
    printf("  Item's name : ");
    scanf(" %[^\n]", item_name);
    printf("  Quantity    : ");
    scanf("%d", &quantity);

    for (int i = 0; i < cart_size; i++) {
        if (strcmp(cart[i].name, item_name) == 0) {
            if (quantity >= cart[i].quantity) {
                // Remove item
                for (int j = i; j < cart_size - 1; j++) {
                    cart[j] = cart[j + 1];
                }
                cart_size--;
            } else {
                cart[i].quantity -= quantity;
            }
            printf("Item removed from cart.\n");
            system("pause");
            return;
        }
    }

    printf("Item not found in cart.\n");
    system("pause");
}


void member(){
	int choice;
	while (1) {
        system("clear");
        printf("+------------------------------------------------+\n");
        printf("|                 STOCK UP CAFFEE                |\n");
        printf("|                  Member Menu                   |\n");
        printf("|------------------------------------------------|\n");
        printf("|                                                |\n");
        printf("| [1] Already member                             |\n");
        printf("| [2] Create member                              |\n");
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
        		already_member();
        		break;
        	case 2:
        		create_member();
        		break;
        	case 3:
        		break;
        	case 0:
        		printf("Loading order menu...\n\n");
        		system("pause");
        		order();
        		break;
        }
	}
}

void already_member() {
    char phone[20];
    FILE *fp = fopen("database/profiles/member/member_data.txt", "r");
    if (!fp) {
        printf("Failed to open member data.\n");
        system("pause");
        return;
    }

    printf("+------------------------------------------------+\n");
    printf("|               Already Member Menu              |\n");
    printf("+------------------------------------------------+\n");
    printf("  No Handphone : ");
    scanf(" %[^\n]", phone);

    char name[50], phone_data[20];
    int found = 0;
    while (fscanf(fp, "%[^,],%s\n", name, phone_data) != EOF) {
        if (strcmp(phone, phone_data) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found) {
        printf("Member verified: %s\n", name);
        system("pause");
        order();
    } else {
        printf("Phone number not registered.\n\n");
        system("pause");
        member();
    }
}


void create_member() {
    char name[50], phone[20];
    FILE *fp = fopen("database/profiles/member/member_data.txt", "a");

    if (!fp) {
        printf("Failed to open member data.\n");
        system("pause");
        return;
    }

    printf("+------------------------------------------------+\n");
    printf("|                Create Member Menu              |\n");
    printf("+------------------------------------------------+\n");

    // Validasi nama
    while (1) {
        printf("  Input Name   : ");
        scanf("%s", name);

        int length = strlen(name);
        int valid = (length >= 3 && length <= 10);

        for (int i = 0; i < length && valid; i++) {
            if (name[i] == ' ') {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("  >> Name must be 3–10 characters and contain no spaces.\n");
        } else {
            break;
        }
    }

    // Validasi nomor telepon
    while (1) {
        printf("  No Handphone : ");
        scanf("%s", phone);

        int length = strlen(phone);
        int valid = (length >= 8 && length <= 13);

        for (int i = 0; i < length && valid; i++) {
            if (phone[i] < '0' || phone[i] > '9') {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("  >> Phone number must be 8–13 digits and numeric only.\n");
        } else {
            break;
        }
    }

    fprintf(fp, "%s,%s\n", name, phone);
    fclose(fp);

    printf("\nMember created successfully!\n\n");
    system("pause");
}


void confirm_order() {
    system("clear");
    printf("+------------------------------------------------+\n");
    printf("|                 STOCK UP CAFFEE                |\n");
    printf("|                Confirm Order Menu              |\n");
    printf("+------------------------------------------------+\n");

    if (cart_size == 0) {
        printf("  Cart is empty.\n");
        system("pause");
        return;
    }

    int grand_total = 0;

    for (int i = 0; i < cart_size; i++) {
        // Cari harga item dari item_stock.txt
        FILE *fp = fopen("database/item_stock.txt", "r");
        if (!fp) {
            printf("Failed to open item_stock.txt\n");
            system("pause");
            return;
        }

        char line[100];
        int id, stock, price, found = 0;
        char name[30];

        while (fgets(line, sizeof(line), fp)) {
            sscanf(line, "%d,%[^,],%d,%d", &id, name, &stock, &price);
            if (strcmp(name, cart[i].name) == 0) {
                int total_price = price * cart[i].quantity;
                printf("  %-25s x%2d  @Rp%-6d  = Rp%-6d\n", name, cart[i].quantity, price, total_price);
                grand_total += total_price;
                found = 1;
                break;
            }
        }

        fclose(fp);

        if (!found) {
            printf("  %-25s x%2d  @Unknown Price\n", cart[i].name, cart[i].quantity);
        }
    }

    printf("--------------------------------------------------\n");
    printf("  Grand Total: Rp%d\n", grand_total);
    printf("--------------------------------------------------\n");

    system("pause");
}

void history(){
	
}


