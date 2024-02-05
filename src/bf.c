#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "List/include/List.h"

void printNodeColors(Node* root, Node* temp, Node* froot) {
    if (froot == root) {
        printf("\033[1;33m");
        printf("%d ", froot->value);
        printf("\033[0m");
    } else if (froot == temp) {
        printf("\033[1;34m");
        printf("%d ", froot->value);
        printf("\033[0m");
    } else {
        printf("%d ", froot->value);
    }
}

void printNextNode(Node* root, Node* temp, Node* froot) {
    printNodeColors(root, temp, froot);
    if (froot->n != NULL) {
        froot = froot->n;
        printNextNode(root, temp, froot);
    }
}

void printNode(Node* root, Node* temp) {
    printNextNode(root, temp, getFirstNode(temp));
}

Node* bfLeft(Node* root) {
    if (root->p == NULL) {
        return addFirstNode(root, 0);
    }
    return root->p;
}

Node* bfRight(Node* root) {
    if (root->n == NULL) {
        return addLastNode(root, 0);
    }
    return root->n;
}

void bfAdd(Node* root) {
    root->value++;
    if (root->value > 255) {
        root->value = 0;
    }
}

void bfSub(Node* root) {
    root->value--;
    if (root->value < 0) {
        root->value = 255;
    }
}

char bfGetC(Node* root) { return (char)root->value; }

char bfSetC(Node* root, char c) { return root->value = (int)c; }

void bfLoopOn(int* loop) {
    *loop = *loop + 1;
    // printf("loop On %d\n",*loop);
}

void bfLoopS(Node* root, FILE* f, int* loop, int* loopi) {
    char c;
    while (true) {
        // printf("loop----\n");
        c = getc(f);
        fseek(f, -2, SEEK_CUR);  // konumu bir geriletir
        if (c == '[')            // acma görüldüyes
        {
            // printf("loop [\n");
            if (*loop == *loopi)  // istenen acma ise
            {
                // printf("loop f\n");
                fseek(f, 1, SEEK_CUR);  // konumu bir geriletir
                return;                 // döndür
            }
            *loop = *loop - 1;  // değilse loop counter i bir azaltır
        }
        c = getc(f);
        fseek(f, -1, SEEK_CUR);  // konumu bir geriletir
        if (c == ']')            // acma kapama
        {
            // printf("loop ]\n");
            *loop = *loop + 1;
        }
        return bfLoopS(root, f, loop, loopi);
    }
}

void bfLoopOff(Node* root, FILE* f, int* loop, int* loopi) {
    if (root->value <= 0)  // loop dan direkt cıkma sartı
    {
        // printf("loop d kapa\n");
        return;
    }
    // loop un basına gider
    *loopi = *loop;
    fseek(f, -1, SEEK_CUR);         // konumu bir geriletir
    bfLoopS(root, f, loop, loopi);  // dosyayı loop un basına alır

    // printf("loop b kapa\n");
    return;
}

void printOutput(char c, int* outputC, int* outputLineC) {
    for (int i = 0; i < 1; ++i) {
        printf("\033[A\r");  // bir satır yukarı
    }
    for (int i = 0; i < *outputC; ++i) {
        printf("\x1b[C");  // bir karakter sağa
    }
    if ((int)c == 10 || (int)c == 11 || (int)c == 12) {
        *outputC = *outputLineC + 1;
        // printf("\033[2K");//satırı sil
        printf("\e[41m");
        printf("-");
        printf("\033[0m");
        *outputC = -1;
    }
    *outputC = *outputC + 1;
    printf("%c", c);
    for (int i = 0; i < 1; ++i) {
        printf("\x1b[B");  // bir satır assağı
    }
}

int setSpeed(FILE* f, int* s) {
    char c = fgetc(f);
    fseek(f, -1, SEEK_CUR);  // konumu bir geriletir
    if (c == '*') {
        fseek(f, 1, SEEK_CUR);  // konumu bir geriletir
        fscanf(f, "%d", s);
    } else {
        *s = 0;
    }
    return *s;
}

int main(int _, char* argv[]) {
    char* inputFile = 0;
    // if(argv[1] == NULL || argv[1][0] == '-'){
    //	inputFile = "input.bf";
    // }
    // else{
    //	inputFile = argv[1];
    // }

    Node* root = newNode(0);
    Node* temp = root;
    // dosya chrosor ü
    char c;
    // loop ların toplamı ve konumu
    int lo = 0;
    int loi;
    // output uzunluk genisliği
    int oc = 9;
    int olc = 1;
    // bekleme süresi
    int speed = -1;

    while (*++argv != NULL) {
        if (strcmp("-f", *argv) == 0 || strcmp("-file", *argv) == 0 ||
            strcmp("-input", *argv) == 0 || strcmp("-i", *argv) == 0) {
            inputFile = *++argv;
        } else if (strcmp("-s", *argv) == 0 || strcmp("-speed", *argv) == 0) {
            speed = atoi(*++argv);
        }
    }
    if (inputFile == 0) {
        inputFile = "input.bf";
    }

    FILE* dosya = fopen(inputFile, "r");
    if (dosya == NULL) {
        printf("%s File not found or Unable to open file\n", inputFile);
        exit(0);
    }

    if (speed == -1) {
        setSpeed(dosya, &speed);
    }
    printf("inputFile : %s\n", inputFile);

    printf("Speed : %d\n", speed);
    speed *= 1000;

    printf("\e[?25l");  // imleci gizler
    printf("OUTPUT : \n\n");

    while (!feof(dosya)) {
        printf("\033[A\r");  // bir satır yukarı
        printf("\033[1;32m");
        printf("\033[2K");

        c = fgetc(dosya);

        switch (c) {
            case '+':
                bfAdd(temp);
                printf("+ \n");
                break;
            case '-':
                bfSub(temp);
                printf("- \n");
                break;
            case '<':
                temp = bfLeft(temp);
                printf("<|\n");
                break;
            case '>':
                temp = bfRight(temp);
                printf("|>\n");
                break;
            case '.':
                printOutput(bfGetC(temp), &oc, &olc);
                printf(". \n");
                break;
            case ',':
                printf("\e[?25h");  // imleci acar
                scanf(" %c", &c);
                printf("\e[?25l");  // imleci gizler
                bfSetC(temp, c);
                printf(", \n");
                break;
            case '[':
                bfLoopOn(&lo);
                printf("[ \n");
                break;
            case ']':
                bfLoopOff(temp, dosya, &lo,
                          &loi);  // dosya nın pointer ini ayarlar
                printf("] \n");
                break;
            default:
                printf("\n");
                break;
        }
        // printf("\n");

        printf("\033[0m");
        // printf("");//satırı sil");
        printf("\r\033[2K\r");
        printNode(root, temp);
        if (speed) {
            if (c == '+' || c == '-' || c == '.' || c == ',' || c == '<' ||
                c == '>' || c == '[' || c == ']')
                usleep(speed);
        }
    }

    printf("\n");

    fclose(dosya);

    temp = getFirstNode(root);
    Node* freeTemp;
    while (temp != NULL) {
        freeTemp = temp;
        temp = temp->n;
        free(freeTemp);
    }

    return 0;
}
