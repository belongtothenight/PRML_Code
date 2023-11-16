#include <stdio.h>

#define CONFIG_SIZE (256)
#define HOST_SET (1)
#define PORT_SET (2)

typedef struct config {
  unsigned set;
  char host[CONFIG_SIZE];
  unsigned long port;
} CONFIG;

// Parse the buffer for config info. Return an error code or 0 for no error.
int parse_config(char *buf, CONFIG *config) {
  char dummy[CONFIG_SIZE];
  if (sscanf(buf, " %s", dummy) == EOF) return 0; // blank line
  if (sscanf(buf, " %[#]", dummy) == 1) return 0; // comment
  if (sscanf(buf, " host = %s", config->host) == 1) {
    if (config->set & HOST_SET) return HOST_SET; // error; host already set
    config->set |= HOST_SET;
    return 0;
  }
  if (sscanf(buf, " port = %lu", &config->port) == 1) {
    if (config->set & PORT_SET) return PORT_SET; // error; port already set
    config->set |= PORT_SET;
    return 0;
  }
  return 3; // syntax error
}

void init_config(CONFIG *config) {
  config->set = 0u;
}

void print_config(CONFIG *config) {
  printf("[host=%s,port=", config->set & HOST_SET ? config->host : "<unset>");
  if (config->set & PORT_SET) printf("%lu]", config->port); else printf("<unset>]");
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s CONFIG_FILE\n", argv[0]);
    return 1;
  }
  FILE *f = fopen(argv[1], "r");
  char buf[CONFIG_SIZE];
  CONFIG config[1];
  init_config(config);
  int line_number = 0;
  while (fgets(buf, sizeof buf, f)) {
    ++line_number;
    int err = parse_config(buf, config);
    if (err) fprintf(stderr, "error line %d: %d\n", line_number, err);
  }
  print_config(config);
  return 0;
}