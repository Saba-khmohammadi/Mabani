#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void extractText(char* str, char userName[]) {
    int start = -1;
    int end = -1;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        if (str[i] == '\"') {
            if (start == -1) {
                start = i + 1;
            } else {
                end = i;
                break;
            }
        }
    }


        userName[end - start + 1];
        strncpy(userName, str + start, end - start);
        userName[end - start] = '\0';
}
int main() {
    char userInput[1000];
    char userName[1000];
    char Gmail[1000];
    while(1){
    gets(userInput);

    if (strncmp(userInput, "neogit config --user.name", 25) == 0) {
        extractText(userInput, userName);

    }
    if (strncmp(userInput, "neogit config --user.email", 26) == 0){
        extractText(userInput, Gmail);
        FILE *file = fopen("user_info.txt", "w");
        file = fopen("user_info.txt", "w");
        if (file != NULL) {
        fprintf(file, "UserName: %s\n", userName);
        fprintf(file, "UserGmail: %s\n", Gmail);
        fclose(file);
        printf("User info saved successfully.\n");
    } break;
}

    }

    return 0;}
