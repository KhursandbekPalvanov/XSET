/* https://blog.disonds.com/2017/02/25/kak-vynesti-funktsiyu-otdelnyj-faj/ */

	char city1[20]; //fromcity
	char city2[20]; //tocity
	int result;

open_site() {
	
	/* Open WebTours site */
	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_add_auto_header("sec-ch-ua", 
		"\"Google Chrome\";v=\"111\", \"Not(A:Brand\";v=\"8\", \"Chromium\";v=\"111\"");

	web_add_auto_header("sec-ch-ua-mobile", 
		"?0");

	web_add_auto_header("sec-ch-ua-platform", 
		"\"Windows\"");
	

/*Correlation comment - Do not change!  Original value='136172.167193196HAAtDffpiftcAczpVDfV' Name ='userSession' Type ='ResponseBased'*/
	web_reg_save_param_attrib(
		"ParamName=userSession",
		"TagName=input",
		"Extract=value",
		"Name=userSession",
		"Type=hidden",
		SEARCH_FILTERS,
		"IgnoreRedirections=No",
		"RequestUrl=*/nav.pl*",
		LAST);
		

	//CHECK: Response - /WebTours/home.html	
	web_reg_find("Text=Welcome to the Web Tours site",
		LAST);
	
	
	web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);
	
}

login() {
	
	/* Login [jojo|bean] */
	web_add_header("Origin", 
		"http://localhost:1080");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");
	

	//CHECK: Response - /cgi-bin/login.pl
	web_reg_find("Text/IC=User password was correct",
	LAST);
	//CHECK: Response - /cgi-bin/login.pl?intro=true
	web_reg_find("Text=Welcome, <b>{login}</b>, to the Web Tours reservation pages",
	LAST);
	
	
	web_submit_data("login.pl",
		"Action=http://localhost:1080/cgi-bin/login.pl",
		"Method=POST",
		"TargetFrame=body",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/nav.pl?in=home",
		"Snapshot=t2.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=userSession", "Value={userSession}", ENDITEM,
		"Name=username", "Value={login}", ENDITEM,
		"Name=password", "Value={password}", ENDITEM,
		"Name=login.x", "Value=46", ENDITEM,
		"Name=login.y", "Value=7", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		LAST);

}

logout() {
	
	/* Logout */
	
	//CHECK: Response - /WebTours/home.html	
	web_reg_find("Text=Welcome to the Web Tours site",
		LAST);
	
	
	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		LAST);

}

check_cities() {
	
	/* Проверка на одинаковость городов. Если одинаково, то переопределяем tocity. (Update value - each occurrence) */
	lr_save_string(lr_eval_string("{departCity}"), "fromcity");
	strcpy(city1, lr_eval_string("{fromcity}"));
	lr_output_message("depart-from - %s", city1);
	
	lr_save_string(lr_eval_string("{arriveCity}"), "tocity");
	strcpy(city2, lr_eval_string("{tocity}"));
	lr_output_message("arrive-to - %s", city2);
	
	result = strcmp(city1, city2);
	lr_output_message("result %d", result);
	
	lr_output_message("MATCH CHECK CITIES");
	while (strcmp(lr_eval_string("{fromcity}"), lr_eval_string("{tocity}")) == 0)
	{
		lr_output_message("CHECK: city1 == city2");
		lr_save_string(lr_eval_string("{arriveCity}"), "tocity");
	}
	//	сохраняем в параметры {fromcity} {tocity} для дальнейших POST...
}
