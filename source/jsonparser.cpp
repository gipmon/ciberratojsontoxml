// parser json (trabalho inicial: Rafael Almeida) gramática reconhecedora de param-list.json

%{
    #include <stdio.h>
    int yylex(void);
    int yyerror(char *s);
%}

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
	 
AT   : /* lambda */
	 | "comment" ":" 
	 | "class" ":"
	 | "value type" ":"
	 | "XML name" ":"
	 | "default value" ":"
	 ;
	 


	 
	 
