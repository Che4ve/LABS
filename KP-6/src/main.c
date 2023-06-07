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
    const char* key;
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
    {"AMD Ryzen 9", 10},
    {NULL, -1}
};

KeyRate kr_allowed_os[] = {
    {"Windows 7", 4},
    {"Windows 8", 6},
    {"Windows 10", 8},
    {"Windows 11", 10},
    {"Ubuntu", 6},
    {"Fedora", 7},
    {"Debian", 8},
    {NULL, -1}
};

int get_fixed_rate(KeyRate* dict, const char* key)
{
    KeyRate cur_elem = dict[0];
    const char* cur_key = cur_elem.key;
    for (int i = 1; strcmp(cur_key, key) != 0; i++) {
        cur_elem = dict[i];
        cur_key = cur_elem.key;
        if (cur_key == NULL) {
            return cur_elem.rate; // return -1
        }
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
    if (this_node == NULL) return NULL;
    StudentPC* this_pc = this_node->value;

    while (this_node->next_node != NULL) {
        int this_cpu_n =    *(int*)get_spec(this_pc, "cpu_n");
        char* this_cpus =          get_spec(this_pc, "cpus");
        int this_ram =      *(int*)get_spec(this_pc, "ram");
        char* this_gpu =           get_spec(this_pc, "gpu");
        int this_vram =     *(int*)get_spec(this_pc, "vram");
        int this_hdd_n =    *(int*)get_spec(this_pc, "hdd_n");
        char* this_hdds =          get_spec(this_pc, "hdds");
        int this_device_n = *(int*)get_spec(this_pc, "device_n");
        char* this_os =            get_spec(this_pc, "os");

        HashNode* next_node = this_node->next_node;
        StudentPC* next_pc = next_node->value;
        int next_cpu_n =    *(int*)get_spec(next_pc, "cpu_n");
        char* next_cpus =          get_spec(next_pc, "cpus");
        int next_ram =      *(int*)get_spec(next_pc, "ram");
        char* next_gpu =           get_spec(next_pc, "gpu");
        int next_vram =     *(int*)get_spec(next_pc, "vram");
        int next_hdd_n =    *(int*)get_spec(next_pc, "hdd_n");
        char* next_hdds =          get_spec(next_pc, "hdds");
        int next_device_n = *(int*)get_spec(next_pc, "device_n");
        char* next_os =            get_spec(next_pc, "os");

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

void add_considered(char* name, char stud_list[TABLE_SIZE][SPEC_SIZE], int* stud_count, HashTable* pc_table)
{
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

StudentPC* fadd_student(const char* filename, char* input_s, HashTable* pc_table)
{
    FILE* f_edit = fopen(filename, "a+");
    if (f_edit == NULL) {
        perror("Error");
        exit(ENOENT);
    }
    
    // Seek to the end of the file
    fseek(f_edit, 0, SEEK_END);
    // Move back one character
    fseek(f_edit, -1, SEEK_CUR);
    // Read the last character
    char last_c = fgetc(f_edit);
    if (last_c == '\n' || ftell(f_edit) == 0) {
        rewind(f_edit);
        fprintf(f_edit, "%s", input_s);
    }
    else {
        rewind(f_edit);
        fprintf(f_edit, "\n%s", input_s);
    }
    StudentPC* new_pc = newPC();
    if (csv_read(new_pc, input_s) != 0) {
        return NULL;
    }
    char* name = get_name(new_pc);
    
    fclose(f_edit);
    printf("Done. It will be a good addition to %s collection.\n", name);
    return new_pc;
}

StudentPC* fadd_student_bin(const char* filename, char* input_s, HashTable* pc_table)
{
    FILE* f_edit = fopen(filename, "ab");
    if (f_edit == NULL) {
        perror("Error");
        exit(ENOENT);
    }
    StudentPC* new_pc = newPC();
    if (csv_read(new_pc, input_s) != 0) {
        return NULL;
    }
    char* name = get_name(new_pc);
    bin_write(new_pc, f_edit);
    fclose(f_edit);
    printf("Done. It will be a good addition to %s collection.\n", name);
    return new_pc;
}

int fremove_student(const char* filename, const char* name)
{
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error");
        return -1;
    }
    // Create a temporary file to store the updated contents
    char tmp_filename[L_tmpnam];
    tmpnam(tmp_filename);
    FILE* tmp_fp = fopen(tmp_filename, "w");
    if (tmp_fp == NULL) {
        perror("Error creating temporary file.");
        fclose(fp);
        return -2;
    }

    char line[MAX_LEN];
    int found = 0; // flag to indicate if the student PC was found and removed
    while (fgets(line, sizeof(line), fp) != NULL) {
        // Check if the line starts with the given name
        if (strncmp(line, name, strlen(name)) == 0) {
            found = 1; // student PC was found
            continue; // skip this line (i.e., do not write it to the temporary file)
        }
        fputs(line, tmp_fp); // write the line to the temporary file
    }
    fclose(fp);
    fclose(tmp_fp);
    // Replace the original file with the temporary file
    int remove_ret = remove(filename);
    int rename_ret = rename(tmp_filename, filename);
    if (remove_ret != 0) {
        perror("Error removing file.");
        return -3;
    }
    if (rename_ret != 0) {
        perror("Error renaming file.");
        return -4;
    }
    if (!found) {
        printf("Student '%s' was not found in file '%s'.\n", name, filename);
        return -5;
    }
    else {
        printf("Done. '%s' was deleted from the table.\n", name);
        return 0; // success
    }
}

int fremove_student_bin(const char* filename, const char* name)
{
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Error");
        return -1;
    }
    // Create a temporary file to store the updated contents
    char tmp_filename[L_tmpnam];
    tmpnam(tmp_filename);
    FILE* tmp_fp = fopen(tmp_filename, "wb");
    if (tmp_fp == NULL) {
        perror("Error creating temporary file.\n");
        fclose(fp);
        return -2;
    }

    int found = 0; // flag to indicate if the student PC was found and removed
    StudentPC* pc = newPC();
    while (bin_read(pc, fp) != 0) {
        char* current_name = pc->name;
        // Check if the line starts with the given name
        if (strncmp(current_name, name, strlen(name)) == 0) {
            found = 1; // student PC was found
            continue; // skip this line (i.e., do not write it to the temporary file)
        }
        bin_write(pc, tmp_fp);
    }
    pc_free(pc);
    fclose(fp);
    fclose(tmp_fp);
    // Replace the original file with the temporary file
    int remove_ret = remove(filename);
    int rename_ret = rename(tmp_filename, filename);
    if (remove_ret != 0) {
        perror("Error removing file.");
        return -3;
    }
    if (rename_ret != 0) {
        perror("Error renaming file.");
        return -4;
    }
    if (!found) {
        printf("Student '%s' was not found in file '%s'.\n", name, filename);
        return -5;
    }
    else {
        printf("Done. '%s' was deleted from the table.\n", name);
        return 0; // success
    }
}

void print_menu() {
    printf("    result - display the result.\n");
    printf("    add [(Surname),(Number of CPUs),(CPUs {use '|' to split them}),(RAM size),(GPU),(Number of HDDs),(HDD sizes {use '|' to split them}),(number of peripherals),(OS)] - add a student.\n");
    printf("    remove [surname] - remove a student.\n");
    printf("    info [surname] - information about a student.\n");
    printf("    table - display information about all students.\n");
    printf("    q - quit the program.\n");
}

int main(int argc, char *argv[])
{  
    if (argc != 2 || argv[1] == NULL) {
        printf("Usage: main.out <data_file>\n");
        exit(1);
    }
    char filename[MAX_LEN];
    strncpy(filename, argv[1], MAX_LEN - 1);
    filename[MAX_LEN - 1] = '\0';
    FILE* f1;
    bool binary = false; // Whether file is binary or not
    
    char* extension = strrchr(filename, '.');
    if (extension == NULL || strcmp(extension, ".txt") == 0) {
        printf("The file has the expected extension (.txt).\n");
    } 
    else if (extension != NULL && strcmp(extension, ".bin") == 0) {
        binary = true;
        printf("The file has the expected extension (.bin).\n");
    }
    else {
        fprintf(stderr, "The file does not have the expected extension.\n");
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
        // Open the binary file for reading
        f1 = fopen(filename, "rb");
        if (f1 == NULL) {
            perror("Error");
            exit(ENOENT);
        }
        while (true) {
            StudentPC* new_pc = newPC();
            if (bin_read(new_pc, f1) == 0) {
                break;
            }
            char* name = get_name(new_pc);
            add_considered(name, considered_stud, &considered_count, pc_table);
            ht_insert(pc_table, name, new_pc);
        }
    }
    else {
        // Open the text file for reading
        f1 = fopen(filename, "r");
        if (f1 == NULL) {
            perror("Error");
            exit(ENOENT);
        }
        while (fgets(buffer, MAX_LEN, f1) != NULL) {
            StudentPC* new_pc = newPC();
            csv_read(new_pc, buffer);
            char* name = get_name(new_pc);
            add_considered(name, considered_stud, &considered_count, pc_table);
            ht_insert(pc_table, name, new_pc);
        }
    }
    printf("Type 'help' to see the list of actions.\n");
    char action[MAX_LEN];
    do {
        fgets(action, sizeof(action), stdin);
        int len = strlen(action);
        if (action[len - 1] == '\n') {
            action[len - 1] = '\0';
        }
        char* command = strtok(action, " ");
        if (command == NULL) {
            fprintf(stderr, "Incorrect input: missing command.\n");
            continue;
        }
        int com_len = strlen(command);
        char* arg = action + com_len + 1;
        
        if      (strcmp(command, "help")   == 0) {
            print_menu();
        }
        else if (strcmp(command, "result") == 0) {
            int found = 0;
            for (int i = 0; i < considered_count; i++) {
                StudentPC* best_pc = cmp_pcs(pc_table, considered_stud[i]);
                if (best_pc == NULL) {
                    continue;
                }
                char spec_list[MAX_LEN];
                specstostr(best_pc, spec_list, MAX_LEN);
                printf("Best PC in %s collection is:\n%s.\n\n", get_name(best_pc), spec_list);
                found = 1;
            }
            if (!found) {
                printf("There are no students with multiple PCs.\n");
            }
        }
        else if (strcmp(command, "add")    == 0) {
            if (arg[0] == '\0') {
                fprintf(stderr, "Incorrect input: missing name.\n");
                continue;
            }
            StudentPC* new_pc;
            if (binary) {
                new_pc = fadd_student_bin(filename, arg, pc_table);
            }
            else {
                new_pc = fadd_student(filename, arg, pc_table);
            }
            if (new_pc == NULL) {
                fprintf(stderr, "Failed to add student '%s'.\n", arg);
                continue;
            }
            ht_insert(pc_table, get_name(new_pc), new_pc);
            add_considered(get_name(new_pc), considered_stud, &considered_count, pc_table);
        }
        else if (strcmp(command, "remove") == 0) {
            if (arg[0] == '\0') {
                fprintf(stderr, "Incorrect input: missing name.\n");
                continue;
            }
            if (f1 != NULL) fclose(f1);
            if (binary) {
                fremove_student_bin(filename, arg);
                f1 = fopen(filename, "rb");
            }
            else {
                fremove_student(filename, arg);
                f1 = fopen(filename, "r");
            }
            if (f1 == NULL) {
                perror("Error");
                exit(ENOENT);
            }
            HashNode* node = ht_get_first(pc_table, arg);
            while (node != NULL) {
                // Freeing PC
                pc_free(node->value);
                node->value = NULL;
                // Freeing HashNode
                HashNode* next_node = ht_get_next(node);
                free(node);
                pc_table->table[hash(pc_table, arg)] = NULL;
                node = next_node;
            }
        }
        else if (strcmp(command, "info")   == 0) {
            if (arg[0] == '\0') {
                fprintf(stderr, "Incorrect input: missing name.\n");
                continue;
            }
            HashNode* pc_node = ht_get_first(pc_table, arg);
            if (pc_node == NULL) {
                printf("There is no student named '%s'.\n", arg);
                continue;
            }
            for (int i = 1; pc_node != NULL; i++) {
                StudentPC* pc = pc_node->value;
                printf("PC number #%d:\n", i);
                pc_print_specs(pc);
                pc_node = ht_get_next(pc_node);
            }
        }
        else if (strcmp(command, "table")  == 0) {
            // Print the contents of the hash table
            if (pc_print_table(pc_table) == 0) {
                printf("No students found.\n");
            }
        }
        else if (strcmp(command, "q")      == 0) {
            continue;
        }
        else {
            printf("Unknown action. Try again.\n");
        }
    } while (strcmp(action, "q") != 0);

    for (int i = 0; i < pc_table->size; i++) {
        if (pc_table->table[i] == NULL) {
            continue;
        }
        HashNode* node = pc_table->table[i];
        while (node != NULL) {
            // Freeing PC
            pc_free(node->value);
            node->value = NULL;
            // Freeing HashNode
            HashNode* next_node = ht_get_next(node);
            free(node);
            pc_table->table[i] = NULL;
            node = next_node;
        }
    }
    ht_free(pc_table);
    // Close the file
    fclose(f1);
    printf("Quitting...\n");
    return 0;
}