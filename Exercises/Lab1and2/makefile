CXX=g++
CXXFLAGS=-std=c++20 -w
TARGET=AnalyseData
OBJECTS=CustomFunctions.o \
		AnalyseData.o 
	    
# Makes as rule that allows for .cxx files
%.o: %.cxx
	$(CXX) $(CXXFLAGS) -c $< -o $@

${TARGET}:${OBJECTS}
	@echo "Linking..."
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${TARGET}

clean:
	@rm -f *.o *~
