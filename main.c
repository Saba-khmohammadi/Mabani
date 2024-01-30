     else if (strncmp(command, "neogit status", 13) == 0)
        {
            DIR *dir_s;
            struct dirent *entry_s;
            char second_con[100][100];
            char temp_cond[100][100];
            int count_s = 0;
            dir_s = opendir(copy_one_cu);

            // Read each entry in the directory
            while ((entry_s = readdir(dir_s)) != NULL)
            {
                // Ignore "." and ".." entries
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
                    staging = fopen("staging.txt", "r");
                    char line[100];
                    int flag = 0;
                    while (fgets(line, sizeof(line), staging) != NULL)
                    {
                        line[strcspn(line, "\n")] = '\0';
                        if (strcmp(line, first_name_cond[i_s]) != 0)
                        {
                            flag = 1;
                            strcpy(temp_cond[i_s], first_name_cond[i_s]);
                            printf("%s || +D\n", first_name_cond[i_s]);
                            break;
                        }
                    }
                    fclose(staging);
                    if (flag == 0)
                    {
                        strcpy(temp_cond[i_s], first_name_cond[i_s]);
                        printf("%s || -D\n", first_name_cond[i_s]);
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
                    staging = fopen("staging.txt", "r");
                    char line[100];
                    int flag = 0;
                    while (fgets(line, sizeof(line), staging) != NULL)
                    {
                        line[strcspn(line, "\n")] = '\0';
                        if (strcmp(line, second_con[k]) != 0)
                        {
                            flag = 1;
                            printf("%s || +A\n", second_con[k]);
                            break;
                        }
                    }
                    fclose(staging);
                    if (flag == 0)
                    {
                        printf("%s || -A\n", second_con[k]);
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
                    staging = fopen("staging.txt", "r");
                    char line[100];
                    int flag = 0;
                    while (fgets(line, sizeof(line), staging) != NULL)
                    {
                        line[strcspn(line, "\n")] = '\0';
                        if (strcmp(line, first_name_cond[k]) != 0)
                        {
                            printf("%s || +M\n", first_name_cond[k]);
                            flag = 1;
                            break;
                        }
                    }
                    if (flag == 0)
                    {
                        printf("%s || -M\n", first_name_cond[k]);
                    }
                }
            }
        }
