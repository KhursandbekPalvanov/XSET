Action()
{

lr_start_transaction("UC_01_BuyTicket");

/* Open WebTours site */
	lr_start_transaction("open_webtours_site");
	
		web_set_sockets_option("SSL_VERSION", "AUTO");
	
		web_add_auto_header("Sec-Fetch-Site", 
			"none");
	
		web_add_auto_header("Sec-Fetch-Dest", 
			"document");
	
		web_add_auto_header("Sec-Fetch-Mode", 
			"navigate");
	
		web_add_auto_header("Sec-Fetch-User", 
			"?1");
	
		web_add_auto_header("Upgrade-Insecure-Requests", 
			"1");
	
		web_add_auto_header("sec-ch-ua", 
			"\"Google Chrome\";v=\"111\", \"Not(A:Brand\";v=\"8\", \"Chromium\";v=\"111\"");
	
		web_add_auto_header("sec-ch-ua-mobile", 
			"?0");
	
		web_add_auto_header("sec-ch-ua-platform", 
			"\"Windows\"");
		
	
	/*Correlation comment - Do not change!  Original value='136142.943782908HAAcifcpzHAiDDDDtcAVHpVVzAcf' Name ='userSession' Type ='ResponseBased'*/
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
	
	
		//Response - /WebTours/home.html	
		web_reg_find("Text=Welcome to the Web Tours site",
			LAST);
		
	
		web_url("WebTours", 
			"URL=http://localhost:1080/WebTours/", 
			"TargetFrame=", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=", 
			"Snapshot=t1.inf", 
			"Mode=HTML", 
			LAST);

	lr_end_transaction("open_webtours_site", LR_AUTO);
	
	lr_think_time(5); //delay 5sec
	
/* Login jojo|bean */
	lr_start_transaction("login");

		web_revert_auto_header("Sec-Fetch-User");
	
		web_add_auto_header("Sec-Fetch-Dest", 
			"frame");
	
		web_revert_auto_header("Upgrade-Insecure-Requests");
	
		web_add_header("Origin", 
			"http://localhost:1080");
	
		web_add_auto_header("Sec-Fetch-Site", 
			"same-origin");
		
		
		//Response - /cgi-bin/login.pl
		web_reg_find("Text/IC=User password was correct",
		LAST);
		//Response - /cgi-bin/login.pl?intro=true
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
			"Name=login.x", "Value=24", ENDITEM,
			"Name=login.y", "Value=8", ENDITEM,
			"Name=JSFormSubmit", "Value=off", ENDITEM,
			LAST);

	lr_end_transaction("login", LR_AUTO);

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
	
	lr_think_time(5); //delay 5sec
	
/* Booking a ticket-page1(POST cities, №passengers, seats) */
	lr_start_transaction("booking_ticket_page1");

		web_add_auto_header("Origin", 
			"http://localhost:1080");
	
	
	/*Correlation comment - Do not change!  Original value='892;1015;04/06/2023' Name ='outboundFlight' Type ='Manual'*/
	web_reg_save_param_ex(
		"ParamName=outboundFlight",
		"LB=name=\"outboundFlight\" value=\"",
		"RB=\"",
		SEARCH_FILTERS,
		"Scope=Body",
		LAST);
	
	
		//Response - /cgi-bin/reservation.pl
		web_reg_find("Text/IC=Flight departing from <b>{departCity}</b> to <b>{arriveCity}</b> on <B>{departDate}</B>",
		LAST);
		

		web_submit_data("reservations.pl", 
				"Action=http://localhost:1080/cgi-bin/reservations.pl", 
				"Method=POST", 
				"TargetFrame=", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
				"Snapshot=t4.inf", 
				"Mode=HTML", 
				ITEMDATA, 
				"Name=advanceDiscount", "Value=0", ENDITEM, 
				"Name=depart", "Value={departCity}", ENDITEM, 
				"Name=departDate", "Value={departDate}", ENDITEM, 
				"Name=arrive", "Value={arriveCity}", ENDITEM, 
				"Name=returnDate", "Value={returnDate}", ENDITEM, 
				"Name=numPassengers", "Value=1", ENDITEM, 
				"Name=seatPref", "Value={seatPref}", ENDITEM, 
				"Name=seatType", "Value={seatType}", ENDITEM, 
				"Name=findFlights.x", "Value=66", ENDITEM, 
				"Name=findFlights.y", "Value=8", ENDITEM, 
				"Name=.cgifields", "Value=roundtrip", ENDITEM, 
				"Name=.cgifields", "Value=seatType", ENDITEM, 
				"Name=.cgifields", "Value=seatPref", ENDITEM, 
				LAST);

	lr_end_transaction("booking_ticket_page1", LR_AUTO);

	lr_think_time(5); //delay 5sec
	
