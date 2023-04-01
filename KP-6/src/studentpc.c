#include "../headers/studentpc.h"

StudentPC* newPC()
{
    StudentPC* new_pc = (StudentPC*)malloc(sizeof(StudentPC));
    new_pc->name = NULL;
    new_pc->cpu_num = 0;
    new_pc->cpus = NULL;
    new_pc->ram = 0;
    new_pc->gpu = NULL;
    new_pc->gmem = 0;
    new_pc->hdd_num = 0;
    new_pc->hdds = NULL;
    new_pc->device_num = 0;
    new_pc->os = NULL;
    new_pc->coolness = 0;
    return new_pc;
}