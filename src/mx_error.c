#include "pathfinder.h"

void mx_error(char *filename)
{ 
    /* •error: file [filename] does not existif the file does not exist. */
    int f1 = open(filename, 0); //Open file
    if(f1 < 0){
        mx_printerr("error: file ");
        mx_printerr(filename);
        mx_printerr(" does not exist\n");
        exit(-1);
    }
    close(f1);
    char *file = mx_file_to_str(filename);
    /* error: file [filename] is empty if the file is empty. */
    if(file == NULL){
        mx_printerr("error: file ");
        mx_printerr(filename);
        mx_printerr(" is empty\n");
        exit(-1);
    }
    char **str_split = mx_strsplit(file, '\n');
    char *first_str = str_split[0];
    /* •error: line 1 is not valid if the first line contains something other than digits orhas a non-positive value */
    for(int i = 0; first_str[i] != '\0'; i++)
    {
        if(mx_isdigit(first_str[i]) == 0)
        {
            mx_printerr("error: line 1 is not valid\n");
            exit(-1);
        }
    }
    if(mx_atoi(first_str) < 1)
    {
        mx_printerr("error: line 1 is not valid\n");
        exit(-1);
    }
    // /* •error: invalid number of islands if the number received in the first line does notmatch with the number of islands */

    char **str_arr = mx_strsplit(file, '\n');
    int islands_first_str = mx_atoi(str_split[0]);
    int amount_of_string = 0;
    for(int i = 1; str_arr[i]; i++)
    {
        amount_of_string++;
    }
    for(int i = 1; i < amount_of_string + 1; i++) //Check
    { 
        if(str_arr[i][mx_strlen(str_arr[i]) - 1] == ',' || str_arr[i][0] == ',' || str_arr[i][0] == '-')
        {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i + 1));
            mx_printerr(" is not valid\n");
            exit(-1);
        }
    } 
    for(int i = 1; i < amount_of_string + 1; i++) //Check
    { 
        int count1 = 0;
        int count2 = 0;
        for(int j = 0; j < mx_strlen(str_arr[i]); j++)
        {
            if(str_arr[i][j] == ',')
            {
                count1++;
            }
            if(str_arr[i][j] == '-')
            {
                count2++;
            }
        }
        if(count1 != 1 || count2 != 1)
        {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i+1));
            mx_printerr(" is not valid\n");
            exit(-1);
        }
    }

    char *final[amount_of_string * 2][4];
    for (int i = 1; i < amount_of_string + 1; i++) 
    {
        char **temp1 = mx_strsplit(str_arr[i], '-');
        if(temp1[1][0] == ',')
        {
            mx_printerr("error: line ");
            mx_printerr(mx_itoa(i+1));
            mx_printerr(" is not valid\n");
            exit(-1);
        }
        char **temp2 = mx_strsplit(temp1[1], ',');
        for(int j = 0; j < mx_strlen(temp2[1]); j++)
        {
            if(!mx_isdigit(temp2[1][j]))
            {
                mx_printerr("error: line ");
                mx_printerr(mx_itoa(i+1));
                mx_printerr(" is not valid\n");
                exit(-1);
            }
            
        }
        
        final[i][0] = mx_strdup(temp1[0]);
        
        if (i != 0){
 
            final[i][1] = mx_strdup(temp2[0]);
            final[i][2] = mx_strdup(temp2[1]);
            final[i][3] = NULL;
        }

        
    }

    for(int i = 1; i < amount_of_string + 1; i++){
        for(int j = 1; j < amount_of_string + 1; j++){
            if(i == j){
                if(mx_strcmp(final[i][0], final[j][1]) == 0){
                    mx_printerr("error: line "); 
                    mx_printerr(mx_itoa(i + 1)); 
                    mx_printerr(" is not valid\n"); 
                    exit(-1);
                }   
            }
        }
    }
      
    char *buffer[amount_of_string * 2];
    
    for (int i = 0, iter = 1; i < amount_of_string; i++, iter++)
    {
        buffer[i] = final[iter][0];
    }
    
    for (int i = amount_of_string, iter = 1; i < amount_of_string * 2; i++, iter++)
    {
        buffer[i] = final[iter][1];   
    }

    int counter = 0;
    int tmp = amount_of_string * 2;
    char *islands[islands_first_str * 2];
    for(int i = 0; i < islands_first_str; i++)
    {
        islands[i] = NULL;
    }
    bool found_island = false;
    for (int line = 1; line <= amount_of_string; line++)
    {
        for (int word = 0; word < 2; word++)
        {
            for (int i = 0; i < islands_first_str; i++)
            {
                if (islands[i] != NULL && !mx_strcmp(final[line][word], islands[i]))
                {
                    found_island = true;
                    break;
                }
            }
            if (!found_island)
            {
                for (int i = 0; i < islands_first_str; i++)
                {
                    if (islands[i] == NULL)
                    {
                        islands[i] = mx_strdup(final[line][word]);
                        break;
                    }
                }
            }
            found_island = false;
        }
    }

    int size = amount_of_string * 2;
    for(int i = 0; i < size; i++)
    {
        for(int j = i + 1; j < size; j++)
        {
            if(mx_strcmp(buffer[i], buffer[j])== 0)
            {
                counter++;
                break;
            }
        }
    }

    int res = tmp - counter;
    if(res != islands_first_str)
    {
        mx_printerr("error: invalid number of islands\n");
        exit(-1);
    }
  
    /* •error: duplicate bridges if there is more than one bridge between the islands */
    char *bridges[amount_of_string * 2][1];
    for(int i = 1; i < amount_of_string + 1; i++)
    {
        char **tmp1 = mx_strsplit(str_arr[i], ',');
        bridges[i][0] = mx_strdup(tmp1[0]);
         
    }
    // mx_printstr(final[i][0]); первый столбец
    // mx_printstr(final[i][1]); второй столбец
    int tmp_size = amount_of_string + 1;
    for(int i = 1; i < tmp_size; i++)
    {
       for(int j = 1; j < tmp_size; j++)
       {
            if(i != j)
            {
                if(mx_strcmp(bridges[i][0], bridges[j][0]) == 0)
                {
                    mx_printerr("error: duplicate bridges\n");
                    exit(-1);
                }
                else if(!mx_strcmp(final[i][0], final[j][1]) && !mx_strcmp(final[i][1], final[j][0]))
                {
                    mx_printerr("error: duplicate bridges\n");
                    exit(-1);
                }
            }
        }
    }
    /* •error: sum of bridges lengths is too big if the sum of the lengths of all bridges inthe file exceeds INT_MAX */
    //final[1][2] = putb
    long int sum = 0;
    for(int i = 1; i <= amount_of_string; i++)
    {
        sum += mx_atoi(final[i][2]);
    }
    
    if(sum > MAX_INT)
    {
        mx_printerr("error: sum of bridges lengths is too big\n");
        exit(-1);
    }
}

