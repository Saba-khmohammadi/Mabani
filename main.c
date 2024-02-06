#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <stdbool.h>
#include <windows.h>
#include <errno.h>
#include <libgen.h>
#include <time.h>
#define MAX_SENTENCES 100
#define MAX_LINE_LENGTH 100
#define MAX_LENGTH 20000

void SetColor(int ForgC)
{
     WORD wColor;

     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;

     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}
void searchWordInFile(char* filename,  char* word, int n) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    char line[256];
    int lineNum = 1;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, word) != NULL) {
                if(n == 1){
            printf("File: %s, Line: %d\n", filename, lineNum);
            printf("%s\n", line);
            }
            if(n == 0){
               printf("File: %s\n", filename);
                printf("%s\n", line);
            }

        }
        lineNum++;
    }

    fclose(file);
}
int checkBlankSpaces(char path[]){
FILE *file = fopen(path, "r");
SetColor(77);

if (file == NULL) {
    printf("Error opening file: %s\n",path);
                return;
        }

            fseek(file, -1, SEEK_END);
            int c = fgetc(file);

            if (c == ' ' || c == '\t' || c == '\n') {
                printf("eof-blank-space................................................FAILED.\n");
                return 0;
            }
else{
  printf("eof-blank-space................................................PASSED.\n");
  return 1;
}
            fclose(file);


SetColor(23);


}
int checkFilesForTodo(const char *dirPath) {
    DIR *dir;
    struct dirent *entry;
    int flag = 0;
    dir = opendir(dirPath);
    if (dir == NULL) {
        printf("Unable to open directory: %s\n", dirPath);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char filePath[256];
            sprintf(filePath, "%s\\%s", dirPath, entry->d_name);

            FILE *file = fopen(filePath, "r");
            if (file == NULL) {
                printf("Unable to open file: %s\n", filePath);
                continue;
            }

            char line[256];
            int lineNum = 1;
            while (fgets(line, sizeof(line), file)) {
                if (strstr(line, "TODO") != NULL) {
                    printf("todo-check.......................................................FAILED.\n");
                    return 0;
                    flag = 1;

                    break;
                }
                lineNum++;
            }

            fclose(file);
        }
    }
    if(flag == 0){
      printf("todo-check....................................................PASSED.\n");
      return 1;
    }

    closedir(dir);
}

int isFileLarge(char filename[]){
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("Error opening file.\n");
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fclose(file);
   SetColor(60);
    if (fileSize > 5 * 1024 * 1024)
    {

        printf("file-size-check................................................FAILED\n");
        return 0;
    }
    else
    {

        printf("file-size-check................................................PASSED\n");
        return 1;
    }
}

int lenght(char file_path[]){
        FILE *file = fopen(file_path, "r");

file_path = strtok(file_path, "\\");
file_path = strtok(NULL, "\\");
file_path = strtok(NULL, "\\");
file_path = strtok(NULL, "\\");
file_path = strtok(NULL, "\\");
file_path = strtok(NULL, "\\");
file_path = strtok(NULL, "\\");
file_path = strtok(NULL, "\\");
        if (file == NULL) {

            printf("Unable to open file: \n");

        }
        fseek(file, 0, SEEK_END);
        long length = ftell(file);
        fseek(file, 0, SEEK_SET);
SetColor(30);

        if (length > MAX_LENGTH) {

            printf("character-limit................................................FAILED.\n");
            return 0;
        }
        else{
            printf("character-limit................................................PASSED.\n", file_path);
            return 1;
        }

        fclose(file);
}
int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void compareAndDeleteFiles(char* dir1,  char* dir2) {
    DIR* directory1 = opendir(dir1);
    DIR* directory2 = opendir(dir2);

    if (directory1 == NULL || directory2 == NULL) {
        printf("Error opening directories.\n");
        return;
    }

    struct dirent* file1;
    struct dirent* file2;

    while ((file1 = readdir(directory1)) != NULL) {
        if (file1->d_type == DT_REG) {
            rewinddir(directory2);

            while ((file2 = readdir(directory2)) != NULL) {
                if (file2->d_type == DT_REG) {
                    if (strcmp(file1->d_name, file2->d_name) == 0) {
                        char path1[100];
                        char path2[100];
                        char command[100];

                        char t[100];
                         strcpy(t, dir2);
                         strcat(t, "\\");
                         strcat(t, file2->d_name);
                        sprintf(path1, "%s/%s", dir1, file1->d_name);
                        sprintf(path2, "%s/%s", dir2, file2->d_name);
                        sprintf(command, "copy %s %s", t, dir1);
                        if (remove(path1) == 0) {
                            printf("Deleted files: %s\n", path1);
                            system(command);
                        } else {
                            printf("Error deleting files: %s, %s\n", path1, path2);
                        }
                    }
                }
            }
        }
    }

    closedir(directory1);
    closedir(directory2);
}
int compareTimes(char* time1, char* time2) {
    int hour1, min1, sec1;
    int hour2, min2, sec2;
    sscanf(time1, "%d:%d:%d", &hour1, &min1, &sec1);
    sscanf(time2, "%d:%d:%d", &hour2, &min2, &sec2);
    int total1 = hour1 * 3600 + min1 * 60 + sec1;
    int total2 = hour2 * 3600 + min2 * 60 + sec2;
    if(total1 > total2 ){
        return 1;
    }
    if(total1 < total2){
        return 0;
    }


}
void removeSpaces(char* str) {
    int i, j;
    for (i = 0, j = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ') {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}
int hasDot(char str[])
{
    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '.')
        {
            return 1;
        }
        i++;
    }
    return 0;
}

int compareTimes2(char* time1, char* time2) {
    int hour1, min1, sec1;
    int hour2, min2, sec2;
    sscanf(time1, "%d:%d:%d", &hour1, &min1, &sec1);
    sscanf(time2, "%d:%d:%d", &hour2, &min2, &sec2);
    int total1 = hour1 * 3600 + min1 * 60 + sec1;
    int total2 = hour2 * 3600 + min2 * 60 + sec2;
    if(total1 > total2 ){
        return 0;
    }
    if(total1 < total2){
        return 1;
    }


}

void printSentencesInReverseOrder(FILE *file) {
    char sentences[MAX_SENTENCES][100];
    int count = 0;

    // Read sentences from file and store them in an array
    while (fgets(sentences[count], 100, file) != NULL) {
        count++;
    }

    // Print sentences in reverse order
    for (int i = count - 1; i >= 0; i--) {
        printf("%s", sentences[i]);
    }
}

void ReverseFile(FILE* file){
    char sentences[MAX_SENTENCES][100];
    int count = 0;
    FILE* temp = fopen("temp_log.txt", "w");
    while (fgets(sentences[count], 100, file) != NULL) {
        count++;
    }
    for (int i = count - 1; i >= 0; i--) {
        fprintf(temp, "%s", sentences[i]);
    }
fclose(temp);

}

void reverseForLog(FILE *file, int number) {
    char sentences[MAX_SENTENCES][100];

    int count = 0;
    int save = 0;
    // Read sentences from file and store them in an array
    while (fgets(sentences[count], 100, file) != NULL) {
        count++;
    }

    // Print sentences in reverse order
    for (int i = count - 1; i >= 0; i--) {

        if(save == (number * 7)){
            break;
        }
        else{
            printf("%s", sentences[i]);
            save++;
        }

    }
}

void replaceDotWithNull(char *str)
{
    while (*str != '\0')
    {
        if (*str == '.')
        {
            *str = '\0';
            return; // Stop after the first occurrence is replaced
        }
        str++;
    }
}

bool directoryExists(char *path)
{
    struct stat info;
    if (stat(path, &info) != 0)
    {
        return false;
    }
    return S_ISDIR(info.st_mode);
}

void search(char user[200], char saved[200])
{
    int start = 0;
    int end = 0;
    int len1 = strlen(user);
    for (int i = 0; i < len1; i++)
    {
        if (user[i] == '\"')
        {
            start = i;
            break;
        }
    }
    end = len1 - 1;
    int i = 0;
    for (int j = start + 1; j < end; j++)
    {
        saved[i] = user[j];
        i++;
    }
    saved[i] = '\0';
}

int match(char *pattern, char *text)
{
    if (*pattern == '\0' && *text == '\0')
    {
        return 1;
    }
    // for *a;
    if (*pattern == '*' && *(pattern + 1) != '\0' && *text == '\0')
    {
        return 0;
    }
    if (*pattern == *text)
    {
        return match(pattern + 1, text + 1);
    }
    if (*pattern == '*')
    {
        return match(pattern + 1, text) || match(pattern, text + 1);
    }
    return 0;
}

int token_del(char *name_of_files[1000], char user[100])
{
    int count = -1;
    int input = 0;
    char del[100] = "<>";
    char *ptr = strtok(user, del);
    while (ptr != NULL)
    {
        count++;
        if (count != 0)
        {
            name_of_files[input] = ptr;
            input++;
        }
        ptr = strtok(NULL, del);
    }
    return input;
}

void addBackslashes(char *str)
{
    int length = strlen(str);

    for (int i = 0; i < length; i++)
    {
        if (str[i] == '\\')
        {
            memmove(&str[i + 2], &str[i + 1], (length - i));
            str[i + 1] = '\\';
            length++;
            i++; // Skip the next character to avoid an infinite loop
        }
    }
}

void reset_for_directory(const char *filename, char *name)
{
    struct stat path_stat_d;
    DIR *dir;
    char line_d[1000];
    struct dirent *entry;
    dir = opendir(name);
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: cannot open the staging file.\n");
        return 1;
    }
    FILE *temp_file = fopen("temp_for_dir.txt", "a");
    if (temp_file == NULL)
    {
        printf("Error: cannot create a temporary file.\n");
        fclose(file);
        return 1;
    }
    FILE *unstaged = fopen("unstage.txt", "a");
    if (unstaged == NULL)
    {
        printf("Error: cannot create unstaged file.\n");
        fclose(file);
        fclose(temp_file);
        return 1;
    }
    fclose(file);
    fclose(temp_file);
    fclose(unstaged);
    file = fopen(filename, "r");
    temp_file = fopen("temp_for_dir.txt", "a");
    unstaged = fopen("unstage.txt", "a");
    // int match = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        if ((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0))
        {
            fprintf(temp_file, "%s\n", entry->d_name);
        }
    }
    fprintf(temp_file, "%s\n", basename(name));
    char line1[1000];
    char line2[1000];
    char cvv[100];
    fclose(temp_file);
    fclose(file);
    fclose(unstaged);
    closedir(dir);
    FILE *file1, *file2, *file3;
    file1 = fopen("temp_for_dir.txt", "r");
    file2 = fopen("staging.txt", "r");
    unstaged = fopen("unstage.txt", "a");
    while (fgets(line1, sizeof(line1), file1) != NULL)
    {
        line1[strcspn(line1, "\n")] = '\0';

        rewind(file2);
        while (fgets(line2, sizeof(line2), file2) != NULL)
        {
            line2[strcspn(line2, "\n")] = '\0';
            if (strcmp(line1, line2) == 0)
            {
                fprintf(unstaged, "%s\n", line2);
            }
        }
    }

    fclose(file1);
    fclose(file2);
    fclose(unstaged);
    // remove(file2);
    remove("temp_for_dir.txt");
    fclose(file2);
    fclose(temp_file);
    FILE *fp1 = fopen("staging.txt", "r");
    FILE *fp2 = fopen("unstage.txt", "r");
    FILE *temp = fopen("t.txt", "a");

    char line11[100];
    char line12[100];
    int match;

    while (fgets(line11, sizeof(line11), fp1))
    {
        line11[strcspn(line11, "\n")] = '\0';
        match = 0;
        rewind(fp2);

        while (fgets(line12, sizeof(line12), fp2))
        {
            line12[strcspn(line12, "\n")] = '\0';
            if (strcmp(line11, line12) == 0)
            {
                match = 1;
                break;
            }
        }

        if (!match)
        {
            fputs(line11, temp);
        }
    }

    fclose(fp1);
    fclose(fp2);
    fclose(temp);
    remove("staging.txt");
    rename("t.txt", "staging.txt");
    fclose(temp);
    fclose(fp2);
}

void extractText(char *str, char userName[])
{
    int start = -1;
    int end = -1;
    int len = strlen(str);

    for (int i = 0; i < len; i++)
    {
        if (str[i] == '\"')
        {
            if (start == -1)
            {
                start = i + 1;
            }
            else
            {
                end = i;
                break;
            }
        }
    }
    userName[end - start + 1];
    strncpy(userName, str + start, end - start);
    userName[end - start] = '\0';
}

