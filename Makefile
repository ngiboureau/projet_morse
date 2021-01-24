CXX=g++
CXXFLAGS=-Wall -ggdb
RM=rm -f

morse : main_morse.o encoder.o wavfile.o
	$(CXX) $(CXXFLAGS) $^ -o $@

tests : tests.o encoder.o wavfile.o
	$(CXX) $(CXXFLAGS) $^ -o $@

main_morse.o : main_morse.cpp encoder.h 

wavfile.o : wavfile.cpp wavfile.h

encoder.o : encoder.cpp encoder.h wavfile.h

tests.o : tests.cpp tests.h encoder.h

%.o:%.cpp; $(CXX) $(CXXFLAGS) -o $@ -c $<

clean :
	$(RM) main_morse.o tests.o encoder.o wavfile.o morse tests