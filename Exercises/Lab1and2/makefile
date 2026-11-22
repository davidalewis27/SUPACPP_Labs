CXX=g++
CXXFLAGS=-std=c++20 -Wall -Wextra
TARGET=AnalyseData
OBJECTS=CustomFunctions.o \
		AnalyseData.o 
	    
# Makes as rule that allows for .cxx files
%.o: %.cxx CustomFunctions.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

${TARGET}:${OBJECTS}
	@echo "Linking..."
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${TARGET}

.PHONY: clean
clean:
	@rm -f *.o *~ ${TARGET}
