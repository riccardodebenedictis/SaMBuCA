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

predicate::predicate(const std::string &n, const std::map<std::string, variable *> &vars) : name(n), variables(vars) {}
predicate::~predicate()
{
    for (auto &&v : variables)
        delete v.second;
}

domain::domain(const std::string &name, const std::vector<requirement *> &reqs, const std::map<std::string, type *> &tps, const std::map<std::string, constant *> &cnsts, const std::map<std::string, predicate *> preds) : compilation_unit(name), requirements(reqs), types(tps), constants(cnsts), predicates(preds) {}
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
}

problem::problem(const std::string &problem_name, std::string &domain_name) : compilation_unit(problem_name), domain_name(domain_name) {}
problem::~problem() {}
} // namespace ast
} // namespace sca
