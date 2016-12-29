#pragma once


/*#include <assert.h>
#include <complex.h>
#include <errno.h>
#include <fenv.h>
#include <float.h>
#include <inttypes.h>
#include <iso646.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <stdalign.h>
#include <stdarg.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
*/
#include <ctype.h>
#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*#include <stdnoreturn.h>
#include <tgmath.h>
//#include <threads.h>
#include <time.h>
#include <uchar.h>
#include <wchar.h>
#include <wctype.h>
*/

#define RPI_TEMP_FILE "/sys/class/thermal/thermal_zone0/temp"
#define RPI_CPUINFO_FILE "/proc/cpuinfo"


int print_temp(char temp_type);
int print_revision();


