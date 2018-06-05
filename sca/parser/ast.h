#pragma once

#include <string>
#include <vector>
#include <map>

namespace sca
{

class domain_parser;

namespace ast
{

class instance;

class compilation_unit
{
private:
  const std::string name;

public:
  compilation_unit(const std::string &name);
  ~compilation_unit();

  std::string get_name() const { return name; }
};

class requirement
{
private:
  const std::string name;

public:
  requirement(const std::string &name);
  ~requirement();

  std::string get_name() const { return name; }
};

class type
{
  friend class instance;
  friend class sca::domain_parser;

private:
  const std::string name;
  type *supertype;
  std::map<std::string, instance *> instances;

public:
  type(const std::string &name);
  ~type();

  std::string get_name() const { return name; }
  type *get_supertype() const { return supertype; }
  std::map<std::string, instance *> get_instances() const { return instances; }
  instance &get_instance(const std::string &n) const { return *instances.at(n); }
};

class instance
{
private:
  const std::string name;
  const type &tp;

public:
  instance(const std::string &n, type &tp);
  virtual ~instance();

  std::string get_name() const { return name; }
  const type &get_type() const { return tp; }
};

class constant : public instance
{
public:
  constant(const std::string &name, type &tp);
  ~constant() override;
};

class object : public instance
{
public:
  object(const std::string &name, type &tp);
  ~object() override;
};

class variable
{
private:
  const std::string name;
  const type &tp;

public:
  variable(const std::string &n, const type &tp);
  ~variable();

  std::string get_name() const { return name; }
  const type &get_type() const { return tp; }
};

class predicate
{
private:
  const std::string name;
  const std::map<std::string, variable *> variables;

public:
  predicate(const std::string &n, const std::map<std::string, variable *> &vars);
  ~predicate();

  std::string get_name() const { return name; }
  std::map<std::string, variable *> get_variables() const { return variables; }
  variable &get_variable(const std::string &n) const { return *variables.at(n); }
};

class function
{
private:
  const std::string name;
  const std::map<std::string, variable *> variables;
  const type &tp;

public:
  function(const std::string &n, const std::map<std::string, variable *> &vars, const type &tp);
  ~function();

  std::string get_name() const { return name; }
  std::map<std::string, variable *> get_variables() const { return variables; }
  variable &get_variable(const std::string &n) const { return *variables.at(n); }
  const type &get_type() const { return tp; }
};

class domain : public compilation_unit
{
private:
  const std::vector<requirement *> requirements;
  const std::map<std::string, type *> types;
  const std::map<std::string, constant *> constants;
  const std::map<std::string, predicate *> predicates;
  const std::map<std::string, function *> functions;

public:
  domain(const std::string &name, const std::vector<requirement *> &reqs, const std::map<std::string, type *> &tps, const std::map<std::string, constant *> &cnsts, const std::map<std::string, predicate *> preds, const std::map<std::string, function *> fncs);
  ~domain();

  std::vector<requirement *> const get_requirements() { return requirements; }
  std::map<std::string, type *> get_types() const { return types; }
  type &get_type(const std::string &n) const { return *types.at(n); }
  std::map<std::string, constant *> get_constants() const { return constants; }
  constant &get_constant(const std::string &n) const { return *constants.at(n); }
  std::map<std::string, predicate *> get_predicates() const { return predicates; }
  predicate &get_predicate(const std::string &n) const { return *predicates.at(n); }
  std::map<std::string, function *> get_functions() const { return functions; }
  function &get_function(const std::string &n) const { return *functions.at(n); }
};

class problem : public compilation_unit
{
private:
  const std::string domain_name;

public:
  problem(const std::string &problem_name, std::string &domain_name);
  ~problem();

  std::string get_domain_name() const { return domain_name; }
};
} // namespace ast

} // namespace sca