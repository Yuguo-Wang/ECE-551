#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void sort_input(std::istream & input) {
  std::string str;
  std::vector<std::string> strings;

  if ((!input.eof()) && (!input.good())) {
    std::cerr << "error when reading from input" << std::endl;
    exit(EXIT_FAILURE);
  }

  while (std::getline(input, str)) {
    strings.push_back(str);
  }

  std::sort(strings.begin(), strings.end());
  std::vector<std::string>::iterator it = strings.begin();

  while (it != strings.end()) {
    std::cout << *it << std::endl;
    ++it;
  }
}

/*
void sort_input(std::istream & is) {
  std::string tmp;
  std::vector<std::string> str_arr;
  while (std::getline(is, tmp)) {
    str_arr.push_back(tmp);
  }

  sort(str_arr.begin(), str_arr.end());

  std::vector<std::string>::iterator it = str_arr.begin();
  while (it != str_arr.end()) {
    std::cout << *it << std::endl;
    it++;
  }
}*/
/*
void sort_file(int argc, char ** argv) {
  std::ifstream f;
  for (int i = 1; i < argc; i++) {
    f.open(argv[i], std::ifstream::in);
    if (!f) {
      std::cerr << "Error: cannot open the file" << std::endl;
      exit(EXIT_FAILURE);
    }

    sort_input(f);
    f.close();
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    sort_input(std::cin);
  }
  if (argc > 1) {
    sort_file(argc, argv);
  }
  return EXIT_SUCCESS;
}
*/

int main(int argc, char ** argv) {
  if (argc == 1) {
    sort_input(std::cin);
  }
  if (argc >= 2) {
    for (int i = 1; i < argc; i++) {
      std::ifstream input_file(argv[i]);
      if (!input_file.is_open()) {
        std::cerr << "read fail." << std::endl;
        return EXIT_FAILURE;
      }
      sort_input(input_file);
    }
  }
  return EXIT_SUCCESS;
}
