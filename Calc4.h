typedef enum { typeCon, typeId, typeOpr } nodeEnum;

typedef class Node {
	public:
	nodeEnum type;
	int label;
	std::vector <Node*> children;
	Node(nodeEnum t){
		type = t;
	}
	virtual ~Node(){};
};

typedef class ConNode : public Node{
	public:
	int value;
	ConNode(int v, nodeEnum t):Node(t){
		value = v;
	}
};

typedef class VarNode : public Node{
	public:
	int i;
	VarNode(int ii, nodeEnum t):Node(t){
		i = ii;
	}
};

typedef class OprNode : public Node{
	public:
	int oper; /* operator */
    int nops; /* number of operands */
	OprNode(int op, int nop, nodeEnum t):Node(t){
		oper = op;
		nops = nop;
	}
};

extern int sym[26];
extern Node* addr[26];