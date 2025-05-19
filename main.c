//=====[[ C Library ]]=====
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//=====[[ Custom Library ]]=====
#include "library/authentication_menu.h"
#include "library/sound_manager.h"

//=====[[ Animation ]]=====
void animation_binus() {
    const char *B[] = {
        " ____  ",
        "| __ ) ",
        "|  _ \\ ",
        "| |_) |",
        "|____/ "
    };

    const char *I[] = {
        " ___ ",
        "|_ _|",
        " | | ",
        " | | ",
        "|___|"
    };

    const char *N[] = {
        " _   _ ",
        "| \\ | |",
        "|  \\| |",
        "| |\\  |",
        "|_| \\_|"
    };

    const char *U[] = {
        " _   _ ",
        "| | | |",
        "| | | |",
        "| |_| |",
        " \\___/ "
    };

    const char *S[] = {
        " ____  ",
        "/ ___| ",
        "\\___ \\ ",
        " ___) |",
        "|____/ "
    };

    const char **letters[] = {B, I, N, U, S};
    const char *rainbow_colors[] = {
        "\x1b[31m", // Red
        "\x1b[33m", // Yellow
        "\x1b[32m", // Green
        "\x1b[36m", // Cyan
        "\x1b[34m", // Blue
        "\x1b[35m", // Magenta
    };

    const char *reset = "\x1b[0m";
    const char *orange = "\x1b[38;2;255;140;0m";
    const char *bg_white = "\x1b[47m";

    int letter_count = 5;
    int rows = 5;

    for (int l = 0; l < letter_count; l++) {
        system("cls");
        printf("%s", bg_white);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j <= l; j++) {
                const char *color = rainbow_colors[(j + i) % 6];
                printf("%s%s  ", color, letters[j][i]);
            }
            printf("%s\n", reset);
            printf("%s", bg_white);
        }

        Sleep(900);
    }

    system("cls");
    printf("%s", bg_white);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < letter_count; j++) {
            printf("%s%s  ", orange, letters[j][i]);
        }
        printf("%s\n", reset);
        printf("%s", bg_white);
    }

    const char *production = "Production";
    printf("\n\n                    %s", bg_white);
    for (int i = 0; production[i]; i++) {
        printf("%s%c", orange, production[i]);
        fflush(stdout);
        Sleep(100);
    }
    printf("%s\n", reset);
    printf("%s", bg_white);
}

//=====[[ Main ]]=====
int main() {
	system("cls");
	
	printf("LOADING MENU...\n");
	printf("\x1b[47m");
	
	play_wav("sound/intro_sound.wav", 0);
	play_wav("sound/binus_sound.wav", 1);
	
	animation_binus();
    
    Sleep(7000);
    
    play_wav("sound/jazz_sound.wav", 1);
    
	authentication_menu();
    
    getchar();
    
    return 0;
}

