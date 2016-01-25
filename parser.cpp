#include "parser.h"

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
	try {
		s->scan(infile);
	}
	catch (exception e) {
		throw;
	}

	toks = s->toks;
	it = toks.begin();
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
	match(COMMA); predicate(); predicateList();
}

void Parser::predicate(){
	match(ID); match(LEFT_PAREN);
	parameter(); parameterList();
	match(RIGHT_PAREN);
}

void Parser::parameterList(){
	match(COMMA);
	parameter(); parameterList();
}

void Parser::parameter(){
	if (curr.t == ID)
	{
		match(STRING);
	}
	else if (curr.t == STRING)
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
