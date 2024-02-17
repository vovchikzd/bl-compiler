%option C++

%{

using std::cout;
using std::endl;

%}

WS      [ \t\n\v]
KEYS    if|else|while|func|return|print
DIGIT   [0-9]
DIGIT1  [1-9]
OP      [\+\-\*\/\=\>\<]
ID      [a-zA-Z_][a-zA-Z_0-9]*
OBR     [\(\{]
CBR     [\)\}]
CL      \:
SCL     \;

%%

{WS}              /* do nothing */
{KEYS}            { yyout << "keyword <"         << yytext << "> length: [" << yyleng << "]\n"; return 1; }
{OP}              { yyout << "operator <"        << yytext << "> length: [" << yyleng << "]\n"; return 1; }
{DIGIT1}{DIGIT}*  { yyout << "number <"          << yytext << "> length: [" << yyleng << "]\n"; return 1; }
{ID}*             { yyout << "ID <"              << yytext << "> length: [" << yyleng << "]\n"; return 1; }
{OBR}             { yyout << "opening bracket <" << yytext << "> length: [" << yyleng << "]\n"; return 1; }
{CBR}             { yyout << "closing bracket <" << yytext << "> length: [" << yyleng << "]\n"; return 1; }
{CL}              { yyout << "colon <"           << yytext << "> length: [" << yyleng << "]\n"; return 1; }
{SCL}             { yyout << "semicolon <"       << yytext << "> length: [" << yyleng << "]\n"; return 1; }
{DIGIT}{ID}*      { yyout << "\tERROR <"         << yytext << "> length: [" << yyleng << "]\n"; return 1; }
.                 { yyout << "\tUNKNOWN <"       << yytext << "> length: [" << yyleng << "]\n"; return 1; }

%%
