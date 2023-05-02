Action_LoginLogout()
{
	
	lr_start_transaction("UC_01_HW5_LoginLogout");
	
	web_set_sockets_option("SSL_VERSION", "AUTO");
	
	/* Open WebTours site */
	lr_start_transaction("open_webtours_site");

	open_site();

	lr_end_transaction("open_webtours_site", LR_AUTO);


//-delay 5sec
	

	/* Login [jojo|bean] */
	lr_start_transaction("login");

	login();

	lr_end_transaction("login", LR_AUTO);


//-delay 5sec
	
	
	/* Go to Flights */
	lr_start_transaction("go_to_flights");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");


	//Response - /cgi-bin/welcome.pl?page=search
	web_reg_find("Text=User has returned to the search page.  Since user has already logged on",
	LAST);
	//Response - /cgi-bin/welcome.pl?page=welcome
	web_reg_find("Text/IC=<font color=\"#003366\">&nbsp;&nbsp;<b>Find Flight</font></b>",
	LAST);


	web_url("Search Flights Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("go_to_flights", LR_AUTO);
	
	
//-delay 5sec
	
	
	/* Logout */
	lr_start_transaction("logout");
	
	logout();

	lr_end_transaction("logout", LR_AUTO);

	
	lr_end_transaction("UC_01_HW5_LoginLogout", LR_AUTO);

	return 0;
}