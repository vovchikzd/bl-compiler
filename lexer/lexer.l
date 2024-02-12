%option C++

%{

using std::cout;
using std::endl;

%}

WS     [ \t\n\v]
DIGIT  [0-9]
DIGIT1 [1-9]
OP     [\+\-\=]
LT     [a-zA-Z_]

%%

{WS}
{OP}             { cout << "operator <" << yytext[0]  << ">" << endl; return 1; }
{DIGIT1}{DIGIT}* { cout << " number <"  << yytext     << ">" << endl; return 1; }
{LT}*            { cout << " word <"    << yytext     << ">" << endl; return 1; }
.                { cout << " UNKNOWN <" << yytext[0]  << ">" << endl; return 1; }

%%
