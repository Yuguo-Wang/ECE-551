
#include "story.h"

//---------step1--------------------

//check a string is a number or not
bool isnumber(std::string & s) {
  size_t blank = 0;
  while (s[blank] == ' ') {
    blank++;
  }
  for (size_t i = blank; i < s.size(); i++) {
    if (!std::isdigit(s[i])) {
      return false;
    }
  }
  return true;
}

//check the line in story.txt is related to choice
//Eg: 4:7:Go alone.
bool check_choice_line(std::string & line) {
  //Blank line
  if (line.empty()) {
    return false;
  }

  //No colon founded
  if (line.find(":") == line.npos) {
    return false;
  }

  int first_colon_index = line.find(":");
  std::string first_str = line.substr(0, first_colon_index);
  if (!isnumber(first_str)) {
    return false;
  }

  std::string remain = line.substr(first_colon_index + 1);
  int second_colon_index = remain.find(":");
  std::string second_str = remain.substr(0, second_colon_index);
  if (!isnumber(second_str)) {
    return false;
  }
  return true;
}

//check the line if it is to declare a page
bool check_page_line(std::string & line) {
  //Blank line
  if (line.empty()) {
    return false;
  }

  //No "@" founded
  if (line.find("@") == line.npos) {
    return false;
  }

  int at_index = line.find("@");
  std::string num = line.substr(0, at_index);
  if (!isnumber(num)) {
    return false;
  }

  std::string remain = line.substr(at_index + 1);

  int colon_index = remain.find(":");
  std::string alpha = remain.substr(0, colon_index);

  if (alpha != "N" && alpha != "W" && alpha != "L") {
    return false;
  }
  return true;
}

//------------step4--------------
// eg: pagenum$var=value
bool check_declare_specified(std::string & line) {
  //blank line
  if (line.empty()) {
    return false;
  }

  //No $ founded
  if (line.find("$") == line.npos) {
    return false;
  }

  int dollar = line.find("$");
  std::string num = line.substr(0, dollar);
  if (!isnumber(num)) {
    return false;
  }

  std::string remain = line.substr(dollar + 1);
  int equal_index = remain.find("=");
  std::string num2 = remain.substr(equal_index + 1);
  if (!isnumber(num2)) {
    return false;
  }
  return true;
}

//------------step4--------------
//eg: pagenum[var=value]:dest:text
bool check_choice_specified(std::string & line) {
  //blank line
  if (line.empty()) {
    return false;
  }

  //No colon founded
  if (line.find("[") == line.npos || line.find("]") == line.npos ||
      line.find(":") == line.npos || line.find("=") == line.npos) {
    return false;
  }

  int par = line.find("[");
  std::string num = line.substr(0, par);
  if (!isnumber(num)) {
    return false;
  }

  int equal_index = line.find("=");

  std::string remain = line.substr(equal_index + 1);
  int right_par = remain.find("]");
  std::string num2 = remain.substr(0, right_par);

  if (!isnumber(num2)) {
    return false;
  }

  int colon = remain.find(":");
  if (right_par + 1 != colon) {
    return false;
  }

  std::string remain2 = remain.substr(colon + 1);
  int colon2 = remain2.find(":");
  std::string num3 = remain2.substr(0, colon2);
  if (!isnumber(num3)) {
    return false;
  }

  return true;
}

