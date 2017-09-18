#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define MAXD 4009
#define UNDEFINED -1000

class Restriction {
public:
	virtual bool check(int v1, int v2) = 0;
};

class EqualRes : public Restriction {
public:
	bool check(int v1, int v2) {
		if(v1 == UNDEFINED || v2 == UNDEFINED) return true;
		return v1 == v2;
	}
};

class DifRes : public Restriction {
public:
	bool check(int v1, int v2) {
		if(v1 == UNDEFINED || v2 == UNDEFINED) return true;
		return v1 != v2;
	}
};

class NeighborRes : public Restriction {
public:
	bool check(int v1, int v2) {
		if(v1 == UNDEFINED || v2 == UNDEFINED) return true;
		return abs(v1 - v2) == 1;
	}
};

class RightRes : public Restriction {
public:
	bool check(int v1, int v2) {
		if(v1 == UNDEFINED || v2 == UNDEFINED) return true;
		return v1 - v2 == 1;
	}
};

class LeftRes : public Restriction {
public:
	bool check(int v1, int v2) {
		if(v1 == UNDEFINED || v2 == UNDEFINED) return true;
		return v1 - v2 == -1;
	}
};

class PSR {
private:

	//restrictions upon neighbor and upon self
	vector<pair<Restriction*, int> > *adjRest, *nodeRest;
	int *values, N, D;
	
	bool checkRestrictions(int u) {
		
		//check node restrictions
		for(int it=0; it<(int)nodeRest[u].size(); it++) {
			Restriction *r = nodeRest[u][it].first;
			int val = nodeRest[u][it].second;
			if (!r->check(values[u], val)) return false;
		}
		
		//check restrictions with neighbors
		for(int it=0; it<(int)adjRest[u].size(); it++) {
			Restriction *r = adjRest[u][it].first;
			int v = adjRest[u][it].second;
			if (!r->check(values[u], values[v])) return false;
		}
		
		//no restricion broken
		return true;
	}
	
	bool backtrack(int u) {
		//all variables set and no restriction broken = success
		if (u == N) return true;
		
		//try all values
		for(int j=0; j<D; j++) {
			
			//set value
			values[u] = j;
			
			//if restrictions are ok, proceed
			if (checkRestrictions(u) && backtrack(u+1)) return true;
		}
		
		//reset value
		values[u] = UNDEFINED;
		return false;
	}
public:
	bool solve(int _N, int _D, vector<pair<Restriction*, int> >* _adjRest, vector<pair<Restriction*, int> >* _nodeRest, int* _values) {
		
		//set all inner variables
		adjRest = _adjRest;
		nodeRest = _nodeRest;
		values = _values;
		N = _N; D = _D;
		
		//reset values
		for(int u=0; u<N;u++) values[u] = UNDEFINED;
		
		//go
		return backtrack(0);
	}
};

//Restrictor instances
static Restriction* equalRestrictor = new EqualRes();
static Restriction* difRestrictor = new DifRes();
static Restriction* neighborRestrictor = new NeighborRes();
static Restriction* rightRestrictor = new RightRes();
static Restriction* leftRestrictor = new LeftRes();

