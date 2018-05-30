#pragma once

#include "lexer.h"
#include <vector>

namespace sca
{

namespace ast
{
class domain;
class problem;
} // namespace ast

class parser
{
private:
  lexer lex;                // the current lexer..
  token *tk = nullptr;      // the current lookahead token..
  std::vector<token *> tks; // all the tokens parsed so far..
  size_t pos = 0;           // the current position within tks'..

public:
  parser(std::istream &is);
  parser(const parser &orig) = delete;
  virtual ~parser();

  ast::domain *parse_domain();
  ast::problem *parse_problem();

private:
  token *next();
  bool match(const symbol &sym);
  void backtrack(const size_t &p);

  void error(const std::string &err);
};
} // namespace sca