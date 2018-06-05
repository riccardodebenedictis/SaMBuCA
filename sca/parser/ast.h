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
class function_term;

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
  const std::vector<variable *> variables;

public:
  predicate(const std::string &n, const std::vector<variable *> &vars);
  ~predicate();

  std::string get_name() const { return name; }
  std::vector<variable *> get_variables() const { return variables; }
};

class function
{
private:
  const std::string name;
  const std::vector<variable *> variables;
  const type &tp;

public:
  function(const std::string &n, const std::vector<variable *> &vars, const type &tp);
  ~function();

  std::string get_name() const { return name; }
  std::vector<variable *> get_variables() const { return variables; }
  const type &get_type() const { return tp; }
};

class term
{
public:
  term() {}
  virtual ~term() {}
};

class function_term : public term
{
private:
  const function fn;
  const std::vector<term *> terms;

public:
  function_term(const function &fn, const std::vector<term *> &terms);
  ~function_term();

  std::vector<term *> get_terms() const { return terms; }
};

class predicate_term : public term
{
private:
  const predicate fn;
  const std::vector<term *> terms;

public:
  predicate_term(const predicate &fn, const std::vector<term *> &terms);
  ~predicate_term();

  std::vector<term *> get_terms() const { return terms; }
};

class constant_term : public term
{
private:
  const constant cnst;

public:
  constant_term(const constant &cnst);
  ~constant_term();

  const constant &get_constant() const { return cnst; }
};

class variable_term : public term
{
private:
  const variable var;

public:
  variable_term(const variable &var);
  ~variable_term();

  const variable &get_variable() const { return var; }
};

class always_term : public term
{
private:
  const term trm;

public:
  always_term(const term &trm);
  ~always_term();

  const term &get_term() const { return trm; }
};

class always_within_term : public term
{
private:
  const double within;
  const term first_trm;
  const term second_trm;

public:
  always_within_term(const double within, const term &first_trm, const term &second_trm);
  ~always_within_term();

  const double &get_within() const { return within; }
  const term &get_first_term() const { return first_trm; }
  const term &get_second_term() const { return second_trm; }
};

class and_term : public term
{
private:
  const std::vector<term *> terms;

public:
  and_term(const std::vector<term *> &trms);
  ~and_term() override;

  std::vector<term *> get_terms() const { return terms; }
};

enum assign_op
{
  assign,
  scale_up,
  scale_down,
  increase,
  decrease
};

class assign_op_term : public term
{
private:
  const assign_op op;
  const function_term fnctn_trm;
  const term trm;

public:
  assign_op_term(const assign_op op, const function_term &fnctn_trm, const term &trm);
  ~assign_op_term();

  const assign_op &get_op() const { return op; }
  const term &get_function_term() const { return fnctn_trm; }
  const term &get_term() const { return trm; }
};

class at_end_term : public term
{
private:
  const term trm;

public:
  at_end_term(const term &trm);
  ~at_end_term();

  const term &get_term() const { return trm; }
};

class at_most_once_term : public term
{
private:
  const term trm;

public:
  at_most_once_term(const term &trm);
  ~at_most_once_term();

  const term &get_term() const { return trm; }
};

class at_start_term : public term
{
private:
  const term trm;

public:
  at_start_term(const term &trm);
  ~at_start_term();

  const term &get_term() const { return trm; }
};

class at_term : public term
{
private:
  const double at;
  const predicate_term trm;

public:
  at_term(const double &at, const predicate_term &trm);
  ~at_term();

  const double get_at() const { return at; }
  const predicate_term &get_term() const { return trm; }
};

enum comparison
{
  Gt,
  Lt,
  Eq,
  GEq,
  LEq
};

class comparison_term : public term
{
private:
  const comparison cmp;
  const term first_trm;
  const term second_trm;

public:
  comparison_term(const comparison &cmp, const term &first_trm, const term &second_trm);
  ~comparison_term();

