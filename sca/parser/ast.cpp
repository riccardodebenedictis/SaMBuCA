#include "ast.h"

namespace sca
{

namespace ast
{
compilation_unit::compilation_unit(const std::string &name) : name(name) {}
compilation_unit::~compilation_unit() {}

requirement::requirement(const std::string &name) : name(name) {}
requirement::~requirement() {}

type::type(const std::string &name) : name(name) {}
type::~type()
{
    for (auto &&i : instances)
        delete i.second;
}

instance::instance(const std::string &n, type &tp) : name(n), tp(tp) { tp.instances.insert({n, this}); }
instance::~instance() {}

constant::constant(const std::string &name, type &tp) : instance(name, tp) {}
constant::~constant() {}

object::object(const std::string &name, type &tp) : instance(name, tp) {}
object::~object() {}

variable::variable(const std::string &n, const type &tp) : name(n), tp(tp) {}
variable::~variable() {}

predicate::predicate(const std::string &n, const std::vector<variable *> &vars) : name(n), variables(vars) {}
predicate::~predicate()
{
    for (auto &&v : variables)
        delete v;
}

function::function(const std::string &n, const std::vector<variable *> &vars, const type &tp) : name(n), variables(vars), tp(tp) {}
function::~function()
{
    for (auto &&v : variables)
        delete v;
}

function_term::function_term(const function &fn, const std::vector<term *> &terms) : fn(fn), terms(terms) {}
function_term::~function_term() {}

predicate_term::predicate_term(const predicate &pred, const std::vector<term *> &terms) : pred(pred), terms(terms) {}
predicate_term::~predicate_term() {}

constant_term::constant_term(const constant &cnst) : cnst(cnst) {}
constant_term::~constant_term() {}

variable_term::variable_term(const variable &var) : var(var) {}
variable_term::~variable_term() {}

always_term::always_term(const term &trm) : trm(trm) {}
always_term::~always_term() {}

always_within_term::always_within_term(const double within, const term &first_trm, const term &second_trm) : within(within), first_trm(first_trm), second_trm(second_trm) {}
always_within_term::~always_within_term() {}

and_term::and_term(const std::vector<term *> &trms) : terms(trms) {}
and_term::~and_term() {}

assign_op_term::assign_op_term(const assign_op &op, const function_term &fnctn_trm, const term &trm) : op(op), fnctn_trm(fnctn_trm), trm(trm) {}
assign_op_term::~assign_op_term() {}

at_end_term::at_end_term(const term &trm) : trm(trm) {}
at_end_term::~at_end_term() {}

at_most_once_term::at_most_once_term(const term &trm) : trm(trm) {}
at_most_once_term::~at_most_once_term() {}

at_start_term::at_start_term(const term &trm) : trm(trm) {}
at_start_term::~at_start_term() {}

at_term::at_term(const double &at, const predicate_term &trm) : at(at), trm(trm) {}
at_term::~at_term() {}

comparison_term::comparison_term(const comparison &cmp, const term &first_trm, const term &second_trm) : cmp(cmp), first_trm(first_trm), second_trm(second_trm) {}
comparison_term::~comparison_term() {}

eq_term::eq_term(const term &first_trm, const term &second_trm) : first_trm(first_trm), second_trm(second_trm) {}
eq_term::~eq_term() {}

exists_term::exists_term(const std::vector<variable *> &vars, const term &trm) : vars(vars), trm(trm) {}
exists_term::~exists_term() {}

for_all_term::for_all_term(const std::vector<variable *> &vars, const term &trm) : vars(vars), trm(trm) {}
for_all_term::~for_all_term() {}

hold_after_term::hold_after_term(const double &after, const term &trm) : after(after), trm(trm) {}
hold_after_term::~hold_after_term() {}

hold_during_term::hold_during_term(const double &start, const double &end, const term &trm) : start(start), end(end), trm(trm) {}
hold_during_term::~hold_during_term() {}

minus_term::minus_term(const term &trm) : trm(trm) {}
minus_term::~minus_term() {}

number_term::number_term(const double &number) : number(number) {}
number_term::~number_term() {}

op_term::op_term(const op &o, const std::vector<term *> &trms) : o(o), terms(trms) {}
op_term::~op_term() {}

or_term::or_term(const std::vector<term *> &trms) : terms(trms) {}
or_term::~or_term() {}

over_all_term::over_all_term(const term &trm) : trm(trm) {}
over_all_term::~over_all_term() {}

preference_term::preference_term(const std::string &name, const term &trm) : name(name), trm(trm) {}
preference_term::~preference_term() {}

sometime_after_term::sometime_after_term(const term &first_trm, const term &second_trm) : first_trm(first_trm), second_trm(second_trm) {}
sometime_after_term::~sometime_after_term() {}

sometime_before_term::sometime_before_term(const term &first_trm, const term &second_trm) : first_trm(first_trm), second_trm(second_trm) {}
sometime_before_term::~sometime_before_term() {}

sometime_term::sometime_term(const term &trm) : trm(trm) {}
sometime_term::~sometime_term() {}

when_term::when_term(const term &condition, const term &effect) : condition(condition), effect(effect) {}
when_term::~when_term() {}

within_term::within_term(const double &within, const term &trm) : within(within), trm(trm) {}
within_term::~within_term() {}

domain::domain(const std::string &name, const std::vector<requirement *> &reqs, const std::map<std::string, type *> &tps, const std::map<std::string, constant *> &cnsts, const std::map<std::string, predicate *> preds, const std::map<std::string, function *> fncs) : compilation_unit(name), requirements(reqs), types(tps), constants(cnsts), predicates(preds), functions(fncs) {}
domain::~domain()
{
    for (auto &&r : requirements)
        delete r;
    for (auto &&t : types)
        delete t.second;
    for (auto &&c : constants)
        delete c.second;
    for (auto &&p : predicates)
        delete p.second;
    for (auto &&f : functions)
        delete f.second;
}

problem::problem(const std::string &problem_name, std::string &domain_name) : compilation_unit(problem_name), domain_name(domain_name) {}
problem::~problem() {}
} // namespace ast
} // namespace sca
