# Make file for pointers assignment

MAIN_OBJS	= main.o house.o floor.o furniture.o
PRACTICE_OBJS = practice.o
CC		= g++
CCFLAGS	= -Wall -Wextra -pedantic -std=c++11 -g

all: main practice 

main: $(MAIN_OBJS)
	@echo "Compiling Home Designer Program"
	$(CC) $(CCFLAGS) -o home_design $(MAIN_OBJS)
	@echo "Done!"

practice: practice.cpp
	@echo "Compiling Practice Program"
	$(CC) $(CCFLAGS) -o practice practice.cpp

main.o: main.cpp
	@echo "Compiling main.cpp"
	$(CC) $(CCFLAGS) -c main.cpp	

house.o: house.cpp
	@echo "Compiling house.cpp"
	$(CC) $(CCFLAGS) -c house.cpp

floor.o: floor.cpp
	@echo "Compiling floor.cpp"
	$(CC) $(CCFLAGS) -c floor.cpp
	
furniture.o: furniture.cpp
	@echo "Compiling furniture.cpp"
	$(CC) $(CCFLAGS) -c furniture.cpp

# -----
# clean by removing object files.

clean:
	rm $(MAIN_OBJS)
	rm home_design
	rm practice
