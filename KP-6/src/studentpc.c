#include "../headers/studentpc.h"

StudentPC* newPC()
{
    StudentPC* new_pc = malloc(sizeof(StudentPC));
    if (new_pc == NULL) {
        return NULL;
    }
    new_pc->name = calloc(SPEC_SIZE, sizeof(char));
    new_pc->cpus = calloc(SPEC_SIZE, sizeof(char));
    new_pc->gpu =  calloc(SPEC_SIZE, sizeof(char));
    new_pc->hdds = calloc(SPEC_SIZE, sizeof(char));
    new_pc->os =   calloc(SPEC_SIZE, sizeof(char));

    *new_pc->name = '\0';
    new_pc->cpu_num = 0;
    *new_pc->cpus = '\0';
    new_pc->ram = 0;
    *new_pc->gpu = '\0';
    new_pc->vram = 0;
    new_pc->hdd_num = 0;
    *new_pc->hdds = '\0';
    new_pc->device_num = 0;
    *new_pc->os = '\0';
    
    new_pc->specs = createTable(SPECS_HT_SIZE);
    HashTable* spec_list = new_pc->specs;
    ht_insert(spec_list, "name",       new_pc->name);
    ht_insert(spec_list, "cpu_n",    &(new_pc->cpu_num));
    ht_insert(spec_list, "cpus",       new_pc->cpus);
    ht_insert(spec_list, "ram",      &(new_pc->ram));
    ht_insert(spec_list, "gpu",        new_pc->gpu);
    ht_insert(spec_list, "vram",     &(new_pc->vram));
    ht_insert(spec_list, "hdd_n",    &(new_pc->hdd_num));
    ht_insert(spec_list, "hdds",       new_pc->hdds);
    ht_insert(spec_list, "device_n", &(new_pc->device_num));
    ht_insert(spec_list, "os",         new_pc->os);
    return new_pc;
}

char* get_name(StudentPC* pc)
{
    if (pc == NULL) {
        return "";
    }
    return pc->name;
}

void* get_spec(StudentPC* pc, const char* key)
{
    HashTable* specs = pc->specs;
    return ht_get_first(specs, key)->value;
}

int read_spec_from(const char* type, void* spec_p, char* input_p)
{
    int ret = 0;
    switch (type[1]) {
    case 's': {
        int len = strlen(input_p);
        if (len > 0 && input_p[len - 1] == '\n') {
            input_p[len - 1] = '\0';
        }
        strcpy(*(char**)spec_p, input_p);
        break;
    }
    case 'd': {
        char* endptr;
        int value = strtol(input_p, &endptr, 10);
        if (input_p == endptr || value <= 0) {
            ret = -1;
        } else {
            *(int*)spec_p = value;
        }
        break;
    }
    default: {
        perror("Invalid type");
        break;
    }
    }
    return ret;
}

int csv_read(StudentPC *pc, char* input_s)
{
    char* stud_token = strtok(input_s, ",");
    // Name
    if (stud_token == NULL) {
        fprintf(stderr, "Error: missing name\n");
        return -1;
    }
    read_spec_from("%s", (void*)&(pc->name), stud_token);
    // CPU number
    stud_token = strtok(NULL, ",");
    if (stud_token == NULL) {
        fprintf(stderr, "Error: missing CPU number\n");
        return -1;
    }
    if (read_spec_from("%d", (void*)&(pc->cpu_num), stud_token) == -1) {
        fprintf(stderr, "Error: invalid CPU number\n");
        return -1;
    }
    // CPUs
    stud_token = strtok(NULL, ",");
    if (stud_token == NULL) {
        fprintf(stderr, "Error: missing CPUs\n");
        return -1;
    }
    read_spec_from("%s", (void*)&(pc->cpus), stud_token);
    // RAM
    stud_token = strtok(NULL, ",");
    if (stud_token == NULL) {
        fprintf(stderr, "Error: missing RAM\n");
        return -1;
    }
    if (read_spec_from("%d", (void*)&(pc->ram), stud_token) == -1) {
        fprintf(stderr, "Error: invalid RAM\n");
        return -1;
    }
    // GPU
    stud_token = strtok(NULL, ",");
    if (stud_token == NULL) {
        fprintf(stderr, "Error: missing GPU\n");
        return -1;
    }
    read_spec_from("%s", (void*)&(pc->gpu), stud_token);
    // GPU memory
    stud_token = strtok(NULL, ",");
    if (stud_token == NULL) {
        fprintf(stderr, "Error: missing GPU memory\n");
        return -1;
    }
    if (read_spec_from("%d", (void*)&(pc->vram), stud_token) == -1) {
        fprintf(stderr, "Error: invalid GPU memory\n");
        return -1;
    }
    // HDD number
    stud_token = strtok(NULL, ",");
    if (stud_token == NULL) {
        fprintf(stderr, "Error: missing HDD number\n");
        return -1;
    }
    if (read_spec_from("%d", (void*)&(pc->hdd_num), stud_token) == -1) {
        fprintf(stderr, "Error: invalid HDD number\n");
        return -1;
    }
    // HDDs
    stud_token = strtok(NULL, ",");
    if (stud_token == NULL) {
        fprintf(stderr, "Error: missing HDDs\n");
        return -1;
    }
    read_spec_from("%s", (void*)&(pc->hdds), stud_token);
    // Devices number
    stud_token = strtok(NULL, ",");
    if (stud_token == NULL) {
        fprintf(stderr, "Error: missing devices number\n");
        return -1;
    }
    if (read_spec_from("%d", (void*)&(pc->device_num), stud_token) == -1) {
        fprintf(stderr, "Error: invalid devices number\n");
        return -1;
    }
    // Operating system
    stud_token = strtok(NULL, ",");
    if (stud_token == NULL) {
        fprintf(stderr, "Error: missing operating system\n");
        return -1;
    }
    read_spec_from("%s", (void*)&(pc->os), stud_token);

    return 0;
}

