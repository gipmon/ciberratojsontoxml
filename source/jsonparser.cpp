// parser json (trabalho inicial: Rafael Almeida) gramática reconhecedora de param-list.json

%{
    #include <stdio.h>
    int yylex(void);
    int yyerror(char *s);
%}

%token <vcomment> COMMENT
%token <vclass> CLASS
%token <vvalue> VALUE_TYPE
%token <vxml> XML_NAME
%token <vdefault> DEFAULT_VALUE


%%

File :	'{' PL '}'									         	   // File = param-list.json
	 ;															   // PL = parameter list
														           // PI = parameter item
 														           // Pk = parameter key
																   // PAL = parameter atribute list
PL   :	/* lambda */											   // AT = atribute
	 |  PI ',' PL
	 ;
	
PI   : PK '{' PAL '}'
	 ;
	 
PK   : id                                                          // reconhecido e fornecido pelo lexer2 (flex)
	 ;
	 
PAL  : /* lambda */
	 | AT ',' PAL
	 ;
	 
AT   : /* lambda */												  // String fornecida pelo lexer2 (flex)
	 | COMMENT ':' String
	 | CLASS ':' String
	 | VALUE_TYPE ':' String
	 | XML_NAME ':' String
	 | DEFAULT_VALUE ':' String
	 ;
	

	 
%%

int yyerror(const char *s)
{
    return 0;
}

	 
	 
