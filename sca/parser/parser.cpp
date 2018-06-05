#include "parser.h"
#include <algorithm>

namespace sca
{

parser::parser(std::istream &is) : lex(is) {}

parser::~parser() {}

ast::requirement *parser::req_def()
{
    switch (tk->sym)
    {
    case STRIPS_ID:
        match(STRIPS_ID);
        return new ast::requirement(":strips");
    case TYPING_ID:
        match(TYPING_ID);
        return new ast::requirement(":typing");
    case NEGATIVE_PRECONDITIONS_ID:
        match(NEGATIVE_PRECONDITIONS_ID);
        return new ast::requirement(":negative-preconditions");
    case DISJUNCTIVE_PRECONDITIONS_ID:
        match(DISJUNCTIVE_PRECONDITIONS_ID);
        return new ast::requirement(":disjunctive-preconditions");
    case EQUALITY_ID:
        match(EQUALITY_ID);
        return new ast::requirement(":equality");
    case EXISTENTIAL_PRECONDITIONS_ID:
        match(EXISTENTIAL_PRECONDITIONS_ID);
        return new ast::requirement(":existential-preconditions");
    case UNIVERSAL_PRECONDITIONS_ID:
        match(UNIVERSAL_PRECONDITIONS_ID);
        return new ast::requirement(":universal-preconditions");
    case QUANTIFIED_PRECONDITIONS_ID:
        match(QUANTIFIED_PRECONDITIONS_ID);
        return new ast::requirement(":quantified-preconditions");
    case CONDITIONAL_EFFECTS_ID:
        match(CONDITIONAL_EFFECTS_ID);
        return new ast::requirement(":conditional-effects");
    case FLUENTS_ID:
        match(FLUENTS_ID);
        return new ast::requirement(":fluents");
    case NUMERIC_FLUENTS_ID:
        match(NUMERIC_FLUENTS_ID);
        return new ast::requirement(":numeric-fluents");
    case ADL_ID:
        match(ADL_ID);
        return new ast::requirement(":adl");
    case DURATIVE_ACTIONS_ID:
        match(DURATIVE_ACTIONS_ID);
        return new ast::requirement(":durative-actions");
    case DURATION_INEQUALITIES_ID:
        match(DURATION_INEQUALITIES_ID);
        return new ast::requirement(":duration-inequalities");
    case CONTINUOUS_EFFECTS_ID:
        match(CONTINUOUS_EFFECTS_ID);
        return new ast::requirement(":continuous-effects");
    case DERIVED_PREDICATES_ID:
        match(DERIVED_PREDICATES_ID);
        return new ast::requirement(":derived-predicates");
    case TIMED_INITIAL_LITERALS_ID:
        match(TIMED_INITIAL_LITERALS_ID);
        return new ast::requirement(":timed-initial-literals");
    case PREFERENCES_ID:
        match(PREFERENCES_ID);
        return new ast::requirement(":preferences");
    case CONSTRAINTS_ID:
        match(CONSTRAINTS_ID);
        return new ast::requirement(":constraints");
    case ACTION_COSTS_ID:
        match(ACTION_COSTS_ID);
        return new ast::requirement(":action-costs");
    default:
        error("expected either ':strips' or ':typing' or ':negative-preconditions' or ':disjunctive-preconditions' or ':equality' or ':existential-preconditions' or ':universal-preconditions' or ':quantified-preconditions' or ':conditional-effects' or ':fluents' or ':numeric-fluents' or ':adl' or ':durative-actions' or ':duration-inequalities' or ':conditional-effects' or ':derived-predicates' or ':timed-initial-literals' or ':preferences' or ':constraints' or ':action-costs'..");
        return nullptr;
    }
}

std::map<std::string, ast::variable *> parser::typed_list_variable(const std::map<std::string, ast::type *> &tps)
{
    ast::type &o_tp = *tps.at("object");
    std::vector<std::string> c_vars;
    std::map<std::string, ast::variable *> vars;
    while (!match(RPAREN_ID))
    {
        if (!match(ID_ID))
            error("expected identifier..");
        c_vars.push_back(static_cast<id_token *>(tks[pos - 2])->id);

        if (match(MINUS_ID)) // we have a supertype..
            if (match(OBJECT_ID))
            {
                for (const std::string &var : c_vars)
                    vars.insert({var, new ast::variable(var, o_tp)});
                c_vars.clear();
            }
            else
            {
                if (!match(ID_ID))
                    error("expected identifier..");
                std::string ctn = static_cast<id_token *>(tks[pos - 2])->id;
                for (const std::string &var : c_vars)
                    vars.insert({var, new ast::variable(var, *tps.at(ctn))});
                c_vars.clear();
            }
    }
    backtrack(pos - 1);
    for (const std::string &var : c_vars)
        vars.insert({var, new ast::variable(var, o_tp)});
    return vars;
}

token *parser::next()
{
    while (pos >= tks.size())
    {
        token *c_tk = lex.next();
        tks.push_back(c_tk);
    }
    return tks[pos++];
}

bool parser::match(const symbol &sym)
{
    if (tk->sym == sym)
    {
        tk = next();
        return true;
    }
    else
        return false;
}

void parser::backtrack(const size_t &p)
{
    pos = p;
    tk = tks[pos - 1];
}

void parser::error(const std::string &err) { throw std::invalid_argument("[" + std::to_string(tk->start_line) + ", " + std::to_string(tk->start_pos) + "] " + err); }

domain_parser::domain_parser(std::istream &is) : parser(is) {}

domain_parser::~domain_parser() {}

ast::domain *domain_parser::parse()
{
    tk = next();

    std::string n;
    std::vector<ast::requirement *> reqs;
    std::map<std::string, ast::type *> tps;
    std::map<std::string, ast::constant *> cnsts;
    std::map<std::string, ast::predicate *> preds;

    if (!match(LPAREN_ID))
        error("expected '('..");

    if (!match(DEFINE_ID))
        error("expected 'define'..");

    if (!match(LPAREN_ID))
        error("expected '('..");

    if (!match(DOMAIN_ID))
        error("expected 'domain'..");

    if (!match(ID_ID))
        error("expected identifier..");
    n = static_cast<id_token *>(tks[pos - 2])->id;

    if (!match(RPAREN_ID))
        error("expected ')'..");

    size_t c_pos = pos;
    if (match(LPAREN_ID))
        if (match(REQUIREMENTS_ID)) // the domain requirements..
            do
            {
                reqs.push_back(req_def());
            } while (!match(RPAREN_ID));
        else
            backtrack(c_pos);

    if (match(LPAREN_ID))
        if (match(TYPES_ID)) // the domain types..
        {
            if (std::none_of(reqs.begin(), reqs.end(), [](ast::requirement *r) { return r->get_name() == ":typing"; }))
                error("expected ':typing' requirement..");

            ast::type *o_tp = new ast::type("object");
            tps.insert({o_tp->get_name(), o_tp});
            std::vector<ast::type *> c_tps;
            while (!match(RPAREN_ID))
            {
                if (!match(ID_ID))
                    error("expected identifier..");
                std::string tn = static_cast<id_token *>(tks[pos - 2])->id;
                auto c_tp = tps.find(tn);
                if (c_tp == tps.end())
                    c_tp = tps.insert({tn, new ast::type(tn)}).first;
                c_tps.push_back((*c_tp).second);

                if (match(MINUS_ID)) // we have a supertype..
                    if (match(OBJECT_ID))
                    {
                        for (ast::type *t : c_tps)
                            t->supertype = o_tp;
                        c_tps.clear();
                    }
                    else
                    {
                        if (!match(ID_ID))
                            error("expected identifier..");
                        std::string stn = static_cast<id_token *>(tks[pos - 2])->id;
                        auto c_st = tps.find(stn);
                        if (c_st == tps.end())
                            c_st = tps.insert({stn, new ast::type(stn)}).first;

                        for (ast::type *t : c_tps)
                            t->supertype = (*c_st).second;
                        c_tps.clear();
                    }
            }
            for (ast::type *t : c_tps)
                t->supertype = o_tp;
        }
        else
            backtrack(c_pos);

    if (match(LPAREN_ID))
        if (match(CONSTANTS_ID)) // the domain constants..
        {
            ast::type &o_tp = *tps["object"];
            std::vector<std::string> c_cnsts;
            while (!match(RPAREN_ID))
            {
                if (!match(ID_ID))
                    error("expected identifier..");
                c_cnsts.push_back(static_cast<id_token *>(tks[pos - 2])->id);

                if (match(MINUS_ID)) // we have a supertype..
                    if (match(OBJECT_ID))
                    {
                        for (const std::string &cnt : c_cnsts)
                            cnsts.insert({cnt, new ast::constant(cnt, o_tp)});
                        c_cnsts.clear();
                    }
                    else
                    {
                        if (!match(ID_ID))
                            error("expected identifier..");
                        std::string ctn = static_cast<id_token *>(tks[pos - 2])->id;
                        for (const std::string &cnt : c_cnsts)
                            cnsts.insert({cnt, new ast::constant(cnt, *tps[ctn])});
                        c_cnsts.clear();
                    }
            }
            for (const std::string &cnt : c_cnsts)
                cnsts.insert({cnt, new ast::constant(cnt, o_tp)});
        }
        else
            backtrack(c_pos);

    if (match(LPAREN_ID))
        if (match(PREDICATES_ID)) // the domain predicates..
            do
            {
                if (!match(ID_ID))
                    error("expected identifier..");
                std::string pn = static_cast<id_token *>(tks[pos - 2])->id;
                ast::predicate *p = new ast::predicate(pn, typed_list_variable(tps));
                preds.insert({pn, p});
            } while (!match(RPAREN_ID));
        else
            backtrack(c_pos);

    if (!match(RPAREN_ID))
        error("expected ')'..");

    return new ast::domain(n, reqs, tps, cnsts, preds);
}

problem_parser::problem_parser(std::istream &is, ast::domain &dom) : parser(is), dom(dom) {}

problem_parser::~problem_parser() {}

ast::problem *problem_parser::parse()
{
    tk = next();

    std::string dn;
    std::string pn;
    std::vector<ast::requirement *> reqs;
    std::map<std::string, ast::object *> objcts;

    if (!match(LPAREN_ID))
        error("expected '('..");

    if (!match(DEFINE_ID))
        error("expected 'define'..");

    if (!match(LPAREN_ID))
        error("expected '('..");

    if (!match(PROBLEM_ID))
        error("expected 'domain'..");

    if (!match(ID_ID))
        error("expected identifier..");
    pn = static_cast<id_token *>(tks[pos - 2])->id;

    if (!match(RPAREN_ID))
        error("expected ')'..");

    if (!match(LPAREN_ID))
        error("expected '('..");

    if (!match(PROBLEM_DOMAIN_ID))
        error("expected 'domain'..");

    if (!match(ID_ID))
        error("expected identifier..");
    dn = static_cast<id_token *>(tks[pos - 2])->id;

    if (!match(RPAREN_ID))
        error("expected ')'..");

    size_t c_pos = pos;
    if (match(LPAREN_ID))
        if (match(REQUIREMENTS_ID)) // the problem requirements..
            do
            {
                reqs.push_back(req_def());
            } while (!match(RPAREN_ID));
        else
            backtrack(c_pos);

    if (match(LPAREN_ID))
        if (match(OBJECTS_ID)) // the problem objects..
        {
            ast::type &o_tp = dom.get_type("object");
            std::vector<std::string> c_objcts;
            while (!match(RPAREN_ID))
            {
                if (!match(ID_ID))
                    error("expected identifier..");
                c_objcts.push_back(static_cast<id_token *>(tks[pos - 2])->id);

                if (match(MINUS_ID)) // we have a supertype..
                    if (match(OBJECT_ID))
                    {
                        for (const std::string &cnt : c_objcts)
                            objcts.insert({cnt, new ast::object(cnt, o_tp)});
                        c_objcts.clear();
                    }
                    else
                    {
                        if (!match(ID_ID))
                            error("expected identifier..");
                        std::string ctn = static_cast<id_token *>(tks[pos - 2])->id;
                        for (const std::string &cnt : c_objcts)
                            objcts.insert({cnt, new ast::object(cnt, dom.get_type(ctn))});
                        c_objcts.clear();
                    }
            }
            for (const std::string &cnt : c_objcts)
                objcts.insert({cnt, new ast::object(cnt, o_tp)});
        }
        else
            backtrack(c_pos);

    if (!match(RPAREN_ID))
        error("expected ')'..");

    return new ast::problem(pn, dn);
}
} // namespace sca