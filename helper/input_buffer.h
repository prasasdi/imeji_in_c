#ifndef INPUTBUFFER_H_
#define INPUTBUFFER_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char* buffer;
  size_t buffer_length;
  size_t input_length;
} InputBuffer;

size_t win_getline(char** lineptr, size_t* n, FILE* stream);
int new_input_buffer(InputBuffer* input_buffer);
int read_input(InputBuffer* input_buffer);

size_t win_getline(char** lineptr, size_t* n, FILE* stream) {
  if (lineptr == NULL || n == NULL || stream == NULL) {
    return -1;
  }
  size_t pos = 0;
  int c; // character
  
  if (*lineptr == NULL) {
    *n = 128; //initial buffer size
    *lineptr = (char*) malloc(*n);
    if (*lineptr == NULL ){
      perror("*lineptr malloc()");
      return -1;
    }
  }

  while((c = fgetc(stream)) != EOF) {
    if (pos + 1 >= *n) {
      size_t new_size = *n * 2;
      char* new_ptr = (char*)realloc(*lineptr, new_size);
      if (new_ptr == NULL) {
        perror("new_ptr realloc()");
        return -1;
      }
      *lineptr = new_ptr;
      *n = new_size;
    }
    (*lineptr)[pos++] = (char)c;
    if (c == '\n') {
      break;
    }
  }
  if (pos == 0 && c == EOF) {
    return -1; // no characters read, end of file
  }

  (*lineptr)[pos] = '\0';
  return pos;
}

int new_input_buffer(InputBuffer* input_buffer) {
  if (input_buffer==NULL) {
    perror("new_input_buffer malloc()");
    return -1;
  }
  input_buffer->buffer = NULL;
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;
  return 0;
}

int read_input(InputBuffer* input_buffer) {
  size_t bytes_read = win_getline(&input_buffer->buffer, &input_buffer->input_length, stdin);

  if (bytes_read <= 0) {
    perror("error reading input");
    return -1;
  }

  input_buffer->input_length = bytes_read - 1;
  input_buffer->buffer[bytes_read - 1] = 0;

  return 0;
}

void close_input_buffer(InputBuffer* input_buffer) {
  free(input_buffer->buffer);
  free(input_buffer);
}

#endif

