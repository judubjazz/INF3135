#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parse_args.h"
#include "maze.h"
#include "drawing.h"
#include <jansson.h>


char *ReadFile(char *filename) {
    char *buffer = NULL;
    int string_size, read_size;
    FILE *handler = fopen(filename, "r");

    if (handler) {
        // Seek the last byte of the file
        fseek(handler, 0, SEEK_END);
        // Offset from the first to the last byte, or in other words, filesize
        string_size = ftell(handler);
        // go back to the start of the file
        rewind(handler);

        // Allocate a string that can hold it all
        buffer = (char *) malloc(sizeof(char) * (string_size + 1));

        // Read it all in one operation
        read_size = fread(buffer, sizeof(char), string_size, handler);

        // fread doesn't set it so put a \0 in the last position
        // and buffer is now officially a string
        buffer[string_size] = '\0';

        if (string_size != read_size) {
            // Something went wrong, throw away the memory and set
            // the buffer to NULL
            free(buffer);
            buffer = NULL;
        }

        // Always remember to close the file.
        fclose(handler);
    }

    return buffer;
}

int main(int argc, char **argv) {
    //--num-rows 2 --num-cols 3 --output-format dot --output-filename test
    //param.json
    json_t *root;
    json_error_t error;
    char *string;

    string = ReadFile("/home/ju/JetBrainsProjects/CLionProjects/INF3135_tp2/param.json");
    root = json_loads(string, 0, &error);
    free(string);

    if (!json_is_object(root)) {
        fprintf(stderr, "error: commit data  is not an object\n");
        json_decref(root);
        return 1;
    }

    bool argv_is_json = true;
    struct Arguments arguments = parseArguments(argc, argv, argv_is_json, root);
    if (arguments.status != TP2_OK) {
        return arguments.status;
    } else {
        struct Maze *maze = Maze_randomMaze(&arguments);
        if (strcmp(arguments.outputFormat, TEXT_FORMAT) == 0) {
            Maze_print(maze, arguments.withSolution);
        } else if (strcmp(arguments.outputFormat, PNG_FORMAT) == 0) {
            Drawing_drawMaze(maze, &arguments);
        } else if (strcmp(arguments.outputFormat, DOT_FORMAT) == 0) {
//            TODO
            createDotFile(maze, &arguments);
            Maze_print(maze, arguments.withSolution);
        }
        if (maze != NULL) {
            Maze_free(maze);
            free(root);
        }
    }
    return TP2_OK;
}