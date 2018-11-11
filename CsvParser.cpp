#include "CsvParser.hpp"

namespace CsvParser {

/*
 *  Row class
 */

Row::Row() {}

Row::~Row() {}

void Row::push_back(const std::string &val) { this->f_Values.push_back(val); }

uint32_t Row::size() const { return this->f_Values.size(); }

template <typename T> const T Row::getValue(uint32_t pos) const {
  T retval;
  std::stringstream ss;
  ss << this->f_Values[pos];
  ss >> retval;
  return retval;
}

const std::string Row::operator[](uint32_t pos) const {
  if (this->f_Values.size() < pos) {
    return "";
  }
  return this->f_Values[pos];
}

std::ostream &operator<<(std::ostream &os, const Row &row) {
  for (uint32_t i = 0; i < row.f_Values.size(); i++)
    os << row.f_Values[i] << " | ";
  return os;
}

std::ostringstream &operator<<(std::ostringstream &oss, const Row &row) {
  for (uint32_t i = 0; i < row.f_Values.size(); i++)
    oss << row.f_Values[i] << " | ";
  return oss;
}

/*
 *  Parser class
 */

Parser::Parser(const char *fileName, const char delim)
    : f_FileName(fileName), f_Delim(delim), f_IsParsed(false) {
  this->f_Content.reserve(RESERVE_ROW);
}

Parser::~Parser() {
  for (Row *row : this->f_Content) {
    delete row;
  }
}

bool Parser::parse() {
  std::ifstream ifs(this->f_FileName.c_str());
  std::string line;
  bool IsParsedHeader = false;

  if (ifs.good()) {
    while (std::getline(ifs, line)) {
      if (line == "") {
        continue;
      }

      if (!IsParsedHeader) {
        this->parseHeader(line);
        IsParsedHeader = true;
      } else {
        this->parseContent(line);
      }
    }
  } else {
    std::cout << "Error! ";
    std::cout << this->f_FileName << "can not open.";
    std::cout << std::endl;
  }
  ifs.close();

  return this->checkContent();
}

void Parser::parseHeader(std::string &line) {
  boost::char_separator<char> sep(",");
  boost::tokenizer<boost::char_separator<char>> tokens(line, sep);
  for (std::string token : tokens) {
    this->f_Header.push_back(token);
  }
}

void Parser::parseContent(std::string &line) {
  boost::char_separator<char> sep(",");
  boost::tokenizer<boost::char_separator<char>> tokens(line, sep);
  Row *row = new Row();
  for (std::string token : tokens) {
    row->push_back(token);
  }
  this->f_Content.push_back(row);
}

bool Parser::checkContent() const noexcept {
  for (Row *row : this->f_Content) {
    if (this->f_Header.size() != row->size()) {
      return false;
    }
  }
  return true;
}

Row *Parser::getRow(uint32_t rowpos) const {
  if (this->f_Content.size() > rowpos) {
    return this->f_Content[rowpos];
  }
  return nullptr;
}

uint32_t Parser::countRow() const { return this->f_Content.size(); }

uint32_t Parser::countColumn() const { return this->f_Header.size(); }

std::vector<std::string> Parser::getHeader() { return this->f_Header; }

const std::string Parser::getHeaderElement(uint32_t pos) {
  if (this->f_Header.size() > pos) {
    return this->f_Header[pos];
  }
  return "";
}

const std::string Parser::dumpAllData() const noexcept {
  std::ostringstream oss;
  for (Row *row : this->f_Content) {
    oss << *row << std::endl;
  }
  return oss.str();
}

const std::string Parser::toString() const noexcept {
  std::ostringstream oss;
  oss << "FileName:[" << this->f_FileName << "]" << std::endl;
  oss << "Delimiter:[" << this->f_Delim << "]" << std::endl;
  oss << "NumOfColumn[" << this->countColumn() << "]" << std::endl;
  oss << "NumOfRow:[" << this->countRow() << "]" << std::endl;
  return oss.str();
}
}

int main() {
  /* Row class test
  CsvParser::Row row;
  row.push("hoge");
  row.push("foo");
  row.push("1.1");

  for (int i = 0; i < row.size(); i++) {
    std::cout << row[i] << std::endl;
  }
  std::cout << row.getValue<std::string>(1) << std::endl;
  std::cout << row.getValue<int>(3) << std::endl;
  std::cout << row.getValue<int>(1) << std::endl;
  std::cout << row.getValue<double>(1) << std::endl;
  std::cout << row.getValue<double>(2) << std::endl;
  */

  // Parser class test
  CsvParser::Parser parser = CsvParser::Parser("test.csv", ',');
  parser.parse();
  if (!parser.checkContent()) {
    std::cout << "Error! checkContent" << std::endl;
  }

  std::cout << parser.toString();
  std::cout << parser.dumpAllData();

  return 0;
}
