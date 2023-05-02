Action_NewRegistration()
{

	lr_start_transaction("UC_06_HW5_NewRegistration");

	web_set_sockets_option("SSL_VERSION", "AUTO");
	
	/* Open WebTours site */
	lr_start_transaction("open_webtours_site");
	open_site();
	lr_end_transaction("open_webtours_site", LR_AUTO);


//-delay 3sec
	

	/* Go to "sign up now" */
	lr_start_transaction("go_to_sign_up_now");
	
	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");
	
	//CHECK: Response - /cgi-bin/login.pl?username=&password=&getInfo=true
	web_reg_find("Text/IC=<B>First time registering? Please complete the form below.</B>",
		LAST);
	
	web_url("login.pl", 
		"URL=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/home.html", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("go_to_sign_up_now", LR_AUTO);
	

//-delay 3sec

	
	/* Entering data: username, password, firstname, lastname, address... */
	lr_start_transaction("entering_registration_data");

	web_add_auto_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");
	
	//Generator username. Example: "qwe123"
	generate_username();
	
	//CHECK: Response - /cgi-bin/login.pl
	web_reg_find("Text/IC=</style><blockquote>Thank you, <b>{username}</b>, for registering and welcome to the Web Tours family.",
		LAST);

	web_submit_data("login.pl_2", 
		"Action=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={username}", ENDITEM, 
		"Name=password", "Value={username}", ENDITEM, 
		"Name=passwordConfirm", "Value={username}", ENDITEM, 
		"Name=firstName", "Value={pFN}", ENDITEM, 
		"Name=lastName", "Value={pLN}", ENDITEM, 
		"Name=address1", "Value={pAddr1}", ENDITEM, 
		"Name=address2", "Value={pAddr2}", ENDITEM, 
		"Name=register.x", "Value=21", ENDITEM, 
		"Name=register.y", "Value=4", ENDITEM, 
		LAST);

	lr_end_transaction("entering_registration_data", LR_AUTO);
	
	
//-delay 3sec


	/* Click "Continue" button after reg */
	lr_start_transaction("click_continue_after_reg");

	web_revert_auto_header("Origin");
	
	//CHECK: Response - /cgi-bin/welcome.pl?page=menus
	web_reg_find("Text/IC=User has returned to the home page.  Since user has already logged on",
		LAST);

	web_url("button_next.gif", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?page=menus", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("click_continue_after_reg", LR_AUTO);
	

	lr_end_transaction("UC_06_HW5_NewRegistration", LR_AUTO);

	return 0;
}