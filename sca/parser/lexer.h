#pragma once

#include <cstddef>
#include <string>
#include <istream>
#include <cmath>
#include <vector>

namespace sca
{

enum symbol
{
  DEFINE_ID,                    // 'define'
  DOMAIN_ID,                    // 'domain'
  REQUIREMENTS_ID,              // ':requirements'
  TYPES_ID,                     // ':types'
  CONSTANTS_ID,                 // ':constants'
  PREDICATES_ID,                // ':predicates'
  FUNCTIONS_ID,                 // ':functions'
  CONSTRAINTS_ID,               // ':constraints'
  OBJECT_ID,                    // 'object'
  EITHER_ID,                    // 'either'
  ACTION_ID,                    // ':action'
  PARAMETERS_ID,                // ':parameters'
  PRECONDITION_ID,              // ':precondition'
  EFFECT_ID,                    // ':effect'
  AND_ID,                       // 'and'
  FORALL_ID,                    // 'forall'
  PREFERENCE_ID,                // 'preference'
  OR_ID,                        // 'or'
  NOT_ID,                       // 'not'
  IMPLY_ID,                     // 'imply'
  EXISTS_ID,                    // 'exists'
  WHEN_ID,                      // 'when'
  ASSIGN_ID,                    // 'assign'
  SCALE_UP_ID,                  // 'scale-up'
  SCALE_DOWN_ID,                // 'scale-down'
  INCREASE_ID,                  // 'increase'
  DECREASE_ID,                  // 'decrease'
  DURATIVE_ACTION_ID,           // ':durative-action'
  DURATION_ID,                  // ':duration'
  AT_ID,                        // 'at'
  OVER_ID,                      // 'over'
  START_ID,                     // 'start'
  END_ID,                       // 'end'
  ALL_ID,                       // 'all'
  DURATION_VAR_ID,              // '?duration'
  PROBLEM_ID,                   // ':problem'
  PROBLEM_DOMAIN_ID,            // ':domain'
  OBJECTS_ID,                   // ':objects'
  INIT_ID,                      // ':init'
  GOAL_ID,                      // ':goal'
  ALWAYS_ID,                    // 'always'
  SOMETIME_ID,                  // 'sometime'
  WITHIN_ID,                    // 'within'
  AT_MOST_ONCE_ID,              // 'at-most-once'
  SOMETIME_AFTER_ID,            // 'sometime-after'
  SOMETIME_BEFORE_ID,           // 'sometime-before'
  ALWAYS_WITHIN_ID,             // 'always-within'
  HOLD_DURING_ID,               // 'hold-during'
  HOLD_AFTER_ID,                // 'hold-after'
  METRIC_ID,                    // ':metric'
  MINIMIZE_ID,                  // 'minimize'
  MAXIMIZE_ID,                  // 'maximize'
  TOTAL_TIME_ID,                // 'total-time'
  SHARP_T_ID,                   // '#t'
  STRIPS_ID,                    // ':strips'
  TYPING_ID,                    // ':typing'
  NEGATIVE_PRECONDITIONS_ID,    // ':negative-preconditions'
  DISJUNCTIVE_PRECONDITIONS_ID, // ':disjunctive-preconditions'
  EQUALITY_ID,                  // ':equality'
  EXISTENTIAL_PRECONDITIONS_ID, // ':existential-preconditions'
  UNIVERSAL_PRECONDITIONS_ID,   // ':universal-preconditions'
  QUANTIFIED_PRECONDITIONS_ID,  // ':quantified-preconditions'
  CONDITIONAL_EFFECTS_ID,       // ':conditiona-effects'
  FLUENTS_ID,                   // ':fluents'
  NUMERIC_FLUENTS_ID,           // ':numeric-fluents'
  ADL_ID,                       // ':adl'
  DURATIVE_ACTIONS_ID,          // ':durative-actions'
  DURATION_INEQUALITIES_ID,     // ':duration-inequalities'
  CONTINUOUS_EFFECTS_ID,        // ':continuous-effects'
  DERIVED_PREDICATES_ID,        // ':derived-predicates'
  TIMED_INITIAL_LITERALS_ID,    // ':timed-initial-literals'
  PREFERENCES_ID,               // ':preferences'
  ACTION_COSTS_ID,              // ':action-costs'
  LPAREN_ID,                    // '('
  RPAREN_ID,                    // ')'
  QUESTION_ID,                  // '?'
  EQ_ID,                        // '='
  PLUS_ID,                      // '+'
  MINUS_ID,                     // '-'
  STAR_ID,                      // '*'
  SLASH_ID,                     // '/'
  GT_ID,                        // '>'
  LT_ID,                        // '<'
  LTEQ_ID,                      // '<='
  GTEQ_ID,                      // '>='
  SEMICOLON_ID,                 // ';'
  ID_ID,                        // ('a'..'z'|'A'..'Z') ('a'..'z'|'A'..'Z'|'0'..'9'|'-'|'_')*
  IntLiteral_ID,                // [0-9]+
  RealLiteral_ID,               // [0-9]+ '.' [0-9]+)? | '.' [0-9]+
  EOF_ID
};

class token
{
public:
  token(const symbol &sym, const size_t &start_line, const size_t &start_pos, const size_t &end_line, const size_t &end_pos) : sym(sym), start_line(start_line), start_pos(start_pos), end_line(end_line), end_pos(end_pos) {}
  virtual ~token() {}

public:
  const symbol sym;
  const size_t start_line;
  const size_t start_pos;
  const size_t end_line;
  const size_t end_pos;
};

class id_token : public token
{
public:
  id_token(const size_t &start_line, const size_t &start_pos, const size_t &end_line, const size_t &end_pos, const std::string &id) : token(ID_ID, start_line, start_pos, end_line, end_pos), id(id) {}
  virtual ~id_token() {}

public:
  const std::string id;
};

class number_token : public token
{
public:
  number_token(const size_t &start_line, const size_t &start_pos, const size_t &end_line, const size_t &end_pos, const double &val) : token(RealLiteral_ID, start_line, start_pos, end_line, end_pos), val(val) {}
  virtual ~number_token() {}

public:
  const double val;
};

class lexer
{
private:
  std::string sb;
  size_t pos = 0;
  int ch;
  size_t start_line = 0;
  size_t start_pos = 0;
  size_t end_line = 0;
  size_t end_pos = 0;

public:
  lexer(std::istream &is);
  lexer(const lexer &orig) = delete;
  virtual ~lexer();

  token *next();

private:
  static bool is_id_part(const char &ch) { return ch == '-' || ch == '_' || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9'); }

  token *mk_token(const symbol &sym)
  {
    token *tk = new token(sym, start_line, start_pos, end_line, end_pos);
    start_line = end_line;
    start_pos = end_pos;
    return tk;
  }

  token *mk_id_token(const std::string &id)
  {
    id_token *tk = new id_token(start_line, start_pos, end_line, end_pos, id);
    start_line = end_line;
    start_pos = end_pos;
    return tk;
  }

  token *mk_number_token(const std::string &str)
  {
    token *tk = new number_token(start_line, start_pos, end_line, end_pos, std::stod(str));
    start_line = end_line;
    start_pos = end_pos;
    return tk;
  }

  token *finish_id(std::string &str);

  void error(const std::string &err);
  int next_char();
};
} // namespace sca