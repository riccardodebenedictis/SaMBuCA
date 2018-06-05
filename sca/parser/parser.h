#pragma once

#include "lexer.h"
#include "ast.h"
#include <vector>

namespace sca
{

class parser
{
protected:
  lexer lex;                // the current lexer..
  token *tk = nullptr;      // the current lookahead token..
  std::vector<token *> tks; // all the tokens parsed so far..
  size_t pos = 0;           // the current position within tks'..

public:
  parser(std::istream &is);
  parser(const parser &orig) = delete;
  virtual ~parser();

  virtual ast::compilation_unit *parse() = 0;

protected:
  token *next();
  bool match(const symbol &sym);
  void backtrack(const size_t &p);

  ast::requirement *req_def();
  std::vector<ast::variable *> typed_list_variable(const std::map<std::string, ast::type *> &tps);

  void error(const std::string &err);
};

class domain_parser : public parser
{
public:
  domain_parser(std::istream &is);
  domain_parser(const domain_parser &orig) = delete;
  virtual ~domain_parser();

  ast::domain *parse() override;
};

class problem_parser : public parser
{
private:
  ast::domain &dom;

public:
  problem_parser(std::istream &is, ast::domain &dom);
  problem_parser(const problem_parser &orig) = delete;
  virtual ~problem_parser();

  ast::problem *parse() override;
};
} // namespace sca