bool model1() {

	//adjRest are restrictions between vertices
	//nodeRest are restrictions upon vertices and a constant value
	vector<pair<Restriction*, int> > adjRest[MAXN], nodeRest[MAXN];

	//number of nodes and possible values for them
	int N = 25;
	int D = 5;
	
	//map os nodes by name
	map<string, int> id;
	
	//houses
	id["vermelho"] = 0;
	id["azul"] = 1;
	id["amarelo"] = 2;
	id["marfim"] = 3;
	id["verde"] = 4;
	//nationalities
	id["ingles"] = 5;
	id["noruegues"] = 6;
	id["japones"] = 7;
	id["espanhol"] = 8;
	id["ucraniano"] = 9;
	//cigarettes
	id["Kool"] = 10;
	id["Winston"] = 11;
	id["Lucky Strike"] = 12;
	id["Parliament"] = 13;
	id["Chesterfield"] = 14;
	//beverages
	id["cafe"] = 15;
	id["leite"] = 16;
	id["cha"] = 17;
	id["agua"] = 18;
	id["suco"] = 19;
	//animals
	id["zebra"] = 20;
	id["cachorro"] = 21;
	id["caramujo"] = 22;
	id["raposa"] = 23;
	id["cavalo"] = 24;
	
	//no house share the same property
	for(int u=0; u<N; u++) {
		for(int v=5*(u/5); v<5*(u/5) + 5; v++) {
			if (u == v) continue;
			adjRest[u].push_back(make_pair(difRestrictor, v));
		}
	}
	
	//"O ingles mora na cada vermelha"
	adjRest[id["ingles"]].push_back(make_pair(equalRestrictor, id["vermelho"]));
	adjRest[id["vermelho"]].push_back(make_pair(equalRestrictor, id["ingles"]));
	
	//"O espanhol e dono do cachorro"
	adjRest[id["espanhol"]].push_back(make_pair(equalRestrictor, id["cachorro"]));
	adjRest[id["cachorro"]].push_back(make_pair(equalRestrictor, id["espanhol"]));
	
	//"O noruegues mora na primeira casa a esquerda"
	nodeRest[id["noruegues"]].push_back(make_pair(equalRestrictor, 0));
	
	//"Fumam-se cigarros Kool na casa amarela"
	adjRest[id["Kool"]].push_back(make_pair(equalRestrictor, id["amarelo"]));
	adjRest[id["amarelo"]].push_back(make_pair(equalRestrictor, id["Kool"]));
	
	//"O homem que fuma cigarros Chesterfield mora na casa ao lado do homem que mora com a raposa"
	adjRest[id["Chesterfield"]].push_back(make_pair(neighborRestrictor, id["raposa"]));
	adjRest[id["raposa"]].push_back(make_pair(neighborRestrictor, id["Chesterfield"]));
	
	//"O noruegues mora ao lado da casa azul"
	adjRest[id["noruegues"]].push_back(make_pair(neighborRestrictor, id["azul"]));
	adjRest[id["azul"]].push_back(make_pair(neighborRestrictor, id["noruegues"]));
	
	//"O fumante de cigarros Winston cria caramujos"
	adjRest[id["Winston"]].push_back(make_pair(equalRestrictor, id["caramujo"]));
	adjRest[id["caramujo"]].push_back(make_pair(equalRestrictor, id["Winston"]));
	
	//"O fumante de cigarros Lucky Strike bebe suco de laranja"
	adjRest[id["Lucky Strike"]].push_back(make_pair(equalRestrictor, id["suco"]));
	adjRest[id["suco"]].push_back(make_pair(equalRestrictor, id["Lucky Strike"]));
	
	//"O ucraniano bebe cha"
	adjRest[id["ucraniano"]].push_back(make_pair(equalRestrictor, id["cha"]));
	adjRest[id["cha"]].push_back(make_pair(equalRestrictor, id["ucraniano"]));
	
	//"O japones fuma cigarros Parliament"
	adjRest[id["japones"]].push_back(make_pair(equalRestrictor, id["Parliament"]));
	adjRest[id["Parliament"]].push_back(make_pair(equalRestrictor, id["japones"]));
	
	//"Fumam-se cigarros Kool em uma casa ao lado da casa em que fica o cavalo"
	adjRest[id["Kool"]].push_back(make_pair(neighborRestrictor, id["cavalo"]));
	adjRest[id["cavalo"]].push_back(make_pair(neighborRestrictor, id["Kool"]));
	
	//"Bebe-se cafe na casa verde"
	adjRest[id["cafe"]].push_back(make_pair(equalRestrictor, id["verde"]));
	adjRest[id["verde"]].push_back(make_pair(equalRestrictor, id["cafe"]));
	
	//"A casa verde esta imediatamente a direita (a sua direita) da casa marfim"
	adjRest[id["marfim"]].push_back(make_pair(leftRestrictor, id["verde"]));
	adjRest[id["verde"]].push_back(make_pair(rightRestrictor, id["marfim"]));
	
	//"Bebe-se leite na casa do meio"
	nodeRest[id["leite"]].push_back(make_pair(equalRestrictor, 2));

	//execute
	PSR solver;
	int answer[MAXN];
	printf("executing...\n");
	if(!solver.solve(N, D, adjRest, nodeRest, answer)) {
		printf("no solution found\n");
		return false;
	}
	
	//printf answer:
	for(map<string, int>::iterator it = id.begin(); it != id.end(); it++) {
		printf("%s is in house %d\n", it->first.c_str(), answer[it->second]);
	}
	return true;
}

int main() {
	model1();
	return 0;
}