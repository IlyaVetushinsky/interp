#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include "Calc4.h"
#include "Calc4.tab.hpp"
#include <FlexLexer.h>
char lbl = 0;
int ex(Node *p1) {
 if (!p1) return 0;
if (lbl == p1->label)
lbl = 0;
 if (!lbl)
switch(p1->type) {
case typeCon: {ConNode* conn = dynamic_cast<ConNode*>(p1); return conn->value;}
case typeId: {VarNode* varn = dynamic_cast<VarNode*>(p1); return sym[varn->i];}
case typeOpr:{
OprNode* p = dynamic_cast<OprNode*>(p1);
switch(p->oper) {
case WHILE: {while(ex(p->children[0])) ex(p->children[1]); return 0;}
case IF:{ if (ex(p->children[0]))
ex(p->children[1]);
else if (p->nops > 2)
ex(p->children[2]);
return 0;}
case PRINT: {if (p->children[0]->type == typeId){
				VarNode* varn = dynamic_cast<VarNode*>(p->children[0]);
				printf ("%c = ",varn->i+'a');
			}
printf("%d\n", ex(p->children[0])); return 0;}
case ';':{ ex(p->children[0]); return ex(p->children[1]);}
case '=':{ VarNode* varn = dynamic_cast<VarNode*>(p->children[0]);
		return sym[varn->i] = ex(p->children[1]);}
case UMINUS:{ return -ex(p->children[0]);}
case '+': {return ex(p->children[0]) + ex(p->children[1]);}
case '-': {return ex(p->children[0]) - ex(p->children[1]);}
case '*':{ return ex(p->children[0]) * ex(p->children[1]);}
case '/': {return ex(p->children[0]) / ex(p->children[1]);}
case '<': {return ex(p->children[0]) < ex(p->children[1]);}
case '>':{ return ex(p->children[0]) > ex(p->children[1]);}
case GE: {return ex(p->children[0]) >= ex(p->children[1]);}
case LE:{ return ex(p->children[0]) <= ex(p->children[1]);}
case NE: {return ex(p->children[0]) != ex(p->children[1]);}
case EQ: {return ex(p->children[0]) == ex(p->children[1]);}
case GOTO: {VarNode* varn = dynamic_cast<VarNode*>(p->children[0]);
		if (!addr[varn->i])
			printf("Identificator '%c' is not detected: - ignore goto!\n", varn->i+'a');
		else
			lbl = varn->i;
return 0;}
}
}
 }
else
{
switch(p1->type) {
case typeCon: {return 0;}
case typeId: {return 0;}
case typeOpr:{
OprNode* p = dynamic_cast<OprNode*>(p1);
switch(p->oper) {
case WHILE: {do ex(p->children[1]); while (ex(p->children[0])); return 0;}
case IF: {ex(p->children[1]);
if (lbl && p->nops > 2)
ex(p->children[2]);
return 0;}
case ';': {ex(p->children[0]); return ex(p->children[1]);}
default: {return 0;}
}
}
}
}
 return 0;
}
int exec(Node *p)
{
do
{
ex(p);
}
while (lbl);
}

void print_Tree(Node *p, int level)
{
	if (p) {
		for (int i = 0; i < 3*level - 3; ++i) {
			printf (" ");
		}
		if (level)
			printf ("-->");
		switch(p->type) {
		case typeCon:{ ConNode* conn = dynamic_cast<ConNode*>(p);
		printf ("%d", conn->value);}
		case typeId: {VarNode* varn = dynamic_cast<VarNode*>(p);
		printf ("%d", varn->i);}
		case typeOpr: {OprNode* oprn = dynamic_cast<OprNode*>(p);
		printf ("%d\n", oprn->oper);}
		}
		if (p->type == typeOpr){
			OprNode* oprn = dynamic_cast<OprNode*>(p);
			for (int i = 0; i < oprn->nops; ++i) {
				print_Tree(oprn->children[i], level + 1);
			}
		}
	}
}