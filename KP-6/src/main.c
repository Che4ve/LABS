#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/studentpc.h"
#include "../headers/dict.h"

#define MAX_LEN 250 // Maximum length of a line in the file

 int main(int argc, char **argv)
{
    // Buffer to store a single line from the file
    char buffer[MAX_LEN];
     // Buffer to store the properties from the first line of the file
    char properties[MAX_LEN];
     // Create a hash table to store the student PCs
    HashTable* pc_table = createTable(TABLE_SIZE);
     // Open the file for reading
    FILE* f1 = fopen("S:/Git/labs/KP-6/info.txt", "r");
    if (f1 == NULL) {
        perror("Failed to open file");
        return 1;
    }
     // Read the first line of the file
    fgets(properties, MAX_LEN, f1);
     // Print the categories that will be compared
    char* token = strtok(properties, ",");
    printf("Comparing categories:\n");
    int categories_num = 0;
    token = strtok(NULL, ",");
    while (token != NULL) {
        printf("\t*) %s\n", token);
        token = strtok(NULL, ",");
        categories_num++;
    }

    char considered_stud[TABLE_SIZE][MAX_SPEC_SIZE];
    int stud_count = 0;

     // Read the rest of the lines and insert them into the hash table
    while (fgets(buffer, MAX_LEN, f1) != NULL) {
        StudentPC* new_pc = newPC();
        csv_read(new_pc, buffer);
        //ht_print_specs(new_pc->specs);
        //printf("\n");

        char* name = get_name(new_pc);
        if (ht_find(pc_table, name) != NULL) {
            strncpy(considered_stud[stud_count], name, MAX_SPEC_SIZE);
            stud_count++;
        }

        ht_insert(pc_table, name, new_pc);
    }
     // Print the contents of the hash table
    ht_print(pc_table);

    for (int i = 0; i < stud_count; i++) {
        printf("%s, ", considered_stud[i]);
    }
    printf("\n");

    //COEFFS


     // Close the file
    fclose(f1);
     return 0;
}