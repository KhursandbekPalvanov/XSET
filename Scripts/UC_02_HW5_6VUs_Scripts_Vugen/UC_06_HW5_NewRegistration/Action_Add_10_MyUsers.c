Action_Add_10_MyUsers()
{
	/* Запускать если 10 пользоваетлей не зарегистрированы еще. 10 итераций в run logic */

	lr_start_transaction("UC_06_HW5_NewRegistration");

	web_set_sockets_option("SSL_VERSION", "AUTO");
	
	/* Open WebTours site */
	lr_start_transaction("open_webtours_site");
	open_site(); //не забыть поменять параметр на рандом после регистрации 10 новых юзеров
	lr_end_transaction("open_webtours_site", LR_AUTO);


	lr_think_time(5); //delay 5sec
	

	/* Go to "sign up now" */
	lr_start_transaction("go_to_sign_up_now");
	
	web_revert_auto_header("Upgrade-Insecure-Requests");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");


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
	

	lr_think_time(5); //delay 5sec

	
	/* Entering data: username, password, firstname, lastname, address... */
	lr_start_transaction("entering_registration_data");

	web_add_auto_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");
	

	web_submit_data("login.pl_2", 
		"Action=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=info", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=passwordConfirm", "Value={password}", ENDITEM, 
		"Name=firstName", "Value={firstName}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={address1}", ENDITEM, 
		"Name=address2", "Value={address2}", ENDITEM, 
		"Name=register.x", "Value=21", ENDITEM, 
		"Name=register.y", "Value=4", ENDITEM, 
		LAST);

	lr_end_transaction("entering_registration_data", LR_AUTO);
	
	
	lr_think_time(5); //delay 5sec


	/* Click "Continue" button after reg */
	lr_start_transaction("click_continue_after_reg");

	web_revert_auto_header("Origin");
	

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


	/* Logout */
	lr_start_transaction("logout");
	
	logout();

	lr_end_transaction("logout", LR_AUTO);
	

	lr_end_transaction("UC_06_HW5_NewRegistration", LR_AUTO);
	
	return 0;
}
