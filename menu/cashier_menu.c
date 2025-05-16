#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "../library/cashier_menu.h"
#include "../library/main_menu.h"

Cart_Item cart[100];
int cart_size;

char member_name[50] = "notmember";
int member_points = 0;
bool is_member = false;

void order(const char *username);
void history(const char *username);
void add_item(const char *username);
void remove_item(const char *username);
void member(const char *username);
void confirm_order(const char *username);
void already_member(const char *username);
void create_member(const char *username);

void cashier_menu(const char *username) {
    int choice;
    while (1) {
        system("cls");
        printf("+------------------------------------------------+\n");
        printf("| User: %-10s                               |\n", username);
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
                order(username);
                break;
            case 2:
                history(username);
                break;
            case 0:
                printf("Loading main menu...\n\n");
                system("pause");
                main_menu(username);
                return;
        }
    }
}

void order(const char *username){
	int choice;
	while (1) {
        system("cls");
        printf("+------------------------------------------------+\n");
    	printf("| User: %-10s                               |\n", username);
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
        		add_item(username);
        		break;
        	case 2:
        		remove_item(username);
        		break;
        	case 3:
        		member(username);
        		break;
        	case 4:
        		confirm_order(username);
        		break;
        	case 0:
        		printf("Loading cashier menu...\n\n");
        		system("pause");
        		cashier_menu(username);
        		break;
        }
	}
}

void add_item(const char *username) {
    char item_name[30];
    int quantity;

    system("cls");
    printf("+------------------------------------------------+\n");
    printf("| User: %-10s                                    |\n", username);
    printf("|                 STOCK UP CAFFEE                |\n");
    printf("|                  Add Item Menu                 |\n");
    printf("|------------------------------------------------|\n");
    printf("  Item's name : ");
    scanf(" %[^\n]", item_name);
    printf("  Quantity    : ");
    scanf("%d", &quantity);

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

    int found_in_cart = 0;
    for (int i = 0; i < cart_size; i++) {
        if (strcmp(cart[i].name, item_name) == 0) {
            cart[i].quantity += quantity;
            found_in_cart = 1;
            break;
        }
    }

    if (!found_in_cart && cart_size < 100) {
        strcpy(cart[cart_size].name, item_name);
        cart[cart_size].quantity = quantity;
        cart_size++;
    }

    printf("Item added to cart!\n");
    system("pause");
}



void remove_item(const char *username) {
    char item_name[30];
    int quantity;

    system("cls");
    printf("+------------------------------------------------+\n");
    printf("| User: %-10s                                    |\n", username);
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


void member(const char *username){
	int choice;
	while (1) {
        system("cls");
        printf("+------------------------------------------------+\n");
        printf("| User: %-10s                                    |\n", username);
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
        		already_member(username);
        		break;
        	case 2:
        		create_member(username);
        		break;
        	case 3:
        		break;
        	case 0:
        		printf("Loading order menu...\n\n");
        		system("pause");
        		order(username);
        		break;
        }
	}
}

void already_member(const char *username) {
    char phone[20];
    FILE *fp = fopen("database/profiles/member/member_data.txt", "r");
    if (!fp) {
        printf("Failed to open member data.\n");
        system("pause");
        return;
    }

    printf("+------------------------------------------------+\n");
    printf("| User: %-10s                                    |\n", username);
    printf("|               Already Member Menu              |\n");
    printf("+------------------------------------------------+\n");
    printf("  No Handphone : ");
    scanf(" %[^\n]", phone);

    char name[50], phone_data[20];
    int points;
    bool found = false;
    char line[128];

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "%[^,],%[^,],%d", name, phone_data, &points) == 3) {
            if (strcmp(phone, phone_data) == 0) {
                found = true;
                break;
            }
        }
    }
    fclose(fp);

    if (found) {
        strcpy(member_name, name);
        member_points = points;
        is_member = true;
        printf("  >> Member verified: %s\n", member_name);
        system("pause");
        order(username);
    } else {
        printf("  >> Phone number not registered.\n\n");
        system("pause");
        member(username);
    }
}

