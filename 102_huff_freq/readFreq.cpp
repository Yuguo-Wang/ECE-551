#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!

  std::ifstream ifs;
  ifs.open(fname, std::ios::in);
  if (!ifs.is_open()) {
    std::cerr << "cannot open the file\n";
    exit(EXIT_FAILURE);
  }

  uint64_t * res = new uint64_t[257]();
  int ch;
  while ((ch = ifs.get()) != EOF) {
    res[ch]++;
  }
  res[256]++;  //last one
  ifs.close();
  return res;
}
