#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../library/leaderboard_menu.h"


typedef struct {
    char username[50];
    int customer_handled;
} UserStat;

int compare_asc(const void *a, const void *b) {
    const UserStat *ua = (const UserStat *)a;
    const UserStat *ub = (const UserStat *)b;
    return ua->customer_handled - ub->customer_handled;
}

int compare_desc(const void *a, const void *b) {
    const UserStat *ua = (const UserStat *)a;
    const UserStat *ub = (const UserStat *)b;
    return ub->customer_handled - ua->customer_handled;
}

void leaderboard(const char *current_username) {
    UserStat users[1000];
    int count = 0;

    FILE *fp = fopen("database/profiles/users_list.txt", "r");
    if (!fp) {
        printf("Failed to open users_list.txt\n");
        system("pause");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp) && count < 1000) {
        line[strcspn(line, "\r\n")] = 0;
        if (strlen(line) == 0) continue;

        char *token = strtok(line, ",");
        if (!token) continue;
        strcpy(users[count].username, token);

        token = strtok(NULL, ",");
        if (!token) continue;
        users[count].customer_handled = atoi(token);

        count++;
    }
    fclose(fp);

    if (count == 0) {
        printf("No users found.\n");
        system("pause");
        return;
    }

    int sort_option = 0;
    do {
        system("clear");
        printf("+================ Leaderboard =================+\n");
        printf("Sort by customer handled:\n");
        printf("1. Ascending\n");
        printf("2. Descending\n");
        printf("0. Back\n");
        printf(">> ");

        if (scanf("%d", &sort_option) != 1) {
            while (getchar() != '\n');
            sort_option = -1;
        }
        while (getchar() != '\n');

        if (sort_option == 1) {
            qsort(users, count, sizeof(UserStat), compare_asc);
        } else if (sort_option == 2) {
            qsort(users, count, sizeof(UserStat), compare_desc);
        }
    } while (sort_option != 0);

    system("clear");
    printf("+================ Leaderboard =================+\n");
    printf(" Rank | Username                | Customers Handled\n");
    printf("+------------------------------------------------+\n");
    for (int i = 0; i < count; i++) {
        printf(" %4d | %-22s | %17d\n", i + 1, users[i].username, users[i].customer_handled);
    }
    printf("+------------------------------------------------+\n");

    int user_rank = -1;
    for (int i = 0; i < count; i++) {
        if (strcmp(users[i].username, current_username) == 0) {
            user_rank = i + 1;
            break;
        }
    }

    if (user_rank != -1) {
        printf("Your rank: %d | Customers handled: %d\n",
               user_rank, users[user_rank - 1].customer_handled);
    } else {
        printf("Your username '%s' not found in leaderboard.\n", current_username);
    }

    printf("\nPress Enter to return...");
    getchar();
}