void create_member(const char *username) {
    char name[50], phone[20];
    FILE *fp;

    printf("+------------------------------------------------+\n");
    printf("| User: %-10s                                    |\n", username);
    printf("|                Create Member Menu              |\n");
    printf("+------------------------------------------------+\n");

    while (1) {
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

        fp = fopen("database/profiles/member/member_data.txt", "r");
        int duplicate = 0;
        if (fp) {
            char existing_name[50], existing_phone[20];
            int existing_points;

            while (fscanf(fp, "%[^,],%[^,],%d\n", existing_name, existing_phone, &existing_points) != EOF) {
                if (strcmp(phone, existing_phone) == 0) {
                    printf("  >> This phone number is already registered.\n");
                    duplicate = 1;
                    break;
                }
                if (strcmp(name, existing_name) == 0) {
                    printf("  >> This name is already registered.\n");
                    duplicate = 1;
                    break;
                }
            }
            fclose(fp);
        }

        if (duplicate) {
            printf("Please enter the details again.\n\n");
            continue;
        }

        break;
    }

    fp = fopen("database/profiles/member/member_data.txt", "a");
    if (!fp) {
        printf("Failed to open member data.\n");
        system("pause");
        return;
    }

    fprintf(fp, "%s,%s,0\n", name, phone);
    fclose(fp);

    printf("\nMember created successfully!\n\n");
    system("pause");
}


