#Definitions

CXX=g++
CXXFLAGS=-std=c++11 -g -Wall
CXXLINK=g++
LIBS=
OBJS=apple.o drawable.o drawable_list.o main.o mini_gui.o monster.o 
RM=rm -f
TARGET = game.exe

$(TARGET): $(OBJS)
	  $(CXXLINK) -o $(TARGET) $(OBJS) $(LIBS)

#Dependencies

apple.o: apple.cpp apple.h drawable.h mini_gui.h ascii_objects.h
drawable.o: drawable.cpp drawable.h mini_gui.h ascii_objects.h
drawable_list.o: drawable_list.cpp drawable_list.h drawable.h mini_gui.h ascii_objects.h
main.o: main.cpp drawable_list.h drawable.h mini_gui.h ascii_objects.h apple.h monster.h
mini_gui.o: mini_gui.cpp mini_gui.h
monster.o: monster.cpp monster.h drawable.h mini_gui.h ascii_objects.h drawable_list.h


#Clean

clean:
	  $(RM) *.exe *.o
