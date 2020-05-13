/*
 * FILE: figure.c
 * Copyright (C) Lunar Eclipse
 * Copyright (C) Railgun
 */

#include "figure.h"

int print_letter(char c) {
    int row;
    if (c == 'R') {
        for (row = 0; row < 5; row++) {
            switch (row) {
                case 0:
                    printf(" ____  \n");
                    break;
                case 1:
                    printf("|  _ \\ \n");
                    break;
                case 2:
                    printf("| |_) |\n");
                    break;
                case 3:
                    printf("|  _ < \n");
                    break;
                case 4:
                    printf("|_| \\_\\\n");
                    break;
            }
        }
    }
    else {
        printf("the character not supported yet\n");
        return -1;
    }
    return 0;
}

void print_row(char* str, int row) {
    char c;
    int i;
    int len = (int)strlen(str);
    for (i = 0; i < len; i++) {
        c = *(str + i);
        switch (c) {
            case 'A':
                switch (row) {
                    case 1:
                        printf("        ");
                        break;
                    case 2:
                        printf("   /\\   ");
                        break;
                    case 3:
                        printf("  /  \\  ");
                        break;
                    case 4:
                        printf(" /----\\ ");
                        break;
                    case 5:
                        printf("/_/  \\_\\");
                        break;
                }
                break;
            case 'B':
                switch (row) {
                    case 1:
                        printf(" ____  ");
                        break;
                    case 2:
                        printf("| __ ) ");
                        break;
                    case 3:
                        printf("|  _ \\ ");
                        break;
                    case 4:
                        printf("| |_) |");
                        break;
                    case 5:
                        printf("|____/ ");
                        break;
                }
                break;
            case 'C':
                switch (row) {
                    case 1:
                        printf("  ____ ");
                        break;
                    case 2:
                        printf(" / ___|");
                        break;
                    case 3:
                        printf("| |    ");
                        break;
                    case 4:
                        printf("| |___ ");
                        break;
                    case 5:
                        printf(" \\____|");
                        break;
                }
                break;
            case 'D':
                switch (row) {
                    case 1:
                        printf(" ____  ");
                        break;
                    case 2:
                        printf("|  _ \\ ");
                        break;
                    case 3:
                        printf("| | | |");
                        break;
                    case 4:
                        printf("| |_| |");
                        break;
                    case 5:
                        printf("|____/ ");
                        break;
                }
                break;
            case 'E':
                switch (row) {
                    case 1:
                        printf(" _____ ");
                        break;
                    case 2:
                        printf("| ____|");
                        break;
                    case 3:
                        printf("|  _|  ");
                        break;
                    case 4:
                        printf("| |___ ");
                        break;
                    case 5:
                        printf("|_____|");
                }
                break;
            case 'F':
                switch (row) {
                    case 1:
                        printf(" _____ ");
                        break;
                    case 2:
                        printf("|  ___|");
                        break;
                    case 3:
                        printf("| |_   ");
                        break;
                    case 4:
                        printf("|  _|  ");
                        break;
                    case 5:
                        printf("|_|    ");
                        break;
                }
                break;
            case 'G':
                switch (row) {
                    case 1:
                        printf("  ____ ");
                        break;
                    case 2:
                        printf(" / ___|");
                        break;
                    case 3:
                        printf("| |  _ ");
                        break;
                    case 4:
                        printf("| |_| |");
                        break;
                    case 5:
                        printf(" \\____|");
                        break;
                }
                break;
            case 'H':
                switch (row) {
                    case 1:
                        printf(" _   _ ");
                        break;
                    case 2:
                        printf("| | | |");
                        break;
                    case 3:
                        printf("| |_| |");
                        break;
                    case 4:
                        printf("|  _  |");
                        break;
                    case 5:
                        printf("|_| |_|");
                        break;
                }
                break;
            case 'I':
                switch (row) {
                    case 1:
                        printf(" ____ ");
                        break;
                    case 2:
                        printf("|_  _|");
                        break;
                    case 3:
                    case 4:
                        printf(" |  | ");
                        break;
                    case 5:
                        printf("|____|");
                        break;
                }
                break;
            case 'J':
                switch (row) {
                    case 1:
                        printf("     _ ");
                        break;
                    case 2:
                        printf("    | |");
                        break;
                    case 3:
                        printf(" _  | |");
                        break;
                    case 4:
                        printf("| |_| |");
                        break;
                    case 5:
                        printf(" \\___/ ");
                        break;
                }
                break;
            case 'K':
                switch (row) {
                    case 1:
                        printf(" _  __");
                        break;
                    case 2:
                        printf("| |/ /");
                        break;
                    case 3:
                        printf("| ' / ");
                        break;
                    case 4:
                        printf("| | \\ ");
                        break;
                    case 5:
                        printf("|_|\\_\\");
                        break;
                }
                break;
            case 'M':
                switch (row) {
                    case 1:
                        printf(" __  __ ");
                        break;
                    case 2:
                        printf("|  \\/  |");
                        break;
                    case 3:
                        printf("| |\\/| |");
                        break;
                    case 4:
                        printf("| |  | |");
                        break;
                    case 5:
                        printf("|_|  |_|");
                        break;
                }
                break;
            case 'L':
                switch (row) {
                    case 1:
                        printf(" _     ");
                        break;
                    case 2:
                    case 3:
                        printf("| |    ");
                        break;
                    case 4:
                        printf("| |___ ");
                        break;
                    case 5:
                        printf("|_____|");
                        break;
                }
                break;
            case 'N':
                switch (row) {
                    case 1:
                        printf(" _   _ ");
                        break;
                    case 2:
                        printf("| \\ | |");
                        break;
                    case 3:
                        printf("|  \\| |");
                        break;
                    case 4:
                        printf("| |\\  |");
                        break;
                    case 5:
                        printf("|_| \\_|");
                        break;
                }
                break;
            case 'O':
                switch (row) {
                    case 1:
                        printf("  ___  ");
                        break;
                    case 2:
                        printf(" / _ \\ ");
                        break;
                    case 3:
                        printf("| | | |");
                        break;
                    case 4:
                        printf("| |_| |");
                        break;
                    case 5:
                        printf(" \\___/ ");
                        break;
                }
                break;
            case 'P':
                switch (row) {
                    case 1:
                        printf(" ____  ");
                        break;
                    case 2:
                        printf("|  _ \\ ");
                        break;
                    case 3:
                        printf("| |_) |");
                        break;
                    case 4:
                        printf("|  __/ ");
                        break;
                    case 5:
                        printf("|_|    ");
                        break;
                }
                break;
            case 'Q':
                switch (row) {
                    case 1:
                        printf("  ___  ");
                        break;
                    case 2:
                        printf(" / _ \\ ");
                        break;
                    case 3:
                        printf("| | | |");
                        break;
                    case 4:
                        printf("| |_| |");
                        break;
                    case 5:
                        printf(" \\__\\_\\");
                        break;
                }
                break;
            case 'R':
                switch (row) {
                    case 1:
                        printf(" ____  ");
                        break;
                    case 2:
                        printf("|  _ \\ ");
                        break;
                    case 3:
                        printf("| |_) |");
                        break;
                    case 4:
                        printf("|  _ < ");
                        break;
                    case 5:
                        printf("|_| \\_\\");
                        break;
                }
                break;
            case 'S':
                switch (row) {
                    case 1:
                        printf(" ____  ");
                        break;
                    case 2:
                        printf("/ ___| ");
                        break;
                    case 3:
                        printf("\\___ \\ ");
                        break;
                    case 4:
                        printf(" ___) |");
                        break;
                    case 5:
                        printf("|____/ ");
                        break;
                }
                break;
            case 'T':
                switch (row) {
                    case 1:
                        printf(" _____ ");
                        break;
                    case 2:
                        printf("|_   _|");
                        break;
                    case 3:
                    case 4:
                        printf("  | |  ");
                        break;
                    case 5:
                        printf("  |_|  ");
                        break;
                }
                break;
            case 'U':
                switch (row) {
                    case 1:
                        printf(" _   _ ");
                        break;
                    case 2:
                    case 3:
                        printf("| | | |");
                        break;
                    case 4:
                        printf("| |_| |");
                        break;
                    case 5:
                        printf(" \\___/ ");
                        break;
                }
                break;
            case 'V':
                switch (row) {
                    case 1:
                        printf("__     __");
                        break;
                    case 2:
                        printf("\\ \\   / /");
                        break;
                    case 3:
                        printf(" \\ \\ / / ");
                        break;
                    case 4:
                        printf("  \\ V /  ");
                        break;
                    case 5:
                        printf("   \\_/   ");
                        break;
                }
                break;
            case 'W':
                switch (row) {
                    case 1:
                        printf("__        __");
                        break;
                    case 2:
                        printf("\\ \\      / /");
                        break;
                    case 3:
                        printf(" \\ \\ /\\ / / ");
                        break;
                    case 4:
                        printf("  \\ V  V /  ");
                        break;
                    case 5:
                        printf("   \\_/\\_/   ");
                        break;
                }
                break;
            case 'X':
                switch (row) {
                    case 1:
                        printf("__  __");
                        break;
                    case 2:
                        printf("\\ \\/ /");
                        break;
                    case 3:
                        printf(" \\  / ");
                        break;
                    case 4:
                        printf(" /  \\ ");
                        break;
                    case 5:
                        printf("/_/\\_\\");
                        break;
                }
                break;
            case 'Y':
                switch (row) {
                    case 1:
                        printf("__   __");
                        break;
                    case 2:
                        printf("\\ \\ / /");
                        break;
                    case 3:
                        printf(" \\ V / ");
                        break;
                    case 4:
                        printf("  | |  ");
                        break;
                    case 5:
                        printf("  |_|  ");
                }
                break;
            case 'Z':
                switch (row) {
                    case 1:
                        printf(" _____");
                        break;
                    case 2:
                        printf("|__  /");
                        break;
                    case 3:
                        printf("  / / ");
                        break;
                    case 4:
                        printf(" / /_ ");
                        break;
                    case 5:
                        printf("/____|");
                        break;
                }
                break;
            default:
                break;
        }
        printf(" ");
    }
    printf("\n");
}


//only upper case supported
void print_str(char* str) {
    int i;
    int len = (int)strlen(str);
    for (i = 0; i < len; i++) {
        if (*(str + i) > 'Z' || *(str + i) < 'A') {
            fprintf(stderr, "only upper case string supported\n");
            return ;
        }
    }
    for (i = 1; i <= 5; i++) {
        print_row(str, i);
    }
}


