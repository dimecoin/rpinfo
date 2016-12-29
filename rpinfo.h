#pragma once

#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RPI_TEMP_FILE "/sys/class/thermal/thermal_zone0/temp"
#define RPI_CPUINFO_FILE "/proc/cpuinfo"

int print_temp (char temp_type);
int print_revision ();
