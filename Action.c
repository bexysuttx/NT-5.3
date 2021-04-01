Action()
{
	int i;
	char* finalDeparted = "London";
	int num;
	char arrayParamName[50];

	web_reg_save_param_ex(
    "ParamName=Departed", 
    "LB/IC=leaves ",
    "RB/IC=  for",
    "Ordinal=all",
	LAST);
	
	web_reg_save_param_ex(
    "ParamName=FlyId", 
    "LB/IC=name=\"flightID\" value=\"",
    "RB/IC=\"",
    "Ordinal=all",
	LAST);
	
	
	web_url("welcome.pl", 
		"URL={Host}/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={Host}/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		LAST);
	
	for (i=1;i<=atoi(lr_eval_string("{Departed_count}"));i++) {
		sprintf(arrayParamName, "{Departed_%d}", i);
		lr_output_message("%s",lr_eval_string(arrayParamName));
		if (strcmp(lr_eval_string(arrayParamName), finalDeparted) != 0) {
			num=i;
		}	
	}
	lr_output_message("%d",num);
	
	lr_save_int(num,"deleteTicket");
	
	web_submit_data("itinerary.pl", 
		"Action={Host}/cgi-bin/itinerary.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={Host}/cgi-bin/itinerary.pl", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=flightID", "Value={FlyId_1}", ENDITEM, 
		"Name=flightID", "Value={FlyId_2}", ENDITEM, 
		"Name={deleteTicket}", "Value=on", ENDITEM, 
		"Name=flightID", "Value={FlyId_3}", ENDITEM, 
		"Name=.cgifields", "Value=1", ENDITEM, 
		"Name=.cgifields", "Value=3", ENDITEM, 
		"Name=.cgifields", "Value=2", ENDITEM, 
		"Name=removeFlights.x", "Value=49", ENDITEM, 
		"Name=removeFlights.y", "Value=5", ENDITEM, 
		LAST);

	return 0;
}