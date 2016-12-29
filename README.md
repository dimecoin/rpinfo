# rpinfo
Raspberry PI Info utility

## Building

See make file. `make` should work on Raspberry Pis (all versions).

## Usage

./rpinfo --help
Usage: ./rpinfo [-h] [-r] [-t unit] [-v]

  -h
  --help
         prints this help menu
  -t
  --temperature
         gets the system tempatures, must give unit parameter (eg. `-t c`):
                [c]elsius (centigrade)
                [f]ahrenheit
                [k]elvin
                [r]ankine
                [s]system (raw int value recorded by linux)
  -r
  --revision
         gets revision of this pi

Examples:
        ./rpinfo -r # prints pi revision info
        ./rpinfo --revision # same as above, long style paraemter
        ./rpinfo -t f # get temperature in fahrenheit
        ./rpinfo --temperature c # get temperature in celsius


## Example output

Revision: a02082
Model Name: Raspberry PI 3 Model B
Manufactor: Sony
Year: 2016
PCB Major Version: 1
PCB Minor Version: 1
Comments/Notes:
Temperature: 77.364 °C
