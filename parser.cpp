#include "parser.h"
#include "datalogProgram.h"

/*datalogProgram	->	SCHEMES COLON scheme schemeList
		        FACTS COLON factList
		        RULES COLON ruleList
		        QUERIES COLON query queryList

schemeList	->	scheme schemeList
schemeList	->	epsilon

factList	->	fact factList
factList	->	epsilon

ruleList	->	rule ruleList
ruleList	->	epsilon

queryList	->	query queryList
queryList	->	epsilon

scheme   	-> 	predicate
fact    	-> 	predicate PERIOD
rule    	->	predicate COLON_DASH predicate predicateList PERIOD
query	        ->      predicate Q_MARK

predicateList	->	COMMA predicate predicateList
predicateList	->	epsilon

predicate	->	ID LEFT_PAREN parameter parameterList RIGHT_PAREN

parameterList	-> 	COMMA parameter parameterList
parameterList	-> 	epsilon

parameter	->	STRING
parameter	->	ID*/


void Parser::parse(char * infile){
	Scanner * s = new Scanner();
	DatalogProgram* prog;
	try {
		s->scan(infile);
		// print_toks(s->toks,cout);
		toks = s->toks;
		it = toks.begin();
		curr = *it;
		prog = new DatalogProgram();
		Predicate* p = new Predicate("BAR");
		p->params.push_back(new Parameter((string)"FOO"));
		prog->addScheme(p);
		cout << prog->toString() << endl;
		datalogProgram();
	}
	catch (exception e) {
		delete prog;
		throw;
	}
}

void Parser::datalogProgram(){
	match(SCHEMES); match(COLON);
	scheme();
	schemeList();
	match(FACTS); match(COLON);
	factList();
	match(RULES); match(COLON);
	ruleList();
	match(QUERIES); match(COLON);
	query(); queryList();
}

void Parser::schemeList() {
	try {scheme();}
	catch (exception e) {return;}
	schemeList();
}

void Parser::factList(){
	try {fact();}
	catch (exception e) {return;}
	factList();
}

void Parser::queryList(){
	try {query();}
	catch (exception e) {return;}
	queryList();
}

void Parser::ruleList(){
	try {rule();}
	catch (exception e) {return;}
	ruleList();
}

void Parser::scheme(){
	predicate();
}

void Parser::fact(){
	predicate(); match(PERIOD);
}

void Parser::rule(){
	predicate();
	match(COLON_DASH);
	predicate(); predicateList();
	match(PERIOD);
}

void Parser::query()
{
	predicate();
	match(Q_MARK);
}

void Parser::predicateList(){
	try {
	match(COMMA); predicate();}
	catch (exception& e) {return;}
	predicateList();
}

void Parser::predicate(){
	match(ID); match(LEFT_PAREN);
	parameter(); parameterList();
	match(RIGHT_PAREN);
}

void Parser::parameterList(){
	try {
		match(COMMA);
		parameter();
	}
	catch (exception& e) {return;}
	parameterList();
}

void Parser::parameter(){
	if (curr.t == STRING)
	{
		match(STRING);
	}
	else if (curr.t == ID)
	{
		match(ID);
	}
	else throw runtime_error("Parse error: invalid token.");
}

void Parser::match(token t)
{
	if (t != curr.t) throw runtime_error("Tokens don't match.");
	it++;
	curr = *it;
}
