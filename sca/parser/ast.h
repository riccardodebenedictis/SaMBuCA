#pragma once

namespace sca
{

namespace ast
{

class domain
{
private:
  const std::string name;

public:
  domain(const std::string &name) : name(name) {}
  ~domain() {}
};

class problem
{
private:
  const std::string problem_name;
  const std::string domain_name;

public:
  problem(const std::string &problem_name, std::string &domain_name) : problem_name(problem_name), domain_name(domain_name) {}
  ~problem() {}
};
} // namespace ast

} // namespace sca