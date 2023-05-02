Action_View_ItenaryList()
{

	lr_start_transaction("UC_04_HW5_View_ItenaryList");
	
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
	

	/* Go to Itenary */
	lr_start_transaction("go_to_itenary");
	
	
	//Response - /cgi-bin/welcome.pl?page=itinerary
	web_reg_find("Text/IC=User wants the intineraries",
		LAST);
	
	/* не подходит, если нет вообще путевых листов у данного аккаунта */
		//Response - /cgi-bin/itinerary.p
	web_reg_find("Text/IC={firstName} {lastName}",
		LAST);
		

	web_url("Itinerary Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("go_to_itenary", LR_AUTO);
	
	
//-delay 5sec
	

//	/* Logout */
//	lr_start_transaction("logout");
//	logout();
//	lr_end_transaction("logout", LR_AUTO);

	
	lr_end_transaction("UC_04_HW5_View_ItenaryList", LR_AUTO);

	return 0;
}