/* Booking a ticket-page2(POST outboundFlight: "Blue Sky Air ###") */
	lr_start_transaction("booking_ticket_page2");

		//Response - /cgi-bin/reservations.pl (2)
		web_reg_find("Text/IC=<tr><td align=\"right\">First Name : <td><input type=\"text\" name=\"firstName\" value=\"{firstName}\" size=\"15\" />",
			LAST);

		web_submit_data("reservations.pl_2", 
				"Action=http://localhost:1080/cgi-bin/reservations.pl", 
				"Method=POST", 
				"TargetFrame=", 
				"RecContentType=text/html", 
				"Referer=http://localhost:1080/cgi-bin/reservations.pl", 
				"Snapshot=t5.inf", 
				"Mode=HTML", 
				ITEMDATA, 
				"Name=outboundFlight", "Value={outboundFlight}", ENDITEM, //892;1015;04/06/2023
				"Name=numPassengers", "Value=1", ENDITEM, 
				"Name=advanceDiscount", "Value=0", ENDITEM, 
				"Name=seatType", "Value={seatType}", ENDITEM, 
				"Name=seatPref", "Value={seatPref}", ENDITEM, 
				"Name=reserveFlights.x", "Value=38", ENDITEM, 
				"Name=reserveFlights.y", "Value=11", ENDITEM, 
				LAST);

	lr_end_transaction("booking_ticket_page2", LR_AUTO);

	lr_think_time(5); //delay 5sec
	
/* Booking a ticket-page3(POST Users.dat) */
	lr_start_transaction("booking_ticket_page3");

		web_revert_auto_header("Origin");
	
		web_revert_auto_header("Sec-Fetch-User");
	
		web_revert_auto_header("Upgrade-Insecure-Requests");
	
		web_add_header("Origin", 
			"http://localhost:1080");
		
		
		//Response - /cgi-bin/reservations.pl (3)
		web_reg_find("Text/IC=from {departCity} to {arriveCity}",
		LAST);

		
		web_submit_data("reservations.pl_3",
		"Action=http://localhost:1080/cgi-bin/reservations.pl",
		"Method=POST",
		"TargetFrame=",
		"RecContentType=text/html",
		"Referer=http://localhost:1080/cgi-bin/reservations.pl",
		"Snapshot=t6.inf",
		"Mode=HTML",
		ITEMDATA,
		"Name=firstName", "Value={firstName}", ENDITEM,
		"Name=lastName", "Value={lastName}", ENDITEM,
		"Name=address1", "Value={address1}", ENDITEM,
		"Name=address2", "Value={address2}", ENDITEM,
		"Name=pass1", "Value={firstName} {lastName}", ENDITEM,
		"Name=creditCard", "Value={creditCard}", ENDITEM,
		"Name=expDate", "Value={expDate}", ENDITEM,
		"Name=oldCCOption", "Value=", ENDITEM,
		"Name=numPassengers", "Value=1", ENDITEM,
		"Name=seatType", "Value={seatType}", ENDITEM,
		"Name=seatPref", "Value={seatPref}", ENDITEM,
		"Name=outboundFlight", "Value={outboundFlight}", ENDITEM,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=returnFlight", "Value=", ENDITEM,
		"Name=JSFormSubmit", "Value=off", ENDITEM,
		"Name=buyFlights.x", "Value=9", ENDITEM,
		"Name=buyFlights.y", "Value=6", ENDITEM,
		"Name=.cgifields", "Value=saveCC", ENDITEM,
		LAST);

	lr_end_transaction("booking_ticket_page3", LR_AUTO);

	lr_think_time(5); //delay 5sec
	
/* Go to Itinerary */
	lr_start_transaction("go_to_iternerary");

		web_add_auto_header("Sec-Fetch-User", 
			"?1");
	
		web_add_auto_header("Upgrade-Insecure-Requests", 
			"1");
	
	
		//Response - /cgi-bin/welcome.pl?page=itinerary
		web_reg_find("Text/IC=User wants the intineraries",
		LAST);
		//Response - /cgi-bin/itinerary.p
		web_reg_find("Text/IC={firstName} {lastName}",
		LAST);

	
		web_url("Itinerary Button", 
			"URL=http://localhost:1080/cgi-bin/welcome.pl?page=itinerary", 
			"TargetFrame=body", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=flights", 
			"Snapshot=t7.inf", 
			"Mode=HTML", 
			LAST);

	lr_end_transaction("go_to_iternerary", LR_AUTO);

	lr_think_time(5); //delay 5sec

/* Go to Home */
	lr_start_transaction("go_to_home");

		web_revert_auto_header("Sec-Fetch-User");
		
		
		//Response - /cgi-bin/login.pl?intro=true
		web_reg_find("Text=Welcome, <b>{login}</b>, to the Web Tours reservation pages",
		LAST);
		
		
		web_url("Home Button", 
			"URL=http://localhost:1080/cgi-bin/welcome.pl?page=menus", 
			"TargetFrame=body", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=itinerary", 
			"Snapshot=t8.inf", 
			"Mode=HTML", 
			LAST);

	lr_end_transaction("go_to_home", LR_AUTO);
	
	lr_think_time(5); //delay 5sec
	
/* Logout */	
	lr_start_transaction("logout");

		web_add_header("Sec-Fetch-User", 
			"?1");
	
	
		//Response - /WebTours/home.html	
		web_reg_find("Text=Welcome to the Web Tours site",
			LAST);
	
	
		web_url("SignOff Button", 
			"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
			"TargetFrame=body", 
			"Resource=0", 
			"RecContentType=text/html", 
			"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
			"Snapshot=t9.inf", 
			"Mode=HTML", 
			LAST);

	lr_end_transaction("logout", LR_AUTO);

lr_end_transaction("UC_01_BuyTicket", LR_AUTO);


return 0;
}