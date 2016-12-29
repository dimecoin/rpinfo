#pragma once
#include <string.h>

typedef struct rpi_model_info
{
  char *revision;

  int release_year;

  char *model_name;

  int pcb_major_revision;
  int pcb_minor_revision;

  char *manufactor;
  char *notes;

} rpi_model_info;


/** Model database taken from : http://elinux.org/RPi_HardwareHistory */
rpi_model_info rpi_models[] = {

  {"Beta", 2012, "B (Beta)", -1, -1, "Unknown", "Beta Board"},

  {"0002", 2012, "B", 1, 0, "Unknown", ""},
  {"0003", 2012, "B (ECN0001)", 2, 0, "Unknown", "Fuses mod and D14 removed"},
  {"0004", 2012, "B", 2, 0, "Sony", ""},
  {"0005", 2012, "B", 2, 0, "Qisda", ""},
  {"0006", 2012, "B", 2, 0, "Egoman", ""},
  {"0007", 2013, "A", 2, 0, "Egoman", ""},
  {"0008", 2013, "A", 2, 0, "Sony", ""},
  {"0009", 2013, "A", 2, 0, "Qisda", ""},
  {"000d", 2012, "B", 2, 0, "Egoman", ""},
  {"000e", 2012, "B", 2, 0, "Sony", ""},
  {"000f", 2012, "B", 2, 0, "Qisda", ""},
  {"0010", 2014, "B+", 1, 0, "Sony", ""},
  {"0011", 2014, "Compute Model", 1, 0, "Sony", ""},
  {"0012", 2014, "A+", 1, 1, "Sony", ""},
  {"0013", 2015, "B+", 1, 2, "Unknown", ""},
  {"0014", 2014, "Compute Model", 1, 0, "Embest", ""},
  {"0015", 0, "A+", 1, 1, "Embest", ""},

  {"a01041", 2015, "2 Model B", 1, 1, "Sony", ""},
  {"a21041", 2015, "2 Model B", 1, 1, "Embest", ""},

  {"900092", 2015, "Zero", 1, 2, "Sony", ""},
  {"900093", 2015, "Zero", 1, 3, "Sony", ""},


  {"a02082", 2016, "3 Model B", 1, 1, "Sony", ""},
  {"a22082", 2016, "3 Model B", 1, 1, "Unknown", ""}
};

/**
 * find id of model in rpi_models struct
 * pass in revision string (ie, a02082)
 * returns index of model in rpi_models 
 * returns -1 on error
 */

int
find_rpid (const char *revision)
{

  int size = sizeof (rpi_models) / sizeof (rpi_models[0]);

  for (int i = 0; i < size; i++)
    {
#ifdef DEBUG_FLAG
      //printf ("Comparing #%s# to #%s#\n", revision, rpi_models[i].revision);
#endif
      if (strcmp (revision, rpi_models[i].revision) == 0)
	{
	  return (i);
	}
    }

  return (-1);
}

/**
 * pass in index of rpi_modules (see find_rpid)
 * prints model information to stdout
 * returns 0 on success 
 * returns -1 on error (most likely because it can't find model information in rpi_models)
 */

int
print_rpi_info (int rpid)
{

  if (rpid == -1)
    {
      return (-1);
    }

  rpi_model_info rpi_model = rpi_models[rpid];

  printf ("Revision: %s\n", rpi_model.revision);
  printf ("Model Name: Raspberry PI %s\n", rpi_model.model_name);
  printf ("Manufactor: %s\n", rpi_model.manufactor);

  printf ("Year: %d\n", rpi_model.release_year);

  printf ("PCB Major Version: %d\n", rpi_model.pcb_major_revision);
  printf ("PCB Minor Version: %d\n", rpi_model.pcb_minor_revision);


  printf ("Comments/Notes: %s\n", rpi_model.notes);

  return (0);
}
