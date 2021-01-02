CXXFLAGS=-std=c++11 -Wpedantic -Wall -Werror -Wextra -Weffc++ -Wzero-as-null-pointer-constant
OPTIMIZE=-O2
FILES=Database.h Database.cpp TurnipDatabase.h TurnipDatabase.cpp main.cpp
LIBRARIES=-l sqlite3
OUTPUT=turnip

all: ${OUTPUT}
${OUTPUT}: ${FILES}
	g++ ${CXXFLAGS} ${OPTIMIZE} ${FILES} ${LIBRARIES} -o ${OUTPUT}

run: ${OUTPUT}
	valgrind ./${OUTPUT}

clean:
	/bin/rm -f ${OUTPUT}
