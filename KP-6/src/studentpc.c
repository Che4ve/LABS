#include "../headers/studentpc.h"

StudentPC* newPC()
{
    StudentPC* new_pc = malloc(sizeof(StudentPC));

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
    return new_pc;
}

void pc_free(StudentPC *pc)
{
    ht_free(pc->specs);
    free(pc);
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

void read_spec_from(const char* type, void* spec_p, char* input_p)
{
    switch (type[1]) {
        case 's': {
            int len = strlen(input_p);
            if (len > 0 && input_p[len - 1] == '\n') {
                input_p[len - 1] = '\0';
            }
            strcpy((char*)spec_p, input_p);
            break;
        }
        case 'd': {
            int value = strtol(input_p, NULL, 10);
            *(int*)spec_p = value;
            break;
        }
        default: {
            perror("Invalid type");
            break;
        }
    }
}

void csv_read(StudentPC* pc, char* input_s)
{
    char* input_copy = strdup(input_s);
    char* stud_token = strtok(input_copy, ",");
    // Name
    read_spec_from("%s", (void*)&(pc->name), stud_token);
    // CPU number
    stud_token = strtok(NULL, ",");
    read_spec_from("%d", (void*)&(pc->cpu_num), stud_token);
    // CPUs
    stud_token = strtok(NULL, ",");
    read_spec_from("%s", (void*)&(pc->cpus), stud_token);
    // RAM
    stud_token = strtok(NULL, ",");
    read_spec_from("%d", (void*)&(pc->ram), stud_token);
    // GPU
    stud_token = strtok(NULL, ",");
    read_spec_from("%s", (void*)&(pc->gpu), stud_token);
    // GPU memory
    stud_token = strtok(NULL, ",");
    read_spec_from("%d", (void*)&(pc->vram), stud_token);
    // HDD number
    stud_token = strtok(NULL, ",");
    read_spec_from("%d", (void*)&(pc->hdd_num), stud_token);
    // HDDs
    stud_token = strtok(NULL, ",");
    read_spec_from("%s", (void*)&(pc->hdds), stud_token);
    // Devices number
    stud_token = strtok(NULL, ",");
    read_spec_from("%d", (void*)&(pc->device_num), stud_token);
    // Operating system
    stud_token = strtok(NULL, ",");
    read_spec_from("%s", (void*)&(pc->os), stud_token);
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

void* specstostr(StudentPC* pc, char* str)
{
    sprintf(str, "CPUs: %d - %s; %dGB of RAM; %s %dGB; HDDs: %d - %s; devices: %d; OS: %s", \
    pc->cpu_num, pc->cpus, pc->ram, pc->gpu, pc->vram, pc->hdd_num, pc->hdds, pc->device_num, pc->os);
}