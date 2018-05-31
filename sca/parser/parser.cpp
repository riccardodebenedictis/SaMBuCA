#include "parser.h"
#include "ast.h"

namespace sca
{

parser::parser(std::istream &is) : lex(is) {}

parser::~parser() {}

ast::domain *parser::parse_domain()
{
    tk = next();

    std::string n;
    std::vector<ast::requirement *> reqs;

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

    while (!match(RPAREN_ID))
    {
        if (!match(LPAREN_ID))
            error("expected '('..");

        switch (tk->sym)
        {
        case REQUIREMENTS_ID:
        {
            match(REQUIREMENTS_ID);
            do
            {
                switch (tk->sym)
                {
                case STRIPS_ID:
                    match(STRIPS_ID);
                    reqs.push_back(new ast::requirement(":strips"));
                    break;
                case TYPING_ID:
                    match(TYPING_ID);
                    reqs.push_back(new ast::requirement(":typing"));
                    break;
                case NEGATIVE_PRECONDITIONS_ID:
                    match(NEGATIVE_PRECONDITIONS_ID);
                    reqs.push_back(new ast::requirement(":negative-preconditions"));
                    break;
                case DISJUNCTIVE_PRECONDITIONS_ID:
                    match(DISJUNCTIVE_PRECONDITIONS_ID);
                    reqs.push_back(new ast::requirement(":disjunctive-preconditions"));
                    break;
                case EQUALITY_ID:
                    match(EQUALITY_ID);
                    reqs.push_back(new ast::requirement(":equality"));
                    break;
                case EXISTENTIAL_PRECONDITIONS_ID:
                    match(EXISTENTIAL_PRECONDITIONS_ID);
                    reqs.push_back(new ast::requirement(":existential-preconditions"));
                    break;
                case UNIVERSAL_PRECONDITIONS_ID:
                    match(UNIVERSAL_PRECONDITIONS_ID);
                    reqs.push_back(new ast::requirement(":universal-preconditions"));
                    break;
                case QUANTIFIED_PRECONDITIONS_ID:
                    match(QUANTIFIED_PRECONDITIONS_ID);
                    reqs.push_back(new ast::requirement(":quantified-preconditions"));
                    break;
                case CONDITIONAL_EFFECTS_ID:
                    match(CONDITIONAL_EFFECTS_ID);
                    reqs.push_back(new ast::requirement(":conditional-effects"));
                    break;
                case FLUENTS_ID:
                    match(FLUENTS_ID);
                    reqs.push_back(new ast::requirement(":fluents"));
                    break;
                case NUMERIC_FLUENTS_ID:
                    match(NUMERIC_FLUENTS_ID);
                    reqs.push_back(new ast::requirement(":numeric-fluents"));
                    break;
                case ADL_ID:
                    match(ADL_ID);
                    reqs.push_back(new ast::requirement(":adl"));
                    break;
                case DURATIVE_ACTIONS_ID:
                    match(DURATIVE_ACTIONS_ID);
                    reqs.push_back(new ast::requirement(":durative-actions"));
                    break;
                case DURATION_INEQUALITIES_ID:
                    match(DURATION_INEQUALITIES_ID);
                    reqs.push_back(new ast::requirement(":duration-inequalities"));
                    break;
                case CONTINUOUS_EFFECTS_ID:
                    match(CONTINUOUS_EFFECTS_ID);
                    reqs.push_back(new ast::requirement(":continuous-effects"));
                    break;
                case DERIVED_PREDICATES_ID:
                    match(DERIVED_PREDICATES_ID);
                    reqs.push_back(new ast::requirement(":derived-predicates"));
                    break;
                case TIMED_INITIAL_LITERALS_ID:
                    match(TIMED_INITIAL_LITERALS_ID);
                    reqs.push_back(new ast::requirement(":timed-initial-literals"));
                    break;
                case PREFERENCES_ID:
                    match(PREFERENCES_ID);
                    reqs.push_back(new ast::requirement(":preferences"));
                    break;
                case CONSTRAINTS_ID:
                    match(CONSTRAINTS_ID);
                    reqs.push_back(new ast::requirement(":constraints"));
                    break;
                case ACTION_COSTS_ID:
                    match(ACTION_COSTS_ID);
                    reqs.push_back(new ast::requirement(":action-costs"));
                    break;
                default:
                    error("expected either ':strips' or ':typing' or ':negative-preconditions' or ':disjunctive-preconditions' or ':equality' or ':existential-preconditions' or ':universal-preconditions' or ':quantified-preconditions' or ':conditional-effects' or ':fluents' or ':numeric-fluents' or ':adl' or ':durative-actions' or ':duration-inequalities' or ':conditional-effects' or ':derived-predicates' or ':timed-initial-literals' or ':preferences' or ':constraints' or ':action-costs'..");
                }
            } while (!match(RPAREN_ID));
            break;
        }
        default:
            error("expected either '(' or ')'..");
        }
    }

    return new ast::domain(n, reqs);
}

ast::problem *parser::parse_problem()
{
    tk = next();

    std::string dn;
    std::string pn;

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

    if (!match(RPAREN_ID))
        error("expected ')'..");

    return new ast::problem(pn, dn);
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
} // namespace sca