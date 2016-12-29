#include "rpinfo.h"
#include "rpimodels.h"

int main(int argc, char * argv[]) {

 	// s = system (raw)
 	// c = celsisu
 	// f = fahrenheit
	// k =  kelvin
	// r = Rankine 

	const int opt_size = 3;
	const char *short_opt = "ht:rv";
	struct option long_opt[] = {
		{"help", no_argument, NULL, 'h'},
		{"temperature", optional_argument, NULL, 't'},
		{"revision", no_argument, NULL, 'r'},
		{"version", no_argument, NULL, 'v'},
		{NULL, 0, NULL, 0 }
	};

	const char *opt_help[] = {
		"prints this help menu",
		"gets the system tempatures, must give unit parameter (eg. `-t c`):\n\t\t[c]elsius (centigrade)\n\t\t[f]ahrenheit\n\t\t[k]elvin\n\t\t[r]ankine\n\t\t[s]system (raw int value recorded by linux)",
		"gets revision of this pi",
	};

	char temp_type = 'c';

	// default display if no parameters are entered
	if (argc == 1) {
		print_revision();
		print_temp(temp_type);
	return (EXIT_SUCCESS);
	}

	int c;

	while((c = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1) {

		switch (c) {
			case -1: // no more args
			case 0: // long options toggled
			break;

			case 'h':

				printf("Usage: %s [-h] [-r] [-t unit] [-v] \n\n", argv[0]);

				// *name, has_arg, *flag, val
				for (int i=0; i<opt_size; i++ ) {
					printf ("  -%c\n  --%s\n\t %s\n", long_opt[i].val, long_opt[i].name, opt_help[i]);
				}

				printf ("\n");

				printf ("Examples: \n");
				printf ("\t%s -r # prints pi revision info\n", argv[0]);
				printf ("\t%s --revision # same as above, long style paraemter\n", argv[0]);
				printf ("\t%s -t f # get temperature in fahrenheit\n", argv[0]);
				printf ("\t%s --temperature c # get temperature in celsius\n", argv[0]);
			
				printf("\n");

			return(EXIT_SUCCESS);

			case 'r':
				print_revision();
			break;

			case 't':
				if (optarg != NULL) {
					//printf("optarg: %s\n", optarg);
					temp_type = *optarg;
				} 
				print_temp(temp_type);
			break;

			case ':':
			case '?':
				fprintf(stderr, "Try `%s --help' for more information.\n", argv[0]);
			return(-2);

			default:
				fprintf(stderr, "%s: invalid option -- %c\n", argv[0], c);
				fprintf(stderr, "Try `%s --help' for more information.\n", argv[0]);
			return (-2);
		}
	}

return (EXIT_SUCCESS);
}



int print_temp(char temp_type) {

	// /sys/class/thermal/thermal_zone0/temp
	#ifdef DEBUG_FLAG
	//printf ("Temperature: %c from %s\n", temp_type, RPI_TEMP_FILE);
	#endif

	char error[1024];

	FILE* fp = fopen(RPI_TEMP_FILE, "r");
	if(!fp) {
		snprintf(error, sizeof(error), "Error reading temperature. Error opening file [ %s ]", RPI_TEMP_FILE);
		perror(error);
		return (EXIT_FAILURE);
	}
 
	char buf[10];
	while (fgets(buf, sizeof buf, fp) != NULL) {
		#ifdef DEBUG_FLAG
		//printf ("In: %s\n", buf);
		#endif
	}
	
	if (ferror(fp)) {
		snprintf(error, sizeof(error), "Error reading temperature. Error reading file [ %s ]", RPI_TEMP_FILE);
		perror(error);
		return (EXIT_FAILURE);
	}

	// Parse string

	// Remove ending LF
	buf[ strlen(buf) - 1 ] = '\0';

	// Reset error status
	errno =0;
	char *temp;
	long raw_temp = strtol(buf, &temp, 0);

	// check that strtol parsed correctly.
	// See: http://stackoverflow.com/a/14176593
	if (temp == buf || *temp != '\0' || ((raw_temp == LONG_MIN || raw_temp == LONG_MAX) && errno == ERANGE)) {
		fprintf(stderr, "Error reading temperature: Could not convert '%s' to long and leftover string is: '%s'\n", buf, temp);
		return (EXIT_FAILURE);
	}


	double formatted_temp = -1;
	char formatted_type[10];

	switch (temp_type) {

		case 'c': 
			strcpy(formatted_type, "°C");
			formatted_temp = raw_temp / 1000.0;
		break;
		case 'f': 
			// Celsius to Fahrenheit:   (°C × 9/5) + 32 = °F
			strcpy(formatted_type, "°F");
			formatted_temp = ( ( raw_temp / 1000.0 ) * 9.0/5.0) + 32;
		break;
		case 'k': 
			strcpy(formatted_type, "°K");
			formatted_temp =  ( raw_temp / 1000.0 ) + 273.15;
		break;
		case 'r': 
			// T(°R) = (T(°C) + 273.15) × 9/5
			strcpy(formatted_type, "°R");
			formatted_temp =  ( ( raw_temp / 1000.0 ) + 273.15)  * (9.0/5.0);
		break;
		case 's':
			strcpy(formatted_type, "int");
			formatted_temp = raw_temp; 
		break;

		default: 
			fprintf(stderr, "Error reading temperature: unknown temp_type: %c\n", temp_type);
			return (EXIT_FAILURE);
		break;

	}
	printf ("Temperature: %g %s\n", formatted_temp, formatted_type);


return (0);
}



// board revisions: http://www.raspberrypi-spy.co.uk/2012/09/checking-your-raspberry-pi-board-version/

/** 
 * Gets value from /proc/cpuinfo.
 * returns NULL on error
 */
char* get_cpuinfo_value(char *key, char *buf) {

	// First will be key	
	char *temp_key = strtok(buf, " :\t");

	#ifdef DEBUG_FLAG
	//printf ("Key: #%s# TempKey: #%s#\n", key, temp_key);
	#endif

	// If not equal, they passed in wrong line, so return NULL
	if ( strcmp(temp_key, key) != 0 ) {
		return (NULL);
	}

	// second call will be value
	char *value = strtok(NULL, " :");

	// Strip LF from end.
	// TODO: should check last character for LF instead of just stripping
	value [ strlen(value) - 1 ]  = '\0'; 

	return (value);
}



int print_revision() {

	char error[1024];

	FILE* fp = fopen(RPI_CPUINFO_FILE, "r");
	if(!fp) {
		snprintf(error, sizeof(error), "Error reading revision. Error opening file [ %s ]", RPI_CPUINFO_FILE);
		perror(error);
		return (EXIT_FAILURE);
	}

 
	char buf[100];
	char *revision = NULL;
	while (fgets(buf, sizeof buf, fp) != NULL) {
		#ifdef DEBUG_FLAG
		//printf ("In: %s", buf);
		#endif

		char *r = get_cpuinfo_value("Revision", buf);
		if (r != NULL) {
			#ifdef DEBUG_FLAG
			//printf ("Revision: %s\n", r);
			#endif
			revision=r;
			break;
		}
	}

	if (ferror(fp)) {
		snprintf(error, sizeof(error), "Error reading revision. Error reading file [ %s ]", RPI_CPUINFO_FILE);
		perror(error);
		return (EXIT_FAILURE);
	}

	// Parse string
	if (revision == NULL) {
		fprintf(stderr, "Error reading revision. Unable to find revision number (are you running from a real Raspberry PI?)\n");
		return (EXIT_FAILURE);
	}
	int rpid=find_rpid(revision);
	#ifdef DEBUG_FLAG
	//printf ("rpid: %d\n", rpid);
	#endif

	if (rpid == -1) {
		fprintf(stderr, "Unable to find model information in revision database.  Please report your revision: %s\n", revision);
		return (EXIT_FAILURE);
	}

	print_rpi_info(rpid);

	// Remove ending LF


return (0);
}































