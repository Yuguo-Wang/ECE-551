#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

class Choice {
 private:
  // eg: if pastry=1 in the hashmap[pastry]
  std::pair<std::string, size_t> requirement;
  // content
  std::string text;

 public:
  Choice() : requirement(), text() {}
  //---------step1,2,3-----------
  Choice(std::string c) : requirement(), text(c) {}
  //---------step4---------------
  Choice(std::pair<std::string, size_t> & r, std::string & t) : requirement(r), text(t) {}

  std::pair<std::string, size_t> get_requirement() { return requirement; }
  std::string get_text() { return text; }
  void assign_requirement(std::string & key, size_t value) {
    requirement.first = key;
    requirement.second = value;
  }
  void assign_text(std::string & str) { text = str; }
};

class Page {
 private:
  // The number of page
  std::string number;
  //N: Normal, W: Win, L: Lose, C: choice
  std::string type;
  //dataPath of this page
  std::string path;
  // content of page
  std::string content;
  // A page has many choices
  std::vector<Choice> vector_choices;
  // A page has many target pages
  std::vector<std::string> vector_targets;
  // specified variable to a value
  std::map<std::string, size_t> hashmap_specified;

 public:
  Page() :
      number(),
      type(),
      path(),
      content(),
      vector_choices(),
      vector_targets(),
      hashmap_specified() {}
  Page(std::string & n,
       std::string & t,
       std::string & p,
       std::string & c,
       std::vector<Choice> & vc,
       std::vector<std::string> & vt,
       std::map<std::string, size_t> & hs);

  std::string get_num() { return number; }
  std::string get_type() { return type; }
  std::string get_path() { return path; }
  std::string get_content() { return content; }
  std::vector<Choice> get_vector_choices() { return vector_choices; }
  std::vector<std::string> get_vector_targets() { return vector_targets; }
  std::map<std::string, size_t> get_map() { return hashmap_specified; }

  void assign_num(std::string & num) { number = num; }
  void assign_type(std::string & str) { type = str; }
  void assign_path(std::string & str) { path = str; }
  void assign_content(std::string & str) { content = str; }

  void assign_vector_choices(std::string & choice) {
    Choice newChoice(choice);
    vector_choices.push_back(newChoice);
  }

  void assign_requirement_choices(std::pair<std::string, size_t> & requirement,
                                  std::string & choice_content) {
    Choice newChoice(requirement, choice_content);
    vector_choices.push_back(newChoice);
  }

  void assign_vector_targets(std::string & target) { vector_targets.push_back(target); }

  //----step4----
  void assign_hashmap_specified(std::string key, size_t value) {
    if (hashmap_specified.find(key) == hashmap_specified.end()) {
      //it's easier to use insert({key, value}) in c++11
      hashmap_specified.insert(std::pair<std::string, size_t>(key, value));
    }
    else {
      hashmap_specified[key] = value;
    }
  }

  void printContent() { std::cout << get_content() << "\n"; };
  void printChoices();

  void assign_choice_text(size_t i, std::string & text) {
    vector_choices[i].assign_text(text);
  }
};

class Story {
 private:
  // A story has many pages
  std::vector<Page> vector_pages;
  // all the specified pair of pages
  std::map<std::string, size_t> pages_hashmap_specified;

 public:
  Story() : vector_pages(), pages_hashmap_specified() {}
  Story(std::vector<Page> & vp);
  bool verify();
  void printStory();
  void printTurnPages(size_t startPage);
  std::vector<size_t> find_win_pages();
  std::vector<std::vector<size_t> > findWinPath();
  void printWinPaths();
};
