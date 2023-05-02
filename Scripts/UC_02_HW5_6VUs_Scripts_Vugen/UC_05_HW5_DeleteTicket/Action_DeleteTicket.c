Action_DeleteTicket()
{
	int counter_flightID; //переменная для подсчета размера массива flightID

	lr_start_transaction("UC_05_HW5_DeleteTicket");

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
	
	web_reg_save_param("flightID",
		"LB/IC=flightID\" value=\"",
		"RB/IC=\"",
		"Ordinal=All",
		LAST);

	
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
	
	//запись кол-ва flightID
	counter_flightID = atoi(lr_eval_string("{flightID_count}"));
	lr_output_message("counter = %d ", counter_flightID);	

	lr_end_transaction("go_to_itenary", LR_AUTO);
	
	
//-delay 5sec
	
	
	/* Delete Ticket - 1 or more tickets */
	lr_start_transaction("delete_ticket");

	web_add_header("Origin", 
		"http://localhost:1080");
	
	/* Проверка на первую удаленную бронь. Если удаленная найдена, то ошибка */
	lr_save_string(lr_paramarr_idx("flightID", 1), "deleted_flightID");
	//CHECK: Response. 
	web_reg_find("Text/IC={deleted_flightID}", "Search=Body", "Fail=Found",
			LAST);
	
	
	//Проверка на кол-во броней: если 2 или меньше - удаляем 1, иначе удаляем 2 брони.
	if (counter_flightID <= 2) {
		web_submit_form("itinerary.pl", 
			"Snapshot=t4.inf", 
			ITEMDATA, 
			"Name=1", "Value=on", ENDITEM, 
			"Name=removeFlights.x", "Value=49", ENDITEM, 
			"Name=removeFlights.y", "Value=12", ENDITEM,
			LAST);
	} else {
		web_submit_form("itinerary.pl", 
			"Snapshot=t4.inf", 
			ITEMDATA, 
			"Name=1", "Value=on", ENDITEM, 
			"Name=2", "Value=on", ENDITEM, 
			"Name=removeFlights.x", "Value=49", ENDITEM, 
			"Name=removeFlights.y", "Value=12", ENDITEM,
			LAST);
	}

	lr_end_transaction("delete_ticket", LR_AUTO);	
	
	lr_end_transaction("UC_05_HW5_DeleteTicket", LR_AUTO);

	return 0;
}