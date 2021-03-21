CXX=g++
# vr: -Wno-stringop-truncation évite des warnings de fin de chaîne tronquée
# vr: j'enlève -Wall
CXXFLAGS= -ggdb  -Wno-stringop-truncation
RM=rm -f


morse : main_morse.o encoder.o wavfile.o
	$(CXX) $(CXXFLAGS) $^ -o $@

tests : tests.o encoder.o wavfile.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# vr: j'ai rajouté une règle pour produire les deux exécutables par simplicité pour mes tests
all: morse tests

main_morse.o : main_morse.cpp encoder.h 

wavfile.o : wavfile.cpp wavfile.h

encoder.o : encoder.cpp encoder.h wavfile.h

tests.o : tests.cpp tests.h encoder.h

%.o:%.cpp; $(CXX) $(CXXFLAGS) -o $@ -c $<

clean :
	$(RM) main_morse.o tests.o encoder.o wavfile.o morse tests
