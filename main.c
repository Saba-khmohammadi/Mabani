   else if (strncmp(command, "neogit add", 10) == 0 && strstr(command, "*") == NULL && strncmp(command, "neogit add -f", 13) != 0 && strncmp(command, "neogit add depth", 16) != 0)
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

                    char* path_temp = basename(path);

                    // Open the directory
                    dir = opendir(path);
                    if (dir == NULL)
                    {
                        printf("something wrong happend. please try again.");
                        continue;
                    }
                    while ((entry = (readdir(dir))) != NULL)
                    {
                        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                        {
                            char* dir_name = basename(entry->d_name);
                            staging = fopen("staging.txt", "r");
                            if (staging == NULL)
                            printf("something wrong happend. plaese try again...\n"); // for sure.
                            int len = strlen(dir_name);
                            dir_name[len] = '\0';
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
                                if (staging == NULL)
                                printf("something wrong happend. olease try again.");
                                fprintf(staging, "%s\n", dir_name);
                                fclose(staging);
                            }
                        }
                    }
                    if (found_2 == 1)
                    {
                        printf("this directory has been already on stage mood.");
                    }
                    else
                    {
                        staging = fopen("staging.txt", "a");
                        fprintf(staging, "%s\n", path_temp);
                        fclose(staging);
                        printf("your directory is on stage mood now.");
                    }
                }
                else
                {
                    // first we check that we have this address in our file or not.
                    staging = fopen("staging.txt", "r");
                    if (staging == NULL)
                    printf("something wrong happend. plaese try again.");
                    int len = strlen(path);
                    path[len] = '\0';
                    char line[100];
                    char* temp_path = basename (path);
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
                        printf("this file has been already on stage mood.");
                    }
                    else
                    {
                        staging = fopen("staging.txt", "a");
                        if (staging == NULL)
                        printf("something wrong happend. olease try again.");
                        // char temp_name [1000] = token_k(0,path);
                        fprintf(staging, "%s\n", temp_path);
                        fclose(staging);
                        printf("your file is on stage mood now.");
                    }
                }
            }
            else
            {
                printf("we dont have such a file or directory");
            }
        }

         if (strstr(command, "*") != NULL)
        {
            char file_star[1000];
            search(command, file_star);
            int counter = 0;
            char names_of_files[100][100];
            char names_of_dir[100][100];
            DIR *dir;
            struct dirent *entry;
            dir = opendir("D:\\GIT");
            // Check if the directory was opened successfully
            if (dir == NULL)
            {
                printf("Unable to open the directory.\n");
            }
            // Read each entry in the directory
            while ((entry = readdir(dir)) != NULL)
            {
                // Ignore the "." and ".." entries
                if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                {
                    strcpy(names_of_files[counter], entry->d_name);
                    counter++;
                }
            }
            closedir(dir);
            for (int i = 0; i <= counter; i++)
            {
                if (strstr(names_of_files[i], ".") == NULL)
                {
                    if (match(file_star, names_of_files[i]))
                    {
                        char string[150] = "D:\\GIT\\";
                        strcat(string, names_of_files[i]);
                        DIR *dir;
                        int counter_dir = 0;
                        struct dirent *entry;
                        dir = opendir(string);
                        // Check if the directory was opened successfully
                        if (dir == NULL)
                        {
                            printf("Unable to open the directory.\n");
                        }
                        // Read each entry in the directory
                        while ((entry = readdir(dir)) != NULL)
                        {
                            // Ignore the "." and ".." entries
                            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                            {
                                strcpy(names_of_dir[counter_dir], entry->d_name);
                                counter_dir++;
                            }
                        }
                        closedir(dir);
                        for (int j = 0; j <= counter_dir; j++)
                        {
                            staging = fopen("staging.txt", "a");
                            if (staging == NULL)
                            printf("something wrong happend. please try again.");
                            char* temp = basename(names_of_dir[j]);
                            fprintf(staging, "%s\n", temp);
                            fclose(staging);
                        }
                        staging = fopen("staging.txt", "a");
                        char* temp1 = basename(string);
                        fprintf(staging, "%s\n", temp1);
                        fclose(staging);
                        printf("This directory is now in stage mood!\n");
                    }
                }
                else if (strstr(names_of_files[i], ".") != NULL)
                {

                    saperator_dot(names_of_files[i]);
                    bool flag = false;
                    for (int i = 0; i <= counter; i++)
                    {
                        if (match(file_star, names_of_files[i]))
                        {
                            staging = fopen("staging.txt", "a");
                            if (staging == NULL)
                            printf("something wrong happend. please try again.");
                            fprintf(staging, "%s\n", names_of_files[i]);
                            fclose(staging);
                            flag = true;
                            break;
                        }
                    }
                    if (flag)
                    {
                        printf("your file is on stage mood.");
                    }
                    else
                    {
                        printf("we dont have such a file.");
                    }
                }
            }
        }

         if (strncmp(command, "neogit add -f", 13) == 0)
        {
            char *name[1000];
            int flag_for_f = 0;
            int y = token_del(name, command);
            for (int d = 0; d < y; d++)
            {
                if (strstr(name[d], ".") != NULL)
                {
                    flag_for_f = 0;
                    char* temp_name;
                    if (access(name[d], F_OK) == 0)
                    {
                        staging = fopen("staging.txt", "r");
                        if (staging == NULL)
                        printf("something wrong happend. plaese try again.");
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
                            printf("%s has been already on stage mood.\n",temp_name);
                        }
                        else
                        {
                            staging = fopen("staging.txt", "a");
                            if (staging == NULL)
                            printf("something wrong happend. olease try again.");
                            fprintf(staging, "%s\n", temp_name);
                            fclose(staging);
                        }
                    }
                    else {
                        printf("file %s is not exists",temp_name);
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
                        if (dir == NULL)
                        {
                            printf("something wrong happend. please try again.");
                            continue;
                        }
                        while ((entry = (readdir(dir))) != NULL)
                        {
                            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
                            {
                                staging = fopen("staging.txt", "r");
                                if (staging == NULL)
                                printf("something wrong happend. plaese try again."); // for sure.
                                char* temp_name = basename(entry->d_name);
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
                                    if (staging == NULL)
                                    printf("something wrong happend. please try again.");
                                    fprintf(staging, "%s\n", temp_name);
                                    fclose(staging);
                                }
                            }
                        }
                        if (flag_for_2 == 1)
                        {
                            printf("this directory has been already on stage mood.\n");
                        }
                        else if (flag_for_2==0)
                        {
                            char* temp_dir = basename(name[d]);
                            staging = fopen("staging.txt", "a");
                            fprintf(staging, "%s\n", temp_dir);
                            fclose(staging);
                        }
                    }

                    else
                    {
                        char* temp = basename(name[d]);
                        printf("directory %s is not exists.\n",temp);
                    }
                }
            }
        }

         if (strncmp(command, "neogit add depth", 16) == 0)
        {
            const char *path = "D:\\GIT" ;
            struct dirent *entry;
            struct stat fileStat;
            DIR *dir = opendir(path);

            if (dir == NULL)
            {
                printf("Unable to open directory.\n");
            }

            while ((entry = readdir(dir)) != NULL)
            {
                char filePath[1000];
                snprintf(filePath, sizeof(filePath), "%s/%s", path, entry->d_name);

                if (stat(filePath, &fileStat) == -1)
                {
                    printf("Unable to get file stats.\n");
                    continue;
                }
                staging = fopen("staging.txt", "r");
                char line[100];
                while (fgets(line, sizeof(line), staging))
                {
                    if (strstr(line, entry->d_name) != NULL)
                    {
                        printf("this %s is on stage mood.\n", entry->d_name);
                    }
                    else
                    {
                        printf("this %s is not on stage mood.\n", entry->d_name);
                    }
                }
            }
            closedir(dir);
        }
    }
}