void specstostr(StudentPC* pc, char* str, size_t len)
{
    if (pc == NULL || str == NULL || len <= 0) return;
    snprintf(str, len, "CPUs: %d - %s; %dGB of RAM; %s %dGB; HDDs: %d - %s; devices: %d; OS: %s", 
    pc->cpu_num, pc->cpus, pc->ram, pc->gpu, pc->vram, pc->hdd_num, pc->hdds, pc->device_num, pc->os);
    return;
}

int bin_read(StudentPC *pc, FILE* fp)
{
    size_t result;
    result = fread(pc->name, sizeof(char), SPEC_SIZE, fp);
    fread(&(pc->cpu_num),    sizeof(int), 1, fp);
    fread(pc->cpus,          sizeof(char), SPEC_SIZE, fp);
    fread(&(pc->ram),        sizeof(int), 1, fp);
    fread(pc->gpu,           sizeof(char), SPEC_SIZE, fp);
    fread(&(pc->vram),       sizeof(int), 1, fp);
    fread(&(pc->hdd_num),    sizeof(int), 1, fp);
    fread(pc->hdds,          sizeof(char), SPEC_SIZE, fp);
    fread(&(pc->device_num), sizeof(int), 1, fp);
    fread(pc->os,            sizeof(char), SPEC_SIZE, fp);
    return result;
}

int bin_write(StudentPC *pc, FILE *fp)
{
    size_t result;
    result = fwrite(pc->name, sizeof(char), SPEC_SIZE, fp);
    fwrite(&(pc->cpu_num),    sizeof(int), 1, fp);
    fwrite(pc->cpus,          sizeof(char), SPEC_SIZE, fp);
    fwrite(&(pc->ram),        sizeof(int), 1, fp);
    fwrite(pc->gpu,           sizeof(char), SPEC_SIZE, fp);
    fwrite(&(pc->vram),       sizeof(int), 1, fp);
    fwrite(&(pc->hdd_num),    sizeof(int), 1, fp);
    fwrite(pc->hdds,          sizeof(char), SPEC_SIZE, fp);
    fwrite(&(pc->device_num), sizeof(int), 1, fp);
    fwrite(pc->os,            sizeof(char), SPEC_SIZE, fp);
    return result;
}

void pc_print_specs(StudentPC* pc)
{
    if (pc == NULL) return;
    HashTable* ht = pc->specs;
    if (ht_get_first(ht, "name") == NULL) return;
    char* name =    ht_get_first(ht, "name")->value;
    int* cpu_n =    ht_get_first(ht, "cpu_n")->value;
    char* cpus =    ht_get_first(ht, "cpus")->value;
    int* ram =      ht_get_first(ht, "ram")->value;
    char* gpu =     ht_get_first(ht, "gpu")->value;
    int* vram =     ht_get_first(ht, "vram")->value;
    int* hdd_n =    ht_get_first(ht, "hdd_n")->value;
    char* hdds =    ht_get_first(ht, "hdds")->value;
    int* device_n = ht_get_first(ht, "device_n")->value;
    char* os =      ht_get_first(ht, "os")->value;

    printf("|==========================================|\n");
    printf("|\t%s PC\t                   |\n", name);
    printf("|=========|================================|\n");
    printf("| CPU num | %15d\t\t   |\n", *cpu_n);
    printf("|=========|=================================-\n");
    printf("|  CPUs   | %27s\t   \n", cpus);
    printf("|=========|=================================-\n");
    printf("|   RAM   | %15d\t\t   |\n", *ram);
    printf("|=========|================================|\n");
    printf("|   GPU   |     %15s\t\t   |\n", gpu);
    printf("|=========|================================|\n");
    printf("|  VRAM   | %15d\t\t   |\n", *vram);
    printf("|=========|================================|\n");
    printf("| HDD num | %15d\t\t   |\n", *hdd_n);
    printf("|=========|================================|\n");
    printf("|  HDDs   |   %20s\t   |\n", hdds);
    printf("|=========|================================|\n");
    printf("| Devices | %15d\t\t   |\n", *device_n);
    printf("|=========|================================|\n");
    printf("|   OS    |     %15s\t\t   |\n", os);
    printf("|=========|================================|\n");
    return;
}

int pc_print_table(HashTable* ht)
{
    int ret = 0;
    int size = ht->size;
    HashNode** table = ht->table;
    for (int i = 0; i < size; i++) {
        HashNode* current_node = table[i];
        if (current_node == NULL) {
            continue;
        }
        ret++;
        printf("||============||==================---------\n");
        do {
            StudentPC* pc = get_value(current_node);
            char* name = get_name(pc);
            char spec_list[MAX_LEN];
            spec_list[MAX_LEN - 1] = '\0';
            specstostr(pc, spec_list, MAX_LEN);
            printf("|| %10s || %30s\n", name, spec_list);
            current_node = ht_get_next(current_node);
        } while (current_node != NULL);
    }
    if (ret) {
        printf("||============||==================---------\n");
    }
    return ret;
}

void pc_free(StudentPC *pc)
{
    if (pc == NULL) return;
    free(pc->name);
    free(pc->cpus);
    free(pc->gpu);
    free(pc->hdds);
    free(pc->os);
    ht_free(pc->specs);
    free(pc);
}