int main()
{
    char cvv[1000];
    char currentDirectory[FILENAME_MAX];
    char copy_currentDirectory[FILENAME_MAX];
    _fullpath(currentDirectory, ".", FILENAME_MAX);
    // printf("%s",currentDirectory);
    addBackslashes(currentDirectory);
    // currentDirectory[0] = currentDirectory [0] - 32 ;
    // printf("%s",currentDirectory);
    strcpy(copy_currentDirectory, currentDirectory);
    char command[200];
    int exists_config_name = 0;
    int exists_config_email = 0;
    char command_saver_config_name[200];  // for username;
    char command_saver_config_email[200]; // for email;
    char file_address[256][256];
    strcat(copy_currentDirectory, "\\global_config.txt");
    // be careful about the directory path.
    char *directoryPath = copy_currentDirectory;
    struct stat directoryStat;
    char first_name_cond[100][100];
    char shortcut[256];
    char shortcut_message[256];
    int countt = 0;
    int i_s = 0;
    int commit_id = 1;
    char WORKING_ADDRESS[MAX_LINE_LENGTH];
    if(getcwd(WORKING_ADDRESS, MAX_LINE_LENGTH) != NULL){
    }

 /*   FILE* glo = fopen("global_config.txt", "r");
    char line[100];
    char* token;
   if (glo != NULL){
       while((fgets(line, sizeof(line), glo))!= NULL){
           token = strtok(line, ":");
           token = strtok(NULL, " ");
            token = strtok(NULL, " ");
        break;
       }
      fclose(glo);
       chdir(token);
    }
    FILE* con = fopen("user_saver.txt", "r");
   char line1[100];
   char* token2;
    if(con != NULL){
       while((fgets(line1, sizeof(line1), con))!= NULL){
       token2 = strtok(line1, ": ");
           token2 = strtok(NULL, " ");
           token2 = strtok(NULL, " ");
            break;
      }printf("%s", token2);
      FILE* p = fopen("dd.txt", "w");
            fclose(con);
      chdir(token2);
  }*/
int result = chdir("neogit");
    char copy_one_cu[260];
    strcpy(copy_one_cu, currentDirectory);
    addBackslashes(copy_one_cu);
    strcat(copy_one_cu, "\\.neogit");
    FILE *global_config_file;
    char copy_address_4[500];
    strcpy(copy_address_4, currentDirectory);
    strcat(copy_address_4, "\\\\branch.txt");
  //  FILE *config_file;
  //  FILE *staging = fopen("staging.txt", "a");
  //  fclose(staging);
  //  FILE *temp = fopen("temp.txt", "a");
  //  fclose(temp);
  //  FILE *commit = fopen("commit.txt", "a");
  //  fclose(commit);
    DIR *dir_1;
    struct dirent *entry_1;

    // Open the directory
    dir_1 = opendir(copy_one_cu);

    // Read each entry in the directory
    while ((entry_1 = readdir(dir_1)) != NULL)
    {
        if (strcmp(entry_1->d_name, ".") != 0 && strcmp(entry_1->d_name, "..") != 0)
        {
            strcpy(first_name_cond[countt], entry_1->d_name);
            countt++;
        }
    }
    closedir(dir_1);

    struct stat filestat;
    time_t lastModifiedTime[256];

    for (int i = 0; i < countt; i++)
    {
        snprintf(file_address[i], sizeof(file_address[i]), "%s\\%s", copy_one_cu, first_name_cond[i]); // making address.
        stat(file_address[i], &filestat);
        lastModifiedTime[i] = filestat.st_mtime;
    }

    while (1)
    {
        gets(command);
        if (strncmp(command, "neogit config --global user.name", 32) == 0)
        {
            FILE* glo  = fopen("global_config.txt", "r");
            if(glo != NULL){
                printf("Erorr: the user name has been set before.\n");fclose(glo);
                continue;
            }
            else
            {

                    extractText(command, command_saver_config_name);
                            /*  FILE *config_file;
                                FILE *staging = fopen("staging.txt", "a");
                                fclose(staging);
                                FILE *temp = fopen("temp.txt", "a");
                                fclose(temp);
                                FILE *commit = fopen("commit.txt", "a");
                                fclose(commit);
                                    mkdir("staging");
                                    closedir("staging");
                                    mkdir("unstage");
                                    closedir("unstage");
                                    mkdir("commit");
                                    closedir("commit");*/

            }
        }

        else if (strncmp(command, "neogit config --global email", 28) == 0)
        {

                    if(getcwd(cvv, sizeof(cvv))!= NULL){

                    }
                    extractText(command, command_saver_config_email);
                    FILE* config_file = fopen("global_config.txt", "w");
                    fprintf(config_file, "Username : %s \n", command_saver_config_name);
                    fprintf(config_file, "Useremail : %s \n", command_saver_config_email);
                    fprintf(config_file, "last_commit_id : %d\n", 0);
                    fprintf(config_file, "current_commit_id : %d\n", 0);
                    fprintf(config_file, "branch : %s\n", "master");
                    fclose(config_file);
                    printf("Alert: the user name and email were set.\n");


            }


        else if (strncmp(command, "neogit config -user.name", 24) == 0)
        {
                   FILE* glo = fopen("global_config.txt", "r");
                   if(glo != NULL){
                    printf("Error: you have set your name globally.\n");
                    fclose(glo);
                    continue;
                   }
                   else{
                        extractText(command, command_saver_config_name);
                    ///ne    mkdir(command_saver_config_name);
                        int result = chdir(command_saver_config_name);
                         closedir(command_saver_config_name);
                        if(result == 0){
                            printf("Notify: Working directory changed succesfully.\n");
                              /*  FILE *config_file;
                                FILE *staging = fopen("staging.txt", "a");
                                fclose(staging);
                                FILE *temp = fopen("temp.txt", "a");
                                fclose(temp);
                                FILE *commit = fopen("commit.txt", "a");
                                fclose(commit);
                                    mkdir("staging");
                                    closedir("staging");
                                    mkdir("unstage");
                                    closedir("unstage");
                                    mkdir("commit");
                                    closedir("commit");*/
                        }

                   }

        }

        else if (strncmp(command, "neogit config -email", 20) == 0)
        {

                            if(getcwd(cvv, sizeof(cvv))!= NULL){

                            }
                            printf("%s\n", cvv);
                    extractText(command, command_saver_config_email);
                    FILE* config_file = fopen("config.txt", "a");
                    fprintf(config_file, "Username : %s \n", command_saver_config_name);
                    fprintf(config_file, "Useremail : %s \n", command_saver_config_email);
                    // extra info for other commands.
                    fprintf(config_file, "last_commit_id : %d\n", 0);
                    fprintf(config_file, "current_commit_id : %d\n", 0);
                    fprintf(config_file, "branch : %s\n", "master");
                    fclose(config_file);
                    fclose(config_file);
                    printf("Notify : you set your name and email succssefully.\n");
                     FILE *info_saver = fopen("user_saver.txt", "w");
                    fprintf(info_saver, "Username : %s\n", command_saver_config_name);
                    fprintf(info_saver, "Useremail : %s\n", command_saver_config_email);
                    fclose(info_saver);


        }
        if (strncmp(command, "neogit init", 11) == 0)
        {
            DIR *dir = opendir(".");
            int flag = 0;
            char tmp_cwd[2000];
            char cwd[2000];
            bool exists = false;
            char comd[1000];
char hey[] = "neogit";
sprintf(command, "dir \"/%s\" /s", hey);
if(!system(command)){
    printf("exists");
    flag = 1;
}
else{
        flag = 0;
    printf("doesnt exist");
}
            if (flag == 1){

                struct dirent *entry;
                while ((entry = readdir(dir)) != NULL)
                {
                    if (strcmp(entry->d_name, "neogit") == 0)
                    {
                        printf("Error: The directory 'neogit' exists in the root folder.\n");
                        flag = 1;
                        exists = true;
                      break;
                   }
                }}
                if (flag == 0)
                {
                    char cwd[1024];
                    mkdir("neogit");
                                rewinddir(dir);
                                struct dirent *entry;
                                while((entry = readdir(dir)) != NULL){
                                    if((strcmp(entry->d_name, ".") !=0) &&(strcmp(entry->d_name, "test.depend") != 0)&& (strcmp(entry->d_name, "neogit") != 0) && (strcmp(entry->d_name, "..")!= 0)&&(strcmp(entry->d_name, "main.exe")) && (strcmp(entry->d_name, "main.o") != 0) && (strcmp(entry->d_name, "main.c") != 0)){
                                       char cmm[100];
                                       char cvv2[1000];
                                       strcpy(cwd, cvv);
                                       strcat(cwd, "\\neogit");
                                       strcpy(cvv2, cvv);
                                        strcat(cvv2, "\\");
                                       strcat(cvv2, entry->d_name);printf("%s\n",entry->d_name);
                                      // printf("%s\n", cwd);printf("%s\n", cwd);
                                       sprintf(cmm, "copy %s %s", cvv2, cwd);
                                      system(cmm);
                                      if(strcmp(entry->d_name , "config.txt") == 0){
                                        char cmm;

                                        sprintf(cmm, "del %s", cvv2);
                                        system(cmm);
                                      }
                                      if(strcmp(entry->d_name, "user_saver.txt") == 0){
                                        char cmm[100];
                                       // printf("%s\n", cvv2);
                                        sprintf(cmm, "del %s", cvv2);
                                        system(cmm);
                                      }
                                      if(strcmp(entry->d_name, "global_config.txt") == 0){
                                        char cmm[100];
                                        char op[100];
                                     sprintf(cmm, "copy %s %s", cvv2, cwd);
                                      system(cmm);
                                        sprintf(op, "del %s", cvv2);
                                        system(op);

                                      }
                                    }
                                }
                       int result = chdir("neogit");
                        mkdir("staging");
                         mkdir("unstage");
                    if (result == 0) {
                   printf("Working directory changed successfully.\n");
                   } else {
                      printf("Failed to change working directory.\n");
                                 exit(1);
                                       }
                    printf("Alert: the intilization has been done succesfully.\n");
                    continue;
                }
                FILE*branch = fopen("branch.txt", "w");
                  long size = ftell(branch);
                    if (size == 0) {
                    fputs("master\n", branch);
                            }
                    fclose(branch);
                closedir("staging");
                closedir("unstage");
                closedir(dir);

        }
        else if (strncmp(command, "neogit add -o", 13) == 0)
        {
            char path[100];
            int found_1 = 0;
            int found_2 = 0;
            search(command, path);
            if (access(path, F_OK) == 0)
            {
                if (directoryExists(path))
                {
                    DIR *dir;
                    struct dirent *entry;

                    char *path_temp = basename(path);

                    // Open the directory
                    dir = opendir(path);
                    if (dir == NULL)
                    {
                        printf("Erorr: the specified path does'nt exist.\n");
                        continue;
                    }
                    while ((entry = (readdir(dir))) != NULL)
                    {
                        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                        {
                            char *dir_name = basename(entry->d_name);
                            FILE* staging = fopen("staging.txt", "r");
                            if (staging == NULL){

                                printf("Error: while finding or creating staging.txt.\n");
                            }
                            int len = strlen(dir_name);
                         rename("k", "staging");

                            dir_name[len-1] = '\0';
                            char line[100];
                            while (fgets(line, (sizeof(line)), staging))
                            {
                                if (strstr(line, dir_name) != NULL)
                                {
                                    found_2 = 1;
                                    break;
                                }
                            }
                            if (found_2 == 0)
                            {
                                staging = fopen("staging.txt", "a");
                                fprintf(staging, "%s\n", dir_name);
                                fclose(staging);
                            }
                        }
                    }
                    if (found_2 == 1)
                    {
                        printf("Alert: this directory has already been on stage mode.\n");
                    }
                    else
                    {
                        FILE* staging = fopen("staging.txt", "a");
                        fprintf(staging,"%s\n", path_temp);
                        char t_path[] = "C:\\Users\\abharNet\\Desktop\\test\\";
                        strcat(t_path, path_temp);
                        fclose(staging);printf("%s", t_path);
                        char command[100];
                        char des[] = "C:\\Users\\abharNet\\Desktop\\test\\neogit\\staging";
                        sprintf(command, "Xcopy %s %s", t_path, des);
                        system(command);
                        printf("Alert: your directory is on stage mode now.\n");
                    }
                }
                else
                {
                    FILE* staging = fopen("staging.txt", "r");
                    int len = strlen(path);
                    path[len] = '\0';
                    char line[100];
                    char *temp_path = basename(path);
                    while (fgets(line, sizeof(line), staging))
                    {
                        if (strstr(line, temp_path) != NULL)
                        {
                            found_1 = 1;
                            break;
                        }
                    }
                    fclose(staging);
                    if (found_1 == 1)
                    {
                        printf("Error: this file has already been  on stage mode.\n");
                        continue;
                    }
                    else
                    {
                        staging = fopen("staging.txt", "a");
                        fprintf(staging, "%s\n", temp_path);
                        fclose(staging);
                        char command[100];
                        char t[] = "staging";
                        sprintf(command, "Xcopy %s %s", temp_path, t);
                        system(command);
                        printf("Alert: your file is on stage mode now.\n");
                        continue;
                    }
                }
            }
            else
            {
                printf("Error: the specified path does not lead to any dir ot file.\n");
            }
        }

        else if (strstr(command, "*") != NULL)
        {
            char file_star[1000];
            extractText(command, file_star);
            int counter = 0;
            char names_of_files[100][100];
            char names_of_dir[100][100];
            DIR *dir;
            struct dirent *entry;
            dir = opendir(currentDirectory);
            while ((entry = readdir(dir)) != NULL)
            {
                if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                {
                    strcpy(names_of_files[counter], entry->d_name);
                    counter++;
                }
            }
            closedir(dir);

            for (int i = 0; i < counter; i++)
            {
                if (strstr(names_of_files[i], ".") == NULL)
                {

                    if (match(file_star, names_of_files[i]))
                    {
                        char string[150];
                        strcpy(string, currentDirectory);
                        strcat(string, "\\\\");
                        strcat(string, names_of_files[i]);
                        DIR *dir;
                        int counter_dir = 0;
                        struct dirent *entry;
                        dir = opendir(string);
                        while ((entry = readdir(dir)) != NULL)
                        {

                            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                            {
                                strcpy(names_of_dir[counter_dir], entry->d_name);
                                counter_dir++;
                            }
                        }
                        closedir(dir);
                        for (int j = 0; j < counter_dir; j++)
                        {
                            FILE* staging = fopen("staging.txt", "a");
                            char *temp = basename(names_of_dir[j]);
                            fprintf(staging, "%s\n", temp);
                            fclose(staging);

                        }
                        FILE* staging = fopen("staging.txt", "a");
                        char *temp1 = basename(string);
                        fprintf(staging, "%s\n", temp1);
                        printf("%s", temp1);
                        fclose(staging);

                        printf("Notify: This directory is now in stage mode.\n");
                    }
                }
                else if (strstr(names_of_files[i], ".txt") != NULL)
                {
                    char m[100];
                    strcpy(m, names_of_files[i]);
                    replaceDotWithNull(names_of_files[i]);
                    if (match(file_star, names_of_files[i]))
                    {
                        int len = strlen(names_of_files[i]);
                        names_of_files[i][len] = '\0';
                        bool flag = false;
                        for (int i = 0; i <= counter; i++)
                        {
                            if (match(file_star, names_of_files[i]))
                            {
                                FILE* staging = fopen("staging.txt", "a");
                                fprintf(staging, "%s\n", m);
                                char command[100];
                                char e[] = "staging";
                               // strcat(m, ".txt");
                                printf("%s", m);// printf("%s", )
                                sprintf(command, "copy %s %s", m, e);
                                system(command);
                                fclose(staging);
                                flag = true;

                            }
                        }
                        if (flag)
                        {
                            printf("Alert: your files are on stage mode.\n");
                        }
                        if(!flag)
                        {
                            printf("Error: No file exists\n.");
                        }
                    }
                }
            }
        }

        else if (strncmp(command, "neogit add -f", 13) == 0)
        {
            char *name[1000];
            int flag_for_f = 0;
            int num = token_del(name, command);
            for (int d = 0; d < num; d++)
            {
                if (strstr(name[d], ".") != NULL)
                {
                    flag_for_f = 0;
                    char *temp_name;
                    if (access(name[d], F_OK) == 0)
                    {
                        FILE* staging = fopen("staging.txt", "r");
                        int len = strlen(name[d]);
                        name[len] = '\0';
                        temp_name = basename(name[d]);
                        char line[100];
                        while (fgets(line, sizeof(line), staging))
                        {
                            if (strstr(line, temp_name) != NULL)
                            {
                                flag_for_f = 1;
                                break;
                            }
                        }
                        fclose(staging);
                        if (flag_for_f == 1)
                        {
                            printf("Error: %s has already been  on stage mode.\n", temp_name);
                            continue;
                        }
                        else
                        {
                            staging = fopen("staging.txt", "a");
                            fprintf(staging, "%s\n", temp_name);
                            fclose(staging);
                            char command[100];
                            char y[] = "staging";
                            sprintf(command, "Xcopy %s %s", temp_name, y);
                            system(command);
                        }
                    }
                    else
                    {
                        printf("Error: file %s does not exist", temp_name);
                    }
                }
                else if (strstr(name[d], ".") == NULL)
                {
                    int flag_for_2 = 0;
                    if (access(name[d], F_OK) == 0)
                    {
                        DIR *dir;
                        struct dirent *entry;

                        // Open the directory
                        dir = opendir(name[d]);
                        while ((entry = (readdir(dir))) != NULL)
                        {
                            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                            {
                                FILE* staging = fopen("staging.txt", "r");
                                char *temp_name = basename(entry->d_name);
                                int len = strlen(temp_name);
                                temp_name[len] = '\0';
                                char line[100];
                                while (fgets(line, (sizeof(line)), staging))
                                {
                                    if (strstr(line, temp_name) != NULL)
                                    {
                                        flag_for_2 = 1;
                                        break;
                                    }
                                }
                                if (flag_for_2 == 0)
                                {
                                    staging = fopen("staging.txt", "a");
                                    fprintf(staging, "%s\n", temp_name);
                                    char command[100];
                                    char u[] = "staging";
                                    sprintf(command, "Xcopy %s %s", u, temp_name);
                                    system(command);
                                    fclose(staging);
                                }
                            }
                        }
                        if (flag_for_2 == 1)
                        {
                            printf("Error: this directory has already been on stage mode.\n");
                        }
                        else if (flag_for_2 == 0)
                        {
                            char *temp_dir = basename(name[d]);
                            FILE* staging = fopen("staging.txt", "a");
                            fprintf(staging, "%s\n", temp_dir);  fclose(staging);
                                char command[100];
                                char h[] = "staging";
                                sprintf(command, "Xcopy /E %s %s", temp_dir, h);
                                system(command);


                        }
                    }

                    else
                    {
                        char *temp = basename(name[d]);
                        printf("directory %s does'nt exist.\n", temp);
                    }
                }
            }
        }

        else if (strcmp(command, "neogit add depth") == 0)
        {
            FILE *file;
            char line[100];
            DIR *dir;
            struct dirent *entry;
            file = fopen("staging.txt", "r");
            if (file == NULL)
                printf("Error opening file.\n");
            dir = opendir(copy_one_cu);
            if (dir == NULL)
                printf("Error opening directory.\n");

            while (fgets(line, sizeof(line), file))
            {
                line[strcspn(line, "\n")] = '\0';
                while ((entry = readdir(dir)) != NULL)
                {
                    if (strcmp(line, entry->d_name) == 0)
                    {
                        printf("Alert:%s is on stage mode\n", entry->d_name);
                        break;
                    }
                }
                rewinddir(dir);
            }
            fclose(file);
            FILE *tem = fopen("depth.txt", "w");
            while ((entry = readdir(dir)) != NULL)
            {
                if ((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0))
                {
                    fprintf(tem, "%s\n", entry->d_name);
                }
            }
            fclose(tem);
            closedir(dir);
            FILE *file1, *file2;
            char line1[100], line2[100];
            int match = 0;

            file1 = fopen("depth.txt", "r");
            file2 = fopen("staging.txt", "r");
            while (fgets(line1, sizeof(line1), file1))
            {
                rewind(file2);
                match = 0;
                while (fgets(line2, sizeof(line2), file2))
                {
                    if (strcmp(line1, line2) == 0)
                    {
                        match = 1;
                        break;
                    }
                }

                if (match == 0)
                {
                    printf("Alert: %s is not on stage mode.\n", line1);
                }
            }

            fclose(file1);
            fclose(file2);
            remove(file1);
            remove(tem);
        }

        else if (strncmp(command, "neogit reset", 12) == 0)
        {
            char reset[200];
            search(command, reset);
    ///neogit reset "C:\Users\abharNet\Downloads\.neogit\unstage.txt"
          //  break;
            const char *filename = "staging.txt";
            struct stat path_stat;
            struct dirent *entry;
            if (stat(reset, &path_stat) == 0)
            {

                if (S_ISDIR(path_stat.st_mode))
                {
                    reset_for_directory(filename, reset);
                                }
                else if (S_ISREG(path_stat.st_mode))
                {

                    char *name = basename(reset);

                    FILE *file = fopen("staging.txt", "r");
                    if (file == NULL)
                    {
                        printf("Error opening file.\n");
                        continue;
                    }
                    FILE *tempFile = fopen("temp_for_file.txt", "w");
                    if (tempFile == NULL)
                    {
                        printf("Error creating temporary file.\n");
                        fclose(file);
                        continue;
                    }
                    FILE *unstaged = fopen("unstage.txt", "a");
                    if (unstaged == NULL)
                    {
                        printf("Error: cannot create unstaged file.\n");
                        fclose(tempFile);
                        fclose(file);
                        continue;
                    }

                    char line[1000];
                    while (fgets(line, sizeof(line), file) != NULL)
                    {
                        line[strcspn(line, "\n")] = '\0';
                        // printf("%s", line);
                        if (strstr(line, name) == NULL)
                        {

                            fprintf(tempFile, "%s\n", line);
                        }
                        else
                        {
                            fprintf(unstaged, "%s\n", line);
                        }
                    }
                    fclose(unstaged);
                    fclose(file);
                    fclose(tempFile);

                    remove("staging.txt");
                    rename("temp_for_file.txt", "staging.txt");
                    fclose(tempFile);
                    char* token  = strtok(reset, "\\");
                    int n = 1;
                    char *k;
                    while(token != NULL){
                      k= token;
                      n++;
                      token = strtok(NULL, "\\");
                    }
                    char command[1000];
                    char source[1000];
                    FILE* ds = fopen("ds.txt", "w");
                    fclose(ds);
                    strcpy(source, "C:\\Users\\abharNet\\Desktop\\test\\neogit\\staging");
                    strcat(source, "\\");
                    strcat(source, k);
                   // printf("%s\n", k);
                    printf("%s\n", source);
                    char des[] = "C:\\Users\\abharNet\\Desktop\\test\\neogit\\unstage";
                     printf("Alert: The mission was done successfully.\n");
                    sprintf(command, "move %s %s", source, des);
                    system(command);


                }
            }
        }
        else if(strcmp(command, "neogit add -undo") == 0){
                DIR *dir;
                struct dirent *entry;
                    struct stat file_stat;
                    time_t last_modified = 0;
                    char last_modified_file[256];
                FILE *unstaged = fopen("unstage.txt", "a");
                    if (unstaged == NULL)
                    {
                        printf("Error opening file.\n");
                        continue;
                    }
                    FILE *tempFile = fopen("temp_for_file.txt", "w");
                    if (tempFile == NULL)
                    {
                        printf("Error: creating temporary file.\n");
                        fclose(tempFile);
                        continue;
                    }
                    FILE *file = fopen("staging.txt", "r");
                    if (file == NULL)
                    {
                        printf("Error: cannot create unstaged file.\n");
                        fclose(tempFile);
                        fclose(file);
                        continue;
                    }
    dir = opendir("staging");
    if (dir == NULL) {
        printf("Error opening directory\n");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') {
            continue;
        }

        char file_path[256];
        sprintf(file_path, "staging/%s", entry->d_name);

        if (stat(file_path, &file_stat) == -1) {
            printf("Error:getting file stats\n");
            continue;
        }

        if (file_stat.st_mtime > last_modified) {
            last_modified = file_stat.st_mtime;
            strcpy(last_modified_file, entry->d_name);
        }
    }

    closedir(dir);

    printf("Last modified file in unstage: %s\n", last_modified_file);
    char line[100];
    fprintf(file, "%s\n", last_modified_file);
    fclose(file);
    while(fgets(line, sizeof(line), unstaged)!=NULL){
        line[strcspn(line, "\n")] = '\0';
        if(strcmp(line, last_modified_file) == 0){
            fprintf(tempFile, "%s\n", last_modified_file);
        }
        else{
            fprintf(tempFile, "%s\n", line);
        }
    }
    fclose(tempFile);
    fclose(unstaged);
    remove("staging.txt");
    rename("temp_for_file.txt", "staging.txt");
    fclose(tempFile);
    char comman[100];
    char t[100];
    char des[] = "unstage";
    sprintf(comman, "move %s %s", last_modified_file, des);
    system(comman);
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
       // printf("Current working directory: %s\n", cwd);
    } else {
        perror("getcwd() error");
       continue;
    }
    char y[] = "\\staging\\";
    strcat(y, last_modified_file);
    strcat(cwd, y);
    sprintf(t, "del %s", cwd);
    system(t);

        }
        else if (strncmp(command, "neogit add -redo", 16) == 0)
        {
            FILE *sourceFile, *destinationFile;
            char ch;
            sourceFile = fopen("unstage.txt", "r");
            if (sourceFile == NULL)
            {
                printf("Unable to open source file.\n");
                continue;
            }

            destinationFile = fopen("staging.txt", "a");
            if (destinationFile == NULL)
            {
                printf("Unable to open destination file.\n");
                fclose(sourceFile);
                continue;
            }

            while ((ch = fgetc(sourceFile)) != EOF)
            {
                fputc(ch, destinationFile);
            }

            fclose(sourceFile);
            fclose(destinationFile);
            sourceFile = fopen("unstage.txt", "w");
            fclose(sourceFile);

            printf("Alert: the redo mission has benn done.\n");
            remove("unstage.txt");
            char command[100];
            char tr[300];
            char source[] = "unstage\\*.txt";
            strcpy(tr, WORKING_ADDRESS);
            strcat(tr, "\\neogit\\");
            strcat(tr, source);

            char sd[100];
            strcpy(sd, WORKING_ADDRESS);
            strcat(sd, "\\neogit\\staging");
            sprintf(command, "move %s %s", source, sd);
            system(command);
        }

        else if (strncmp(command, "neogit status", 13) == 0)
        {
            DIR *dir_s;
            struct dirent *entry_s;
            char second_con[100][100];
            char temp_cond[100][100];
            int count_s = 0;
            dir_s = opendir("neogit");
            printf("hi");
            while ((entry_s = readdir(dir_s)) != NULL)
            {

                if (strcmp(entry_s->d_name, ".") != 0 && strcmp(entry_s->d_name, "..") != 0)
                {
                    strcpy(second_con[count_s], entry_s->d_name);
                    count_s++;
                }
            }
            closedir(dir_s);
            int flag_for_stat_d = 0;
            for (i_s = 0; i_s < countt; i_s++)
            {
                flag_for_stat_d = 0;
                for (int j = 0; j < count_s; j++)
                {
                    if (flag_for_stat_d == 0)
                    {
                        if (strcmp(first_name_cond[i_s], second_con[j]) == 0)
                        {
                            flag_for_stat_d = 1;
                        }
                    }
                }
                if (flag_for_stat_d == 0)
                {
                    FILE* staging = fopen("staging.txt", "r");
                    char line[100];
                    int flag = 0;
                    while (fgets(line, sizeof(line), staging) != NULL)
                    {
                        line[strcspn(line, "\n")] = '\0';
                        if (strcmp(line, first_name_cond[i_s]) != 0)
                        {
                            flag = 1;
                            strcpy(temp_cond[i_s], first_name_cond[i_s]);
                            printf("%s --> +D\n", first_name_cond[i_s]);
                            break;
                        }
                    }
                    fclose(staging);
                    if (flag == 0)
                    {
                        strcpy(temp_cond[i_s], first_name_cond[i_s]);
                        printf("%s --> -D\n", first_name_cond[i_s]);
                    }
                }
            }
            int flag_for_stat_a = 0;
            for (int k = 0; k < count_s; k++)
            {
                flag_for_stat_a = 0;
                for (int l = 0; l < countt; l++)
                {
                    if (flag_for_stat_a == 0)
                    {
                        if (strcmp(second_con[k], first_name_cond[l]) == 0)
                        {
                            flag_for_stat_a = 1;
                        }
                    }
                }
                if (flag_for_stat_a == 0)
                {
                    FILE* staging = fopen("staging.txt", "r");
                    char line[100];
                    int flag = 0;
                    while (fgets(line, sizeof(line), staging) != NULL)
                    {
                        line[strcspn(line, "\n")] = '\0';
                        if (strcmp(line, second_con[k]) != 0)
                        {
                            flag = 1;
                            printf("%s --> +A\n", second_con[k]);
                            break;
                        }
                    }
                    fclose(staging);
                    if (flag == 0)
                    {
                        printf("%s --> -A\n", second_con[k]);
                    }
                }
            }
            struct stat updatedFileStat;
            time_t updatedLastModifiedTime[256];
            for (int k = 0; k < countt; k++)
            {
                stat(file_address[k], &updatedFileStat);
                updatedLastModifiedTime[k] = updatedFileStat.st_mtime;
                if ((lastModifiedTime[k] != updatedLastModifiedTime[k] && strcmp(temp_cond[k], first_name_cond[k]) != 0))
                {
                    FILE* staging = fopen("staging.txt", "r");
                    char line[100];
                    int flag = 0;
                    while (fgets(line, sizeof(line), staging) != NULL)
                    {
                        line[strcspn(line, "\n")] = '\0';
                        if (strcmp(line, first_name_cond[k]) != 0)
                        {
                            printf("%s --> +M\n", first_name_cond[k]);
                            flag = 1;
                            break;
                        }
                    }
                    if (flag == 0)
                    {
                        printf("%s --> -M\n", first_name_cond[k]);
                    }
                }
            }
        }
              //  else if(strncmp("neogit reset -f", 14, ))
        else if (strncmp(command, "neogit commit -m", 16) == 0)
        {
            if (access(directoryPath,F_OK)!=-1)
            {
            char commit_message[1000];
            if (strstr(command, "\"")!=NULL)
            {
                extractText(command, commit_message);
                int len = strlen(commit_message);
                if (len >= 72)
                {
                    printf("Error: number of characters must not be more than 72.\n");
                    continue;
                }
               FILE* staging = fopen("staging.txt", "r");
                char copy_address[500];
                strcpy(copy_address, currentDirectory);
                strcat(copy_address, "\\\\staging.txt");
                fseek(staging, 0, SEEK_END);
                long size = ftell(staging);
                if (size == 0 || staging ==NULL)
                {
                    printf("Error: There are no files on stage mode.\n");
                    fclose(staging);
                }
                else
                {



                    char line[300];
                    FILE *message = fopen("message.txt", "a");
                    // Get the current time
                    time_t currentTime = time(NULL);
                    char *timeString;
                    FILE* commit = fopen("commit.txt", "a");
                    rewind(staging);
                    int count = 0; // number of files that goes to staging.
                    while(fgets(line,sizeof(line),staging)!=NULL)
                    {    if(hasDot){
                        int len = strlen(line);
                        line[len] = '\0';
                        fprintf(commit,"%s\n",line);
                        count++;}
                    }
                    fclose(staging);
                    char line1[100];
                    char *ptr;
                    global_config_file = fopen("global_config.txt", "r");
                    if (global_config_file != NULL)
                    {
                            while (fgets(line1,sizeof(line1),global_config_file)!=NULL)
                            {
                                if (strstr(line1,"last")!=NULL) {
                                    char* token;
                                    token = strtok(line1,":");
                                    token = strtok(NULL," ");
                                    commit_id = atoi(token);
                                    commit_id++;
                                    ptr = malloc(sizeof(char) * 2);
                                    sprintf(ptr, "%d", commit_id);
                                }
                            }
                    }
                            fclose(global_config_file);
                            global_config_file = fopen("global_config.txt", "r");
                            char line2 [100];
                            FILE *fcommit = fopen("temp_c.txt","w");
                            while (fgets(line2, sizeof(line2),global_config_file)!=NULL)
                            {
                                int len = strlen(line2);
                                line2[len] = '\0';

                                if (strstr(line2,"last")!= NULL)
                                {
                                    fprintf(fcommit,"last_commit_id : %s\n",ptr);
                                }
                                else {
                                    fprintf(fcommit,"%s",line2);
                                }
                            }
                            fclose(fcommit);
                            fclose(global_config_file);
                            remove("global_config.txt");
                            rename ("temp_c.txt","global_config.txt");
                            fclose(fcommit);
                            char line3[100];
                            staging = fopen("staging.txt","r");
                            rewind(staging);
                            FILE* gc = fopen("global_config.txt","r");
                            char line_gc [100];
                            char* saver_user;
                            while (fgets(line_gc,sizeof(line_gc),gc)!=NULL)
                            {
                                saver_user = strtok(line_gc,":");
                                saver_user = strtok(NULL, " ");
                                break;
                            }
                            fclose(gc);
                            while (fgets(line3, sizeof(line3), staging)!= NULL)
                            {   if(hasDot(line3)){
                                fprintf(message,"file : %s", line3);
                                fprintf (message,"username : %s\n",saver_user);
                                fprintf(message, "commit id : %d\n ", commit_id);
                                fprintf(message, "message is : %s\n", commit_message);
                                fprintf(message, "number of files in this commit is : %d\n", count);
                                timeString = ctime(&currentTime);
                                fprintf(message, "time : %s", timeString);
                                fprintf(message, "branch : %s\n", "master");
                            }
                            }
                            fclose(commit);
                            fclose(message);
                            fclose(staging);
                            staging = fopen("staging.txt", "w");
                            fclose(staging);
                            printf("your commit id is : %d\n", commit_id);
                            printf("your commit message is :%s\n", commit_message);
                            printf("your commit time : %s", timeString);
                         char directoryName[10];
                            sprintf(directoryName, "%d", commit_id);
                            char pth[100] = "C:\\Users\\abharNet\\Desktop\\test\\neogit\\";
                            strcat(pth, directoryName);
                            mkdir(pth);
                        char cmmand[200];
                            sprintf(cmmand, "move C:\\Users\\abharNet\\Desktop\\test\\neogit\\staging\\*.txt %s", pth);
                                    system(cmmand);
                }
            }
            else{
                char saved[100];
                char* extract[1000];
                int index = 0;
                char* ptr = strtok(command, " ");
                while(ptr != NULL){
                    extract[index] = ptr;
                    index++;
                    ptr = strtok(NULL, " ");
                }
                int len = strlen(commit_message);
                if (strcmp(extract [index-1],"-m")==0)
                {
                    printf("Error: Enter a valid message!\n");
                    continue;
                }
                if (len >= 72)
                {
                    printf("Error: number of characters must not be more than 72.\n");
                    continue;
                }
                FILE* staging = fopen("staging.txt", "r");
                char copy_address[500];
                strcpy(copy_address, currentDirectory);
                strcat(copy_address, "\\\\staging.txt");
                fseek(staging, 0, SEEK_END);
                long size = ftell(staging);
                if (size == 0 || staging ==NULL)
                {
                    printf("Error: There are no files on stage mode.\n");
                    fclose(staging);
                    continue;
                }
                else
                {
                    char line[300];
                    FILE *message = fopen("message.txt", "a");
                    // Get the current time
                    time_t currentTime = time(NULL);
                    char *timeString;
                    FILE* commit = fopen("commit.txt", "a");
                    rewind(staging);
                    int count = 0;
                    while(fgets(line,sizeof(line),staging)!=NULL)
                    {
                        if(hasDot(line)){
                          fprintf(commit ,"%s", line);
                        count++;
                        }
                    }
                    fclose(staging);
                    char line1[100];
                    char *ptr;
                    global_config_file = fopen("global_config.txt", "r");
                    if (global_config_file != NULL)
                    {
                            while (fgets(line1,sizeof(line1),global_config_file)!=NULL)
                            {
                                if (strstr(line1,"last")!=NULL) {
                                    char* token;
                                    token = strtok(line1,":");
                                    token = strtok(NULL," ");
                                    commit_id = atoi(token);
                                    commit_id++;
                                    ptr = malloc(sizeof(char) * 2);
                                    sprintf(ptr, "%d", commit_id);
                                }
                            }
                    }
                            fclose(global_config_file);
                            global_config_file = fopen("global_config.txt", "r");
                            char line2 [100];
                            FILE *fcommit = fopen("temp_c.txt","w");
                            while (fgets(line2, sizeof(line2),global_config_file)!=NULL)
                            {
                                if (strstr(line2,"last")!= NULL)
                                {
                                    fprintf(fcommit,"last_commit_id : %s\n",ptr);
                                }
                                else {
                                    fprintf(fcommit,"%s",line2);
                                }
                            }
                            fclose(fcommit);
                            fclose(global_config_file);
                            remove("global_config.txt");
                            rename ("temp_c.txt","global_config.txt");
                            fclose(fcommit);
                            char line3[100];
                            FILE* gc = fopen("global_config.txt","r");
                            char line_gc [100];
                            char* saver_user;
                            while (fgets(line_gc,sizeof(line_gc),gc)!=NULL)
                            {
                                saver_user = strtok(line_gc,":");
                                saver_user = strtok(NULL, " ");
                                break;
                            }
                            fclose(gc);
                            staging = fopen("staging.txt","r");
                            rewind(staging);
                            while (fgets(line3, sizeof(line3), staging)!= NULL)
                            {     if(strstr(line3, "." ) != NULL){
                                fprintf(message,"file : %s", line3);
                                fprintf(message,"username : %s\n",saver_user);
                                fprintf(message, "commit id : %d\n ", commit_id);
                                fprintf(message, "message is : %s\n", extract[index-1]);
                                fprintf(message,"number of files in this commit is : %d\n",count);
                                timeString = ctime(&currentTime);
                                fprintf(message, "time : %s", timeString);
                                fprintf(message, "branch : %s\n", "master");
                            }
                            }
                            fclose(commit);
                            fclose(message);
                            fclose(staging);
                            staging = fopen("staging.txt", "w");
                            fclose(staging);
                            printf("your commit id is : %d\n", commit_id);
                            printf("your commit message is :%s\n", extract[index-1]);
                            printf("your commit time : %s", timeString);
                               char directoryName[10];
                            sprintf(directoryName, "%d", commit_id);
                            char pth[100] = "C:\\Users\\abharNet\\Desktop\\test\\neogit\\";
                            strcat(pth, directoryName);
                            mkdir(pth);
                        char cmmand[200];
                            sprintf(cmmand, "move C:\\Users\\abharNet\\Desktop\\test\\neogit\\staging\\*.txt %s", pth);
                                    system(cmmand);

                }
            }
            }

            else{
            char commit_message[1000];
            if (strstr(command, "\"")!=NULL)
            {
                search(command, commit_message);
                int len = strlen(commit_message);
                if (len >= 72)
                {
                    printf("Error: number of characters must not be more than 72.\n");
                    continue;
                }
                FILE* staging = fopen("staging.txt", "r");
                char copy_address[500];
                strcpy(copy_address, currentDirectory);
                strcat(copy_address, "\\\\staging.txt");
                fseek(staging, 0, SEEK_END);
                long size = ftell(staging);
                if (size == 0 || staging ==NULL)
                {
                    printf("Error: There are no files on stage mode.\n");
                    fclose(staging);
                    continue;
                }
                else
                {
                    char line[300];
                    FILE *message = fopen("message.txt", "a");
                    // Get the current time
                    time_t currentTime = time(NULL);
                    char *timeString;
                    FILE* commit = fopen("commit.txt", "a");
                    rewind(staging);
                    int count = 0; // number of files that goes to staging.
                    while(fgets(line,sizeof(line),staging)!=NULL)
                    {
                        if(hasDot(line)){
                        fputs(line,commit);
                        count++;
                        }
                    }
                    fclose(staging);
                    fclose(commit);
                    char line_user[100];
                    char *ptr;
                    char line_con[100];
                    FILE *config = fopen("config.txt", "r");
                    FILE* user = fopen("user_saver.txt", "r");
                     char* token2;
                     rewind(user);
                     rewind(config);
                    while(fgets(line_user, sizeof(line_user), user) != NULL){
                            line_user[strcspn(line_user, "\n")] = '\0';
                            if(strstr(line_user, "Username") != NULL){
                                token2 = strtok(line_user,":");
                                token2 = strtok(NULL," ");
                                break;
                            }
                        }
                            int count_l = 1;
                            rewind(config);
                            int saver =0;
                            rewind(config);
                            while(fgets(line_con, sizeof(line_con),config) != NULL){
                                   line_con[strlen(line_con) - 1] = '\0';
                                     if((count_l % 5 == 1 )){
                                            char* extract;
                                            extract = strtok(line_con,":");
                                            extract = strtok(NULL," ");
                                            if (strcmp(extract,token2)==0)
                                            {
                                                saver = count_l+2;
                                            }
                                     }
                                     if (count_l == saver)
                                     {
                                        char* token;
                                            token = strtok(line_con,":");
                                            token = strtok(NULL," ");
                                            //printf("%s", token);
                                            commit_id = atoi(token);
                                            commit_id++;
                                            ptr = malloc(sizeof(char) * 2);
                                            sprintf(ptr, "%d", commit_id);
                                            break;
                                     }
                                     count_l++;
                                     }
                            fclose(config);
                            fclose(user);
                            config = fopen("config.txt", "r");
                            char line2 [100];
                            FILE *fcommit = fopen("temp_c.txt","w");
                            int counter_c =0;
                            while (fgets(line2,sizeof(line2),config)!=NULL)
                            {
                                counter_c++;
                                if (counter_c==saver)
                                {
                                    fprintf(fcommit,"last_commit_id : %s\n",ptr);
                                }
                                else {
                                    fprintf(fcommit,"%s",line2);
                                }
                            }
                            fclose(fcommit);
                            fclose(config);
                            remove("config.txt");
                            rename ("temp_c.txt","config.txt");
                            fclose(fcommit);
                            char line3[100];
                            staging = fopen("staging.txt","r");
                            rewind(staging);
                            while (fgets(line3, sizeof(line3), staging)!= NULL)
                            {  if(hasDot(line3)){
                                fprintf(message,"file : %s", line3);
                                fprintf(message, "username : %s\n", token2);
                                fprintf(message, "commit id : %d\n ", commit_id);
                                fprintf(message, "message is : %s\n", commit_message);
                                fprintf(message,"number of files in this commit is : %d\n",count);
                                timeString = ctime(&currentTime);
                                fprintf(message, "time : %s", timeString);
                                fprintf(message, "branch : %s\n", "master");
                            }}
                            fclose(commit);
                            fclose(message);
                            fclose(staging);
                            staging = fopen("staging.txt", "w");
                            fclose(staging);
                            printf("the user committing project is: %s\n", token2);
                            printf("your commit id is : %d\n", commit_id);
                            printf("your commit message is :%s\n", commit_message);
                            printf("your commit time : %s", timeString);
                             char directoryName[10];
                            sprintf(directoryName, "%d", commit_id);
                            char pth[100] = "C:\\Users\\abharNet\\Desktop\\test\\neogit\\";
                            strcat(pth, directoryName);
                            mkdir(pth);
                        char cmmand[200];
                            sprintf(cmmand, "move C:\\Users\\abharNet\\Desktop\\test\\neogit\\staging\\*.txt %s", pth);
                                    system(cmmand);



                }
            }
            else{

                char saved[100];
                char* extract[1000];
                int index = 0;
                char* ptr = strtok(command, " ");
                while(ptr != NULL){
                    extract[index] = ptr;
                    index++;
                    ptr = strtok(NULL, " ");
                }
                strcpy(commit_message,extract[index-1]);
               int len = strlen(commit_message);
               if (strcmp(extract [index-1],"-m")==0)
                {
                    printf("Error: Please enter a valid message.\n");
                    continue;
                }
                if (len >= 72)
                {
                    printf("Error: number of characters must not be more than 72.\n");
                    continue;
                }
                FILE* staging = fopen("staging.txt", "r");
                char copy_address[500];
                strcpy(copy_address, currentDirectory);
                strcat(copy_address, "\\\\staging.txt");
                fseek(staging, 0, SEEK_END);
                long size = ftell(staging);
                if (size == 0 || staging ==NULL)
                {
                    printf("Error: There are no files on stage mode.\n");
                    fclose(staging);
                    continue;
                }
                else
                {
                    char line[300];
                    FILE *message = fopen("message.txt", "a");
                    // Get the current time
                    time_t currentTime = time(NULL);
                    char *timeString;
                   FILE*  commit = fopen("commit.txt", "a");
                    rewind(staging);
                    int count = 0; // number of files that goes to staging.
                    while(fgets(line,sizeof(line),staging)!=NULL)
                    {
                        if(hasDot(line)){
                        fputs(line,commit);
                        count++;
                        }
                    }
                    fclose(staging);
                    fclose(commit);
                    char line_user[100];
                    char *ptr;
                    char line_con[100];
                    FILE *config = fopen("config.txt", "r");
                    FILE* user = fopen("user_saver.txt", "r");
                     char* token2;
                     rewind(user);
                     rewind(config);
                    while(fgets(line_user, sizeof(line_user), user) != NULL){
                            line_user[strcspn(line_user, "\n")] = '\0';
                            if(strstr(line_user, "Username") != NULL){
                                token2 = strtok(line_user,":");
                                token2 = strtok(NULL," ");
                                break;
                            }
                        }
                            int count_l = 1;
                            rewind(config);
                            int saver =0;
                            rewind(config);
                            while(fgets(line_con, sizeof(line_con),config) != NULL){
                                   line_con[strlen(line_con) - 1] = '\0';
                                     if((count_l % 5 == 1 )){
                                            char* extract;
                                            extract = strtok(line_con,":");
                                            extract = strtok(NULL," ");
                                            if (strcmp(extract,token2)==0)
                                            {
                                                saver = count_l+2;
                                            }
                                     }
                                     if (count_l == saver)
                                     {
                                            char* token;
                                            token = strtok(line_con,":");
                                            token = strtok(NULL," ");
                                            commit_id = atoi(token);
                                            commit_id++;
                                            ptr = malloc(sizeof(char) * 2);
                                            sprintf(ptr, "%d", commit_id);
                                            break;
                                     }
                                     count_l++;
                                     }
                            fclose(config);
                            fclose(user);
                            config = fopen("config.txt", "r");
                            char line2 [100];
                            FILE *fcommit = fopen("temp_c.txt","w");
                            int flag_for_print = 0;
                            int counter_c =0;
                            while (fgets(line2,sizeof(line2),config)!=NULL)
                            {
                                counter_c++;
                                if (counter_c==saver)
                                {
                                    fprintf(fcommit,"last_commit_id : %s\n",ptr);
                                }
                                else {
                                    fprintf(fcommit,"%s",line2);
                                }
                            }
                            fclose(fcommit);
                            fclose(config);
                            remove("config.txt");
                            rename ("temp_c.txt","config.txt");
                            fclose(fcommit);
                            char line3[100];
                            staging = fopen("staging.txt","r");
                            rewind(staging);
                            while (fgets(line3, sizeof(line3), staging)!= NULL)
                            {     if(hasDot(line3)){
                                fprintf(message,"file : %s", line3);
                                fprintf(message, "username : %s\n", token2);
                                fprintf(message, "commit id : %d\n ", commit_id);
                                fprintf(message, "message is : %s\n", commit_message);
                                fprintf(message,"number of files in this commit is : %d\n",count);
                                timeString = ctime(&currentTime);
                                fprintf(message, "time : %s", timeString);
                                fprintf(message, "branch : %s\n", "master");
                            }}
                            fclose(commit);
                            fclose(message);
                            fclose(staging);
                            staging = fopen("staging.txt", "w");
                            fclose(staging);
                            printf("the user committing project is: %s\n", token2);
                            printf("your commit id is : %d\n", commit_id);
                            printf("your commit message is :%s\n", commit_message);
                            printf("your commit time : %s", timeString);
                       char directoryName[10];
                            sprintf(directoryName, "%d", commit_id);
                            char pth[100] = "C:\\Users\\abharNet\\Desktop\\test\\neogit\\";
                            strcat(pth, directoryName);
                            mkdir(pth);
                        char cmmand[200];
                            sprintf(cmmand, "move C:\\Users\\abharNet\\Desktop\\test\\neogit\\staging\\*.txt %s", pth);
                                    system(cmmand);

                }
          }
         }

        }

        else if (strncmp(command, "neogit set -m", 13) == 0)
        {printf("hi");
            FILE *shortcuts = fopen("shortcut.txt", "a");
            extractText(command, shortcut_message);
            char *extract[1000];
            int index = 0;
            char *ptr = strtok(command, " ");
            while (ptr != NULL)
            {
                extract[index] = ptr;
                index++;
                ptr = strtok(NULL, " ");
            }
            strcpy(shortcut, extract[index - 1]);

            fprintf(shortcuts, "%s\n", shortcut);
            fprintf(shortcuts, "%s\n", shortcut_message);
            fclose(shortcuts);
        }

        else if (strncmp(command, "neogit commit -s", 16) == 0)
        {
            char *extract_1[1000];
            int index_1 = 0;
            char delimeter[] = " ";
            char *ptr = strtok(command, delimeter);
            while (ptr != NULL)
            {
                extract_1[index_1] = ptr;
                index_1++;
                ptr = strtok(NULL, delimeter);
            }
            char line[100];
            int flag_for_commit = 0;
            FILE *shorts = fopen("shortcut.txt", "r");
            rewind(shorts);
            while (fgets(line, sizeof(line), shorts) != NULL)
            {
                line[strcspn(line, "\n")] = '\0';
                if (strcmp(line, extract_1[index_1 - 1]) == 0)
                {   flag_for_commit =1;
                    if (access(directoryPath,F_OK)!=-1){
                    char commit_message[1000];
                    strcpy(commit_message,extract_1 [index_1-1]);
                    int len = strlen(extract_1 [index_1-1]);
                if (strcmp(extract_1 [index_1-1],"-m")==0)
                {
                    printf("please enter a message.");
                    continue;
                }
                if (len >= 72)
                {
                    printf("plaese enter a shorter commit.");
                    continue;
                }
                FILE* staging = fopen("staging.txt", "r");
                char copy_address[500];
                strcpy(copy_address, currentDirectory);
                strcat(copy_address, "\\\\staging.txt");
                fseek(staging, 0, SEEK_END);
                long size = ftell(staging);
                if (size == 0 || staging ==NULL)
                {
                    printf("Error: Staging file does'nt exist.\n");
                    fclose(staging);
                    continue;
                }
                else
                {
                strcpy(commit_message,extract_1[index_1-1]);
                int len = strlen(commit_message);
                if (strcmp(extract_1 [index_1-1],"-m")==0)
                {
                    printf("Error: enter a valid message.\n");
                    continue;
                }
                if (len >= 72)
                {
                    printf("plaese enter a shorter commit.");
                    continue;
                }
                staging = fopen("staging.txt", "r");
                char copy_address[500];
                strcpy(copy_address, currentDirectory);
                strcat(copy_address, "\\\\staging.txt");
                fseek(staging, 0, SEEK_END);
                long size = ftell(staging);
                if (size == 0 || staging ==NULL)
                {
                    printf("Error: There are no files on stage mode.\n");
                    fclose(staging);
                    continue;
                }
                else
                {
                    char line[300];
                    FILE *message = fopen("message.txt", "a");
                    // Get the current time
                    time_t currentTime = time(NULL);
                    char *timeString;
                    FILE* commit = fopen("commit.txt", "a");
                    rewind(staging);
                    int count = 0; // number of files that goes to staging.
                    while(fgets(line,sizeof(line),staging)!=NULL)
                    {
                        if(hasDot(line)){
                        fprintf(commit ,"%s", line);
                        count++;
                        }
                    }
                    fclose(staging);
                    char line1[100];
                    char *ptr;
                    global_config_file = fopen("global_config.txt", "r");
                    if (global_config_file != NULL)
                    {
                            while (fgets(line1,sizeof(line1),global_config_file)!=NULL)
                            {
                                if (strstr(line1,"last")!=NULL) {
                                    char* token;
                                    token = strtok(line1,":");
                                    token = strtok(NULL," ");
                                    commit_id = atoi(token);
                                    commit_id++;
                                    ptr = malloc(sizeof(char) * 2);
                                    sprintf(ptr, "%d", commit_id);
                                }
                            }
                    }
                            fclose(global_config_file);
                            global_config_file = fopen("global_config.txt", "r");
                            char line2 [100];
                            FILE *fcommit = fopen("temp_c.txt","w");
                            while (fgets(line2, sizeof(line2),global_config_file)!=NULL)
                            {
                                if (strstr(line2,"last")!= NULL)
                                {
                                    fprintf(fcommit,"last_commit_id : %s\n",ptr);
                                }
                                else {
                                    fprintf(fcommit,"%s",line2);
                                }
                            }
                            fclose(fcommit);
                            fclose(global_config_file);
                            remove("global_config.txt");
                            rename ("temp_c.txt","global_config.txt");
                            fclose(fcommit);
                            char line3[100];
                            FILE* gc = fopen("global_config.txt","r");
                            char line_gc [100];
                            char* saver_user;
                            while (fgets(line_gc,sizeof(line_gc),gc)!=NULL)
                            {
                                saver_user = strtok(line_gc,":");
                                saver_user = strtok(NULL, " ");
                                break;
                            }
                            fclose(gc);
                            staging = fopen("staging.txt","r");
                            rewind(staging);
                            int co=0;
                            int check=0;
                            char line18[100];
                            char commit_n [100];
                            FILE* sh = fopen("shortcut.txt","r");
                            while(fgets(line18,sizeof(line18),sh)!=NULL)
                            {
                                co++;
                                line18[strcspn(line18,"\n")]='\0';
                                if (strcmp(line18,commit_message)==0)
                                {
                                    check = co+1;
                                }
                                if (check==co)
                                {
                                    strcpy(commit_n,line18);
                                    break;
                                }
                            }
                            fclose(sh);
                            while (fgets(line3, sizeof(line3), staging)!= NULL)
                            {    if(hasDot(line3)){
                                fprintf(message,"file : %s", line3);
                                fprintf(message,"username : %s\n",saver_user);
                                fprintf(message, "commit id : %d\n ", commit_id);
                                fprintf(message, "message is : %s\n", commit_n);
                                fprintf(message,"number of files in this commit is : %d\n",count);
                                timeString = ctime(&currentTime);
                                fprintf(message, "time : %s", timeString);
                                fprintf(message, "branch : %s\n", "master");
                            }}
                            fclose(commit);
                            fclose(message);
                            fclose(staging);
                            staging = fopen("staging.txt", "w");
                            fclose(staging);
                            printf("your commit id is : %d\n", commit_id);
                            printf("your commit message is :%s\n", commit_n);
                            printf("your commit time : %s", timeString);
                              char directoryName[10];
                            sprintf(directoryName, "%d", commit_id);
                            char pth[100] = "C:\\Users\\abharNet\\Desktop\\test\\neogit\\";
                            strcat(pth, directoryName);
                            mkdir(pth);
                        char cmmand[200];
                            sprintf(cmmand, "move C:\\Users\\abharNet\\Desktop\\test\\neogit\\staging\\*.txt %s", pth);
                                    system(cmmand);
                }
            }}

           else{
                char commit_message[1000];
                strcpy(commit_message,extract_1[index_1-1]);
               int len = strlen(commit_message);
               if (strcmp(extract_1 [index_1-1],"-m")==0)
                {
                    printf("Alert: please enter a message.\n");
                    continue;
                }
                if (len >= 72)
                {
                    printf("Error: The number of characters can not be more  than 72.\n");
                    continue;
                }
                FILE* staging = fopen("staging.txt", "r");
                char copy_address[500];
                strcpy(copy_address, currentDirectory);
                strcat(copy_address, "\\\\staging.txt");
                fseek(staging, 0, SEEK_END);
                long size = ftell(staging);
                if (size == 0 || staging ==NULL)
                {
                    printf("Error: there are no files in stage mode.\n");
                    fclose(staging);
                    continue;
                }
                else
                {
                    char line[300];
                    FILE *message = fopen("message.txt", "a");
                    // Get the current time
                    time_t currentTime = time(NULL);
                    char *timeString;
                    FILE* commit = fopen("commit.txt", "a");
                    rewind(staging);
                    int count = 0; // number of files that goes to staging.
                    while(fgets(line,sizeof(line),staging)!=NULL)
                    {
                        fputs(line,commit);
                        count++;
                    }
                    fclose(staging);
                    fclose(commit);
                    char line_user[100];
                    char *ptr;
                    char line_con[100];
                    FILE *config = fopen("config.txt", "r");
                    FILE* user = fopen("user_saver.txt", "r");
                    char* token2;
                    rewind(user);
                    rewind(config);
                    while(fgets(line_user, sizeof(line_user), user) != NULL){
                            line_user[strcspn(line_user, "\n")] = '\0';
                            if(strstr(line_user, "Username") != NULL){
                                token2 = strtok(line_user,":");
                                token2 = strtok(NULL," ");
                                break;
                            }
                        }
                            int count_l = 1;
                            rewind(config);
                            int saver =0;
                            rewind(config);
                            while(fgets(line_con, sizeof(line_con),config) != NULL){
                                   line_con[strlen(line_con) - 1] = '\0';
                                     if((count_l % 5 == 1 )){
                                            char* extract;
                                            extract = strtok(line_con,":");
                                            extract = strtok(NULL," ");
                                            if (strcmp(extract,token2)==0)
                                            {
                                                saver = count_l+2;
                                            }
                                     }
                                     if (count_l == saver)
                                     {
                                        char* token;
                                            token = strtok(line_con,":");
                                            token = strtok(NULL," ");
                                            //printf("%s", token);
                                            commit_id = atoi(token);
                                            commit_id++;
                                            //  printf("%d\n", commit_id);
                                            ptr = malloc(sizeof(char) * 2);
                                            sprintf(ptr, "%d", commit_id);
                                            break;
                                     }
                                     count_l++;
                                     }
                            fclose(config);
                            fclose(user);
                            config = fopen("config.txt", "r");
                            char line2 [100];
                            FILE *fcommit = fopen("temp_c.txt","w");
                            int counter_c =0;
                            while (fgets(line2,sizeof(line2),config)!=NULL)
                            {
                                counter_c++;
                                if (counter_c==saver)
                                {
                                    fprintf(fcommit,"last_commit_id : %s\n",ptr);
                                }
                                else {
                                    fprintf(fcommit,"%s",line2);
                                }
                            }
                            fclose(fcommit);
                            fclose(config);
                            remove("config.txt");
                            rename ("temp_c.txt","config.txt");
                            fclose(fcommit);
                            char line3[100];
                            int co=0;
                            int check=0;
                            char line18[100];
                            char commit_n [100];
                            FILE* sh = fopen("shortcut.txt","r");
                            while(fgets(line18,sizeof(line18),sh)!=NULL)
                            {
                                co++;
                                line18[strcspn(line18,"\n")]='\0';
                                if (strcmp(line18,commit_message)==0)
                                {
                                    check = co+1;
                                }
                                if (check==co)
                                {
                                    strcpy(commit_n,line18);
                                    break;
                                }
                            }
                            fclose(sh);
                            staging = fopen("staging.txt","r");
                            rewind(staging);
                            while (fgets(line3, sizeof(line3), staging)!= NULL)
                            {   if(hasDot(line3)){
                                fprintf(message,"file : %s", line3);
                                fprintf(message, "username : %s\n", token2);
                                fprintf(message, "commit id : %d\n ", commit_id);
                                fprintf(message, "message is : %s\n", commit_n);
                                fprintf(message,"number of files in this commit is : %d\n",count);
                                timeString = ctime(&currentTime);
                                fprintf(message, "time : %s", timeString);
                                fprintf(message, "branch : %s\n", "matser");
                            }}
                            fclose(commit);
                            fclose(message);
                            fclose(staging);
                            staging = fopen("staging.txt", "w");
                            fclose(staging);
                            printf("the user committing project is: %s\n", token2);
                            printf("your commit id is : %d\n", commit_id);
                            printf("your commit message is :%s\n", commit_n);
                            printf("your commit time : %s", timeString);
                                  char directoryName[10];
                            sprintf(directoryName, "%d", commit_id);
                            char pth[100] = "C:\\Users\\abharNet\\Desktop\\test\\neogit\\";
                            strcat(pth, directoryName);
                            mkdir(pth);
                        char cmmand[200];
                            sprintf(cmmand, "move C:\\Users\\abharNet\\Desktop\\test\\neogit\\staging\\*.txt %s", pth);
                                    system(cmmand);
                }
         }
                }
            }
            if (flag_for_commit == 0)
            {
                printf("Error: the shortcut is invalid.\n");
            }
            fclose(shorts);
        }

        else if (strncmp(command, "neogit replace -m", 17) == 0)
        {
            char saved[100];
            extractText(command, saved);
            char *extract[1000];
            int index = 0;
            char delimeter[] = " ";
            char *ptr = strtok(command, delimeter);
            while (ptr != NULL)
            {
                extract[index] = ptr;
                index++;
                ptr = strtok(NULL, delimeter);
            }
            FILE *cf = fopen("temp_commit.txt", "w");
            FILE *ct = fopen("shortcut.txt", "r");
            int number = 1;
            char line[100];
            int flag_for_replace = 0;
            while (fgets(line, sizeof(line), ct) != NULL)
            {
                // printf("%d\n",number);
                number++;
                line[strcspn(line, "\n")] = '\0';
                if (strcmp(line, extract[index - 1]) == 0)
                {
                    flag_for_replace = 1;
                    break;
                }
            }
            if (flag_for_replace == 0)
            {
                printf("please enter valid shortcut.");
                continue;
            }
            // printf("%d",number);
            fclose(ct);
            fclose(cf);
            ct = fopen("shortcut.txt", "r");
            cf = fopen("temp_commit.txt", "w");
            int number2 = 1;
            while (fgets(line, sizeof(line), ct) != NULL)
            {
                line[strcspn(line, "\n")] = '\0';
                if (number2 == number)
                {
                    fprintf(cf, "%s\n", saved);
                }
                else
                {
                    fprintf(cf, "%s\n", line);
                }
                number2++;
            }
            fclose(ct);
            fclose(cf);
            remove("shortcut.txt");
            rename("temp_commit.txt", "shortcut.txt");
            fclose(cf);
        }

        else if (strncmp(command, "neogit remove -s", 16) == 0)
        {
            char *extract[1000];
            int index = 0;
            char delimeter[] = " ";
            char *ptr = strtok(command, delimeter);
            while (ptr != NULL)
            {
                extract[index] = ptr;
                index++;
                ptr = strtok(NULL, delimeter);
            }
            FILE *sh = fopen("shortcut.txt", "r");
            FILE *delet = fopen("delet.txt", "w");
            char line[100];
            int flag_for_delet = 0;
            int number = 1;
            while (fgets(line, sizeof(line), sh) != NULL)
            {
                line[strcspn(line, "\n")] = '\0';
                if (strcmp(line, extract[index - 1]) == 0)
                {
                    flag_for_delet = 1;
                    break;
                }
                number++;
            }
            if (flag_for_delet == 0)
            {
                printf("please enter valid shortcut.");
                continue;
            }
            // printf("%d",number);
            fclose(sh);
            sh = fopen("shortcut.txt", "r");
            int flag_n = 0;
            int number2 = 1;
            while (fgets(line, sizeof(line), sh) != NULL)
            {
                line[strcspn(line, "\n")] = '\0';
                if (flag_n == 1)
                {
                    flag_n = 0;
                    continue;
                }
                if (number2 == number)
                {
                    flag_n = 1;
                    continue;
                }
                else
                {
                    fprintf(delet, "%s\n", line);
                }
                number2++;
            }
            fclose(delet);
            fclose(sh);
            remove("shortcut.txt");
            rename("delet.txt", "shortcut.txt");
            fclose(delet);
        }

        else if(strcmp("neogit log", command) == 0){
            FILE* message = fopen("message.txt", "r");
            printSentencesInReverseOrder(message);
            fclose(message);

        }

        else if(strncmp("neogit log -n", command, 13) == 0){
            char number[100];
            char line[100];
            search(command, number);
             int count = atoi(number);
            FILE* message = fopen("message.txt", "r");
            reverseForLog(message, count);
            fclose(message);
       }

        else if(strncmp("neogit log -author", command, 18) == 0){
        char user_name[200];
        extractText(command, user_name);
        //printf("%s", user_name);
       // user_name[strlen(user_name)] = '\0';
        FILE* message = fopen("message.txt", "r");
        ReverseFile(message);
        fclose(message);
        FILE* temp_log = fopen("temp_log.txt", "r");
        int log = 0;
        int check = 0;
        char line2[100];
        char* extract;
        while(fgets(line2, sizeof(line2), temp_log) !=  NULL){
                 log++;
            line2[strcspn(line2, "\n")] = '\0';
                if(log % 7  == 6){
                        extract = strtok(line2 ,":");
                        extract = strtok(NULL," ");
                if(strncmp(user_name, extract, 3) == 0){
                   check = log + 1;
                   continue;

                }

                }
             if(check == log){
                    char* ex;
                  //  printf("po");
                    ex = strtok(line2,":");
                    ex = strtok(NULL," ");
                printf("%s was commited by %s\n", ex, user_name);
             }
        }
        fclose(temp_log);
       }

        else if(strncmp("neogit log -since", command, 17) == 0){
        char time[100];
        char* token;
        extractText(command, time);
        char line3[100];
        char* extract[100];
        int line_c = 0;
        int index = 0;
        FILE* temp_log = fopen("temp_log.txt","r");
//printf("%s", time);
        while(fgets(line3, sizeof(line3), temp_log) != NULL){
            line_c++;
            if(line_c % 7 == 2){
                    char *ptr = strtok(line3, " ");
                   while (ptr != NULL)
                    {
                        extract[index] = ptr;
                        index++;
                        ptr = strtok(NULL, " ");
                    }
                    if(compareTimes(extract[index -2], time)){
                        printf("%s %s %s %s %s\n", extract[index-5],  extract[index - 4], extract[index - 3] , extract[index - 2]);
                    }

            }
        }
        fclose(temp_log);
        printf("Notify: done!");
       }

        else if(strncmp("neogit log -before", command, 18) == 0){
        char time[100];
        char* token;
        search(command, time);
        char line3[100];
        char* extract[100];
        int line_c = 0;
        int index = 0;
        char delimeter[] = " ";
        FILE* temp_log = fopen("temp_log.txt","r");
         while(fgets(line3, sizeof(line3), temp_log) != NULL){
            line_c++;
            if(line_c % 7 == 2){
                    char *ptr = strtok(line3, delimeter);
                   while (ptr != NULL)
                    {
                        extract[index] = ptr;
                        index++;
                        ptr = strtok(NULL, delimeter);
                    }
                    if(compareTimes2(extract[index -2], time)){
                        printf("%s %s %s %s %s\n", extract[index-5],  extract[index - 4], extract[index - 3] , extract[index - 2]);
                    }

            }
       }
         printf("Notify: done!");
         fclose(temp_log);


}
else if(strncmp(command, "neogit log -search", 18) == 0){
    char hint[100];
            extractText(command, hint);
            int saver[100];
            char *file_name = "temp_log.txt";
            searchWordInFile(file_name, hint, saver);
            FILE *log = fopen("temp_log.txt", "r");
            char line[100];
            int line_2 = 1;
            int index = 0;
            int flag = 0;
            int c = 1;
            while (fgets(line, sizeof(line), log) != NULL)
            {
                if (line_2 == (saver[index]) - 3)
                {
                    flag = 1;
                    index++;
                }
                if (flag == 1 && c <= 7)
                {
                    c++;
                    printf("%s", line);
                }
                if (flag == 1 && c > 7)
                {
                    flag = 0;
                    c = 1;
                }
                line_2++;
            }
            fclose(log);
}

       else if(strcmp("neogit branch", command) == 0){
            char line[100];
                FILE* branch = fopen("branch.txt", "r");
                    while(fgets(line, sizeof(line), branch) != NULL){
                            printf("%s", line);
                            }
                            fclose(branch);
        }

        else if(strncmp("neogit branch ", command, 13) == 0){
            DIR *dir;
            struct dirent *entry;
            struct stat file_stat;
            time_t last_modified = 0;
            char last_modified_file[256];
            char branch_name[100];
            char line1[100];

            extractText(command, branch_name);
            FILE* branch = fopen("branch.txt", "a");
            fprintf(branch, "%s\n", branch_name);
            fclose(branch);
            FILE *m = fopen("message.txt","r");
            char line_m [100];
            int line_counter = 0;
            while (fgets(line_m,sizeof(line_m),m)!=NULL)
            {
                line_counter++;
            }

            fclose(m);
            FILE* log = fopen("temp_log.txt","r");
             FILE* me = fopen("message.txt","r");
            char line_t [100];
            int counter_t=1;
            int num;
            while(fgets(line_t,sizeof(line_t),log)!=NULL)

            {
                printf("%d\n", counter_t);
                if (counter_t==3)
                {
                    char* number;
                    number = strtok(line_t,":");
                    number = strtok(NULL," ");
                    num = atoi(number);
                    break;
                }
                counter_t++;
            }
            printf("%d", num);
            fclose(me);
            m = fopen("message.txt","r");
            FILE* temp = fopen("temp_b.txt","w");
            char line9[100];
            int co_temp = 1;
            int sum = line_counter - (7*num);

        for (int i=1; i<=num ; i++)
            {
                sum = sum + 7;
                while (fgets(line9,sizeof(line9),m)!=NULL)
                {
                    if (co_temp==sum)
                    {
                        fprintf(temp,"branch : %s\n",branch_name);
                        co_temp++;
                        break;
                    }
                    else {
                        fprintf(temp,"%s",line9);
                    }
                    co_temp++;
                }
            }
    struct stat fileStat;
    time_t latestTime = 0;
    char latestFolder[256];

    dir = opendir(".");
    if (dir == NULL) {
        printf("Error opening directory.\n");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            stat(entry->d_name, &fileStat);
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && fileStat.st_mtime > latestTime) {
                latestTime = fileStat.st_mtime;
                strcpy(latestFolder, entry->d_name);
            }
        }
    }

    closedir(dir);

    printf("Latest folder added: %s\n", latestFolder);
    mkdir(branch_name);
    char source[] =  "C:\\Users\\abharNet\\Desktop\\test\\neogit\\";
    strcat(source, latestFolder);

    char dess[] = "C:\\Users\\abharNet\\Desktop\\test\\neogit\\";
    strcat(dess, branch_name);
        char command[100];
   char* des = branch_name;
   sprintf(command, "Xcopy %s %s", latestFolder, dess);
   system(command);
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
    } else {
        perror("getcwd() error");
       continue;
    } printf("%s", cwd);
 /*   char y[] = "\\commit\\";
    char t[100];
    strcat(y, last_modified_file);
    strcat(cwd, y);
    sprintf(t, "del %s", cwd);
    system(t);*/





            fclose(temp);
            ReverseFile(m);
            fclose (m);
            remove("message.txt");
            rename ("temp_b.txt","message.txt");
            fclose(temp);
        }

       else if(strncmp("neogit log -branch", command, 18) == 0){
        char branch_name[100];
        search(command, branch_name);
        FILE*  branch = fopen("branch.txt", "r");
        char line[100];
        int flag = 0;
        while(fgets(line, sizeof(line), branch) != NULL){
         line[strcspn(line, "\n")] = '\0';
         if(strcmp(line, branch_name) == 0){
             flag = 1;
            break;
         }
       }
       if(flag == 0){
        printf("Error: the branch name is invalid.\n");
        continue;
       }
       fclose(branch);
       FILE* temp_log = fopen("temp_log.txt", "r");
        char line1[100];
        int log = 1;
        int flag2 = 0;
        int num = 6;
      //  int line_counter
        while(fgets(line1, sizeof(line1), temp_log) != NULL){

            if(log % 7 == 2){
                    flag2 = 0;
                char* token;
                char* line_copy;
                strcpy(line_copy, line1);
                token = strtok(line_copy, ":");
                token = strtok (NULL, " ");
                token[strlen(token) - 1] = '\0';
                if(strcmp(token, branch_name) == 0){
                        flag2 = 1;
                       }

                }
                if(flag2 == 1){
             printf("%s", line1);

                }

        log++;



    }

    fclose(temp_log);


       }
       else if(strncmp(command, "neogit checkout -b", 18) == 0){
    char b_name[100];
    extractText(command, b_name);
   // printf("%s", b_name);
    char directory1[] = "C:\\Users\\abharNet\\Desktop\\test";
    char directory2[] ="C:\\Users\\abharNet\\Desktop\\test\\neogit\\";
    strcat(directory2, b_name);
    printf("%s", directory2);
    compareAndDeleteFiles(directory1, directory2);
    FILE* mes = fopen("message.txt", "r");
    char line_mes[1000];
    while((fgets(line_mes, sizeof(line_mes), mes))!= NULL){

    }
    FILE* save = fopen("user_saver.txt", "r");
    if(save != NULL){
    char line[100];
    char* token;
    while(fgets(line, sizeof(line), save)!= NULL){

    token = strtok(line, ":");
        token = strtok(NULL, " ");
                break;
            }
            fclose(save);

          char u[] = "username : ";
            strcat(u, token);
              FILE* mes = fopen("message.txt", "r");
                char line_mes[1000];
                int checking = 0;
                int f = 0;
                char* save;
            while((fgets(line_mes, sizeof(line_mes), mes))!= NULL){
                    checking++;
                if(strcmp(line_mes, u) == 0){
                            f = 1;
                            continue;
                    }
                    if(f == 1){
                            f = 0;
                       save = strtok(line_mes, ":");
                       save = strtok(NULL, " ");
                        break;
                    }
    }
    fclose(mes);
          //  printf("%s", save);
            FILE*  con = fopen("config.txt", "r");
            FILE* temp = fopen("temp_con.txt", "w");
            char line1[100];
            int check = 0;
            char y[] = "Username : ";
            strcat(y, token);
            int num = 0;
            int flag = 0;
           // rewind(con);
            while((fgets(line1, sizeof(line1), con)) != NULL){
                    check ++;
                    line1[strcspn(line1, "\n")] = '\0';
                    if(strncmp(y, line1, 14) == 0){
                        num = check + 3;
                       // continue;
                    }
                if(num  == check){
                   fprintf(temp, "current_commit_id : %s", save);
                   fprintf(temp, "branch : %s", b_name);
flag =1;
                }
                else {
                        if(flag == 0){
                    fprintf(temp, "%s\n", line1);
                        }

                }
            }
            fclose(con);
            fclose(temp);
            char cp[100];
            char r[] = "C:\\Users\\abharNet\\Desktop\\test\\neogit\\config.txt";
            sprintf(cp, "del /F %s", r);
            system(cp);
            rename("temp_con.txt", "config.txt");
            fclose(temp);


            }
            else if(save == NULL){
                FILE* glo = fopen("global_config.txt", "r");
                char glo_line[100];
                char* user;
                while((fgets(glo_line, sizeof(glo_line), glo))!= NULL){
                    user = strtok(glo_line, ":");
                    user = strtok(NULL, " ");
                    break;
                }

fclose(glo);
                FILE* mes = fopen("message.txt", "r");
                char line_mes[1000];
                int checking = 0;
                int f = 0;
                char u[] = "username : ";
                strcat(u, user);
                char* save;
            while((fgets(line_mes, sizeof(line_mes), mes))!= NULL){
                    checking++;
                if(strcmp(line_mes, u) == 0){
                            f = 1;
                            continue;
                    }
                    if(f == 1){
                            f = 0;
                       save = strtok(line_mes, ":");
                       save = strtok(NULL, " ");
                        break;
                    }
    }
                fclose(mes);
                char q[] = "Username : ";
                strcat(q, user);
                FILE* glow = fopen("global_config.txt", "r");
                FILE* temp = fopen("temp_con.txt", "w");
                char line7[100];
                int check = 0;
                int num = 0;
                int flag = 0;
                while((fgets(line7, sizeof(line7), glow)) != NULL){
                    check ++;
                if(strcmp(q, line7) == 0){
                    num  = check+ 3;
                                    }
                if(num == check){
                    fprintf(temp, "current_commit_id : %s", save);
                    fprintf(temp, "branch : %s\n", b_name);
                    flag = 1;
                }
                else {
                        if(flag == 0){
                          fprintf(temp, "%s", line7);
                        }

                }
            }
            fclose(glow);
            fclose(temp);
            char cp[100];
            char r[] = "C:\\Users\\abharNet\\Desktop\\test\\neogit\\global_config.txt";
            sprintf(cp, "del /F %s", r);
            system(cp);
            rename("temp_con.txt", "global_config.txt");
            fclose(temp);


            }





       }
        else if(strncmp(command, "neogit checkout -id", 19) == 0){
            char idd[100];
            DIR* dir;
            struct dirent *entry;
            extractText(command, idd);
            char directory1[] = "C:\\Users\\abharNet\\Desktop\\test";
            char directory2[] ="C:\\Users\\abharNet\\Desktop\\test\\neogit\\";
             char directory3[] ="C:\\Users\\abharNet\\Desktop\\test\\neogit\\staging";
             strcat(directory2, idd);
             if(!directoryExists(directory2)){
                    printf("Error: the commit id is invalid");
             }
            dir = opendir(directory3);
             int o = 0;
            while((entry = readdir(dir)) != NULL){
             o++;
          }
            closedir(dir);
            if(o > 2){
                printf("Error: No commited files exists.\n");
            }
            compareAndDeleteFiles(directory1, directory2);
            FILE* save = fopen("user_saver.txt", "r");
            if(save != NULL){
             char line[100];
             char* token;
            while(fgets(line, sizeof(line), save)!= NULL){

                token = strtok(line, ":");
                token = strtok(NULL, " ");
                break;
            }
            fclose(save);
            char u[] = "Username : ";
            strcat(u, token);
            //printf("%s", u);
            FILE*  con = fopen("config.txt", "r");
            FILE* temp = fopen("temp_con.txt", "w");
            char line1[100];
            int check = 0;
            int num = 0;
            while((fgets(line1, sizeof(line1), con)) != NULL){
                    check ++;
                if(strcmp(u, line1) == 0){
                    num = 3 + check;
                        }
                if(num == check){
                    fprintf(temp, "current_commit_id : %s\n", idd);
                }
                else{
                    fprintf(temp, "%s", line1);
                }
            }
            fclose(con);
            fclose(temp);
            char cp[100];
            char r[] = "C:\\Users\\abharNet\\Desktop\\test\\neogit\\config.txt";
            sprintf(cp, "del /F %s", r);
            system(cp);
            rename("temp_con.txt", "config.txt");
            fclose(temp);
            }
            else if(save == NULL){
                FILE* glo = fopen("global_config.txt", "r");
                FILE* temp = fopen("temp_con.txt", "w");
                char line1[100];
                int check = 0;
                int num = 0;
                while((fgets(line1, sizeof(line1), glo)) != NULL){
                    check ++;

                if(4 == check){
                    fprintf(temp, "current_commit_id : %s\n", idd);
                }
                else{
                    fprintf(temp, "%s", line1);
                }
            }
            fclose(glo);
            fclose(temp);
            char cp[100];
            char r[] = "C:\\Users\\abharNet\\Desktop\\test\\neogit\\global_config.txt";
            sprintf(cp, "del /F %s", r);
            system(cp);
            rename("temp_con.txt", "global_config.txt");
            fclose(temp);

            }
            printf("Alert : checked out to the %s commit", idd);
        }
        else if(strncmp(command, "neogit tag -a -m -c", 19) == 0){
    char token[100];
    char* c_mit = "8";
    extractText(command, token);
    char* token2;

   char* namee;
   char* message;
  time_t currentTime = time(NULL);
    char* timeString;
  int overwrite = 0;
  namee = strtok(token, " ");

  message =  strtok(NULL , " ");
c_mit = strtok(NULL, " ");
//printf("%s",c_mit);
   if(strstr(command, "-f") != NULL){
            overwrite = 1;
          }

                char line_m[100];
                int l = 0;
                int n = 0;
                const char* op;
          char u[] = "tag : ";
          strcat(u, namee);
          int j = sizeof(u) + 1;
          FILE* tag = fopen("tag.txt", "r");
          char t_line[100];
          int g = 0;
          const char* id;
          while((fgets(t_line, sizeof(t_line), tag)) != NULL){
                if(strncmp(t_line, u, 8)== 0){
                    printf("Error: the tag name already exists.\n");
                    g = 1;
                    break;
                }
            if(g == 1){
                fclose(tag);
                    continue;
                }
                }
                fclose(tag);
                 FILE* gl = fopen("global_config.txt", "r");
                char * user;
                char* user22;
               const char* email;
               int p = 0;
                if(gl != NULL){
                tag = fopen("tag.txt", "a");
                fprintf(tag, "tag : %s\n", namee);
                char g_line[100];
                rewind(gl);
                    while((fgets(g_line, sizeof(g_line), gl)) != NULL){
                            p++;
                    if(p == 1){
                        user22 = strtok(g_line, ":");
                        user22 = strtok(NULL, " ");
                    fprintf(tag, "Author: %s", user22);


                    }
                    if(p == 2){
                        email = strtok(g_line, ":");
                        email = strtok(NULL, " ");
                        fprintf(tag, "<<%s>>\n", email);

                    }
                    }
                    fclose(gl);
                    fprintf(tag, "commit : %s\n", c_mit);
                    fprintf(tag, "message : %s\n", message);
                    timeString = ctime(&currentTime);
                    fprintf(tag, "Date : %s\n", timeString);
                        fclose(tag);
                        continue;
                }
                else{
                  FILE* cn = fopen("user_saver.txt", "r");
                    char c_line[100];
                    char we[] = "Username : ";
                    rewind(cn);
                    while((fgets(c_line, sizeof(c_line), cn)) != NULL){
                            c_line[strcspn(c_line, "\n")] = '\0';
                            if(strstr(c_line, we) != NULL){
                            user = strtok(c_line, ":");
                            user = strtok(NULL, " ");
                            }
                            if(strstr(c_line, "email : ") != NULL){
                                email = strtok(c_line, ":");
                                email = strtok(NULL, " ");
                            }
                          }
                    fclose(cn);
                     tag = fopen("tag.txt", "a");
                    fprintf(tag, "tag : %s\n", namee);
                    fprintf(tag, "Author: %s <<%s>>\n", user, email);
                    fprintf(tag, "commit : %s\n", c_mit);
                    fprintf(tag, "message : %s\n", message);
                    timeString = ctime(&currentTime);
                    fprintf(tag, "Date : %s\n", timeString);
                    fclose(tag);
                }

        }

        else if(strncmp(command, "neogit tag -a -m", 16) == 0){
           char token[1000];
           char* message;
           time_t currentTime = time(NULL);
           char* timeString;
           extractText(command, token);
           int overwrite = 0;
          char* name = strtok(token, " ");
          message = strtok(NULL, " ");
          if(strstr(command, "-f") != NULL){
            overwrite = 1;
          }

              //  FILE* mes = fopen("message.txt", "r");
                char line_m[100];
                char iuiu[] = "username : ";
               // strcat(o, user);
                int l = 0;
                int n = 0;
                const char* op;
          char u[] = "tag: ";
          strcat(u, name);
          int j = sizeof(u) + 1;
          FILE* tag = fopen("tag.txt", "r");
          char t_line[100];
          int g = 0;
          const char* id;
          while((fgets(t_line, sizeof(t_line), tag)) != NULL){
                if(strncmp(t_line, u, j)== 0){
                    printf("Error: the tag name already exists.\n");
                    g = 1;
                    break;
                }
            if(g == 1){
                fclose(tag);
                    continue;
                }
                }
                fclose(tag);

                FILE* gl = fopen("global_config.txt", "r");
                char * user;
                char* user22;
               const char* email;
               int p = 0;
                if(gl != NULL){
                tag = fopen("tag.txt", "a");
                fprintf(tag, "tag : %s\n", name);
                char g_line[100];
                rewind(gl);
                    while((fgets(g_line, sizeof(g_line), gl)) != NULL){
                            p++;
                    if(p == 1){
                        user22 = strtok(g_line, ":");
                        user22 = strtok(NULL, " ");
                    fprintf(tag, "Author: %s", user22);


                    }
                    if(p == 2){
                        email = strtok(g_line, ":");
                        email = strtok(NULL, " ");
                        fprintf(tag, "<<%s>>\n", email);

                    }
                    if(p == 3){
                       id = strtok(g_line, ":");
                       id = strtok(NULL, " ");
                        fprintf(tag, "commit : %s", id);
                    }
                    }
                    fclose(gl);

                    fprintf(tag, "message : %s\n", message);
                    timeString = ctime(&currentTime);
                    fprintf(tag, "Date : %s\n", timeString);
                        fclose(tag);
                        continue;
                }

                else{
                    FILE* cn = fopen("user_saver.txt", "r");
                    char c_line[100];
                    char we[] = "Username : ";
                    rewind(cn);
                    while((fgets(c_line, sizeof(c_line), cn)) != NULL){
                            c_line[strcspn(c_line, "\n")] = '\0';
                            if(strstr(c_line, we) != NULL){
                            user = strtok(c_line, ":");
                            user = strtok(NULL, " ");
                            }
                            if(strstr(c_line, "email : ") != NULL){
                                email = strtok(c_line, ":");
                                email = strtok(NULL, " ");
                            }
                          }
                    fclose(cn);
                    FILE* cc = fopen("config.txt", "r");
                    char co_line[100];
                    strcat(we, user);
                    int o = 0;
                    int u = 0;

                    while((fgets(co_line, sizeof(co_line), cc)) != NULL){
                            o++;

                        if(4 == o){
                            id = strtok(co_line, ":");
                            id = strtok(NULL, " ");
                            break;
                        }
                    }
                    fclose(cc);
                     tag = fopen("tag.txt", "a");
                    fprintf(tag, "tag : %s\n", name);
                    fprintf(tag, "Author: %s <<%s>>\n", user, email);

                    fprintf(tag, "commit : %s", id);
                    fprintf(tag, "message : %s\n", message);
                    timeString = ctime(&currentTime);
                    fprintf(tag, "Date : %s\n", timeString);
                    fclose(tag);

                }}


