#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include "../headers/studentpc.h"
#include "../headers/dict.h"

#define MAX_SIZE 250

int main(int argc, char **argv)
{
    char buffer[MAX_SIZE];
    char properties[MAX_SIZE];

    //StudentPC** pc_dict = (StudentPC**)malloc(sizeof(StudentPC*) * TABLE_SIZE);

    FILE* f1 = fopen("info.txt", "r");

    //fread(&buffer, sizeof(buffer), 1, f1);
    //printf("%s\n", buffer);

    fgets(properties, 255, f1);

    char* token = strtok(properties, ",");

    printf("Comparing categories:\n");
    int categories_num = 0;
    token = strtok(NULL, ","); // Surname
    while (token != NULL) {
        printf("\t*) %s\n", token);
        token = strtok(NULL, ",");
        categories_num++;
    }
    //printf("%d\n", categories_num);
    while (fgets(buffer, 255, f1) != NULL) {
        StudentPC* new_pc = newPC();
        char* stud_token = strtok(buffer, ",");
        for (int i = 0; i < categories_num + 1; i++) {
            if (stud_token == NULL) {
                break;
            }
            switch (i) {
            case 0: // Name
                new_pc->name = stud_token;
                printf("--%s--\n", stud_token);
                break;
            case 1: // CPU number
            {
                long value;
                stud_token = strtok(NULL, ",");
                value = strtol(stud_token, NULL, 10);
                new_pc->cpu_num = value;
                printf("CPU number: %s\n", stud_token);
                break;
            }
            case 2: // CPUs
                stud_token = strtok(NULL, ",");
                new_pc->cpus = stud_token;
                printf("CPUs: %s\n", stud_token);
                break;
            case 3: // RAM
            {
                long value;
                stud_token = strtok(NULL, ",");
                value = strtol(stud_token, NULL, 10);
                new_pc->ram = value;
                printf("RAM: %ld\n", value);
                break;
            }
            case 4: // GPU
                stud_token = strtok(NULL, ",");
                new_pc->gpu = stud_token;
                printf("GPU: %s\n", stud_token);
                break;
            case 5: // GPU memory
            {
                long value;
                stud_token = strtok(NULL, ",");
                value = strtol(stud_token, NULL, 10);
                new_pc->gmem = value;
                break;
            }
            case 6: // HDD number
            {
                long value;
                stud_token = strtok(NULL, ",");
                value = strtol(stud_token, NULL, 10);
                new_pc->hdd_num = value;
                break;
            }
            case 7: // HDDs
                
                break;
            case 8: // Devices number

                break;
            case 9: // Operating system

                break;
            }
        }
        //printf("%s\n", buffer);
    }



    fclose(f1);
    return 0;
}