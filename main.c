
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
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
int isFile(const char* name)
{
    DIR* directory = opendir(name);
    if(errno == ENOTDIR)
    {
     return 1;
    }

    return -1;
}
int main() {
    char userInput[1000];
    char userName[1000];
    char Gmail[1000];
    DIR *dir;
    struct dirent *entry;
    int flag = 0;
    int flag2 = 0;
    int flag_config = 0;
    char add[1000];

    while(1){
    gets(userInput);
  
if(strcmp(userInput, "neogit init") == 0){
    struct stat st = {0};
    if (stat(".neogit", &st) == 0) {
        printf("Error: The folder '.neogit' already exists.\n");
        continue;
    }
    int result =  mkdir(".neogit");
    if (result == 0) {
        printf("The hidden folder '.neogit' has been created successfully.\n");
    } else {
        printf("Error: Failed to create the hidden folder '.neogit'.\n");
    }
    }

    if(strncmp(userInput, "neogit add", 10) == 0){

        extractText(userInput,add);
        const char* directory = ".neogit";printf("%s", directory);
        dir = opendir(".neogit");
    if (isFile(directory) == -1) {
        printf("Unable to find the directory.\n");
        continue;
    }
  

    }


}
    return 0;
    }