# Simple Search
## Installation
The program comes in two flavors - a command line-version and a gui version.
### Dependencies
First you must install `pkg-config` and `gtkmm 3.0` to build the application.
#### On Debian/Ubuntu 
```
sudo apt-get install pkg-config libgtkmm-3.0-dev
```
### Building
The application can be built using the Makefile.
```
cd simple-search
make
```
## Usage
To run the command-line version, send in any arbitrary command line arguments.
```
./search --cli
```
To run the gui version, run the program *without* any command line arguments.
```
./search
```
