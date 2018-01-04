CXX     = g++
CFLAGS  = -Os -Wall 
LDFLAGS = --std=c++11 -lpthread

PRG = lightlog_test
SRC = test/$(PRG).cc

$(PRG): $(SRC) lightlog.h
		$(CXX) -o $(PRG) $(CFLAGS) $(SRC) $(LDFLAGS)

.PHONY : clean
 	clean :
		rm $(PRG)