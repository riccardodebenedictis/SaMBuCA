#pragma once

#include <string>
#include <vector>
#include <map>

namespace sca
{

class parser;

namespace ast
{

class requirement
{
private:
  const std::string name;

public:
  requirement(const std::string &name) : name(name) {}
  ~requirement() {}

  std::string get_name() const { return name; }
};

class type
{
  friend class sca::parser;

private:
  const std::string name;
  type *supertype;

public:
  type(const std::string &name) : name(name) {}
  ~type() {}

  std::string get_name() const { return name; }
  type *get_supertype() const { return supertype; }
};

class domain
{
private:
  const std::string name;
  const std::vector<requirement *> requirements;
  const std::map<std::string, type *> types;

public:
  domain(const std::string &name, const std::vector<requirement *> &reqs, const std::map<std::string, type *> &tps) : name(name), requirements(reqs), types(tps) {}
  ~domain() {}

  std::string get_name() const { return name; }
  std::vector<requirement *> const get_requirements() { return requirements; }
  std::map<std::string, type *> get_types() const { return types; }
};

class problem
{
private:
  const std::string problem_name;
  const std::string domain_name;

public:
  problem(const std::string &problem_name, std::string &domain_name) : problem_name(problem_name), domain_name(domain_name) {}
  ~problem() {}

  std::string get_problem_name() const { return problem_name; }
  std::string get_domain_name() const { return domain_name; }
};
} // namespace ast

} // namespace sca