#include "../headers/studentpc.h"

StudentPC* newPC()
{
    StudentPC* new_pc = malloc(sizeof(StudentPC));
    new_pc->name = malloc(MAX_SPEC_SIZE * sizeof(char));
    new_pc->cpus = malloc(MAX_SPEC_SIZE * sizeof(char));
    new_pc->gpu = malloc(MAX_SPEC_SIZE * sizeof(char));
    new_pc->hdds = malloc(MAX_SPEC_SIZE * sizeof(char));
    new_pc->os = malloc(MAX_SPEC_SIZE * sizeof(char));

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
    new_pc->coolness = 0;

    new_pc->specs = createTable(SPECS_HT_SIZE);
    HashTable* spec_list = new_pc->specs;
    ht_insert(spec_list, "name", new_pc->name);
    ht_insert(spec_list, "cpu_n", &(new_pc->cpu_num));
    ht_insert(spec_list, "cpus", new_pc->cpus);
    ht_insert(spec_list, "ram", &(new_pc->ram));
    ht_insert(spec_list, "gpu", new_pc->gpu);
    ht_insert(spec_list, "vram", &(new_pc->vram));
    ht_insert(spec_list, "hdd_n", &(new_pc->hdd_num));
    ht_insert(spec_list, "hdds", new_pc->hdds);
    ht_insert(spec_list, "device_n", &(new_pc->device_num));
    ht_insert(spec_list, "os", new_pc->os);
    ht_insert(spec_list, "coolness", &(new_pc->coolness));
    return new_pc;
}

char* get_name(StudentPC* pc)
{
    if (pc == NULL) {
        return "";
    }
    return pc->name;
}

void read_spec_from(const char* type, void* spec_p, char* input_p)
{
    if (strcmp(type, "%s") == 0) {
        int len = strlen(input_p);
        if (len > 0 && input_p[len - 1] == '\n') {
            input_p[len - 1] = '\0';
        }
        strcpy(*(char**)spec_p, input_p);
    }
    else if (strcmp(type, "%d") == 0) {
        int value = strtol(input_p, NULL, 10);
        *(int*)spec_p = value;
    }
    else {
        perror("Invalid type");
    }
}

void csv_read(StudentPC* pc, char* input_s)
{
    char* stud_token = strtok(input_s, ",");
    // Name
    read_spec_from("%s", (void*)&(pc->name), stud_token);
    //read_char_spec(stud_token, &(pc->name));
    //printf("--%s has--\n", pc->name);
    // CPU number
    stud_token = strtok(NULL, ",");
    read_spec_from("%d", (void*)&(pc->cpu_num), stud_token);
    //read_int_spec(stud_token, &(pc->cpu_num));
    //printf("CPU number: %d units\n", pc->cpu_num);
    // CPUs
    stud_token = strtok(NULL, ",");
    read_spec_from("%s", (void*)&(pc->cpus), stud_token);
    //read_char_spec(stud_token, &(pc->cpus));
    //printf("CPUs: %s\n", pc->cpus);
    // RAM
    stud_token = strtok(NULL, ",");
    read_spec_from("%d", (void*)&(pc->ram), stud_token);
    //printf("RAM: %d GB\n", pc->ram);
    // GPU
    stud_token = strtok(NULL, ",");
    read_spec_from("%s", (void*)&(pc->gpu), stud_token);
    //printf("GPU: %s\n", pc->gpu);
    // GPU memory
    stud_token = strtok(NULL, ",");
    read_spec_from("%d", (void*)&(pc->vram), stud_token);
    //printf("GPU memory: %d GB\n", pc->vram);
    // HDD number
    stud_token = strtok(NULL, ",");
    read_spec_from("%d", (void*)&(pc->hdd_num), stud_token);
    //printf("HDD number: %d units\n", pc->hdd_num);
    // HDDs
    stud_token = strtok(NULL, ",");
    read_spec_from("%s", (void*)&(pc->hdds), stud_token);
    //printf("HDD: %s\n", pc->hdds);
    // Devices number
    stud_token = strtok(NULL, ",");
    read_spec_from("%d", (void*)&(pc->device_num), stud_token);
    //printf("Devices: %d units\n", pc->device_num);
    // Operating system
    stud_token = strtok(NULL, ",");
    read_spec_from("%s", (void*)&(pc->os), stud_token);
    //printf("Operating system: %s\n", pc->os);
}

void* specstostr(StudentPC* pc, char* str)
{
    sprintf(str, "CPUs: %d - %s; %d GB of RAM; %s; HDDs: %d - %s; devices: %d; OS: %s", \
    pc->cpu_num, pc->cpus, pc->ram, pc->gpu, pc->hdd_num, pc->hdds, pc->device_num, pc->os);
}