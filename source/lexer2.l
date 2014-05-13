// lexer para fornecer aspetos permitidos ao parser1

%{
    #include <stdlib.h>
%}

id      [a-z]

spaces  [ \t]+

String  ([a-z] | [A-Z] | [0-9] | spaces | valid)*

valid [-+/(^)*/=\n]