//Read a file and put its content into a std::string
std::string readPage(std::string & path) {
  std::ifstream ifs;
  ifs.open(path.c_str());

  if (!ifs.is_open()) {
    std::cerr << "cannot open 'txt' file\n" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  //put the content of the file into Object os_object
  std::ostringstream os_object;
  char ch;

  while (os_object && ifs.get(ch))
    os_object.put(ch);

  return os_object.str();
}

//Step1 only need to print a page with choices
void parseline(std::string & filePath,
               std::string & line,
               std::vector<Page> & vector_pages) {
  //check if the line is choice
  if (check_choice_line(line)) {
    // Find the number first
    int first_colon_index = line.find(":");
    std::string fileNum = line.substr(0, first_colon_index);

    // Find the choice text and target page number
    std::string remain = line.substr(first_colon_index + 1);
    int second_colon_index = remain.find(":");
    std::string targetNum = remain.substr(0, second_colon_index);
    std::string text = remain.substr(second_colon_index + 1);

    // Find the number in the vector_pages
    std::string c = "C";
    std::vector<Page>::iterator it = vector_pages.begin();
    while (it != vector_pages.end()) {
      if ((*it).get_num() == fileNum) {
        // check that the win and lose page cannot continue to give choice to other pages
        if ((*it).get_type() == "W" || (*it).get_type() == "L") {
          std::cerr << "The Win and Lose page number could not go ahead" << std::endl;
          exit(EXIT_FAILURE);
        }

        (*it).assign_vector_choices(text);
        (*it).assign_type(c);
        (*it).assign_vector_targets(targetNum);
      }
      ++it;
    }
  }

  //check if the line is to declare the page
  else if (check_page_line(line)) {
    //file number
    int at_index = line.find("@");
    std::string fileNum = line.substr(0, at_index);

    //file type
    std::string remain = line.substr(at_index + 1);
    int colon_index = remain.find(":");
    std::string type = remain.substr(0, colon_index);

    //file path
    std::string path = filePath + "/" + remain.substr(colon_index + 1);

    //file content
    std::string content = readPage(path);

    Page onePage;
    onePage.assign_num(fileNum);

    //confirm the order
    if (strtoull(fileNum.c_str(), NULL, 10) != vector_pages.size()) {
      std::cerr << "page number not in order\n";
      exit(EXIT_FAILURE);
    }

    onePage.assign_type(type);
    onePage.assign_path(path);
    onePage.assign_content(content);

    vector_pages.push_back(onePage);
  }

  // step 4---------------
  // check if the format is "pagenum$var=value"
  else if (check_declare_specified(line)) {
    int dollar = line.find("$");
    std::string pageNum = line.substr(0, dollar);
    std::string remain = line.substr(dollar + 1);

    int equal = remain.find("=");
    std::string item = remain.substr(0, equal);
    size_t num = strtoull(remain.substr(equal + 1).c_str(), NULL, 10);

    for (size_t i = 0; i < vector_pages.size(); i++) {
      if (vector_pages[i].get_num() == pageNum) {
        // put the pair in the map in class Page, to update
        vector_pages[i].assign_hashmap_specified(item, num);
      }
    }
  }

  // step 4
  // check if the format is "pagenum[var=value]:dest:text"
  else if (check_choice_specified(line)) {
    int left_per = line.find("[");
    std::string pageNum = line.substr(0, left_per);

    std::string remain1 = line.substr(left_per + 1);
    int equal = remain1.find("=");
    std::string item = remain1.substr(0, equal);

    std::string remain2 = remain1.substr(equal + 1);
    int right_per = remain2.find("]");
    size_t num = strtoull(remain2.substr(0, right_per).c_str(), NULL, 10);

    std::string remain3 = remain2.substr(right_per + 2);
    int second_colon = remain3.find(":");
    std::string targetPage = remain3.substr(0, second_colon);
    std::string choice_content = remain3.substr(second_colon + 1);

    std::string c = "C";
    for (size_t i = 0; i < vector_pages.size(); i++) {
      if (vector_pages[i].get_num() == pageNum) {
        vector_pages[i].assign_type(c);
        vector_pages[i].assign_vector_targets(targetPage);

        std::pair<std::string, size_t> requirement;
        requirement.first = item;
        requirement.second = num;

        // update the requirement of every choice
        vector_pages[i].assign_requirement_choices(requirement, choice_content);
      }
    }
  }

  //blank line, just ignore it
  else if (line.empty()) {
  }
  //other situation, regard it as a fault
  else {
    std::cerr << "Wrong format of the line";
    std::exit(EXIT_FAILURE);
  }
}

//---------class methods-------------

Story::Story(std::vector<Page> & vp) : vector_pages() {
  for (size_t i = 0; i < vp.size(); i++) {
    vector_pages.push_back(vp[i]);
  }
}

// print the choices according to the page number
void Page::printChoices() {
  if (!vector_choices.empty()) {
    int num = 1;
    for (size_t i = 0; i < vector_choices.size(); i++) {
      std::cout << num << "." << vector_choices[i].get_text() << "\n";
      num++;
    }
  }
}

// verify the format of the input file
bool Story::verify() {
  std::vector<bool> referenced(vector_pages.size(), false);
  referenced[0] = true;

  for (size_t i = 0; i < vector_pages.size(); i++) {
    std::vector<std::string> targets = vector_pages[i].get_vector_targets();

    for (size_t j = 0; j < targets.size(); j++) {
      size_t target_number = strtoull(targets[j].c_str(), NULL, 10);

      // check every page that is referenced by a choice is valid
      if (target_number < vector_pages.size()) {
        // this page is marked
        referenced[target_number] = true;
      }
      else {
        return false;
      }
    }
  }

  //Every page (except page 0) is referenced by at least one *other* page's choices
  for (size_t i = 0; i < referenced.size(); i++) {
    if (!referenced[i]) {
      return false;
    }
  }

  bool win_exit = false;
  bool lose_exit = false;

  for (size_t i = 0; i < vector_pages.size(); i++) {
    // check that at least one page must be a WIN page and at least one page must be a LOSE page

    if (vector_pages[i].get_type() == "W") {
      win_exit = true;
    }

    if (vector_pages[i].get_type() == "L") {
      lose_exit = true;
    }
  }
  return win_exit && lose_exit;
}

// ------------step1-------------
// print the whole story
void Story::printStory() {
  if (!vector_pages.empty()) {
    std::vector<Page>::iterator it = vector_pages.begin();

    while (it != vector_pages.end()) {
      std::cout << "Page " << (*it).get_num() << "\n"
                << "==========\n";

      //1. First, print the text of the page, which is param content
      std::cout << (*it).get_content();

      //2. Next, print a blank line
      std::cout << "\n";

      if ((*it).get_type() == "W") {
        std::cout << "Congratulations! You have won. Hooray!\n";
      }
      else if ((*it).get_type() == "L") {
        std::cout << "Sorry, you have lost. Better luck next time!\n";
      }
      else if ((*it).get_type() == "C") {
        std::cout << "What would you like to do?\n";
        //4. Then print another blank line.
        std::cout << "\n";
        // print the choices
        (*it).printChoices();
      }
      ++it;
    }
  }
}

//------------step2 and step4---------------
// depends on the input (2 types or 4 types)
void Story::printTurnPages(size_t startPage) {  // start from page 0
  // ----------step4----------
  std::vector<Choice> currChoice = vector_pages[startPage].get_vector_choices();
  // current page's map of requirement
  std::map<std::string, size_t> currMap = vector_pages[startPage].get_map();

  // update the map of class Story where there are all pairs of requirement
  // it's better for c++11 by using auto
  std::map<std::string, size_t>::iterator it = currMap.begin();
  while (it != currMap.end()) {
    if (pages_hashmap_specified.find((*it).first) == pages_hashmap_specified.end()) {
      pages_hashmap_specified.insert(*it);
    }
    else {
      pages_hashmap_specified[(*it).first] = (*it).second;
    }
    ++it;
  }

  std::string str = "<UNAVAILABLE>";
  //-------------step4-----------
  // tell the difference of step2 and step4 by checking if this map is empty or not
  if (!pages_hashmap_specified.empty()) {
    for (size_t i = 0; i < currChoice.size(); i++) {
      std::pair<std::string, size_t> currRequirement = currChoice[i].get_requirement();
      if (!currRequirement.first.empty()) {
        //If your story encounters a variable which has not been set
        //it should treat it as having a value of 0.
        if ((pages_hashmap_specified.find(currRequirement.first) ==
                 pages_hashmap_specified.end() &&
             currRequirement.second != 0) ||
            pages_hashmap_specified[currRequirement.first] != currRequirement.second) {
          // change the text to <UNAVAILABLE>
          vector_pages[startPage].assign_choice_text(i, str);
          // change currChoice in order to check its content later
          currChoice[i].assign_text(str);
        }
      }
    }
  }

  // print content
  std::cout << vector_pages[startPage].get_content() << "\n";

  // print type
  if (vector_pages[startPage].get_type() == "W") {
    std::cout << "Congratulations! You have won. Hooray!\n";
    return;
  }
  else if (vector_pages[startPage].get_type() == "L") {
    std::cout << "Sorry, you have lost. Better luck next time!\n";
    return;
  }
  else if (vector_pages[startPage].get_type() == "C") {
    std::cout << "What would you like to do?\n";
    std::cout << "\n";

    vector_pages[startPage].printChoices();
  }

  std::vector<std::string> targets = vector_pages[startPage].get_vector_targets();

  std::string index_str;
  size_t currPage;

  //confirm the format of input
  while (true) {
    std::cin >> index_str;

    // if this page is not marked as type, it means Normal page without choices line
    // If you get end of file on stdin it is an error.
    if (std::cin.get() == EOF) {
      std::cerr << "Timeout! check the input.txt if it is ending and the story.txt if there is a page without choices" << std::endl;
      exit(EXIT_FAILURE);
    }
    // fail to cin the stream, repeat till the right input
    if (std::cin.fail()) {
      // change cin.fail() to 0, which means situation that we can continue doing "cin"
      std::cin.clear();
      // remove one error input from cache
      std::cin.ignore();
    }

    else {    

      size_t index = strtoull(index_str.c_str(), NULL, 10);
      if (index >= 1 && index <= targets.size()) {
        // if the choice is <UNAVAILABLE>, print the not available text
        if (currChoice[index - 1].get_text() == str) {
          std::cout << "That choice is not available at this time, please try again"
                    << "\n";
        }
        else {
          currPage = strtoull(targets[index - 1].c_str(), NULL, 10);
          break;
        }
      }
      else {
        std::cout << "That is not a valid choice, please try again"
                  << "\n";
      }
    }
  }

  //recursion
  printTurnPages(currPage);
}

//------------------step3-------------------
//find all the win page number and put in a vector
// no need to check if there is no win page, because function verity has already do it in cyoa-step3
std::vector<size_t> Story::find_win_pages() {
  std::vector<size_t> winPages;
  for (size_t i = 0; i < vector_pages.size(); i++) {
    if (vector_pages[i].get_type() == "W") {
      size_t win_page_number = strtoull(vector_pages[i].get_num().c_str(), NULL, 10);
      winPages.push_back(win_page_number);
    }
  }
  return winPages;
}

// to find the win path
bool reachable = false;
void dfs(std::vector<Page> & vector_pages,
         std::vector<std::vector<size_t> > & res,
         std::vector<size_t> & path,
         std::vector<bool> & visited,
         size_t currPage,
         size_t destPage) {
  if (currPage == destPage) {
    res.push_back(path);
    reachable = true;
    return;
  }

  std::vector<std::string> vector_targets = vector_pages[currPage].get_vector_targets();

  for (size_t i = 0; i < vector_targets.size(); i++) {
    size_t nextPage = strtoull(vector_targets[i].c_str(), NULL, 10);

    // if this page is already marked visited, cross off
    if (visited[nextPage]) {
      continue;
    }
    // marked as visited
    visited[nextPage] = true;
    path.push_back(nextPage);

    //recursion
    dfs(vector_pages, res, path, visited, nextPage, destPage);

    //backtrack
    path.pop_back();
    visited[nextPage] = false;
  }
}

//to find all the win path and put into a vector
std::vector<std::vector<size_t> > Story::findWinPath() {
  std::vector<std::vector<size_t> > res;
  std::vector<size_t> path(1, 0);

  //base case
  std::vector<bool> visited(vector_pages.size(), false);
  visited[0] = true;

  // To find all the Win Path, use dfs
  std::vector<size_t> winPages = find_win_pages();
  for (size_t i = 0; i < winPages.size(); i++) {
    size_t winNum = winPages[i];
    // beginning of dfs
    dfs(vector_pages, res, path, visited, 0, winNum);
  }
  if (!reachable) {
    std::cout << "This story is unwinnable!" << std::endl;
  }
  return res;
}

void Story::printWinPaths() {
  std::vector<std::vector<size_t> > res = findWinPath();

  if (res.size() == 0) {
    return;
  }

  //many winPath
  for (size_t k = 0; k < res.size(); k++) {
    std::vector<size_t> winPath = res[k];

    //one of the winPath
    for (size_t i = 0; i < winPath.size() - 1; i++) {
      size_t currPageNum = winPath[i];

      std::cout << currPageNum;
      std::vector<std::string> curr_targets =
          vector_pages[currPageNum].get_vector_targets();

      //find the relationship between choices and the nextPage number
      for (size_t j = 0; j < curr_targets.size(); j++) {
        size_t target = strtoull(curr_targets[j].c_str(), NULL, 10);

        if (winPath[i + 1] == target) {
          std::cout << "(" << (j + 1) << "),";
        }
      }
    }
    // print the win page and its format
    std::cout << winPath[winPath.size() - 1] << "(win)"
              << "\n";
  }
}
