It may not be completely clear what this lab is trying to do....

At it's heart, it wants to convert our normal infix expressions like:

(a + b) * (c + d)

into a tree.  These trees are super important for things like code generation
and execution.  For instance, you will see when you take CS61 that we have
machine instructions like ADD, SUB, and MULT; but we don't have anything
for parenthesis.  What we want is a way to convert the expression into
an unambiguous data structure that completely describes the operations,
values, and the order in which to apply them.

So....

We start with the expression above.  If we run it through the provided
arithmeticExpression::infix_to_postfix() method, we get

a b + c d + *

This is sometimes called RPN (Reverse Polish Notation) after Łukasiewicz,
a Polish mathematician that came up with the idea.  Together with a stack,
we can compute values unabiguously without regard to parenthesis or to
operator precidence (so you don't have to remember that */ is stronger
than +- or that you have to do things left to right).

We think of working through the string, one token at a time in conjunction
with a stack.

If the token is a name or number, we push it onto the stack.  If it is an
operator, we pop some operands off the stack, perform the operation, and
push the result back onto the stack.  This can work with either numbers
(a calculator) or symbols.  So given

2 5 + 4 12 + *
^ Push 2 onto the stack
[   2   ]  
---------

2 5 + 4 3 + *
  ^ Push 5 onto the stack
[   5   ]  
[   2   ]
---------

2 5 + 4 3 + *
    ^ Pop 5 and 2 off the stack, put (2 + 5) onto the stack
[   7   ]  
---------

2 5 + 4 3 + *
      ^ Push 4 onto the stack
[   4   ]
[   7   ]
---------
2 5 + 4 3 + *
         ^ Push 3 onto the stack
[   3  ]
[   4   ]
[   7   ]
---------

2 5 + 4 3 + *
           ^ Pull 3 and 4 off the stack, put 12 back on
[   12  ]
[   7   ]
---------

2 5 + 4 3 + *
             ^ Pull 48 and 7 off the stack, put (7 * 12) back on
[   94   ]
---------

Our answer is now on top of the stack!

For this lab, instead of doing it as a calculator, we'll be making TreeNode* and putting them on the stack

a b + c d + *
^ Make a treenode with a and put it on the stack
[   <a>   ]   
-----------
	   
a b + c d + *
  ^ Make a treenode with b and put it on the stack
[   <b>   ]   
[   <a>   ]   
-----------
	   
a b + c d + *
    ^ Pop the <b> tree and the <a> tree off the stack and make a new tree with + as the key
      and <a> and <b> as left/right sub-trees and push that on the stack
[   <+>   ]
[   / \   ]
[ <a> <b> ]   
-----------

a b + c d + *
      ^ Make <c>
[   <c>   ]   
[   <+>   ]
[   / \   ]
[ <a> <b> ]   
-----------

a b + c d + *
        ^ Make <d>
[   <d>   ]   
[   <c>   ]   
[   <+>   ]
[   / \   ]
[ <a> <b> ]   
-----------

a b + c d + *
          ^ Pop <c> and <d> and make a new + tree with those as children
[   <+>   ]
[   / \   ]
[ <c> <d> ]   
[   <+>   ]
[   / \   ]
[ <a> <b> ]   
-----------
	   

a b + c d + *
            ^ Finally, pop the two plus-trees off and make a times-tree
[         <*>        ]
[       /    \       ]
[      /      \      ]
[     /        \     ]
[    /          \    ]
[   <+>        <+>   ]
[   / \        / \   ]
[ <a> <b>    <c> <d> ]
---------------------

The tree on top is the tree you are supposed to work with
	   
