SOURCE_FILES = field.c game.c piece.c piece_types.c pieces.c main.c error.c
OUTPUT_FILE = pentomino

all: $(OUTPUT_FILE)

$(OUTPUT_FILE): $(SOURCE_FILES)
	cc -o $@ $^