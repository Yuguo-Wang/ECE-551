#include "story.cpp"

int main(int argc, char ** argv) {
  if (argc != 2) {
    std::cerr << "Wrong format of input\n";
    return EXIT_FAILURE;
  }

  std::ifstream ifs;

  std::string oriPath = argv[1];

  std::string filename = oriPath + "/story.txt";

  ifs.open(filename.c_str(), std::ios::in);
  if (!ifs.is_open()) {
    std::cerr << "cannot open story.txt" << std::endl;
    return EXIT_FAILURE;
  }

  std::string line;
  std::vector<Page> vector_page;

  while (std::getline(ifs, line)) {
    parseline(oriPath, line, vector_page);
  }
  ifs.close();
  Story s1(vector_page);
  if (!s1.verify()) {
    std::cerr << "The format of the story.txt is wrong" << std::endl;
    return EXIT_FAILURE;
  }

  s1.printTurnPages(0);

  return EXIT_SUCCESS;
}
