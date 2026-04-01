CC ?= C:/msys64/ucrt64/bin/gcc.exe
CFLAGS ?= -std=c11 -Wall -Wextra

TARGET = program.exe
SOURCES = \
	add_polynomials.c \
	create_polynomial.c \
	derivative.c \
	evaluate_polynomial.c \
	field_info.c \
	main.c \
	menu.c \
	mult_by_scalar.c \
	mult_polys.c \
	polynomial.c \
	print_list_polynomials.c \
	set_coef.c \
	tests.c
OBJECTS = $(SOURCES:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS) $(TARGET)
