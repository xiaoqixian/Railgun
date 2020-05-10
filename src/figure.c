#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int print_letter(char c) {
    int row, column;
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
    for (int i = 0; i < strlen(str); i++) {
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
    for (i = 0; i < strlen(str); i++) {
        if (*(str + i) >= 'Z' || *(str + i) <= 'A') {
            //fprintf(stderr, "only upper case string supported\n");
            //return ;
        }
    }
    for (i = 1; i <= 5; i++) {
        print_row(str, i);
    }
}

int main() {
    printf("-----Welcome to Railgun!-----\n");
    print_str("RAILGUN");
    return 0;
}
