Main: main.cpp
	g++ -Wall -o main main.cpp
# C++17 is needed
#CC = g++

#OBJ_FILE = Hirschberg_JS.o hirschberg_js_main.o
#EXE_FILE = hirschberg

#${EXE_FILE}: ${OBJ_FILE}
#				${CC} -o ${EXE_FILE} ${OBJ_FILE}

#Hirschberg_JS.o: Hirschberg_JS.cpp
#				${CC} -c Hirschberg_JS.cpp

#hirschberg_js_main.o: hirschberg_js_main.cpp
#				${CC} -c hirschberg_js_main.cpp