#define NOMINMAX 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include "../headers/globals.h"

#define max(a, b) ((((int) a) > ((int) b)) ? ((int) a) : ((int) b))

#define TABLE_SIZE 727

typedef struct {
    char* key;
    int rate;
} KeyRate;

KeyRate kr_allowed_cpus[] = {
    {"Intel Core i3", 3},
    {"Intel Core i5", 5},
    {"Intel Core i7", 7},
    {"Intel Core i9", 9},
    {"AMD Ryzen 3", 3},
    {"AMD Ryzen 5", 5},
    {"AMD Ryzen 7", 7},
    {"AMD Ryzen 9", 10}
};

KeyRate kr_allowed_os[] = {
    {"Windows 7", 4},
    {"Windows 8", 6},
    {"Windows 10", 8},
    {"Windows 11", 10},
    {"Ubuntu", 6},
    {"Fedora", 7},
    {"Debian", 8}
};

int get_fixed_rate(KeyRate* dict, const char* key)
{
    KeyRate cur_elem = dict[0];
    char* cur_key = cur_elem.key;
    for (int i = 1; strcmp(cur_key, key) != 0; i++) {
        cur_elem = dict[i];
        cur_key = cur_elem.key;
    }
    return cur_elem.rate;
}

int rate_best_cpu(char* list)
{
    char tmp[SPEC_SIZE];
    strcpy(tmp, list);
    char *token;
    token = strtok(tmp, "|");
    int max_rate = 0;
    while (token != NULL) {
        max_rate = max(max_rate, get_fixed_rate(kr_allowed_cpus, token));
        token = strtok(NULL, "|");
    }
    return max_rate;
}

int gpu_evaluate(char* gpu)
{
    int result = 0;
    char* cursor = gpu;
    while (cursor < gpu + strlen(gpu)) {
        if (!isdigit(*cursor)) {
            cursor++;
            continue;
        }
        result += *cursor - '0';
        cursor++;
    }
    return result;
}

int ltm_evaluate(char* gpu)
{
    int result = 0;
    char* cursor = gpu;
    while (cursor < gpu + strlen(gpu)) {
        if (!isdigit(*cursor)) {
            cursor++;
            continue;
        }
        result += *cursor - '0';
        cursor++;
    }
    return result;
}

int hdds_evaluate(char* hdds)
{
    int result = 0;
    char* cursor = hdds;
    while (cursor < hdds + strlen(hdds)) {
        if (!isdigit(*cursor)) {
            cursor++;
            continue;
        }
        result += *cursor - '0';
        cursor++;
    }
    return result;
}

int os_evaluate(char* os)
{
    return get_fixed_rate(kr_allowed_os, os);
}

