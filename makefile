INC = -I/opt/homebrew/Cellar/portaudio/19.7.0/include -I/opt/homebrew/Cellar/libsndfile/1.2.2/include
LINK = -L/opt/homebrew/Cellar/portaudio/19.7.0/lib -L/opt/homebrew/Cellar/libsndfile/1.2.2/lib
CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lportaudio -lsndfile
LIBS = $(shell pkg-config --libs portaudio)

TARGET = audio_recorder
SRC = main.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INC) -o $@ $^ $(LINK) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)