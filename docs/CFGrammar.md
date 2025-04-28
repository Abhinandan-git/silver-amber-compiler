# Grammar for the languge

- **Program Structure**
  - `program -> declList`
  - `declList -> declList decl`
  - `declList -> decl`

- **Declaration Disambiguation**
  - `decl -> typeSpec ID declRest`
  - `declRest -> varDeclRest`
  - `declRest -> ( parms ) stmt`

- **Variable Declarations**
  - `varDeclRest -> varDeclListRest ;`
  - `varDeclListRest -> , varDeclInit varDeclListRest`
  - `varDeclListRest -> ''`
  - `varDeclInit -> varDeclId`
  - `varDeclId -> ID`
  - `varDeclId -> ID [ NUMCONST ]`

- **Type Specifiers**
  - `typeSpec -> integer`
  - `typeSpec -> boolean`
  - `typeSpec -> character`

- **Function Parameters**
  - `parms -> parmList`
  - `parms -> ''`
  - `parmList -> parmList ; parmTypeList`
  - `parmList -> parmTypeList`
  - `parmTypeList -> typeSpec parmIdList`
  - `parmIdList -> parmIdList , parmId`
  - `parmIdList -> parmId`
  - `parmId -> ID`
  - `parmId -> ID [ ]`

- **Statements**
  - `stmt -> expStmt`
  - `stmt -> compoundStmt`
  - `stmt -> selectStmt`
  - `stmt -> iterStmt`
  - `stmt -> returnStmt`
  - `stmt -> breakStmt`

- **Compound & Expression Statements**
  - `expStmt -> exp ;`
  - `expStmt -> ;`
  - `compoundStmt -> { localDecls stmtList }`
  - `localDecls -> localDecls scopedVarDecl`
  - `localDecls -> ''`
  - `stmtList -> stmtList stmt`
  - `stmtList -> ''`

- **Scoped Declarations**
  - `scopedVarDecl -> static typeSpec varDeclInit ;`
  - `scopedVarDecl -> typeSpec varDeclInit ;`

- **Control Flow Statements**
  - `selectStmt -> if simpleExp then stmt`
  - `iterStmt -> while simpleExp do stmt`
  - `iterStmt -> for ID = iterRange do stmt`
  - `iterRange -> simpleExp to simpleExp`
  - `returnStmt -> return ;`
  - `returnStmt -> return exp ;`
  - `breakStmt -> break ;`

- **Expressions**
  - `exp -> mutable = exp`
  - `exp -> simpleExp`
  - `simpleExp -> simpleExp or andExp`
  - `simpleExp -> andExp`
  - `andExp -> andExp and unaryRelExp`
  - `andExp -> unaryRelExp`
  - `unaryRelExp -> not unaryRelExp`
  - `unaryRelExp -> relExp`
  - `relExp -> minmaxExp relop minmaxExp`
  - `relExp -> minmaxExp`

- **Relational Operators**
  - `relop -> <= | < | > | >= | == | !=`

- **Arithmetic Expressions**
  - `minmaxExp -> minmaxExp minmaxop sumExp`
  - `minmaxExp -> sumExp`
  - `sumExp -> sumExp sumop mulExp`
  - `sumExp -> mulExp`
  - `sumop -> + | −`
  - `mulExp -> mulExp mulop unaryExp`
  - `mulExp -> unaryExp`
  - `mulop -> * | / | %`

- **Unary Expressions**
  - `unaryExp -> unaryop unaryExp`
  - `unaryExp -> factor`
  - `unaryop -> − | * | ?`

- **Factors**
  - `factor -> immutable`
  - `factor -> mutable`
  - `mutable -> ID`
  - `immutable -> ( exp )`
  - `immutable -> call`
  - `immutable -> constant`

- **Function Calls**
  - `call -> ID ( args )`
  - `args -> argList`
  - `args -> ''`
  - `argList -> argList , exp`
  - `argList -> exp`

- **Constants**
  - `constant -> NUMCONST`
  - `constant -> CHARCONST`
  - `constant -> STRINGCONST`
  - `constant -> true`
  - `constant -> false`

# FIRST Table