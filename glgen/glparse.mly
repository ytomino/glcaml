%{
	open Data
	let extension = ref false;;
%}

%token <string> GLCONSTANT
%token <string> GLFUNCTION
%token <string> GLTYPE
%token <int32> NUMBER
%token <string> GLNAME
%token GLCONST
%token BEGIN_EXTENSION
%token END_EXTENSION
%token EOF
%token OPEN CLOSE COMMA
%start decls
%type <unit> decls
%%

decls:
	| constant decls {  qconstants := !qconstants @ [$1] }
	| func decls { qfunctions := !qfunctions @ [$1] }
	| begin_extension decls { }
	| end_extension decls { }
	| EOF { }
	
constant:
	| GLCONSTANT NUMBER { mkconst1 $1 $2 }
	| GLCONSTANT GLCONSTANT { mkconst2 $1 $2 }	

func:
	| GLTYPE GLFUNCTION OPEN params CLOSE { mkfunc !extension $1 $2 $4 }
	
params:
	| param { [$1] }
	| param COMMA params { [$1] @ $3 }

param:	
	| GLCONST GLTYPE GLNAME { mktype3 $2 }
	| GLTYPE GLNAME { mktype2 $1 }
	| GLTYPE  { mktype1 $1}

begin_extension:
	| BEGIN_EXTENSION { extension := true }

end_extension:
	| END_EXTENSION { extension := false }
