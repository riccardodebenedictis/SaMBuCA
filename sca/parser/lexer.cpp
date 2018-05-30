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