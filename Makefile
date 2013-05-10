TARGET = c-foundation-test
SRC=$(wildcard *.c)

$(TARGET): $(SRC)
	gcc $^ -o $@

