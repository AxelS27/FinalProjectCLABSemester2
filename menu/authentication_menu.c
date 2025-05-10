#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../library/authentication_menu.h"
#include "../library/main_menu.h"

#define USERNAME_SIZE 50
#define PASSWORD_SIZE 50

struct User {
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
};

void register_user() {
    FILE *file = fopen("database/authentication.bin", "ab");
    if (!file) {
        file = fopen("database/authentication.bin", "ab");
        if (!file) {
            printf("Failed to open file.\n");
            return;
        }
    }
    fclose(file);

    struct User new_user, existing_user;
    int username_exists = 0;

    while (getchar() != '\n');

    system("clear");
    printf("+----------------------------------------+\n");
    printf("|             REGISTER PAGE              |\n");
    printf("+----------------------------------------+\n");

    printf("  Input Username: ");
    fgets(new_user.username, USERNAME_SIZE, stdin);
    new_user.username[strcspn(new_user.username, "\n")] = 0;

    printf("  Input Password: ");
    fgets(new_user.password, PASSWORD_SIZE, stdin);
    new_user.password[strcspn(new_user.password, "\n")] = 0;

    int len = strlen(new_user.username);
    int valid = 1;

    if (len < 3 || len > 10) {
        valid = 0;
    } else {
        for (int i = 0; i < len; i++) {
            if (new_user.username[i] == ' ') {
                valid = 0;
                break;
            }
        }
    }

    if (!valid) {
        printf("+----------------------------------------+\n");
        printf("-> Username must be 3-10 characters and\n   not contain white space character !\n\n");
        system("pause");
        authentication_menu();
        return;
    }

    file = fopen("database/authentication.bin", "rb");
    if (!file) {
        printf("+----------------------------------------+\n");
        printf("-> Failed to open file.\n\n");
        return;
    }

    while (fread(&existing_user, sizeof(struct User), 1, file)) {
        if (strcmp(existing_user.username, new_user.username) == 0) {
            username_exists = 1;
            break;
        }
    }

    fclose(file);

    if (username_exists) {
        printf("+----------------------------------------+\n");
        printf("-> Username is already taken by other\n   user !\n\n");
        system("pause");
        authentication_menu();
        return;
    }

    file = fopen("database/authentication.bin", "ab");
    if (!file) {
        printf("+----------------------------------------+\n");
        printf("-> Failed to store user's data !\n\n");
        return;
    }

    fwrite(&new_user, sizeof(struct User), 1, file);
    fclose(file);

    char profile_path[100];
    sprintf(profile_path, "database/profiles/%s_file.txt", new_user.username);

    FILE *profile_file = fopen(profile_path, "w");
    if (profile_file) {
        fprintf(profile_file, "username,customer_handled\n");
        fprintf(profile_file, "%s,0\n", new_user.username);
        fclose(profile_file);
    }

    printf("+----------------------------------------+\n");
    printf("-> Register success !\n\n");

    system("pause");
    authentication_menu();
}

int login_user() {
    FILE *file = fopen("database/authentication.bin", "rb");

    struct User user;
    char username[USERNAME_SIZE];
    char password[PASSWORD_SIZE];
    int found = 0;

    while (getchar() != '\n'); 
    system("clear");
    printf("+----------------------------------------+\n");
    printf("|              LOGIN PAGE                |\n");
    printf("+----------------------------------------+\n");
    printf("  Input Username: ");
    fgets(username, USERNAME_SIZE, stdin);
    username[strcspn(username, "\n")] = 0;

    printf("  Input Password: ");
    fgets(password, PASSWORD_SIZE, stdin);
    password[strcspn(password, "\n")] = 0;

    while (fread(&user, sizeof(struct User), 1, file)) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            found = 1;
            break;
        }
    }

    fclose(file);

    if (found) {
        printf("+----------------------------------------+\n");
        printf("-> Login success! Welcome, %s.\n\n", username);
        return 1;
    } else {
        printf("+----------------------------------------+\n");
        printf("-> Username or password is incorrect !\n\n");

        return 0;
    }
}

void authentication_menu() {
    int choice;

    while (1) {
        system("clear");
        printf("+------------------------------------------------+\n");
        printf("|                STOCK UP CAFE                   |\n");
        printf("|------------------------------------------------|\n");
        printf("| [1] Login                                      |\n");
        printf("| [2] Register                                   |\n");
        printf("|                                                |\n");
        printf("| [0] Exit                                       |\n");
        printf("+------------------------------------------------+\n");
        printf(">> ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (choice >= 0 && choice <= 2) break;
        while (getchar() != '\n');
    }

    int logged_in = 0;
    if (choice == 1) {
        logged_in = login_user();
    } else if (choice == 2) {
        register_user();
        logged_in = login_user();
    } else if (choice == 0) {
        printf("Good bye !.\n");
        exit(0);
        return;
    }

    if (logged_in) {
        system("pause");
        main_menu();
    } else {
        system("pause");
        authentication_menu();
    }
}