StudentPC* cmp_pcs(HashTable* pc_table, const char* key) 
{
    float this_rates[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    float this_sum = 0;
    float next_rates[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    float next_sum = 0;
    float coeff_sum = CPU_N_COEFF + CPUS_COEFF + RAM_COEFF + GPU_COEFF + VRAM_COEFF \
        + HDD_N_COEFF + HDDS_COEFF + DEVICE_N_COEFF + OS_COEFF;
    HashNode* this_node = ht_get_first(pc_table, key);
    StudentPC* this_pc = this_node->value;

    while (this_node->next_node != NULL) {
        int this_cpu_n = *(int*)get_spec(this_pc, "cpu_n");
        char* this_cpus = get_spec(this_pc, "cpus");
        int this_ram = *(int*)get_spec(this_pc, "ram");
        char* this_gpu = get_spec(this_pc, "gpu");
        int this_vram = *(int*)get_spec(this_pc, "vram");
        int this_hdd_n = *(int*)get_spec(this_pc, "hdd_n");
        char* this_hdds = get_spec(this_pc, "hdds");
        int this_device_n = *(int*)get_spec(this_pc, "device_n");
        char* this_os = get_spec(this_pc, "os");

        HashNode* next_node = this_node->next_node;
        StudentPC* next_pc = next_node->value;
        int next_cpu_n = *(int*)get_spec(next_pc, "cpu_n");
        char* next_cpus = get_spec(next_pc, "cpus");
        int next_ram = *(int*)get_spec(next_pc, "ram");
        char* next_gpu = get_spec(next_pc, "gpu");
        int next_vram = *(int*)get_spec(next_pc, "vram");
        int next_hdd_n = *(int*)get_spec(next_pc, "hdd_n");
        char* next_hdds = get_spec(next_pc, "hdds");
        int next_device_n = *(int*)get_spec(next_pc, "device_n");
        char* next_os = get_spec(next_pc, "os");

        int max_cpu_n = max(this_cpu_n, next_cpu_n);
        this_rates[0] = (float)this_cpu_n / (float)max_cpu_n * CPU_N_COEFF;
        next_rates[0] = (float)next_cpu_n / (float)max_cpu_n * CPU_N_COEFF;
        this_sum += this_rates[0];
        next_sum += next_rates[0];

        int this_cpu_rate = rate_best_cpu(this_cpus);
        int next_cpu_rate = rate_best_cpu(next_cpus);
        int max_cpu_rate = max(this_cpu_rate, next_cpu_rate);
        this_rates[1] = (float)this_cpu_rate / (float)max_cpu_rate * CPUS_COEFF;
        next_rates[1] = (float)next_cpu_rate / (float)max_cpu_rate * CPUS_COEFF;
        this_sum += this_rates[1];
        next_sum += next_rates[1];

        int max_ram = max(this_ram, next_ram);
        this_rates[2] = (float)this_ram / (float)max_ram * RAM_COEFF;
        next_rates[2] = (float)next_ram / (float)max_ram * RAM_COEFF;
        this_sum += this_rates[2];
        next_sum += next_rates[2];

        int this_gpu_rate = gpu_evaluate(this_gpu);
        int next_gpu_rate = gpu_evaluate(next_gpu);
        int max_gpu_rate = max(this_gpu_rate, next_gpu_rate);
        this_rates[3] = (float)this_gpu_rate / (float)max_gpu_rate * GPU_COEFF;
        next_rates[3] = (float)next_gpu_rate / (float)max_gpu_rate * GPU_COEFF;
        this_sum += this_rates[3];
        next_sum += next_rates[3];

        int max_vram = max(this_vram, next_vram);
        this_rates[4] = (float)this_vram / (float)max_vram * VRAM_COEFF;
        next_rates[4] = (float)next_vram / (float)max_vram * VRAM_COEFF;
        this_sum += this_rates[4];
        next_sum += next_rates[4];

        int max_hdd_n = max(this_hdd_n, next_hdd_n);
        this_rates[5] = (float)this_hdd_n / (float)max_hdd_n * HDD_N_COEFF;
        next_rates[5] = (float)next_hdd_n / (float)max_hdd_n * HDD_N_COEFF;
        this_sum += this_rates[5];
        next_sum += next_rates[5];

        int this_hdds_rate = hdds_evaluate(this_hdds);
        int next_hdds_rate = hdds_evaluate(next_hdds);
        int max_hdds_rate = max(this_hdds_rate, next_hdds_rate);
        this_rates[6] = (float)this_hdds_rate / (float)max_hdds_rate * HDDS_COEFF;
        next_rates[6] = (float)next_hdds_rate / (float)max_hdds_rate * HDDS_COEFF;
        this_sum += this_rates[6];
        next_sum += next_rates[6];

        int max_device_n = max(this_device_n, next_device_n);
        this_rates[7] = (float)this_device_n / (float)max_device_n * DEVICE_N_COEFF;
        next_rates[7] = (float)next_device_n / (float)max_device_n * DEVICE_N_COEFF;
        this_sum += this_rates[7];
        next_sum += next_rates[7];

        int this_os_rate = os_evaluate(this_os);
        int next_os_rate = os_evaluate(next_os);
        int max_os_rate = max(this_os_rate, next_os_rate);
        this_rates[8] = (float)this_os_rate / (float)max_os_rate * OS_COEFF;
        next_rates[8] = (float)next_os_rate / (float)max_os_rate * OS_COEFF;
        this_sum += this_rates[8];
        next_sum += next_rates[8];
        ///
        this_sum /= coeff_sum;
        next_sum /= coeff_sum;
        if (this_sum < next_sum) {
            this_pc = next_pc;
        }
        this_node = next_node;

    }   
    return this_pc;
}

void add_considered(StudentPC * pc, char stud_list[TABLE_SIZE][SPEC_SIZE], int* stud_count, HashTable* pc_table)
{
    char* name = get_name(pc);
    bool already_considered = false;
    if (ht_get_first(pc_table, name) != NULL) {
        for (int i = 0; i < *stud_count; i++) {
            if (strcmp(stud_list[i], name) == 0) {
                already_considered = true;
                break;
            }
        }
        if (!already_considered) {
            strncpy(stud_list[*stud_count], name, SPEC_SIZE);
            *stud_count = *stud_count + 1;
        }
    }
    return;
}

void print_menu() {
    printf("    result - display the result\n");
    printf("    add [(Surname),(Number of CPUs),(CPUs {use '|' to split them}),(RAM size),(GPU),(Number of HDDs),(HDD sizes {use '|' to split them}),(number of peripherals),(OS)] - add a student\n");
    printf("    remove [surname] - remove a student\n");
    printf("    info [surname] - information about a student\n");
    printf("    table - display information about all students\n");
    printf("    q - quit the program\n");
}

int main(int argc, char *argv[])
{  
    if (argc != 2 || argv[1] == NULL) {
        printf("Usage: main.out <data_file>\n");
        exit(1);
    }
    char filename[MAX_LEN];
    strncpy(filename, argv[1], MAX_LEN);
    // Open the file for reading
    FILE* f1 = fopen(filename, "r");
    if (f1 == NULL) {
        perror("Error");
        exit(ENOENT);
    }
    bool binary = false; // Whether file is binary or not
    
    char* extension = strrchr(filename, '.');
    if (extension == NULL || strcmp(extension, ".txt") == 0) {
        printf("The file has the expected extension (.txt)\n");
    } 
    else if (extension != NULL && strcmp(extension, ".bin") == 0) {
        binary = true;
        printf("The file has the expected extension (.bin)\n");
    }
    else {
        printf("The file does not have the expected extension.\n");
        exit(2);
    }
    
    // Buffer to store a single line from the file
    char buffer[MAX_LEN];
    // Create a hash table to store the student PCs
    HashTable* pc_table = createTable(TABLE_SIZE);
    char considered_stud[TABLE_SIZE][SPEC_SIZE];
    int considered_count = 0;
    // Read the rest of the lines and insert them into the hash table
    if (binary) {
        while (true) {
            StudentPC* new_pc = newPC();
            if (bin_read(new_pc, f1) == 0) {
                break;
            }
            char* name = get_name(new_pc);
            add_considered(new_pc, considered_stud, &considered_count, pc_table);
            ht_insert(pc_table, name, new_pc);
            new_pc = newPC();
        }
    }
    else {
        while (fgets(buffer, MAX_LEN, f1) != NULL) {
            StudentPC* new_pc = newPC();
            csv_read(new_pc, buffer);
            char* name = get_name(new_pc);
            add_considered(new_pc, considered_stud, &considered_count, pc_table);
            ht_insert(pc_table, name, new_pc);
            //ht_print_specs(new_pc);
        }
    }
    printf("Type 'help' to see the list of actions\n");
    char action[MAX_LEN];
    do {
        fscanf(stdin, "%s", action);
        char* command = strtok(action, " ");
        if (strcmp(command, "help") == 0) {
            print_menu();
        }
        else if (strcmp(command, "result") == 0) {
            for (int i = 0; i < considered_count; i++) {
                StudentPC* best_pc = cmp_pcs(pc_table, considered_stud[i]);
                char spec_list[MAX_LEN];
                specstostr(best_pc, spec_list, MAX_LEN);
                printf("Best PC in %s collection is:\n%s\n", get_name(best_pc), spec_list);
            }
        }
        else if (strcmp(action, "add") == 0) {
            FILE* f_edit = open(filename, "a");
            if (f_edit == NULL) {
                perror("Error");
                exit(ENOENT);
            }
            StudentPC* new_pc = newPC();
            csv_read(new_pc, action);
            char* name = get_name(new_pc);
            add_considered(new_pc, considered_stud, &considered_count, pc_table);
            ht_insert(pc_table, name, new_pc);
        }
        else if (strcmp(command, "remove") == 0) {
            
        }
        else if (strcmp(command, "info") == 0) {

        }
        else if (strcmp(command, "table") == 0) {
            // Print the contents of the hash table
            pc_print_table(pc_table);
        }
        else if (strcmp(command, "q") == 0) {
            continue;
        }
        else {
            printf("Unknown action. Try again.\n");
        }
    } while (strcmp(action, "q") != 0);
    
    

    
    //printf("\n");
    for (int i = 0; i < pc_table->size; i++) {
        if (pc_table->table[i] == NULL) {
            continue;
        }
        HashNode* node = pc_table->table[i];
        while (node != NULL) {
            StudentPC* pc = (StudentPC*)node->value;
            HashNode* tmp = node;
            node = node->next_node;
            pc_free(pc);
            free(tmp);
            pc_table->table[i] = NULL;
        }
    }
    //free(considered_stud);
    ht_free(pc_table);
    // Close the file
    fclose(f1);
    return 0;
}