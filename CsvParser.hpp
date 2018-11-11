#ifndef _CSVPARSER_HPP_
#define _CSVPARSER_HPP_

#include <boost/foreach.hpp>
#include <boost/tokenizer.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>

namespace CsvParser {

class Row {

public:
  Row();
  ~Row();

public:
  // setter
  void push_back(const std::string &);

  // getter
  uint32_t size() const;
  template <typename T> const T getValue(uint32_t pos) const;

  // operator
  const std::string operator[](uint32_t) const;
  friend std::ostream &operator<<(std::ostream &os, const Row &row);
  friend std::ostringstream &operator<<(std::ostringstream &os, const Row &row);

private:
  std::vector<std::string> f_Values;
};

class Parser {

public:
  Parser(const char *, const char delim = ',');
  ~Parser();

public:
  bool parse();
  void parseHeader(std::string &);
  void parseContent(std::string &);
  bool checkContent() const noexcept;

  // gettters
  Row *getRow(uint32_t row) const;
  uint32_t countRow() const;
  uint32_t countColumn() const;
  std::vector<std::string> getHeader();
  const std::string getHeaderElement(uint32_t pos);
  const std::string &getFileName() const;
  const std::string dumpAllData() const noexcept;
  const std::string toString() const noexcept;

  // operator
  Row &operator[](uint32_t row) const;

private:
  const std::string f_FileName;
  const char f_Delim;
  bool f_IsParsed;
  std::vector<std::string> f_Header;
  std::vector<Row *> f_Content;
};
}

#endif /* _CSVPARSER_HPP_ */
