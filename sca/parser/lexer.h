#pragma once

namespace sca
{

enum symbol
{
  DEFINE_ID,          // 'define'
  DOMAIN_ID,          // 'domain'
  REQUIREMENTS_ID,    // ':requirements'
  TYPES_ID,           // ':types'
  CONSTANTS_ID,       // ':constants'
  PREDICATES_ID,      // ':predicates'
  FUNCTIONS_ID,       // ':functions'
  CONSTRAINTS_ID,     // ':constraints'
  OBJECT_ID,          // 'object'
  EITHER_ID,          // 'either'
  ACTION_ID,          // ':action'
  PARAMETERS_ID,      // ':parameters'
  PRECONDITION_ID,    // ':precondition'
  EFFECT_ID,          // ':effect'
  AND_ID,             // 'and'
  FORALL_ID,          // 'forall'
  PREFERENCE_ID,      // 'preference'
  OR_ID,              // 'or'
  NOT_ID,             // 'not'
  IMPLY_ID,           // 'imply'
  EXISTS_ID,          // 'exists'
  WHEN_ID,            // 'when'
  ASSIGN_ID,          // 'assign'
  SCALE_UP_ID,        // 'scale-up'
  SCALE_DOWN_ID,      // 'scale-down'
  INCREASE_ID,        // 'increase'
  DECREASE_ID,        // 'decrease'
  DURATIVE_ACTION_ID, // ':durative-action'
  DURATION_ID,        // ':duration'
  AT_ID,              // 'at'
  OVER_ID,            // 'over'
  START_ID,           // 'start'
  END_ID,             // 'end'
  ALL_ID,             // 'all'
  DURATION_VAR_ID,    // '?duration'
  PROBLEM_ID,         // ':problem'
  PROBLEM_DOMAIN_ID,  // ':domain'
  OBJECTS_ID,         // ':objects'
  INIT_ID,            // ':init'
  GOAL_ID,            // ':goal'
  ALWAYS_ID,          // 'always'
  SOMETIME_ID,        // 'sometime'
  WITHIN_ID,          // 'within'
  AT_MOST_ONCE_ID,    // 'at-most-once'
  SOMETIME_AFTER_ID,  // 'sometime-after'
  SOMETIME_BEFORE_ID, // 'sometime-before'
  ALWAYS_WITHIN_ID,   // 'always-within'
  HOLD_DURING_ID,     // 'hold-during'
  HOLD_AFTER_ID,      // 'hold-after'
  METRIC_ID,          // ':metric'
  MINIMIZE_ID,        // 'minimize'
  MAXIMIZE_ID,        // 'maximize'
  TOTAL_TIME_ID,      // 'total-time'
  LPAREN_ID,          // '('
  RPAREN_ID,          // ')'
  QUESTION_ID,        // '?'
  EQ_ID,              // '='
  PLUS_ID,            // '+'
  MINUS_ID,           // '-'
  STAR_ID,            // '*'
  SLASH_ID,           // '/'
  GT_ID,              // '>'
  LT_ID,              // '<'
  LTEQ_ID,            // '<='
  GTEQ_ID,            // '>='
  ID_ID,              // ('a'..'z'|'A'..'Z'|'_') ('a'..'z'|'A'..'Z'|'0'..'9'|'_')*
  IntLiteral_ID,      // [0-9]+
  RealLiteral_ID,     // [0-9]+ '.' [0-9]+)? | '.' [0-9]+
  EOF_ID
};

class lexer
{
private:
  /* data */
public:
  lexer(/* args */);
  ~lexer();
};
} // namespace sca