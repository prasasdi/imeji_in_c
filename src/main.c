#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  long leng;
  char* buf = NULL;
  FILE* fp = NULL;
  
  if (argc < 2) {
    printf("Must supply a image file\n");
    return EXIT_FAILURE;
  }

  char* srcfile = argv[1];
  
  // open file
  fp = fopen(srcfile, "rb+");
  if (!fp) {  
    printf("Failed to open file, either it's corrupt or not existed\n");
    return EXIT_FAILURE;
  }

  // leng file
  fseek(fp, 0, SEEK_END);
  leng = ftell(fp);
  rewind(fp);
  
  if (leng == 0) {
    printf("Read file source but read as empty\n");
    return EXIT_FAILURE;
  }

  buf = (char*)malloc(sizeof(char) * leng);
  if (!buf) {
    fclose(fp);
    printf("Failed to allocate buffer\n");
    return EXIT_FAILURE;
  }

  if (!fread(buf, leng, 1, fp)) {
    free(buf);
    fclose(fp);
    printf("Failed to write to allocated buffer\n");
    return EXIT_FAILURE;
  }

  fclose(fp);
  printf("Executed, but we have no idea what is this buffer, wether really as binary or as an text\n");
  return EXIT_SUCCESS;
}
