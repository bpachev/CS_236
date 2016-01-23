

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
