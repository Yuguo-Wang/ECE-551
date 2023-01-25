CFLAGS=--std=gnu++98 -pedantic -Wall -Werror -ggdb3
all: cyoa-step4 cyoa-step3 cyoa-step2 cyoa-step1
cyoa-step4: cyoa-step2.cpp story.h story.cpp
	g++ -o cyoa-step4 $(CFLAGS) cyoa-step2.cpp
cyoa-step3: cyoa-step3.cpp story.h story.cpp
	g++ -o cyoa-step3 $(CFLAGS) cyoa-step3.cpp
cyoa-step2: cyoa-step2.cpp story.h story.cpp
	g++ -o cyoa-step2 $(CFLAGS) cyoa-step2.cpp
cyoa-step1: cyoa-step1.cpp story.h story.cpp
	g++ -o cyoa-step1 $(CFLAGS) cyoa-step1.cpp
clean:
	rm -f *.o *~

