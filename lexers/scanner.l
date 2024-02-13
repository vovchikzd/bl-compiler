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

{WS}             /* do nothing */
{KEYS}            { cout << "keyword <"         << yytext << ">" << endl; return 1; }
{OP}              { cout << "operator <"        << yytext << ">" << endl; return 1; }
{DIGIT1}{DIGIT}*  { cout << "number <"          << yytext << ">" << endl; return 1; }
{ID}*             { cout << "ID <"              << yytext << ">" << endl; return 1; }
{OBR}             { cout << "opening bracket <" << yytext << ">" << endl; return 1; }
{CBR}             { cout << "closing bracket <" << yytext << ">" << endl; return 1; }
{CL}              { cout << "colon <"           << yytext << ">" << endl; return 1; }
{SCL}             { cout << "semicolon <"       << yytext << ">" << endl; return 1; }
{DIGIT}{ID}*      { cout << "\tERROR <"         << yytext << ">" << endl; return 1; }
.                 { cout << "\tUNKNOWN <"       << yytext << ">" << endl; return 1; }

%%
