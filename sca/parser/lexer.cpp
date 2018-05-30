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
            if ((ch = next_char()) != 'c' || (ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'o' || (ch = next_char()) != 'n')
                error("invalid keyword..");
            ch = next_char();
            return mk_token(ACTION_ID);
        case 'c':
            if ((ch = next_char()) != 'o' || (ch = next_char()) != 'n' || (ch = next_char()) != 's' || (ch = next_char()) != 't')
                error("invalid keyword..");
            switch (ch = next_char())
            {
            case 'a':
                if ((ch = next_char()) != 'n' || (ch = next_char()) != 't' || (ch = next_char()) != 's')
                    error("invalid keyword..");
                ch = next_char();
                return mk_token(CONSTANTS_ID);
            case 'r':
                if ((ch = next_char()) != 'a' || (ch = next_char()) != 'i' || (ch = next_char()) != 'n' || (ch = next_char()) != 't' || (ch = next_char()) != 's')
                    error("invalid keyword..");
                ch = next_char();
                return mk_token(CONSTRAINTS_ID);
            default:
                error("invalid keyword..");
            }
        case 'd':
            switch (ch = next_char())
            {
            case 'o':
                if ((ch = next_char()) != 'm' || (ch = next_char()) != 'a' || (ch = next_char()) != 'i' || (ch = next_char()) != 'n')
                    error("invalid keyword..");
                ch = next_char();
                return mk_token(DOMAIN_ID);
            case 'u':
                if ((ch = next_char()) != 'r' || (ch = next_char()) != 'a' || (ch = next_char()) != 't' || (ch = next_char()) != 'i')
                    error("invalid keyword..");
                switch (ch = next_char())
                {
                case 'o':
                    if ((ch = next_char()) != 'n')
                        error("invalid keyword..");
                    ch = next_char();
                    return mk_token(DURATION_ID);
                case 'v':
                    if ((ch = next_char()) != 'e' || (ch = next_char()) != '-' || (ch = next_char()) != 'a' || (ch = next_char()) != 'c' || (ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'o' || (ch = next_char()) != 'n')
                        error("invalid keyword..");
                    ch = next_char();
                    return mk_token(DURATIVE_ACTION_ID);
                default:
                    error("invalid keyword..");
                }
                return mk_token(CONSTRAINTS_ID);
            default:
                error("invalid keyword..");
            }
        case 'e':
            if ((ch = next_char()) != 'f' || (ch = next_char()) != 'f' || (ch = next_char()) != 'e' || (ch = next_char()) != 'c' || (ch = next_char()) != 't')
                error("invalid keyword..");
            ch = next_char();
            return mk_token(EFFECT_ID);
        case 'f':
            if ((ch = next_char()) != 'u' || (ch = next_char()) != 'n' || (ch = next_char()) != 'c' || (ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'o' || (ch = next_char()) != 'n' || (ch = next_char()) != 's')
                error("invalid keyword..");
            ch = next_char();
            return mk_token(FUNCTIONS_ID);
        case 'g':
            if ((ch = next_char()) != 'o' || (ch = next_char()) != 'a' || (ch = next_char()) != 'l')
                error("invalid keyword..");
            ch = next_char();
            return mk_token(GOAL_ID);
        case 'i':
            if ((ch = next_char()) != 'n' || (ch = next_char()) != 'i' || (ch = next_char()) != 't')
                error("invalid keyword..");
            ch = next_char();
            return mk_token(INIT_ID);
        case 'm':
            if ((ch = next_char()) != 'e' || (ch = next_char()) != 't' || (ch = next_char()) != 'r' || (ch = next_char()) != 'i' || (ch = next_char()) != 'c')
                error("invalid keyword..");
            ch = next_char();
            return mk_token(METRIC_ID);
        case 'o':
            if ((ch = next_char()) != 'b' || (ch = next_char()) != 'j' || (ch = next_char()) != 'e' || (ch = next_char()) != 'c' || (ch = next_char()) != 't' || (ch = next_char()) != 's')
                error("invalid keyword..");
            ch = next_char();
            return mk_token(OBJECTS_ID);
        case 'p':
            switch (ch = next_char())
            {
            case 'a':
                if ((ch = next_char()) != 'r' || (ch = next_char()) != 'a' || (ch = next_char()) != 'm' || (ch = next_char()) != 'e' || (ch = next_char()) != 't' || (ch = next_char()) != 'e' || (ch = next_char()) != 'r' || (ch = next_char()) != 's')
                    error("invalid keyword..");
                ch = next_char();
                return mk_token(PARAMETERS_ID);
            case 'r':
                switch (ch = next_char())
                {
                case 'e':
                    switch (ch = next_char())
                    {
                    case 'c':
                        if ((ch = next_char()) != 'o' || (ch = next_char()) != 'n' || (ch = next_char()) != 'd' || (ch = next_char()) != 'i' || (ch = next_char()) != 't' || (ch = next_char()) != 'i' || (ch = next_char()) != 'o' || (ch = next_char()) != 'n')
                            error("invalid keyword..");
                        ch = next_char();
                        return mk_token(PRECONDITION_ID);
                    case 'd':
                        if ((ch = next_char()) != 'i' || (ch = next_char()) != 'c' || (ch = next_char()) != 'a' || (ch = next_char()) != 't' || (ch = next_char()) != 'e' || (ch = next_char()) != 's')
                            error("invalid keyword..");
                        ch = next_char();
                        return mk_token(PREDICATES_ID);
                    default:
                        error("invalid keyword..");
                    }
                case 'o':
                    if ((ch = next_char()) != 'b' || (ch = next_char()) != 'l' || (ch = next_char()) != 'e' || (ch = next_char()) != 'm')
                        error("invalid keyword..");
                    ch = next_char();
                    return mk_token(PROBLEM_ID);
                default:
                    error("invalid keyword..");
                }
            default:
                error("invalid keyword..");
            }
        case 'r':
            if ((ch = next_char()) != 'e' || (ch = next_char()) != 'q' || (ch = next_char()) != 'u' || (ch = next_char()) != 'i' || (ch = next_char()) != 'r' || (ch = next_char()) != 'e' || (ch = next_char()) != 'm' || (ch = next_char()) != 'e' || (ch = next_char()) != 'n' || (ch = next_char()) != 't' || (ch = next_char()) != 's')
                error("invalid keyword..");
            ch = next_char();
            return mk_token(REQUIREMENTS_ID);
        case 't':
            if ((ch = next_char()) != 'y' || (ch = next_char()) != 'p' || (ch = next_char()) != 'e' || (ch = next_char()) != 's')
                error("invalid keyword..");
            ch = next_char();
            return mk_token(TYPES_ID);
        default:
            error("invalid keyword..");
        }
    case '#':
        if ((ch = next_char()) != 't')
            error("invalid keyword..");
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
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    case 'g':
    case 'h':
    case 'i':
    case 'j':
    case 'k':
    case 'l':
    case 'm':
    case 'n':
    case 'o':
    case 'p':
    case 'q':
    case 'r':
    case 's':
    case 't':
    case 'u':
    case 'v':
    case 'w':
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