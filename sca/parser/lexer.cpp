#include "lexer.h"

namespace sca
{

lexer::lexer(std::istream &is)
{
    char buffer[1024];
    while (is.read(buffer, sizeof(buffer)))
        sb.append(buffer, sizeof(buffer));
    sb.append(buffer, is.gcount());
    ch = next_char();
}

lexer::~lexer() {}

token *lexer::next()
{
    switch (ch)
    {
    case ';': // in single-line comment
        while (true)
            switch (ch = next_char())
            {
            case '\r':
            case '\n':
                return next();
            case -1:
                return mk_token(EOF_ID);
            }
    case '=':
        ch = next_char();
        return mk_token(EQ_ID);
    case '>':
        if ((ch = next_char()) == '=')
        {
            ch = next_char();
            return mk_token(GTEQ_ID);
        }
        return mk_token(GT_ID);
    case '<':
        if ((ch = next_char()) == '=')
        {
            ch = next_char();
            return mk_token(LTEQ_ID);
        }
        return mk_token(LT_ID);
    case '+':
        ch = next_char();
        return mk_token(PLUS_ID);
    case '-':
        ch = next_char();
        return mk_token(MINUS_ID);
    case '*':
        ch = next_char();
        return mk_token(STAR_ID);
    case '/':
        ch = next_char();
        return mk_token(SLASH_ID);
    case '.': // in a number literal..
    {
        std::string num(".");
        while (true)
        {
            switch (ch = next_char())
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                num += ch;
                break;
            case '.':
                error("invalid numeric literal..");
            default:
                return mk_number_token(num);
            }
        }
    }
    case ':':
        switch (ch = next_char())
        {
        case 'a':
            switch (ch = next_char())
            {
            case 'c':
                if ((ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'o' || (ch = next_char()) != 'n')
                    error("invalid token..");
                if ((ch = next_char()) == '-')
                {
                    if ((ch = next_char()) != 'c' || (ch = next_char()) != 'o' || (ch = next_char()) != 's' || (ch = next_char()) != 't' || (ch = next_char()) != 's')
                        error("invalid token..");
                    ch = next_char();
                    return mk_token(ACTION_COSTS_ID);
                }
                else if (!is_id_part(ch))
                {
                    ch = next_char();
                    return mk_token(ACTION_ID);
                }
                else
                    error("invalid token..");
            case 'd':
                if ((ch = next_char()) != 'l')
                    error("invalid token..");
                ch = next_char();
                return mk_token(ADL_ID);
            default:
                error("invalid token..");
            }
        case 'c':
            if ((ch = next_char()) != 'o' || (ch = next_char()) != 'n')
                error("invalid token..");
            switch (ch = next_char())
            {
            case 'd':
                if ((ch = next_char()) != 'i' || (ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'o' || (ch = next_char()) != 'n' || (ch = next_char()) != 'a' || (ch = next_char()) != 'l' || (ch = next_char()) != '-' || (ch = next_char()) != 'e' || (ch = next_char()) != 'f' || (ch = next_char()) != 'f' || (ch = next_char()) != 'e' || (ch = next_char()) != 'c' || (ch = next_char()) != 't' || (ch = next_char()) != 's')
                    error("invalid token..");
                ch = next_char();
                return mk_token(CONDITIONAL_EFFECTS_ID);
            case 's':
                if ((ch = next_char()) != 't')
                    error("invalid token..");
                switch (ch = next_char())
                {
                case 'a':
                    if ((ch = next_char()) != 'n' || (ch = next_char()) != 't' || (ch = next_char()) != 's')
                        error("invalid token..");
                    ch = next_char();
                    return mk_token(CONSTANTS_ID);
                case 'r':
                    if ((ch = next_char()) != 'a' || (ch = next_char()) != 'i' || (ch = next_char()) != 'n' || (ch = next_char()) != 't' || (ch = next_char()) != 's')
                        error("invalid token..");
                    ch = next_char();
                    return mk_token(CONSTRAINTS_ID);
                default:
                    error("invalid token..");
                }
            case 't':
                if ((ch = next_char()) != 'i' || (ch = next_char()) != 'n' || (ch = next_char()) != 'u' || (ch = next_char()) != 'o' || (ch = next_char()) != 'u' || (ch = next_char()) != 's' || (ch = next_char()) != '-' || (ch = next_char()) != 'e' || (ch = next_char()) != 'f' || (ch = next_char()) != 'f' || (ch = next_char()) != 'e' || (ch = next_char()) != 'c' || (ch = next_char()) != 't' || (ch = next_char()) != 's')
                    error("invalid token..");
                ch = next_char();
                return mk_token(CONTINUOUS_EFFECTS_ID);
            default:
                error("invalid token..");
            }
        case 'd':
            switch (ch = next_char())
            {
            case 'e':
                if ((ch = next_char()) != 'r' || (ch = next_char()) != 'i' || (ch = next_char()) != 'v' || (ch = next_char()) != 'e' || (ch = next_char()) != 'd' || (ch = next_char()) != '-' || (ch = next_char()) != 'p' || (ch = next_char()) != 'r' || (ch = next_char()) != 'e' || (ch = next_char()) != 'd' || (ch = next_char()) != 'i' || (ch = next_char()) != 'c' || (ch = next_char()) != 'a' || (ch = next_char()) != 't' || (ch = next_char()) != 'e' || (ch = next_char()) != 's')
                    error("invalid token..");
                ch = next_char();
                return mk_token(DERIVED_PREDICATES_ID);
            case 'i':
                if ((ch = next_char()) != 's' || (ch = next_char()) != 'j' || (ch = next_char()) != 'u' || (ch = next_char()) != 'n' || (ch = next_char()) != 'c' || (ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'v' || (ch = next_char()) != 'e' || (ch = next_char()) != '-' || (ch = next_char()) != 'p' || (ch = next_char()) != 'r' || (ch = next_char()) != 'e' || (ch = next_char()) != 'c' || (ch = next_char()) != 'o' || (ch = next_char()) != 'n' || (ch = next_char()) != 'd' || (ch = next_char()) != 'i' || (ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'o' || (ch = next_char()) != 'n' || (ch = next_char()) != 's')
                    error("invalid token..");
                ch = next_char();
                return mk_token(DISJUNCTIVE_PRECONDITIONS_ID);
            case 'o':
                if ((ch = next_char()) != 'm' || (ch = next_char()) != 'a' || (ch = next_char()) != 'i' || (ch = next_char()) != 'n')
                    error("invalid token..");
                ch = next_char();
                return mk_token(PROBLEM_DOMAIN_ID);
            case 'u':
                if ((ch = next_char()) != 'r' || (ch = next_char()) != 'a' || (ch = next_char()) != 't' || (ch = next_char()) != 'i')
                    error("invalid token..");
                switch (ch = next_char())
                {
                case 'o':
                    if ((ch = next_char()) != 'n')
                        error("invalid token..");
                    if ((ch = next_char()) == '-')
                    {
                        if ((ch = next_char()) != 'i' || (ch = next_char()) != 'n' || (ch = next_char()) != 'e' || (ch = next_char()) != 'q' || (ch = next_char()) != 'u' || (ch = next_char()) != 'a' || (ch = next_char()) != 'l' || (ch = next_char()) != 'i' || (ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'e' || (ch = next_char()) != 's')
                            error("invalid token..");
                        ch = next_char();
                        return mk_token(DURATION_INEQUALITIES_ID);
                    }
                    else if (!is_id_part(ch))
                    {
                        ch = next_char();
                        return mk_token(DURATION_ID);
                    }
                    else
                        error("invalid token..");
                case 'v':
                    if ((ch = next_char()) != 'e' || (ch = next_char()) != '-' || (ch = next_char()) != 'a' || (ch = next_char()) != 'c' || (ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'o' || (ch = next_char()) != 'n')
                        error("invalid token..");
                    if ((ch = next_char()) == 's')
                    {
                        ch = next_char();
                        return mk_token(DURATIVE_ACTIONS_ID);
                    }
                    else if (!is_id_part(ch))
                    {
                        ch = next_char();
                        return mk_token(DURATIVE_ACTION_ID);
                    }
                    else
                        error("invalid token..");
                default:
                    error("invalid token..");
                }
                return mk_token(CONSTRAINTS_ID);
            default:
                error("invalid token..");
            }
        case 'e':
            switch (ch = next_char())
            {
            case 'f':
                if ((ch = next_char()) != 'f' || (ch = next_char()) != 'e' || (ch = next_char()) != 'c' || (ch = next_char()) != 't')
                    error("invalid token..");
                ch = next_char();
                return mk_token(EFFECT_ID);
            case 'q':
                if ((ch = next_char()) != 'u' || (ch = next_char()) != 'a' || (ch = next_char()) != 'l' || (ch = next_char()) != 'i' || (ch = next_char()) != 't' || (ch = next_char()) != 'y')
                    error("invalid token..");
                ch = next_char();
                return mk_token(EQUALITY_ID);
            case 'x':
                if ((ch = next_char()) != 'i' || (ch = next_char()) != 's' || (ch = next_char()) != 't' || (ch = next_char()) != 'e' || (ch = next_char()) != 'n' || (ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'a' || (ch = next_char()) != 'l' || (ch = next_char()) != '-' || (ch = next_char()) != 'p' || (ch = next_char()) != 'r' || (ch = next_char()) != 'e' || (ch = next_char()) != 'c' || (ch = next_char()) != 'o' || (ch = next_char()) != 'n' || (ch = next_char()) != 'd' || (ch = next_char()) != 'i' || (ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'o' || (ch = next_char()) != 'n')
                    error("invalid token..");
                ch = next_char();
                return mk_token(EXISTENTIAL_PRECONDITIONS_ID);
            default:
                error("invalid token..");
            }
        case 'f':
            switch (ch = next_char())
            {
            case 'l':
                if ((ch = next_char()) != 'u' || (ch = next_char()) != 'e' || (ch = next_char()) != 'n' || (ch = next_char()) != 't' || (ch = next_char()) != 's')
                    error("invalid token..");
                ch = next_char();
                return mk_token(FLUENTS_ID);
            case 'u':
                if ((ch = next_char()) != 'n' || (ch = next_char()) != 'c' || (ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'o' || (ch = next_char()) != 'n' || (ch = next_char()) != 's')
                    error("invalid token..");
                ch = next_char();
                return mk_token(FUNCTIONS_ID);
            default:
                error("invalid token..");
            }
        case 'g':
            if ((ch = next_char()) != 'o' || (ch = next_char()) != 'a' || (ch = next_char()) != 'l')
                error("invalid token..");
            ch = next_char();
            return mk_token(GOAL_ID);
        case 'i':
            if ((ch = next_char()) != 'n' || (ch = next_char()) != 'i' || (ch = next_char()) != 't')
                error("invalid token..");
            ch = next_char();
            return mk_token(INIT_ID);
        case 'm':
            if ((ch = next_char()) != 'e' || (ch = next_char()) != 't' || (ch = next_char()) != 'r' || (ch = next_char()) != 'i' || (ch = next_char()) != 'c')
                error("invalid token..");
            ch = next_char();
            return mk_token(METRIC_ID);
        case 'n':
            switch (ch = next_char())
            {
            case 'e':
                if ((ch = next_char()) != 'g' || (ch = next_char()) != 'a' || (ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'v' || (ch = next_char()) != 'e' || (ch = next_char()) != '-' || (ch = next_char()) != 'p' || (ch = next_char()) != 'r' || (ch = next_char()) != 'e' || (ch = next_char()) != 'c' || (ch = next_char()) != 'o' || (ch = next_char()) != 'n' || (ch = next_char()) != 'd' || (ch = next_char()) != 'i' || (ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'o' || (ch = next_char()) != 'n' || (ch = next_char()) != 's')
                    error("invalid token..");
                ch = next_char();
                return mk_token(NEGATIVE_PRECONDITIONS_ID);
            case 'u':
                if ((ch = next_char()) != 'm' || (ch = next_char()) != 'e' || (ch = next_char()) != 'r' || (ch = next_char()) != 'i' || (ch = next_char()) != 'c' || (ch = next_char()) != '-' || (ch = next_char()) != 'f' || (ch = next_char()) != 'l' || (ch = next_char()) != 'u' || (ch = next_char()) != 'e' || (ch = next_char()) != 'n' || (ch = next_char()) != 't' || (ch = next_char()) != 's')
                    error("invalid token..");
                ch = next_char();
                return mk_token(NUMERIC_FLUENTS_ID);
            default:
                error("invalid token..");
            }
        case 'o':
            if ((ch = next_char()) != 'b' || (ch = next_char()) != 'j' || (ch = next_char()) != 'e' || (ch = next_char()) != 'c' || (ch = next_char()) != 't' || (ch = next_char()) != 's')
                error("invalid token..");
            ch = next_char();
            return mk_token(OBJECTS_ID);
        case 'p':
            switch (ch = next_char())
            {
            case 'a':
                if ((ch = next_char()) != 'r' || (ch = next_char()) != 'a' || (ch = next_char()) != 'm' || (ch = next_char()) != 'e' || (ch = next_char()) != 't' || (ch = next_char()) != 'e' || (ch = next_char()) != 'r' || (ch = next_char()) != 's')
                    error("invalid token..");
                ch = next_char();
                return mk_token(PARAMETERS_ID);
            case 'r':
                if ((ch = next_char()) != 'e')
                    error("invalid token..");
                switch (ch = next_char())
                {
                case 'c':
                    if ((ch = next_char()) != 'o' || (ch = next_char()) != 'n' || (ch = next_char()) != 'd' || (ch = next_char()) != 'i' || (ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'o' || (ch = next_char()) != 'n')
                        error("invalid token..");
                    ch = next_char();
                    return mk_token(PRECONDITION_ID);
                case 'd':
                    if ((ch = next_char()) != 'i' || (ch = next_char()) != 'c' || (ch = next_char()) != 'a' || (ch = next_char()) != 't' || (ch = next_char()) != 'e' || (ch = next_char()) != 's')
                        error("invalid token..");
                    ch = next_char();
                    return mk_token(PREDICATES_ID);
                case 'f':
                    if ((ch = next_char()) != 'e' || (ch = next_char()) != 'r' || (ch = next_char()) != 'e' || (ch = next_char()) != 'n' || (ch = next_char()) != 'c' || (ch = next_char()) != 'e' || (ch = next_char()) != 's')
                        error("invalid token..");
                    ch = next_char();
                    return mk_token(PREFERENCES_ID);
                default:
                    error("invalid token..");
                }
            default:
                error("invalid token..");
            }
        case 'q':
            if ((ch = next_char()) != 'u' || (ch = next_char()) != 'a' || (ch = next_char()) != 'n' || (ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'f' || (ch = next_char()) != 'i' || (ch = next_char()) != 'e' || (ch = next_char()) != 'd' || (ch = next_char()) != '-' || (ch = next_char()) != 'p' || (ch = next_char()) != 'r' || (ch = next_char()) != 'e' || (ch = next_char()) != 'c' || (ch = next_char()) != 'o' || (ch = next_char()) != 'n' || (ch = next_char()) != 'd' || (ch = next_char()) != 'i' || (ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'o' || (ch = next_char()) != 'n' || (ch = next_char()) != 's')
                error("invalid token..");
            ch = next_char();
            return mk_token(QUANTIFIED_PRECONDITIONS_ID);
        case 'r':
            if ((ch = next_char()) != 'e' || (ch = next_char()) != 'q' || (ch = next_char()) != 'u' || (ch = next_char()) != 'i' || (ch = next_char()) != 'r' || (ch = next_char()) != 'e' || (ch = next_char()) != 'm' || (ch = next_char()) != 'e' || (ch = next_char()) != 'n' || (ch = next_char()) != 't' || (ch = next_char()) != 's')
                error("invalid token..");
            ch = next_char();
            return mk_token(REQUIREMENTS_ID);
        case 's':
            if ((ch = next_char()) != 't' || (ch = next_char()) != 'r' || (ch = next_char()) != 'i' || (ch = next_char()) != 'p' || (ch = next_char()) != 's')
                error("invalid token..");
            ch = next_char();
            return mk_token(STRIPS_ID);
        case 't':
            switch (ch = next_char())
            {
            case 'i':
                if ((ch = next_char()) != 'm' || (ch = next_char()) != 'e' || (ch = next_char()) != 'd' || (ch = next_char()) != '-' || (ch = next_char()) != 'i' || (ch = next_char()) != 'n' || (ch = next_char()) != 'i' || (ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'a' || (ch = next_char()) != 'l' || (ch = next_char()) != '-' || (ch = next_char()) != 'l' || (ch = next_char()) != 'i' || (ch = next_char()) != 't' || (ch = next_char()) != 'e' || (ch = next_char()) != 'r' || (ch = next_char()) != 'a' || (ch = next_char()) != 'l' || (ch = next_char()) != 's')
                    error("invalid token..");
                ch = next_char();
                return mk_token(TIMED_INITIAL_LITERALS_ID);
            case 'y':
                if ((ch = next_char()) != 'p')
                    error("invalid token..");
                switch (ch = next_char())
                {
                case 'e':
                    if ((ch = next_char()) != 's')
                        error("invalid token..");
                    ch = next_char();
                    return mk_token(TYPES_ID);
                case 'i':
                    if ((ch = next_char()) != 'n' || (ch = next_char()) != 'g')
                        error("invalid token..");
                    ch = next_char();
                    return mk_token(TYPING_ID);
                default:
                    error("invalid token..");
                }
            default:
                error("invalid token..");
            }
        case 'u':
            if ((ch = next_char()) != 'n' || (ch = next_char()) != 'i' || (ch = next_char()) != 'v' || (ch = next_char()) != 'e' || (ch = next_char()) != 'r' || (ch = next_char()) != 's' || (ch = next_char()) != 'a' || (ch = next_char()) != 'l' || (ch = next_char()) != '-' || (ch = next_char()) != 'p' || (ch = next_char()) != 'r' || (ch = next_char()) != 'e' || (ch = next_char()) != 'c' || (ch = next_char()) != 'o' || (ch = next_char()) != 'n' || (ch = next_char()) != 'd' || (ch = next_char()) != 'i' || (ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'o' || (ch = next_char()) != 'n' || (ch = next_char()) != 's')
                error("invalid token..");
            ch = next_char();
            return mk_token(STRIPS_ID);
        default:
            error("invalid token..");
        }
    case '#':
        if ((ch = next_char()) != 't')
            error("invalid token..");
        ch = next_char();
        return mk_token(SHARP_T_ID);
    case '(':
        ch = next_char();
        return mk_token(LPAREN_ID);
    case ')':
        ch = next_char();
        return mk_token(RPAREN_ID);
    case '0': // in a number literal..
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        std::string num; // the integer part..
        num += ch;
        while (true)
            switch (ch = next_char())
            {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                num += ch;
                break;
            case '.':
            { // the decimal part..
                num += ch;
                while (true)
                    switch (ch = next_char())
                    {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        num += ch;
                        break;
                    case '.':
                        error("invalid numeric literal..");
                    default:
                        return mk_number_token(num);
                    }
            }
            default:
                return mk_number_token(num);
            }
    }
    case 'a':
    {
        std::string str;
        str += ch;
        switch (ch = next_char())
        {
        case 'l':
            str += ch;
            switch (ch = next_char())
            {
            case 'l':
                str += ch;
                if ((ch = next_char()) != -1 && is_id_part(ch))
                    return finish_id(str);
                else
                    return mk_token(ALL_ID);
            case 'w':
                str += ch;
                if ((ch = next_char()) != 'a')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != 'y')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != 's')
                    return finish_id(str);
                str += ch;
                switch (ch = next_char())
                {
                case '-':
                    str += ch;
                    if ((ch = next_char()) != 'w')
                        return finish_id(str);
                    str += ch;
                    if ((ch = next_char()) != 'i')
                        return finish_id(str);
                    str += ch;
                    if ((ch = next_char()) != 't')
                        return finish_id(str);
                    str += ch;
                    if ((ch = next_char()) != 'h')
                        return finish_id(str);
                    str += ch;
                    if ((ch = next_char()) != 'i')
                        return finish_id(str);
                    str += ch;
                    if ((ch = next_char()) != 'n')
                        return finish_id(str);
                    str += ch;
                    if ((ch = next_char()) != -1 && is_id_part(ch))
                        return finish_id(str);
                    else
                        return mk_token(ALWAYS_WITHIN_ID);
                default:
                    str += ch;
                    if (is_id_part(ch))
                        return finish_id(str);
                    else
                        return mk_token(ALWAYS_ID);
                }
            default:
                return finish_id(str);
            }
        case 'n':
            str += ch;
            if ((ch = next_char()) != 'd')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(AND_ID);
        case 's':
            str += ch;
            if ((ch = next_char()) != 's')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'i')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'g')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'n')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(ASSIGN_ID);
        case 't':
            str += ch;
            switch (ch = next_char())
            {
            case '-':
                str += ch;
                if ((ch = next_char()) != 'm')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != 'o')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != 's')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != 't')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != '-')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != 'o')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != 'n')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != 'c')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != 'e')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != -1 && is_id_part(ch))
                    return finish_id(str);
                else
                    return mk_token(ALWAYS_WITHIN_ID);
            default:
                str += ch;
                if (is_id_part(ch))
                    return finish_id(str);
                else
                    return mk_token(AT_ID);
            }
        default:
            return finish_id(str);
        }
    }
    case 'd':
    {
        std::string str;
        str += ch;
        switch (ch = next_char())
        {
        case 'e':
            str += ch;
            switch (ch = next_char())
            {
            case 'c':
                str += ch;
                if ((ch = next_char()) != 'r')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != 'e')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != 'a')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != 's')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != 'e')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != -1 && is_id_part(ch))
                    return finish_id(str);
                else
                    return mk_token(DECREASE_ID);
            case 'f':
                str += ch;
                if ((ch = next_char()) != 'i')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != 'n')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != 'e')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != -1 && is_id_part(ch))
                    return finish_id(str);
                else
                    return mk_token(DEFINE_ID);
            default:
                return finish_id(str);
            }
        case 'o':
            str += ch;
            if ((ch = next_char()) != 'm')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'a')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'i')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'n')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(DOMAIN_ID);
        default:
            return finish_id(str);
        }
    }
    case 'e':
    {
        std::string str;
        str += ch;
        switch (ch = next_char())
        {
        case 'n':
            str += ch;
            if ((ch = next_char()) != 'd')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(END_ID);
        case 'i':
            str += ch;
            if ((ch = next_char()) != 't')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'h')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'e')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'r')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(EITHER_ID);
        case 'x':
            str += ch;
            if ((ch = next_char()) != 'i')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 's')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 't')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 's')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(EXISTS_ID);
        default:
            return finish_id(str);
        }
    }
    case 'f':
    {
        std::string str;
        str += ch;
        if ((ch = next_char()) != 'o')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 'r')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 'a')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 'l')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 'l')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != -1 && is_id_part(ch))
            return finish_id(str);
        else
            return mk_token(FORALL_ID);
    }
    case 'h':
    {
        std::string str;
        str += ch;
        if ((ch = next_char()) != 'o')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 'l')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 'd')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != '-')
            return finish_id(str);
        str += ch;
        switch (ch = next_char())
        {
        case 'a':
            str += ch;
            if ((ch = next_char()) != 'f')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 't')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'e')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'r')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(HOLD_AFTER_ID);
        case 'd':
            str += ch;
            if ((ch = next_char()) != 'u')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'r')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'i')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'n')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'g')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(HOLD_DURING_ID);
        default:
            return finish_id(str);
        }
    }
    case 'i':
    {
        std::string str;
        str += ch;
        switch (ch = next_char())
        {
        case 'm':
            str += ch;
            if ((ch = next_char()) != 'p')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'l')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'y')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(IMPLY_ID);
        case 'n':
            str += ch;
            if ((ch = next_char()) != 'c')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'r')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'e')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'a')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 's')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'e')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(INCREASE_ID);
        default:
            return finish_id(str);
        }
    }
    case 'm':
    {
        std::string str;
        str += ch;
        switch (ch = next_char())
        {
        case 'a':
            str += ch;
            if ((ch = next_char()) != 'x')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'i')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'm')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'i')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'z')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'e')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(MAXIMIZE_ID);
        case 'i':
            str += ch;
            if ((ch = next_char()) != 'n')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'i')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'm')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'i')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'z')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'e')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(MINIMIZE_ID);
        default:
            return finish_id(str);
        }
    }
    case 'n':
    {
        std::string str;
        str += ch;
        if ((ch = next_char()) != 'o')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 't')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != -1 && is_id_part(ch))
            return finish_id(str);
        else
            return mk_token(NOT_ID);
    }
    case 'o':
    {
        std::string str;
        str += ch;
        switch (ch = next_char())
        {
        case 'b':
            str += ch;
            if ((ch = next_char()) != 'j')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'e')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'c')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 't')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(OBJECT_ID);
        case 'r':
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(OR_ID);
        case 'v':
            str += ch;
            if ((ch = next_char()) != 'e')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'r')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(OVER_ID);
        default:
            return finish_id(str);
        }
    }
    case 'p':
    {
        std::string str;
        str += ch;
        if ((ch = next_char()) != 'r')
            return finish_id(str);
        str += ch;
        switch (ch = next_char())
        {
        case 'e':
            str += ch;
            if ((ch = next_char()) != 'f')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'e')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'r')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'e')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'n')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'c')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'e')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(PREFERENCE_ID);
        case 'o':
            str += ch;
            if ((ch = next_char()) != 'b')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'l')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'e')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'm')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(PROBLEM_ID);
        default:
            return finish_id(str);
        }
    }
    case 's':
    {
        std::string str;
        str += ch;
        switch (ch = next_char())
        {
        case 'c':
            str += ch;
            if ((ch = next_char()) != 'a')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'l')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'e')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != '-')
                return finish_id(str);
            str += ch;
            switch (ch = next_char())
            {
            case 'd':
                str += ch;
                if ((ch = next_char()) != 'o')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != 'w')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != 'n')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != -1 && is_id_part(ch))
                    return finish_id(str);
                else
                    return mk_token(SCALE_DOWN_ID);
            case 'u':
                str += ch;
                if ((ch = next_char()) != 'p')
                    return finish_id(str);
                str += ch;
                if ((ch = next_char()) != -1 && is_id_part(ch))
                    return finish_id(str);
                else
                    return mk_token(SCALE_UP_ID);
            default:
                return finish_id(str);
            }
        case 'o':
            str += ch;
            if ((ch = next_char()) != 'm')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'e')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 't')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'i')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'm')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'e')
                return finish_id(str);
            str += ch;
            switch (ch = next_char())
            {
            case '-':
                str += ch;
                switch (ch = next_char())
                {
                case 'a':
                    str += ch;
                    if ((ch = next_char()) != 'f')
                        return finish_id(str);
                    str += ch;
                    if ((ch = next_char()) != 't')
                        return finish_id(str);
                    str += ch;
                    if ((ch = next_char()) != 'e')
                        return finish_id(str);
                    str += ch;
                    if ((ch = next_char()) != 'r')
                        return finish_id(str);
                    str += ch;
                    if ((ch = next_char()) != -1 && is_id_part(ch))
                        return finish_id(str);
                    else
                        return mk_token(SOMETIME_AFTER_ID);
                case 'b':
                    str += ch;
                    if ((ch = next_char()) != 'e')
                        return finish_id(str);
                    str += ch;
                    if ((ch = next_char()) != 'f')
                        return finish_id(str);
                    str += ch;
                    if ((ch = next_char()) != 'o')
                        return finish_id(str);
                    str += ch;
                    if ((ch = next_char()) != 'r')
                        return finish_id(str);
                    str += ch;
                    if ((ch = next_char()) != 'e')
                        return finish_id(str);
                    str += ch;
                    if ((ch = next_char()) != -1 && is_id_part(ch))
                        return finish_id(str);
                    else
                        return mk_token(SOMETIME_BEFORE_ID);
                default:
                    return finish_id(str);
                }
            default:
                str += ch;
                if (is_id_part(ch))
                    return finish_id(str);
                else
                    return mk_token(SOMETIME_ID);
            }
        case 't':
            str += ch;
            if ((ch = next_char()) != 'a')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'r')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 't')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(START_ID);
        default:
            return finish_id(str);
        }
    }
    case 't':
    {
        std::string str;
        str += ch;
        if ((ch = next_char()) != 'o')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 't')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 'a')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 'l')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != '-')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 't')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 'i')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 'm')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 'e')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != -1 && is_id_part(ch))
            return finish_id(str);
        else
            return mk_token(TOTAL_TIME_ID);
    }
    case 'w':
    {
        std::string str;
        str += ch;
        switch (ch = next_char())
        {
        case 'h':
            str += ch;
            if ((ch = next_char()) != 'e')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'n')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(WHEN_ID);
        case 'i':
            str += ch;
            if ((ch = next_char()) != 't')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'h')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'i')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != 'n')
                return finish_id(str);
            str += ch;
            if ((ch = next_char()) != -1 && is_id_part(ch))
                return finish_id(str);
            else
                return mk_token(WITHIN_ID);
        default:
            return finish_id(str);
        }
    }
    case '?':
    {
        std::string str;
        str += ch;
        if ((ch = next_char()) != 'd')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 'u')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 'r')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 'a')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 't')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 'i')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 'o')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != 'n')
            return finish_id(str);
        str += ch;
        if ((ch = next_char()) != -1 && is_id_part(ch))
            return finish_id(str);
        else
            return mk_token(DURATION_VAR_ID);
    }
    case 'b':
    case 'c':
    case 'g':
    case 'j':
    case 'k':
    case 'l':
    case 'q':
    case 'r':
    case 'u':
    case 'v':
    case 'x':
    case 'y':
    case 'z':
    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    case 'G':
    case 'H':
    case 'I':
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    case 'O':
    case 'P':
    case 'Q':
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
    case '_':
    {
        std::string str;
        return finish_id(str);
    }
    case '\t':
    case ' ':
    case '\r':
    case '\n':
        while (true)
            switch (ch = next_char())
            {
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                break;
            case -1:
                return mk_token(EOF_ID);
            default:
                return next();
            }
    case -1:
        return mk_token(EOF_ID);
    default:
        error("invalid token..");
        return nullptr;
    }
}

int lexer::next_char()
{
    if (pos == sb.length())
        return -1;
    switch (sb[pos])
    {
    case ' ':
        start_pos++;
        end_pos++;
        break;
    case '\t':
        start_pos += 4 - (start_pos % 4);
        end_pos += 4 - (end_pos % 4);
        break;
    case '\r':
        if (pos + 1 != sb.length() && sb[pos + 1] == '\n')
        {
            pos++;
            end_line++;
            end_pos = 0;
            break;
        }
    case '\n':
        end_line++;
        end_pos = 0;
        break;
    default:
        end_pos++;
        break;
    }
    return sb[pos++];
}

token *lexer::finish_id(std::string &str)
{
    if (!is_id_part(ch))
        return mk_id_token(str);
    str += ch;
    while ((ch = next_char()) != -1 && is_id_part(ch))
        str += ch;
    return mk_id_token(str);
}

void lexer::error(const std::string &err) { throw std::invalid_argument("[" + std::to_string(start_line) + ", " + std::to_string(start_pos) + "] " + err); }
} // namespace sca