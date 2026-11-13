
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char productions[MAX][MAX];
int n;

void add(char *set, char ch)
{
    if (!strchr(set, ch)) {
        int len = strlen(set);
        set[len] = ch;
        set[len + 1] = '\0';
    }
}

int precedence(char op)
{
    if (op == '*' || op == '/')
        return 2;
    if (op == '+' || op == '-')
        return 1;
    return 0;
}

void findFirst(char *res, char ch)
{
    int i, j;
    char temp[MAX];

    if (!isupper((unsigned char)ch)) {
        add(res, ch);
        return;
    }

    for (i = 0; i < n; i++) {
        if (productions[i][0] == ch) {
            if (productions[i][2] == '#')
                add(res, '#');
            else {
                for (j = 2; productions[i][j]; j++) {
                    temp[0] = '\0';
                    findFirst(temp, productions[i][j]);

                    for (int k = 0; temp[k]; k++)
                        if (temp[k] != '#')
                            add(res, temp[k]);

                    if (!strchr(temp, '#'))
                        break;

                    if (!productions[i][j + 1])
                        add(res, '#');
                }
            }
        }
    }
}

void findFollow(char *res, char ch)
{
    int i, j;
    char temp[MAX];

    if (ch == productions[0][0])
        add(res, '$');

    for (i = 0; i < n; i++) {
        for (j = 2; productions[i][j]; j++) {
            if (productions[i][j] == ch) {
                if (productions[i][j + 1]) {
                    temp[0] = '\0';
                    findFirst(temp, productions[i][j + 1]);

                    for (int k = 0; temp[k]; k++)
                        if (temp[k] != '#')
                            add(res, temp[k]);

                    if (strchr(temp, '#')) {
                        temp[0] = '\0';
                        findFollow(temp, productions[i][0]);

                        for (int k = 0; temp[k]; k++)
                            add(res, temp[k]);
                    }
                }
                else if (productions[i][0] != ch) {
                    temp[0] = '\0';
                    findFollow(temp, productions[i][0]);

                    for (int k = 0; temp[k]; k++)
                        add(res, temp[k]);
                }
            }
        }
    }
}

int main()
{
    int i, count = 0;
    char nt[MAX] = "";

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (use # for epsilon):\n");

    for (i = 0; i < n; i++)
        scanf("%19s", productions[i]);

    for (i = 0; i < n; i++) {
        char ch = productions[i][0];

        if (!strchr(nt, ch)) {
            nt[count++] = ch;
            nt[count] = '\0';
        }
    }

    printf("\nFIRST sets:\n");

    for (i = 0; i < count; i++) {
        char res[MAX] = "";
        findFirst(res, nt[i]);
        printf("FIRST(%c) = { %s }\n", nt[i], res);
    }

    printf("\nFOLLOW sets:\n");

    for (i = 0; i < count; i++) {
        char res[MAX] = "";
        findFollow(res, nt[i]);
        printf("FOLLOW(%c) = { %s }\n", nt[i], res);
    }

    return 0;
}

