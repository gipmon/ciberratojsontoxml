%{
    #include <stdlib.h>
%}

id      ([a-z]|[A-Z]|{spaces}|[-])+

spaces  [ \t]+

str  [^\"]*

comment ["]comment["]

class ["]class["]

value_type ["]value type["]

xml_name ["]XML name["]

default_value ["]default value["]

double ["]double["]

uint ["]uint["]

switch ["]switch["]

booelan ["]boolean["]

class_value {str}

default_value_value {str}

xml_name_value {str}

/*valid [-+/(^)/=\n:;,.!*]*/

%%

{id}        { p->vid = strdup(yytext); return ID; }

{spaces}    { }

/*{valid}     { return yytext[0]; }*/

{str}		{ p->vstr = yytext[0]; return STR; }

{comment}	{ return COMMENT; }

{class}		{ return CLASS; }

{value_type} { return VALUE_TYPE; }

{xml_name}  { return XML_NAME; }

{default_value} { return DEFAULT_VALUE; }
/*.           { p->vchar = yytext[0]; return OTHER; }*/

{double} {return DOUBLE;}

{uint} {return UINT}

{switch} {return SWITCH}

{boolean} {return BOOLEAN}

{class_value} { p->vclassvalue = yytext[0]; return CLASS_VALUE; }

{xml_name_value} { p->vxml = yytext[0]; return XML_NAME_VALUE; }

{default_value_value} { p->vdvv = yytext[0]; return DEFAULT_VALUE_VALUE; }

%%