else if(strncmp(command, "neogit tag -a -c", 16) == 0){
    char token[100];
    extractText(command, token);
    char* c_mit;
  char* namee;
  time_t currentTime = time(NULL);
    char* timeString;
  int overwrite = 0;
  namee = strtok(token, " ");
  c_mit  = strtok(NULL, " ");
   if(strstr(command, "-f") != NULL){
            overwrite = 1;
          }

                char line_m[100];
                int l = 0;
                int n = 0;
                const char* op;
          char u[] = "tag : ";
          strcat(u, namee);
          int j = sizeof(u) + 1;
          FILE* tag = fopen("tag.txt", "r");
          char t_line[100];
          int g = 0;
          const char* id;
          while((fgets(t_line, sizeof(t_line), tag)) != NULL){
                if(strncmp(t_line, u, 6)== 0){
                    printf("Error: the tag name already exists.\n");
                    g = 1;
                    break;
                }
            if(g == 1){
                fclose(tag);
                    continue;
                }
                }
                fclose(tag);

                FILE* gl = fopen("global_config.txt", "r");
                char * user;
                char* user22;
               const char* email;
               int p = 0;
                if(gl != NULL){
                tag = fopen("tag.txt", "a");
                fprintf(tag, "tag : %s\n", namee);
                char g_line[100];
                rewind(gl);
                    while((fgets(g_line, sizeof(g_line), gl)) != NULL){
                            p++;
                    if(p == 1){
                        user22 = strtok(g_line, ":");
                        user22 = strtok(NULL, " ");
                    fprintf(tag, "Author: %s", user22);


                    }
                    if(p == 2){
                        email = strtok(g_line, ":");
                        email = strtok(NULL, " ");
                        fprintf(tag, "<<%s>>\n", email);

                    }
                    }
                    fclose(gl);
                    fprintf(tag, "commit : %s\n", c_mit);
                    char message[] = "empty";
                    fprintf(tag, "message : %s\n", message);
                    timeString = ctime(&currentTime);
                    fprintf(tag, "Date : %s\n", timeString);
                        fclose(tag);
                        continue;
                }
                else{
                  FILE* cn = fopen("user_saver.txt", "r");
                    char c_line[100];
                    char we[] = "Username : ";
                    rewind(cn);
                    while((fgets(c_line, sizeof(c_line), cn)) != NULL){
                            c_line[strcspn(c_line, "\n")] = '\0';
                            if(strstr(c_line, we) != NULL){
                            user = strtok(c_line, ":");
                            user = strtok(NULL, " ");
                            }
                            if(strstr(c_line, "email : ") != NULL){
                                email = strtok(c_line, ":");
                                email = strtok(NULL, " ");
                            }
                          }
                    fclose(cn);
                     tag = fopen("tag.txt", "a");
                    fprintf(tag, "tag : %s\n", namee);
                    fprintf(tag, "Author: %s <<%s>>\n", user, email);
                    char message[] = "empty";
                    fprintf(tag, "commit : %s\n", c_mit);
                    fprintf(tag, "message : %s\n", message);
                    timeString = ctime(&currentTime);
                    fprintf(tag, "Date : %s\n", timeString);
                    fclose(tag);





                }

}


    else if(strncmp(command, "neogit tag -a", 13) == 0){
     char name[100];
     extractText(command, name);
     time_t currentTime = time(NULL);
    char* timeString;
    int overwrite = 0;

          if(strstr(command, "-f") != NULL){
            overwrite = 1;
          }
          char u[] = "tag: ";
          strcat(u, name);
          int j = sizeof(u) + 1;
        FILE* tag = fopen("tag.txt", "r");
          char t_line[100];
          int g = 0;
          char* id;
          while((fgets(t_line, sizeof(t_line), tag)) != NULL){
                if(strncmp(t_line, u, j)== 0){
                    printf("Error: the tag name already exists.\n");
                    g = 1;
                    break;
                }
            if(g == 1){
                fclose(tag);
                    continue;
                }
                }
                fclose(tag);
                FILE* gl = fopen("global_config.txt", "r");
                char * user;
                char* user22;
               const char* email;
               int p = 0;
                if(gl != NULL){
                tag = fopen("tag.txt", "a");
                fprintf(tag, "tag : %s\n", name);
                char g_line[100];
                rewind(gl);
                    while((fgets(g_line, sizeof(g_line), gl)) != NULL){
                            p++;
                    if(p == 1){
                        user22 = strtok(g_line, ":");
                        user22 = strtok(NULL, " ");
                    fprintf(tag, "Author: %s", user22);


                    }
                    if(p == 2){
                        email = strtok(g_line, ":");
                        email = strtok(NULL, " ");
                        fprintf(tag, "<<%s>>\n", email);

                    }
                    if(p == 3){
                       id = strtok(g_line, ":");
                       id = strtok(NULL, " ");
                        fprintf(tag, "commit : %s", id);
                    }
                    }
                    fclose(gl);
                    char mess[] = "empty";
                    fprintf(tag, "message : %s\n", mess);
                    timeString = ctime(&currentTime);
                    fprintf(tag, "Date : %s\n", timeString);
                        fclose(tag);
                        continue;
                }

                else{
                    FILE* cn = fopen("user_saver.txt", "r");
                    char c_line[100];
                    char we[] = "Username : ";
                    rewind(cn);
                    while((fgets(c_line, sizeof(c_line), cn)) != NULL){
                            c_line[strcspn(c_line, "\n")] = '\0';
                            if(strstr(c_line, we) != NULL){
                            user = strtok(c_line, ":");
                            user = strtok(NULL, " ");
                            }
                            if(strstr(c_line, "email : ") != NULL){
                                email = strtok(c_line, ":");
                                email = strtok(NULL, " ");
                            }
                          }
                    fclose(cn);
                    FILE* cc = fopen("config.txt", "r");
                    char co_line[100];
                    strcat(we, user);
                    int o = 0;
                    int u = 0;

                    while((fgets(co_line, sizeof(co_line), cc)) != NULL){
                            o++;

                        if(4 == o){
                            id = strtok(co_line, ":");
                            id = strtok(NULL, " ");
                            break;
                        }
                    }
                    fclose(cc);
                     tag = fopen("tag.txt", "a");
                    fprintf(tag, "tag : %s\n", name);
                    fprintf(tag, "Author: %s <<%s>>\n", user, email);
                    fprintf(tag, "commit : %s", id);
                    char mess[] = "empty";
                    fprintf(tag, "message : %s\n", mess);
                    timeString = ctime(&currentTime);
                    fprintf(tag, "Date : %s\n", timeString);
                    fclose(tag);

                }




    }
    else if(strcmp(command, "neogit tag -l") == 0){
        FILE* tag = fopen("tag.txt", "r");
        char tag_line[100];
        int u = 0;
        char line_1[MAX_LINE_LENGTH];
        char **lines = NULL;
        int numLines = 0;
        FILE* temp = fopen("sort_tag.txt", "w");
        char* token;
        while((fgets(tag_line, sizeof(tag_line), tag)) != NULL){
            u++;
            if(u % 6 == 1){
              token = strtok(tag_line, ":");
              token = strtok(NULL, " ");
              fprintf(temp, "%s", token);
            }
        }
        fclose(temp);
        fclose(temp);
        fclose(tag);
        FILE* tep = fopen("sort_tag.txt", "r");

    if (tep == NULL) {
        printf("Error opening file.\n");
        continue;
    }

    while (fgets(line_1, MAX_LINE_LENGTH, tep) != NULL) {
        line_1[strcspn(line_1, "\n")] = '\0';
        char *newLine = malloc(strlen(line_1) + 1);
        strcpy(newLine, line_1);
        lines = realloc(lines, (numLines + 1) * sizeof(char *));
        lines[numLines] = newLine;
        numLines++;
    }
    fclose(tep);
    qsort(lines, numLines, sizeof(char *), compare);
    for (int i = 0; i < numLines; i++) {
        printf("%s\n", lines[i]);
    }
    for (int i = 0; i < numLines; i++) {
        free(lines[i]);
    }
    free(lines);


    }
    else if(strncmp(command, "neogit tag show", 15) == 0){
            char tag_name[100];
            extractText(command, tag_name);
            FILE* tag = fopen("tag.txt", "r");
            char ta_line[100];
            char u[] = "Author: ";
            strcat(u, tag_name);
            int flag = 0;
            int num = 0;
            int s = 0;
            char* token;
            while((fgets(ta_line, sizeof(ta_line), tag)) != NULL){
                s++;
                ta_line[strcspn(ta_line, "\n")] = '\0';
                if(s % 6 == 1){
                        char copy[100];
                    strcpy(copy, ta_line);
                    token = strtok(copy, ":");
                    token = strtok(NULL, " ");
                  //  printf("%s\n", token);
                    if(strcmp(token , tag_name) == 0){
                    flag = 1;
                    num = s +5;
                       // printf("%s\n", ta_line);
                      }

                    }
                    if(flag == 1 && num != s){
                        printf("%s\n", ta_line);

                    }
                    if(num == s){
                        break;
                    }
                }

        fclose(tag);
    }
    else if(strcmp(command, "neogit pre-commit hooks list") == 0){
        printf("These hooks are available:\n");
        printf("todo-check\n");
        printf("eof-blank-space\n");
        printf("format-check\n");
   //     printf("balance-braces\n");
       // printf("indentation-check\n");
  //      printf("static-error-check\n");
        printf("file-size-check\n");
        printf("character-limit\n");
        printf("time-limit\n");


    }
    else if(strncmp(command, "neogit pre-commit applied hooks", 32) == 0){
      FILE* hook = fopen("hook.txt", "r");
      char ho_lines[100];
      printf("Applied hooks are: \n");
      while((fgets(ho_lines, sizeof(ho_lines), hook)) != NULL){
        printf("%s", ho_lines);
      }
      fclose(hook);
    }
    else if(strncmp(command, "neogit pre-commit add hook", 26) == 0){
        FILE* hook = fopen("hook.txt", "a");
        char name[100];
        extractText(command, name);
        fprintf(hook, "%s\n", name);
        fclose(hook);
        printf("Notify: The hook was added successfully.\n");
    }
    else if(strncmp(command, "neogit pre-commit remove hook", 29) == 0){
        FILE* hook = fopen("hook.txt", "r");
        FILE* t_hook = fopen("temp_hook.txt", "w");
        char name[100];
        extractText(command, name);
        char h_line[100];
        while((fgets(h_line, sizeof(h_line), hook)) != NULL){
            h_line[strcspn(h_line, "\n")] = '\0';
            if(strcmp(h_line, name) == 0){
                continue;
            }
            else{
                fprintf(t_hook, "%s\n", h_line);
            }
        }
        fclose(t_hook);
        fclose(hook);
        fclose(hook);
        char ty;
        strcpy(ty, WORKING_ADDRESS);
        strcat(ty, "\\neogit\\");
        strcat(ty, "hook.txt");
        char g[100];
        sprintf(g, "del %s", ty);
        system(g);
        rename("temp_hook.txt", "hook.txt");
        fclose(t_hook);
    }
    else if(strcmp(command, "neogit pre-commit") == 0){
                FILE* hook = fopen("hook.txt", "r");
                char hoo_l[100];
                char *u;
                int index = 0;
                int flag_limit = 0;
                int flag_blank = 0;
                int flag_todo = 0;
                int flag_size = 0;
                int flag_time = 0;
                int flag_format = 0;
                int flag_check = 0;
                while((fgets(hoo_l, sizeof(hoo_l), hook)) != NULL){
                    hoo_l[strcspn(hoo_l, "\n")] = '\0';
                    if(strcmp(hoo_l, "character-limit") == 0){
                        flag_limit = 1;
                    }
                    else if(strcmp(hoo_l, "eof-blank-space") == 0){
                            flag_blank = 1;
                            }
                    else if(strcmp(hoo_l, "todo-check") == 0){
                        flag_todo = 1;
                    }
                    else if(strcmp(hoo_l, "file-size-check") == 0){
                        flag_size = 1;
                    }
                    else if(strcmp(hoo_l, "time-limit") == 0){
                        flag_time = 1;
                    }
                    else if(strncmp(hoo_l, "format-check", 12) == 0){
                            flag_format = 1;
                    }
                                     }
                fclose(hook);

                    DIR *dir;
                    struct dirent *entry;
                    char n_stage[500];
                    strcpy(n_stage, WORKING_ADDRESS);
                    strcat(n_stage, "\\neogit\\");
                    char path[500];
                    strcpy(path, WORKING_ADDRESS);
                    strcat(path, "\\neogit\\");
                    strcat(path, "staging");
                    dir = opendir(path);
                        if (dir == NULL) {
                    printf("Error : Unable to open the directory.\n");
                            continue;
                            }
                            int flag = 0;
                            int num =0;
    while ((entry = readdir(dir)) != NULL) {
            flag_check = 0;
        if (entry->d_type != DT_REG || entry->d_name[0] == '.') {
            continue;
        }
         SetColor(23);
        printf("%s:\n", entry->d_name);

        if(flag_limit == 1){
        char file_path[256];
        strcpy(file_path, path);
        strcat(file_path, "\\");
        strcat(file_path, entry->d_name);

        int d = lenght(file_path);
if (!d){
    flag_check = 1;
}
        }
        if(flag_size == 1){
        char file_pah[256];
        strcpy(file_pah, path);
        strcat(file_pah, "\\");
        strcat(file_pah, entry->d_name);
        int u = isFileLarge(file_pah);
        if(!u){
            flag_check = 1;
        }
        }
        if(flag_todo == 1){
         char fle_pah[256];
        strcpy(fle_pah, path);
        int o = checkFilesForTodo(fle_pah);
        if(!o){
            flag_check = 1;
        }
        }
        if(flag_blank == 1){
        char file_p[256];
        strcpy(file_p, path);
        strcat(file_p, "\\");
        strcat(file_p, entry->d_name);
           int p =  checkBlankSpaces(file_p);
           if(!p){
            flag_check = 1;
           }
        }
        if(flag_time == 1){
        SetColor(50);
        char *filename = entry->d_name;
        if (strstr(filename, ".mp3") != NULL || strstr(filename, ".mov") != NULL) {
            FILE *file = fopen(filename, "r");
            if (file != NULL) {
                fseek(file, 0, SEEK_END);
                long file_size = ftell(file);
                fclose(file);

                if (file_size > 10 * 60 * 1024) {
                    printf("time-limit...................................FAILED.\n");
                } else {
                    flag_check = 1;
                    printf("time-limit...................................PASSED.\n");
                }
            }

        }
        }
       // printf("%d", flag_format);
        if(flag_format == 1){
        SetColor(50);
        if (strstr(entry->d_name, ".txt") ||
            strstr(entry->d_name, ".csv") ||
            strstr(entry->d_name, ".jpg") ||
            strstr(entry->d_name, ".png") ||
            strstr(entry->d_name, ".pdf") ||
            strstr(entry->d_name, ".doc") ||
            strstr(entry->d_name, ".xlsx")) {
            printf("format-check......................................PASSED.\n");
        } else {
            flag_check = 1;
            printf("format-check......................................FAILED.\n");
        }

        }
        if(flag_check == 1){
            printf("Alert: some files failed enter 1 to continue..\n");
            scanf("%d", num);
            if(num == 0){
                continue;
            }
        }
       if(flag_check == 0 || num == 1){
        char e_path[500];
       strcpy(e_path, path);
        strcat(e_path, "\\");
       strcat(e_path, entry->d_name);
        FILE* con = fopen("config.txt", "r");
        int check = 0;
        char l_p[100];
        char* token;
        char* o;
        while((fgets(l_p, sizeof(l_p), con)) != NULL){
            check++;
            if(check == 3){
                token  = strtok(l_p, ":");
                token = strtok(NULL, " ");
                int a = atoi(token);
                a++;
                o = malloc(sizeof(char) * 2);
                sprintf(o, "%d", a); printf("%s", o);

        }
        char cmb[100];
        mkdir(o);
        char op[1000];
        strcpy(op, WORKING_ADDRESS);
        strcat(op, "\\neogit\\");
        strcat(op, o);
        sprintf(cmb, "move %s %s", e_path, op);
        system(cmb);
        fclose(con);
        }

    }

    }
 closedir(dir);

    }
    else if(strncmp(command, "neogit pre-commit -f", 20) == 0){
        char add[300];
        extractText(command, add);
        char* f1;
        char* f2;
        f1 = strtok(add, " ");
        char * q;
        strcpy(q, f1);
        char* w;
        f2 = strtok(NULL, " ");
        strcpy(w, f2);
        char* f1_1;
        char* f2_1;
        FILE* hook = fopen("hook.txt", "r");
                char hoo_l[100];
                char *u;
                int index = 0;
                int flag_limit = 0;
                int flag_blank = 0;
                int flag_todo = 0;
                int flag_size = 0;
                int flag_time = 0;
                int flag_format = 0;
                int flag_check = 0;
                while((fgets(hoo_l, sizeof(hoo_l), hook)) != NULL){
                    hoo_l[strcspn(hoo_l, "\n")] = '\0';
                    if(strcmp(hoo_l, "character-limit") == 0){
                        flag_limit = 1;
                    }
                    else if(strcmp(hoo_l, "eof-blank-space") == 0){
                            flag_blank = 1;
                            }
                    else if(strcmp(hoo_l, "todo-check") == 0){
                        flag_todo = 1;
                    }
                    else if(strcmp(hoo_l, "file-size-check") == 0){
                        flag_size = 1;
                    }
                    else if(strcmp(hoo_l, "time-limit") == 0){
                        flag_time = 1;
                    }
                    else if(strncmp(hoo_l, "format-check", 12) == 0){
                            flag_format = 1;
                    }
                                     }
                fclose(hook);

                    DIR *dir;
                    struct dirent *entry;
                    char n_stage[500];
                    strcpy(n_stage, WORKING_ADDRESS);
                    strcat(n_stage, "\\neogit\\");
                    char path[500];
                    strcpy(path, WORKING_ADDRESS);
                    strcat(path, "\\neogit\\");
                    strcat(path, "staging");
                    dir = opendir(path);
                        if (dir == NULL) {
                    printf("Error : Unable to open the directory.\n");
                            continue;
                            }
                            int flag = 0;
                            int num =0;

  for(int i = 1 ; i < 3; i++) {
            flag_check = 0;
         SetColor(23);
        printf("File %d", i);

        if(flag_limit == 1 && i == 1){
        int d = lenght(f1);
if (!d){
    flag_check = 1;
}
        }
        if(flag_limit == 1 && i == 2){
                   int d = lenght(f2);
            if (!d){
            flag_check = 1;
}
        }
        if(flag_size == 1 && i == 1){
        int u = isFileLarge(f1);
        if(!u){
            flag_check = 1;
        }
        }
        if(flag_size == 1 && i == 2){
        int u = isFileLarge(f2);
        if(!u){
            flag_check = 1;
        }
        }
        if(flag_todo == 1 && i == 1){
        int o = checkFilesForTodo(f1);
        if(!o){
            flag_check = 1;
        }
        }
                if(flag_todo == 1 && i == 2){
        int o = checkFilesForTodo(f2);
        if(!o){
            flag_check = 1;
        }
        }
        if(flag_blank == 1 && i == 1){
           int p =  checkBlankSpaces(f1);
           if(!p){
            flag_check = 1;
           }
        }
              if(flag_blank == 1 && i == 2){
           int p =  checkBlankSpaces(f2);
           if(!p){
            flag_check = 1;
           }
        }
        if(flag_time == 1 && i == 1){
        SetColor(50);;
        if (strstr(f1, ".mp3") != NULL || strstr(f1, ".mov") != NULL) {
            FILE *file = fopen(f1, "r");
            if (file != NULL) {
                fseek(file, 0, SEEK_END);
                long file_size = ftell(file);
                fclose(file);

                if (file_size > 10 * 60 * 1024) {
                    printf("time-limit...................................FAILED.\n");
                } else {
                    flag_check = 1;
                    printf("time-limit...................................PASSED.\n");
                }
            }

        }
        }
          if(flag_time == 1 && i == 2){
        SetColor(50);;
        if (strstr(f2, ".mp3") != NULL || strstr(f2, ".mov") != NULL) {
            FILE *file = fopen(f2, "r");
            if (file != NULL) {
                fseek(file, 0, SEEK_END);
                long file_size = ftell(file);
                fclose(file);

                if (file_size > 10 * 60 * 1024) {
                    printf("time-limit...................................FAILED.\n");
                } else {
                    flag_check = 1;
                    printf("time-limit...................................PASSED.\n");
                }
            }

        }
        }
       // printf("%d", flag_format);
        if(flag_format == 1&& i == 1){
        SetColor(50);
        if (strstr(f1, ".txt") ||
            strstr(f1, ".csv") ||
            strstr(f1, ".jpg") ||
            strstr(f1, ".png") ||
            strstr(f1, ".pdf") ||
            strstr(f1, ".doc") ||
            strstr(f1, ".xlsx")) {
            printf("format-check......................................PASSED.\n");
        } else {
            flag_check = 1;
            printf("format-check......................................FAILED.\n");
        }

        }
               if(flag_format == 1&& i == 2){
        SetColor(50);
        if (strstr(f2, ".txt") ||
            strstr(f2, ".csv") ||
            strstr(f2, ".jpg") ||
            strstr(f2, ".png") ||
            strstr(f2, ".pdf") ||
            strstr(f2, ".doc") ||
            strstr(f2, ".xlsx")) {
            printf("format-check......................................PASSED.\n");
        } else {
            flag_check = 1;
            printf("format-check......................................FAILED.\n");
        }

        }
        if(flag_check == 1){
            printf("Alert: some files failed enter 1 to continue..\n");
            scanf("%d", num);
            if(num == 0){
                continue;
            }
        }
       if(flag_check == 0 || num == 1){
        char e_path[500];
       strcpy(e_path, path);
        strcat(e_path, "\\");
       strcat(e_path, entry->d_name);
        FILE* con = fopen("config.txt", "r");
        int check = 0;
        char l_p[100];
        char* token;
        char* o;
        while((fgets(l_p, sizeof(l_p), con)) != NULL){
            check++;
            if(check == 3){
                token  = strtok(l_p, ":");
                token = strtok(NULL, " ");
                int a = atoi(token);
                a++;
                o = malloc(sizeof(char) * 2);
                sprintf(o, "%d", a); printf("%s", o);

        }
        char cmb[100];
        mkdir(o);
        char op[1000];
        strcpy(op, WORKING_ADDRESS);
        strcat(op, "\\neogit\\");
        strcat(op, o);
        sprintf(cmb, "move %s %s", e_path, op);
        system(cmb);
        fclose(con);
        }

    }





    }


    }
    else if(strncmp(command, "neogit grep -f -p", 17) == 0){
char* path;
char* word;
char kol[100];
extractText(command, kol);
path = strtok(kol, " ");
word = strtok(NULL, " ");
int n;
printf("Show the line? 1== yes 0 == no \n ");
scanf("%d", &n);
searchWordInFile(path, word, n);
    }


    }
                }