  const comparison &get_comparison() const { return cmp; }
  const term &get_first_term() const { return first_trm; }
  const term &get_second_term() const { return second_trm; }
};

class eq_term : public term
{
private:
  const term first_trm;
  const term second_trm;

public:
  eq_term(const term &first_trm, const term &second_trm);
  ~eq_term();

  const term &get_first_term() const { return first_trm; }
  const term &get_second_term() const { return second_trm; }
};

class exists_term : public term
{
private:
  const std::vector<variable *> vars;
  const term trm;

public:
  exists_term(const std::vector<variable *> &vars, const term &trm);
  ~exists_term();

  const std::vector<variable *> &get_variables() const { return vars; }
  const term &get_term() const { return trm; }
};

class for_all_term : public term
{
private:
  const std::vector<variable *> vars;
  const term trm;

public:
  for_all_term(const std::vector<variable *> &vars, const term &trm);
  ~for_all_term();

  const std::vector<variable *> &get_variables() const { return vars; }
  const term &get_term() const { return trm; }
};

class hold_after_term : public term
{
private:
  const double after;
  const term trm;

public:
  hold_after_term(const double &after, const term &trm);
  ~hold_after_term();

  const double get_after() const { return after; }
  const term &get_term() const { return trm; }
};

class hold_during_term : public term
{
private:
  const double start;
  const double end;
  const term trm;

public:
  hold_during_term(const double &start, const double &end, const term &trm);
  ~hold_during_term();

  const double get_start() const { return start; }
  const double get_end() const { return end; }
  const term &get_term() const { return trm; }
};

class minus_term : public term
{
private:
  const term trm;

public:
  minus_term(const term &trm);
  ~minus_term();

  const term &get_term() const { return trm; }
};

class number_term : public term
{
private:
  const double number;

public:
  number_term(const double &number);
  ~number_term();

  const double get_number() const { return number; }
};

enum op
{
  add,
  sub,
  mul,
  div
};

class op_term : public term
{
private:
  const op o;
  const std::vector<term *> terms;

public:
  op_term(const op &o, const std::vector<term *> &trms);
  ~op_term();

  const double get_op() const { return o; }
  std::vector<term *> get_terms() const { return terms; }
};

class or_term : public term
{
private:
  const std::vector<term *> terms;

public:
  or_term(const std::vector<term *> &trms);
  ~or_term();

  std::vector<term *> get_terms() const { return terms; }
};

class over_all_term : public term
{
private:
  const term trm;

public:
  over_all_term(const term &trm);
  ~over_all_term();

  const term &get_term() const { return trm; }
};

class preference_term : public term
{
private:
  const std::string name;
  const term trm;

public:
  preference_term(const std::string &name, const term &trm);
  ~preference_term();

  const std::string get_name() const { return name; }
  const term &get_term() const { return trm; }
};

class sometime_after_term : public term
{
private:
  const term first_trm;
  const term second_trm;

public:
  sometime_after_term(const term &first_trm, const term &second_trm);
  ~sometime_after_term();

  const term &get_first_term() const { return first_trm; }
  const term &get_second_term() const { return second_trm; }
};

class sometime_before_term : public term
{
private:
  const term first_trm;
  const term second_trm;

public:
  sometime_before_term(const term &first_trm, const term &second_trm);
  ~sometime_before_term();

  const term &get_first_term() const { return first_trm; }
  const term &get_second_term() const { return second_trm; }
};

class sometime_term : public term
{
private:
  const term trm;

public:
  sometime_term(const term &trm);
  ~sometime_term();

  const term &get_term() const { return trm; }
};

class when_term : public term
{
private:
  const term condition;
  const term effect;

public:
  when_term(const term &condition, const term &effect);
  ~when_term();

  const term &get_condition() const { return condition; }
  const term &get_effect() const { return effect; }
};

class within_term : public term
{
private:
  const double within;
  const term trm;

public:
  within_term(const double &within, const term &trm);
  ~within_term();

  const double get_within() const { return within; }
  const term &get_term() const { return trm; }
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