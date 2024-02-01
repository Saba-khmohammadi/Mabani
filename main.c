   else{
            char commit_message[1000];
            if (strstr(command, "\"")!=NULL)
            {
                search(command, commit_message);
                int len = strlen(commit_message);
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
                    printf("there is no file on stage mood. first please add some file.");
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
                    commit = fopen("commit.txt", "a");
                    rewind(staging);
                    int count = 0; // number of files that goes to staging.
                    while(fgets(line,sizeof(line),staging)!=NULL)
                    {
                        fputs(line,commit);
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
                            {
                                fprintf(message,"file : %s", line3);
                                fprintf(message, "username : %s\n", token2);
                                fprintf(message, "commit id : %d\n ", commit_id);
                                fprintf(message, "message is : %s\n", commit_message);
                                timeString = ctime(&currentTime);
                                fprintf(message, "time : %s", timeString);
                                count++;
                            }
                            fprintf(message, "number of files is : %d", count);
                            fclose(commit);
                            fclose(message);
                            fclose(staging);
                            staging = fopen("staging.txt", "w");
                            fclose(staging);
                            printf("the user committing project is: %s\n", token2);
                            printf("your commit id is : %d\n", commit_id);
                            printf("your commit message is :%s\n", commit_message);
                            printf("your commit time : %s", timeString);
                }
            }
            else{

                char saved[100];
                char* extract[1000];
                int index = 0;
                char delimeter[] = " ";
                char* ptr = strtok(command, delimeter);
                while(ptr != NULL){
                    extract[index] = ptr;
                    index++;
                    ptr = strtok(NULL, delimeter);
                }
                strcpy(commit_message,extract[index-1]);
               int len = strlen(commit_message);
               if (strcmp(extract [index-1],"-m")==0)
                {
                    printf("please enter a message.");
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
                    printf("there is no file on stage mood. first please add some file.");
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
                    commit = fopen("commit.txt", "a");
                    rewind(staging);
                    int count = 0; // number of files that goes to staging.
                    while(fgets(line,sizeof(line),staging)!=NULL)
                    {
                        fputs(line,commit);
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
                            {
                                fprintf(message,"file : %s", line3);
                                fprintf(message, "username : %s\n", token2);
                                fprintf(message, "commit id : %d\n ", commit_id);
                                fprintf(message, "message is : %s\n", commit_message);
                                timeString = ctime(&currentTime);
                                fprintf(message, "time : %s", timeString);
                                count++;
                            }
                            fprintf(message, "number of files is : %d", count);
                            fclose(commit);
                            fclose(message);
                            fclose(staging);
                            staging = fopen("staging.txt", "w");
                            fclose(staging);
                            printf("the user committing project is: %s\n", token2);
                            printf("your commit id is : %d\n", commit_id);
                            printf("your commit message is :%s\n", commit_message);
                            printf("your commit time : %s", timeString);
                }
          }
         }
        }

        else if (strncmp(command, "neogit set -m", 13) == 0)
        {
            FILE *shortcuts = fopen("shortcut.txt", "a");
            extractText(command, shortcut_message);
            // printf("%s",shortcut_message);
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
                staging = fopen("staging.txt", "r");
                char copy_address[500];
                strcpy(copy_address, currentDirectory);
                strcat(copy_address, "\\\\staging.txt");
                fseek(staging, 0, SEEK_END);
                long size = ftell(staging);
                if (size == 0 || staging ==NULL)
                {
                    printf("there is no file on stage mood. first please add some file.");
                    fclose(staging);
                    continue;
                }
                else
                {
                strcpy(commit_message,extract_1[index_1-1]);
                int len = strlen(commit_message);
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
                staging = fopen("staging.txt", "r");
                char copy_address[500];
                strcpy(copy_address, currentDirectory);
                strcat(copy_address, "\\\\staging.txt");
                fseek(staging, 0, SEEK_END);
                long size = ftell(staging);
                if (size == 0 || staging ==NULL)
                {
                    printf("there is no file on stage mood. first please add some file.");
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
                    commit = fopen("commit.txt", "a");
                    rewind(staging);
                    int count = 0; // number of files that goes to staging.
                    while(fgets(line,sizeof(line),staging)!=NULL)
                    {
                        //int len = strlen(line);
                        //line[len] = '\0';
                        fprintf(commit ,"%s", line);
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
                                //int len = strlen(line2);
                                //line2[len] = '\0';
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
                            {
                                fprintf(message,"file : %s", line3);
                                fprintf(message, "commit id : %d\n ", commit_id);
                                fprintf(message, "message is : %s\n", commit_n);
                                timeString = ctime(&currentTime);
                                fprintf(message, "time : %s", timeString);
                                count++;
                            }
                            fprintf(message, "number of files is : %d\n", count);
                            fclose(commit);
                            fclose(message);
                            fclose(staging);
                            staging = fopen("staging.txt", "w");
                            fclose(staging);
                            printf("your commit id is : %d\n", commit_id);
                            printf("your commit message is :%s\n", commit_n);
                            printf("your commit time : %s", timeString);
                }
                }
            }

                    else{
                char commit_message[1000];
                strcpy(commit_message,extract_1[index_1-1]);
               int len = strlen(commit_message);
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
                staging = fopen("staging.txt", "r");
                char copy_address[500];
                strcpy(copy_address, currentDirectory);
                strcat(copy_address, "\\\\staging.txt");
                fseek(staging, 0, SEEK_END);
                long size = ftell(staging);
                if (size == 0 || staging ==NULL)
                {
                    printf("there is no file on stage mood. first please add some file.");
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
                    commit = fopen("commit.txt", "a");
                    rewind(staging);
                    int count = 0; // number of files that goes to staging.
                    while(fgets(line,sizeof(line),staging)!=NULL)
                    {
                        fputs(line,commit);
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
                            {
                                fprintf(message,"file : %s", line3);
                                fprintf(message, "username : %s\n", token2);
                                fprintf(message, "commit id : %d\n ", commit_id);
                                fprintf(message, "message is : %s\n", commit_n);
                                timeString = ctime(&currentTime);
                                fprintf(message, "time : %s", timeString);
                                count++;
                            }
                            fprintf(message, "number of files is : %d", count);
                            fclose(commit);
                            fclose(message);
                            fclose(staging);
                            staging = fopen("staging.txt", "w");
                            fclose(staging);
                            printf("the user committing project is: %s\n", token2);
                            printf("your commit id is : %d\n", commit_id);
                            printf("your commit message is :%s\n", commit_n);
                            printf("your commit time : %s", timeString);
                }
         }
                }
            }
            if (flag_for_commit == 0)
            {
                printf("you enterd invalid shortcut.");
            }
            fclose(shorts);
        }