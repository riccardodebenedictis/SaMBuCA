#include "parser.h"
#include <iostream>
#include <sstream>

using namespace sca;

void test0() // testing basic domain and basic problem..
{
    std::stringstream dss("(define (domain test-0))");
    domain_parser dp(dss);
    ast::domain *dom = dp.parse();

    std::stringstream pss("(define (problem prob-0) (:domain test-0))");
    problem_parser pp(pss, *dom);
    ast::problem *prob = pp.parse();
}

void test1() // testing domain requirements..
{
    std::stringstream dss("(define (domain test-0) (:requirements :strips :typing :negative-preconditions :disjunctive-preconditions :equality :existential-preconditions :universal-preconditions :quantified-preconditions :conditional-effects :fluents :numeric-fluents :adl :durative-actions :duration-inequalities :conditional-effects :derived-predicates :timed-initial-literals :preferences :constraints :action-costs))");
    domain_parser dp(dss);
    ast::domain *dom = dp.parse();
}

void test2() // testing domain requirements..
{
    std::stringstream dss("(define (domain test-0) (:requirements :typing) (:types tp0 tp1 - object tp2 - tp1 tp3))");
    domain_parser dp(dss);
    ast::domain *dom = dp.parse();
}

int main(int argc, char *argv[])
{
    test0();
    test1();
    test2();
}