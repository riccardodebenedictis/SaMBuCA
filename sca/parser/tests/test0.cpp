#include "parser.h"
#include "ast.h"
#include <iostream>
#include <sstream>

using namespace sca;

void test0()
{
    std::stringstream dss("(define (domain test-0))");
    parser dp(dss);
    ast::domain *dom = dp.parse_domain();

    std::stringstream pss("(define (problem prob-0) (:domain test-0))");
    parser pp(pss);
    ast::problem *prob = pp.parse_problem();
}

int main(int argc, char *argv[])
{
    test0();
}