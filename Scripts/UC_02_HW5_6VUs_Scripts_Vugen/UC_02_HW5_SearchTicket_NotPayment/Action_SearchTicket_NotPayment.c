Action_SearchTicket_NotPayment()
{
	char * FlightVal; //переменная-ссылка для присваивания одного из 4 рейсов.
	int CostVal;

	
	
	lr_start_transaction("UC_02_HW5_SearchTicket_NotPayment");
	
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
	
	
//-dealy 5sec
	

	/* Go to Flights */
	lr_start_transaction("go_to_flights");
		
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
	
	
//-dealy 5sec


	/* Booking a ticket-page1 (Choise cities, №passengers, seats) */
	lr_start_transaction("choise_cities_passengers_seats");

	web_add_auto_header("Origin", 
		"http://localhost:1080");
	

///*Correlation comment - Do not change!  Original value='891;1793;04/10/2023' Name ='outboundFlight' Type ='ResponseBased'*/
//	web_reg_save_param_attrib(
//		"ParamName=outboundFlight",
//		"TagName=input",
//		"Extract=value",
//		"Name=outboundFlight",
//		"Type=radio",
//		SEARCH_FILTERS,
//		"IgnoreRedirections=No",
//		LAST);


/* Corelation outboundFlight. Array[1-4]. Example value='891;1793;04/10/2023' */
	web_reg_save_param_ex(
		"ParamName=outboundFlight",
		"LB=name=\"outboundFlight\" value=\"",
		"RB=\"",
		"Ordinal=All",
		SEARCH_FILTERS,
		"Scope=BODY",
		LAST);

	
/* Correlation cost. Response - $ Array[1-4]. Не забыть про экранирование '\d' */
	web_reg_save_param_regexp(
		"ParamName=cost",
		"RegExp=(?<=;)\\d+(?=;)",
		"NotFound=warning",
		"Group=0",
		"Ordinal=All",
		SEARCH_FILTERS,
		"Scope=BODY",
		LAST);
	
	
	/* Проверка на одинаковость городов. Если одинаково, то переопределяем tocity. (Update value - each occurrence) */
	check_cities();
	//	сохраняем в параметры {fromcity} {tocity} для дальнейших POST...
	
	//CHECK: Response - /cgi-bin/reservation.pl
	web_reg_find("Text/IC=Flight departing from <b>{fromcity}</b> to <b>{tocity}</b> on <B>{departDate}</B>",
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
		"Name=depart", "Value={fromcity}", ENDITEM, 
		"Name=departDate", "Value={departDate}", ENDITEM, 
		"Name=arrive", "Value={tocity}", ENDITEM, 
		"Name=returnDate", "Value={returnDate}", ENDITEM, // +30days (in parameter setting)
		"Name=numPassengers", "Value={randNumPas}", ENDITEM, //вставлю здесь параметр {randNumPas} до 4 пассажиров вместо 1 пассажира
		"Name=seatPref", "Value={seatPref}", ENDITEM, 
		"Name=seatType", "Value={seatType}", ENDITEM, 
		"Name=findFlights.x", "Value=58", ENDITEM, 
		"Name=findFlights.y", "Value=11", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		LAST);

	lr_end_transaction("choise_cities_passengers_seats", LR_AUTO);
	
	
//-delay 5sec


	/* Booking a ticket-page2(POST outboundFlight: Choice "Blue Sky Air ###") */
	lr_start_transaction("choice_time_and_cost");
	
//	/* Проверка страницы не работает, потому что у нас нет пост-запроса (юзер-инфо не передаем) */
//	//CHECK: Response - /cgi-bin/reservations.pl (2)
//	web_reg_find("Text/IC=<tr><td align=\"right\">First Name : <td><input type=\"text\" name=\"firstName\" value=\"{firstName}\" size=\"15\" />",
//		LAST);
	
	/* Способ передачи рандомного параметра из 4 outboudFlight в web_submit_data. Выбор рандомного рейса из списка. */
	FlightVal = lr_paramarr_random("outboundFlight");
	lr_save_string(FlightVal, "outboundFlightRandom");
	
	//Парсим переменную {outboundFlightRandom} чтобы вытащить из неё цену и записать в "costRandom"
	lr_save_param_regexp (
	  	lr_eval_string("{outboundFlightRandom}"),
		  strlen(lr_eval_string("{outboundFlightRandom}")),
		  "RegExp=\\d*;(\\d*);\\d{2}",
		  "Ordinal=All",
		  "ResultParam=costRandom",
		  LAST);
	
	/* Проверка на Итоговую цену на странице. Итоговая цена = кол-во пассажиров * цену рейса */
	CostVal = atoi(lr_eval_string("{randNumPas}")) * atoi(lr_eval_string("{costRandom_1}"));
	lr_output_message("CostVal = %d", CostVal);
	lr_save_int(CostVal, "totalCost");
	//CHECK: Response - /cgi-bin/reservation.pl
	web_reg_find("Text/IC={totalCost}",
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
		"Name=outboundFlight", "Value={outboundFlightRandom}", ENDITEM,
		"Name=numPassengers", "Value={randNumPas}", ENDITEM,
		"Name=advanceDiscount", "Value=0", ENDITEM,
		"Name=seatType", "Value={seatType}", ENDITEM,
		"Name=seatPref", "Value={seatPref}", ENDITEM,
		"Name=reserveFlights.x", "Value=38", ENDITEM,
		"Name=reserveFlights.y", "Value=8", ENDITEM,
		LAST);
	

	lr_end_transaction("choice_time_and_cost", LR_AUTO);


//-delay 5sec

	
	/* Logout */
	lr_start_transaction("logout");
	logout();
	lr_end_transaction("logout", LR_AUTO);


	lr_end_transaction("UC_02_HW5_SearchTicket_NotPayment", LR_AUTO);
	
	return 0;
}