
#gcc -> arm-linux-gcc
CC = gcc
CFLAGS = -Wall
OBJS = add.o sub.o mul.o main.o
TARGET = calc

$(TARGET) : $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

add.o : add.c
	$(CC) -c add.c -o add.o

sub.o : sub.c
	$(CC) -c sub.c -o sub.o

mul.o : mul.c
	$(CC) -c mul.c -o mul.o

main.o : main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
	
clean :
	rm $(OBJS) $(TARGET)
