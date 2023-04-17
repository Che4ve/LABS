#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <errno.h>

#define MAX_LEN 200 // Maximum length of a line in the file
#define SPEC_SIZE 55 // Maximum size of a (char*) specification

#define MAX_STUDENTS 50

// from 0.0 to 1.0
#define CPU_N_COEFF 0.8
#define CPUS_COEFF 0.9
#define RAM_COEFF 0.6
#define GPU_COEFF 0.7
#define VRAM_COEFF 0.5
#define HDD_N_COEFF 0.2
#define HDDS_COEFF 0.4
#define DEVICE_N_COEFF 0.1
#define OS_COEFF 0.6

//
#define NUM_ALWD_NAMES 15
#define NUM_ALWD_CPUS 8
#define NUM_ALWD_GPUS 13
#define NUM_ALWD_OS 7

//
#define MAX_CPUS 4
#define MAX_RAM 64
#define MAX_VRAM 64
#define MAX_HDDS 5
#define MAX_LTM 10
#define MAX_DEVICES 15

//
extern char* Properties;
extern char* allowed_cpus[];
extern char* allowed_os[];
extern char* allowed_gpus[];
extern char* allowed_names[];

#include "../headers/dict.h"
#include "../headers/studentpc.h"

#endif