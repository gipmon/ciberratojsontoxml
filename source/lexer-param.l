%{
    #include <stdlib.h>
%}

id      ([a-z] | [A-Z] | spaces | [-])+

spaces  [ \t]+

str  [^\"]*

comment "comment"

class "class"

value_type "value type"

xml_name "XML name"

default_value "default value"

/*valid [-+/(^)/=\n:;,.!*]*/

%%

{id}        { p->vid = yytext[0]; return ID; }

{spaces}    { }

/*{valid}     { return yytext[0]; }*/

{str}		{ p->vstr = yytext[0]; return STR; }

{comment}	{ p->vcomment = yytext[0]; return COMMENT; }

{class}		{ p->vclass = yytext[0]; return CLASS; }

{value_type} { p->vvalue = yytext[0]; return VALUE_TYPE; }

{xml_name}  { p->vxml = yytext[0]; return XML_NAME; }

{default_value} { p->vdefault = yytext[0]; return DEFAULT_VALUE; }
/*.           { p->vchar = yytext[0]; return OTHER; }*/

%%