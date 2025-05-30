$$
\begin{align}
    [\text{Prog}] &\to [\text{Stmt}]^* \\
    [\text{Stmt}] &\to
    \begin{cases}
        \text{exit}([\text{Expr}]); \\
        \text{variable}\space\text{ident} = [\text{Expr}]; \\
        \text{ident} = \text{[Expr]}; \\
        \text{if}([\text{Expr}])[\text{Scope}]\text{[IfPred]} \\
        \text{function}\space\text{ident}[\text{Scope}] \\
        \text{call}\space\text{ident}; \\
        [\text{Scope}]
    \end{cases} \\
    \text{[Scope]} &\to \{[\text{Stmt}]^*\} \\
    \text{[IfPred]} &\to
    \begin{cases}
        \text{else}\text{[Scope]} \\
        \epsilon
    \end{cases} \\
    [\text{Expr}] &\to
    \begin{cases}
        [\text{Term}] \\
        [\text{BinExpr}]
    \end{cases} \\
    [\text{BinExpr}] &\to
    \begin{cases}
        [\text{Expr}] * [\text{Expr}] & \text{prec} = 1 \\
        [\text{Expr}] / [\text{Expr}] & \text{prec} = 1 \\
        [\text{Expr}] + [\text{Expr}] & \text{prec} = 0 \\
        [\text{Expr}] - [\text{Expr}] & \text{prec} = 0 \\
    \end{cases} \\
    [\text{Term}] &\to
    \begin{cases}
        \text{int\_lit} \\
        \text{ident} \\
        ([\text{Expr}])
    \end{cases}
\end{align}
$$