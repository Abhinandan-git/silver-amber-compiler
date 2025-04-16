# Grammar for the languge

1. program -> declList

2. declList -> declList decl  
3. declList -> decl

4. decl -> varDecl  
5. decl -> funDecl

6. varDecl -> typeSpec varDeclList ;

7. scopedVarDecl -> static typeSpec varDeclList ;  
8. scopedVarDecl -> typeSpec varDeclList ;

9. varDeclList -> varDeclList , varDeclInit  
10. varDeclList -> varDeclInit

11. varDeclInit -> varDeclId

12. varDeclId -> ID  
13. varDeclId -> ID [ NUMCONST ]

14. typeSpec -> integer
15. typeSpec -> boolean
16. typeSpec -> character

17. funDecl -> typeSpec ID ( parms ) stmt  
18. funDecl -> ID ( parms ) stmt

19. parms -> parmList  
20. parms -> ''

21. parmList -> parmList ; parmTypeList  
22. parmList -> parmTypeList

23. parmTypeList -> typeSpec parmIdList

24. parmIdList -> parmIdList , parmId  
25. parmIdList -> parmId

26. parmId -> ID  
27. parmId -> ID [ ]

28. stmt -> expStmt  
29. stmt -> compoundStmt  
30. stmt -> selectStmt  
31. stmt -> iterStmt  
32. stmt -> returnStmt  
33. stmt -> breakStmt

34. expStmt -> exp ;  
35. expStmt -> ;

36. compoundStmt -> { localDecls stmtList }

37. localDecls -> localDecls scopedVarDecl  
38. localDecls -> ''

39. stmtList -> stmtList stmt  
40. stmtList -> ''

41. selectStmt -> if simpleExp then stmt

42. iterStmt -> while simpleExp do stmt  
43. iterStmt -> for ID = iterRange do stmt

44. iterRange -> simpleExp to simpleExp

45. returnStmt -> return ;  
46. returnStmt -> return exp ;

47. breakStmt -> break ;

48. exp -> mutable = exp  
49. exp -> simpleExp

50. simpleExp -> simpleExp or andExp  
51. simpleExp -> andExp

52. andExp -> andExp and unaryRelExp  
53. andExp -> unaryRelExp

54. unaryRelExp -> not unaryRelExp  
55. unaryRelExp -> relExp

56. relExp -> minmaxExp relop minmaxExp  
57. relExp -> minmaxExp

58. relop -> <=  
59. relop -> <  
60. relop -> >  
61. relop -> >=  
62. relop -> ==  
63. relop -> !=

64. minmaxExp -> minmaxExp minmaxop sumExp  
65. minmaxExp -> sumExp

66. sumExp -> sumExp sumop mulExp  
67. sumExp -> mulExp

68. sumop -> +  
69. sumop -> −

70. mulExp -> mulExp mulop unaryExp  
71. mulExp -> unaryExp

72. mulop -> ∗  
73. mulop -> /  
74. mulop -> %

75. unaryExp -> unaryop unaryExp  
76. unaryExp -> factor

77. unaryop -> −  
78. unaryop -> ∗  
79. unaryop -> ?

80. factor -> immutable  
81. factor -> mutable

82. mutable -> ID

83. immutable -> ( exp )  
84. immutable -> call  
85. immutable -> constant

86. call -> ID ( args )

87. args -> argList  
88. args -> ''

89. argList -> argList , exp  
90. argList -> exp

91. constant -> NUMCONST  
92. constant -> CHARCONST  
93. constant -> STRINGCONST  
94. constant -> true  
95. constant -> false
