// TODO: sprwadzic czy w takich przypadkach trzeba robic IFNDEF stdio?
#include <stdio.h>

int isdigit(int c) {
  if (c == EOF) {
    return 0;
  }

  if (c >= 48 && c <= 57)
    return 1;

  return 0;
}

int isspace(int c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' ||
         c == '\r';
}