void confirm_order(const char *username) {
    system("cls");
    while (1) {
        printf("+------------------------------------------------+\n");
        printf("| User: %-10s                                    |\n", username);
        printf("|                 STOCK UP CAFFEE                |\n");
        printf("|                Confirm Order Menu              |\n");
        printf("+------------------------------------------------+\n");

        if (cart_size == 0) {
            printf("  Cart is empty.\n");
            system("pause");
            return;
        }

        typedef struct {
            int id, stock, price;
            char name[30];
        } StockItem;

        StockItem stock_items[100];
        int stock_count = 0;

        FILE *fp = fopen("database/item_stock.txt", "r");
        if (!fp) {
            printf("Failed to open item_stock.txt\n");
            system("pause");
            return;
        }

        char line[100];
        while (fgets(line, sizeof(line), fp)) {
            if (sscanf(line, "%d,%[^,],%d,%d", &stock_items[stock_count].id,
                       stock_items[stock_count].name,
                       &stock_items[stock_count].stock,
                       &stock_items[stock_count].price) == 4) {
                stock_count++;
            }
        }
        fclose(fp);

        int grand_total = 0;
        for (int i = 0; i < cart_size; i++) {
            for (int j = 0; j < stock_count; j++) {
                if (strcmp(stock_items[j].name, cart[i].name) == 0) {
                    int total_price = stock_items[j].price * cart[i].quantity;
                    printf("  %-25s x%2d  @Rp%-6d  = Rp%-6d\n",
                           cart[i].name, cart[i].quantity, stock_items[j].price, total_price);
                    grand_total += total_price;
                    break;
                }
            }
        }

        printf("--------------------------------------------------\n");

        int discount = 0;
        int points_used = 0;
        if (is_member) {
            discount = (member_points / 3) * 10000;
            if (discount > grand_total) {
                discount = (grand_total / 10000) * 10000;
            }
            points_used = (discount / 10000) * 3;

            printf("  Member : %s\n", member_name);
            printf("  Points : %d\n", member_points);
            printf("  Discount: Rp%d (used %d points)\n", discount, points_used);
        }

        printf("  Grand Total: Rp%d\n", grand_total - discount);
        printf("--------------------------------------------------\n");
        printf(" [1] Confirm\n");
        printf(" [2] Back\n");
        printf(" >> ");

        int user_choice;
        while (scanf("%d", &user_choice) != 1) {
            while (getchar() != '\n');
        }

        if (user_choice == 1) {
            if (is_member) {
                member_points -= points_used;
                int earned_points = (grand_total / 20000) * 3;
                member_points += earned_points;

                FILE *fp = fopen("database/profiles/member/member_data.txt", "r");
                FILE *temp = fopen("database/profiles/member/temp.txt", "w");
                if (!fp || !temp) {
                    printf("Failed to update member data.\n");
                    system("pause");
                    return;
                }

                char name[50], phone[20];
                int points;
                while (fgets(line, sizeof(line), fp)) {
                    if (sscanf(line, "%[^,],%[^,],%d", name, phone, &points) == 3) {
                        if (strcmp(name, member_name) == 0) {
                            fprintf(temp, "%s,%s,%d\n", name, phone, member_points);
                        } else {
                            fprintf(temp, "%s,%s,%d\n", name, phone, points);
                        }
                    }
                }

                fclose(fp);
                fclose(temp);
                remove("database/profiles/member/member_data.txt");
                rename("database/profiles/member/temp.txt", "database/profiles/member/member_data.txt");
            }

            FILE *stock_fp = fopen("database/item_stock.txt", "w");
            if (!stock_fp) {
                printf("Failed to update stock.\n");
                system("pause");
                return;
            }

            for (int i = 0; i < stock_count; i++) {
                for (int j = 0; j < cart_size; j++) {
                    if (strcmp(stock_items[i].name, cart[j].name) == 0) {
                        stock_items[i].stock -= cart[j].quantity;
                        if (stock_items[i].stock < 0) stock_items[i].stock = 0;
                    }
                }
                fprintf(stock_fp, "%d,%s,%d,%d\n", stock_items[i].id,
                        stock_items[i].name, stock_items[i].stock, stock_items[i].price);
            }
            fclose(stock_fp);

            FILE *hist = fopen("database/history_transaction.txt", "a");
            if (hist) {
                for (int i = 0; i < cart_size; i++) {
                    for (int j = 0; j < stock_count; j++) {
                        if (strcmp(stock_items[j].name, cart[i].name) == 0) {
                            fprintf(hist, "%s/%d/%d,", cart[i].name, cart[i].quantity, stock_items[j].price);
                            break;
                        }
                    }
                }
                fprintf(hist, "%s, diskon:%d\n", member_name, discount);
                fclose(hist);
            }

            char path[100];
            sprintf(path, "database/profiles/user/%s.txt", username);

            FILE *userfp = fopen(path, "r+");
            if (userfp) {
                char uname[50];
                int handled;

                if (fscanf(userfp, "%[^,],%d", uname, &handled) == 2) {
                    rewind(userfp);
                    fprintf(userfp, "%s,%d\n", uname, handled + 1);
                } else {
                    printf("Failed to read user data format.\n");
                }

                fclose(userfp);
            } else {
                printf("Failed to open user file for handled update.\n");
                system("pause");
            }

            printf("\nOrder confirmed!\n\n");
            cart_size = 0;
            system("pause");
            cashier_menu(username);
        } else if (user_choice == 2) {
            order(username);
        }
    }
}

