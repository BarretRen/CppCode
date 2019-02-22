SRCS:=nothing
LIBS:=../lib/libapue.a
HEADERS:=../include/apue.h

all: test

test:$(SRCS) $(HEADERS)
	gcc $(SRCS) $(LIBS) -o a.out

clean:
	rm *.out
