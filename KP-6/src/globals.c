#include "../headers/globals.h"

char* Properties = "Surname,ProcessorsNumber,CPUs,Memory,NvidiaGPU,GraphicalMemory,HDDsNumber,HDDs,DevicesNumber,OS";

char* allowed_cpus[] = {
    "Intel Core i3",
    "Intel Core i5",
    "Intel Core i7",
    "Intel Core i9",
    "AMD Ryzen 3",
    "AMD Ryzen 5",
    "AMD Ryzen 7",
    "AMD Ryzen 9"
};

char* allowed_os[] = {
    "Windows 7",
    "Windows 8",
    "Windows 10",
    "Windows 11",
    "Ubuntu",
    "Fedora",
    "Debian"
};

char* allowed_gpus[] = {
    "RTX 4090",
    "RTX 4080",
    "RTX 3090",
    "RTX 3080",
    "RTX 3070",
    "RTX 3060",
    "RTX 2080",
    "RTX 2070",
    "RTX 2060",
    "RTX 1080",
    "RTX 1070",
    "RTX 1060",
    "RTX 1050",
};

char* allowed_names[] = {
    "Smith",
    "Jones",
    "Brown",
    "Garcia",
    "Miller",
    "Simpson",
    "Rodriguez",
    "Williams",
    "Hernandez",
    "Lopez",
    "Gonzalez",
    "Wayne",
    "Taylor",
    "Chesnokov",
    "Wilson"
};