void history(const char *username) {
    FILE *fp = fopen("database/history_transaction.txt", "r");
    if (!fp) {
        printf("Failed to open history_transaction.txt\n");
        system("pause");
        return;
    }

    typedef struct {
        char items[10][50];
        int item_qty[10];
        int item_price[10];
        int item_count;
        int discount;
        char member_name[50];
        int total;
        int id;
    } Transaction;

    Transaction transactions[1000];
    int count = 0;
    char line[512];

	void parse_transaction_line(char *line, Transaction *t) {
	    t->item_count = 0;
	    t->discount = 0;
	    t->total = 0;
	    t->member_name[0] = '\0';
	    
	    char *discount_ptr = strstr(line, ", diskon:");
	    if (!discount_ptr) return;
	
	    *discount_ptr = '\0';
	    discount_ptr += 8;
	    t->discount = atoi(discount_ptr);

	    char *tokens[20];
	    int token_count = 0;
	    char *token = strtok(line, ",");
	    while (token != NULL && token_count < 20) {
	        while (*token == ' ') token++;
	
	        tokens[token_count++] = token;
	        token = strtok(NULL, ",");
	    }
	
	    if (token_count == 0) return;
	
	    strcpy(t->member_name, tokens[token_count - 1]);
	
	    for (int i = 0; i < token_count - 1 && i < 10; i++) {
	        int qty = 0, price = 0;
	        char item_name[50] = {0};
	
	        if (sscanf(tokens[i], "%[^/]/%d/%d", item_name, &qty, &price) == 3) {
	            strcpy(t->items[t->item_count], item_name);
	            t->item_qty[t->item_count] = qty;
	            t->item_price[t->item_count] = price;
	            t->total += qty * price;
	            t->item_count++;
	        }
	    }
	}


    void print_transaction_table(Transaction *t, int index) {
        printf("\n\n\n\n+------------------------------------------------+\n");
        printf("  Transaction #%d                                   \n", index);
        printf("+------------------------------------------------+\n");
        printf("  %-25s %5s %10s\n", "Item", "Qty", "Price (Rp)");
        printf("+------------------------------------------------+\n");
        for (int i = 0; i < t->item_count; i++) {
            printf("  %-25s %5d %10d\n", t->items[i], t->item_qty[i], t->item_price[i]);
        }
        printf("+------------------------------------------------+\n");
        printf("  Member  : %s\n", t->member_name[0] ? t->member_name : "No");
        printf("  Discount: Rp%d\n", t->discount);
        printf("  Total   : Rp%d\n", t->total - t->discount);
        printf("+------------------------------------------------+\n");
    }

    while (fgets(line, sizeof(line), fp) && count < 1000) {
        line[strcspn(line, "\r\n")] = 0;
        parse_transaction_line(line, &transactions[count]);
        transactions[count].id = count + 1;
        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("No transactions found.\n");
        system("pause");
        return;
    }

    int items_per_page = 0;
    do {
        printf("Enter how many transactions to show per page (1-20): ");
        if (scanf("%d", &items_per_page) != 1) {
            while (getchar() != '\n');
            items_per_page = 0;
        }
    } while (items_per_page < 1 || items_per_page > 20);
    while(getchar() != '\n');

    int filter_member_only = 0;
    int filter_total_cmp = 0;
    int filter_total_value = 0;
    char search_member[50] = "";
    int search_id = 0;

    int matches_filter(Transaction *t) {
        if (filter_member_only && t->member_name[0] == '\0') return 0;

        if (filter_total_cmp == 1 && (t->total - t->discount) <= filter_total_value) return 0;
        if (filter_total_cmp == 2 && (t->total - t->discount) >= filter_total_value) return 0;

        if (search_id > 0 && t->id != search_id) return 0;

        if (search_member[0] != '\0') {
            char member_lower[50], search_lower[50];
            for (int i = 0; t->member_name[i]; i++)
                member_lower[i] = tolower(t->member_name[i]);
            member_lower[strlen(t->member_name)] = 0;
            for (int i = 0; search_member[i]; i++)
                search_lower[i] = tolower(search_member[i]);
            search_lower[strlen(search_member)] = 0;
            if (!strstr(member_lower, search_lower)) return 0;
        }

        return 1;
    }

    Transaction filtered[1000];
    int filtered_count = 0;

    void apply_filters() {
        filtered_count = 0;
        for (int i = 0; i < count; i++) {
            if (matches_filter(&transactions[i])) {
                filtered[filtered_count++] = transactions[i];
            }
        }
    }

    apply_filters();

    if (filtered_count == 0) {
        printf("No transactions matched your filter/search.\n");
        system("pause");
        return;
    }

    int page = 0;
    int max_page = (filtered_count + items_per_page - 1) / items_per_page;
    char input;

    while (1) {
        system("cls");
        printf("+==================== Transaction History ====================+\n");
        printf("  Filters: Member only: %s | Total ",
               filter_member_only ? "Yes" : "No");
        if (filter_total_cmp == 1) printf("> %d", filter_total_value);
        else if (filter_total_cmp == 2) printf("< %d", filter_total_value);
        else printf("= None");
        printf("   Search by ID: %d | Search by Member: %s\n",
               search_id, search_member[0] ? search_member : "None");
        printf("+============================================================+\n");

        int start = page * items_per_page;
        int end = start + items_per_page;
        if (end > filtered_count) end = filtered_count;

        for (int i = start; i < end; i++) {
            print_transaction_table(&filtered[i], filtered[i].id);
        }
		
        printf("\n+=======================================+\nPage %d of %d\n", page + 1, max_page);
        printf("\n[1] Previous\n[2] Next\n\n[3] Set Sort/Filter/Search\n\n[0] Back\n+=======================================+\n");
        printf(">>");

        input = getchar();
        while (getchar() != '\n');

        if (input == '0') {
            break;
        } else if (input == '1') {
            if (page > 0) page--;
        } else if (input == '2') {
            if (page < max_page -1) page++;
        } else if (input == '3') {
            int filter_option = -1;
            do {
                system("cls");
                printf("+============== Set Sort/Filter/Search ===============+\n");
                printf("  [1] Toggle Member Only Filter (Current: %s)\n", filter_member_only ? "On" : "Off");
                printf("  [2] Set Total Price Filter (> or <)\n\n");
                printf("  [3] Search by Transaction ID\n");
                printf("  [4] Search by Member Name\n\n");
                printf("  [5] Clear All Filters/Search\n\n");
                printf("  [0] Back\n");
                printf("=============== Set Sort/Filter/Search ================\n");
                printf(">> ");
                if (scanf("%d", &filter_option) != 1) {
                    while(getchar() != '\n');
                    filter_option = -1;
                }
                while(getchar() != '\n');

                if (filter_option == 1) {
                    filter_member_only = !filter_member_only;
                } else if (filter_option == 2) {
                    printf("Set total filter:\n");
                    printf("1. Greater than (>)\n2. Less than (<)\n3. No filter\n>>: ");
                    int cmp;
                    if (scanf("%d", &cmp) != 1) {
                        while(getchar() != '\n');
                        cmp = 3;
                    }
                    while(getchar() != '\n');
                    if (cmp == 1 || cmp == 2) {
                        filter_total_cmp = cmp;
                        printf("Enter total value: ");
                        if (scanf("%d", &filter_total_value) != 1) {
                            while(getchar() != '\n');
                            filter_total_value = 0;
                        }
                        while(getchar() != '\n');
                    } else {
                        filter_total_cmp = 0;
                        filter_total_value = 0;
                    }
            } else if (filter_option == 3) {
                printf("Enter Transaction ID (0 to cancel): ");
                int id;
                if (scanf("%d", &id) != 1) {
                    while(getchar() != '\n');
                    id = 0;
                }
                while(getchar() != '\n');
                search_id = id;
            } else if (filter_option == 4) {
                printf("Enter Member Name to search (empty to clear): ");
                fgets(search_member, sizeof(search_member), stdin);
                search_member[strcspn(search_member, "\r\n")] = 0;
            } else if (filter_option == 5) {
                filter_member_only = 0;
                filter_total_cmp = 0;
                filter_total_value = 0;
                search_id = 0;
                search_member[0] = '\0';
            }
        } while (filter_option != 0);

        apply_filters();
        filtered_count = 0;
        for (int i = 0; i < count; i++) {
            if (matches_filter(&transactions[i])) {
                filtered[filtered_count++] = transactions[i];
            }
        }
        max_page = (filtered_count + items_per_page - 1) / items_per_page;
        page = 0;
}}}
