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
  compilation_unit(const std::string &name) : name(name) {}
  ~compilation_unit() {}

  std::string get_name() const { return name; }
};

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
  friend class instance;
  friend class sca::domain_parser;

private:
  const std::string name;
  type *supertype;
  std::map<std::string, instance *> instances;

public:
  type(const std::string &name) : name(name) {}
  ~type() {}

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
  instance(const std::string &n, type &tp) : name(n), tp(tp) { tp.instances.insert({n, this}); }
  ~instance() {}

  std::string get_name() const { return name; }
  const type &get_type() const { return tp; }
};

class constant : public instance
{
public:
  constant(const std::string &name, type &tp) : instance(name, tp) {}
  ~constant() {}
};

class object : public instance
{
public:
  object(const std::string &name, type &tp) : instance(name, tp) {}
  ~object() {}
};

class variable
{
private:
  const std::string name;
  const type &tp;

public:
  variable(const std::string &n, const type &tp) : name(n), tp(tp) {}
  ~variable() {}

  std::string get_name() const { return name; }
  const type &get_type() const { return tp; }
};

class domain : public compilation_unit
{
private:
  const std::vector<requirement *> requirements;
  const std::map<std::string, type *> types;
  const std::map<std::string, constant *> constants;

public:
  domain(const std::string &name, const std::vector<requirement *> &reqs, const std::map<std::string, type *> &tps, const std::map<std::string, constant *> &cnsts) : compilation_unit(name), requirements(reqs), types(tps), constants(cnsts) {}
  ~domain() {}

  std::vector<requirement *> const get_requirements() { return requirements; }
  std::map<std::string, type *> get_types() const { return types; }
  type &get_type(const std::string &n) const { return *types.at(n); }
  std::map<std::string, constant *> get_constants() const { return constants; }
  constant &get_constant(const std::string &n) const { return *constants.at(n); }
};

class problem : public compilation_unit
{
private:
  const std::string domain_name;

public:
  problem(const std::string &problem_name, std::string &domain_name) : compilation_unit(problem_name), domain_name(domain_name) {}
  ~problem() {}

  std::string get_domain_name() const { return domain_name; }
};
} // namespace ast

} // namespace sca