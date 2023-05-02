generate_username()
{
	char * sBuff1;
	char * sBuff2;
	char * sBuff3;
	int sBuff4;
	int sBuff5;
	int sBuff6;
	
	
	sBuff1 = lr_eval_string("{pRandomLetter}");
	sBuff2 = lr_eval_string("{pRandomLetter}");
	sBuff3 = lr_eval_string("{pRandomLetter}");
	sBuff4 = atoi(lr_eval_string("{pRandomNumber}"));
	sBuff5 = atoi(lr_eval_string("{pRandomNumber}"));
	sBuff6 = atoi(lr_eval_string("{pRandomNumber}"));
	
	// username: abc123
	lr_param_sprintf ("username", "%s%s%s%d%d%d", 
	                 sBuff1,
	                 sBuff2,
	                 sBuff3,
	                 sBuff4,
	                 sBuff5,
	                 sBuff6
	                 );
	lr_message("username - %s", lr_eval_string("{username}"));
	

	return 0;
}
