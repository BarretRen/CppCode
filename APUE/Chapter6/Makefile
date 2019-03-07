S:=nothing
LIBS:=../lib/libapue.a
HEADERS:=../include/apue.h

all: test

test:$(SRCS) $(HEADERS)
	gcc $(S) $(LIBS) -o a.out --std=c11

clean:
	rm *.out
