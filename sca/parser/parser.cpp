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

    if (!match(RPAREN_ID))
        error("expected ')'..");

    return new ast::domain(n);
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