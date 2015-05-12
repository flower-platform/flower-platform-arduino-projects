#include <dht.h>

#include <Ethernet.h>
#include <SPI.h>

#include <FlowerPlatformArduinoRuntime.h>
#include <DHTSensor.h>
#include <Output.h>
#include <UpdatesBuffer.h>
#include <HttpServer.h>

#include <Input.h>
#include <Timer.h>
//#include <Logger.h>

class ApplicationGen {
protected:
	Input input2;
	Output output5;
	HttpServer httpServer;
	DHTSensor dhtSensor;

	virtual void input2_onValueChanged(Event* event) {
		ValueChangedEvent* castedEvent = (ValueChangedEvent*) event;
		{
			output5.toggleHighLow();
		}
	}
	virtual void httpServer_onCommandReceived(Event* event) {
		HttpCommandEvent* castedEvent = (HttpCommandEvent*) event;
		
		char command[32];
		castedEvent->server->getCommandFromUrl(castedEvent->url, command);
		
		if (strcmp_P(command, PSTR("")) == 0) {
			castedEvent->server->httpSuccess(HttpServer::CONTENT_TYPE_HTML);
			castedEvent->client->print(F("<!DOCTYPE html> <html> <head> <meta charset=\"ISO-8859-1\"> <script src=\"http:\/\/code.jquery.com\/jquery-1.11.2.min.js\"><\/script> <link rel=\"stylesheet\" href=\"https:\/\/maxcdn.bootstrapcdn.com\/bootstrap\/3.3.4\/css\/bootstrap.min.css\"> <script src=\"https:\/\/maxcdn.bootstrapcdn.com\/bootstrap\/3.3.4\/js\/bootstrap.min.js\"><\/script> <link rel=\"stylesheet\" href=\"http:\/\/bootswatch.com\/paper\/bootstrap.min.css\"> <link href='http:\/\/fonts.googleapis.com\/css?family=Roboto' rel='stylesheet' type='text\/css'> <script>var url=\"\";var bindingManager={data:{temperature:25,humidity:25},listeners:{},addListener:function(c,b){var a=this.listeners[c];if(typeof a===\"undefined\"){a=[];this.listeners[c]=a}a.push(b)},set:function(d,c){if(this.data[d]!==c){this.data[d]=c;var b=this.listeners[d];if(typeof b!==\"undefined\"&&b!==null){for(var a=0;a<b.length;a++){b[a]()}}}}};var addTextListener=function(d,c,a){var b=function(){var e=$(\"#\"+d);var f=bindingManager.data[c];if(typeof a!==\"undefined\"){f=a[f]}e.text(f)};bindingManager."));
			castedEvent->client->print(F("addListener(c,b);b()};var addClassListener=function(d,c,a){var b=function(){var f=$(\"#\"+d);var h=bindingManager.data[c];for(var g in a){var e=a[g];if(g==h){f.addClass(e)}else{f.removeClass(e)}}};bindingManager.addListener(c,b);b()};var invoke=function(a){$.get(url+a,function(c){for(var b in c){bindingManager.set(b,c[b])}})};var refresh=function(){invoke(\"getState\")};setInterval(function(){refresh()},1000);<\/script> <\/head> <body> <br\/> <div class=\"container-fluid lead\"> <div class=\"row\"> <div class=\"col-md-3\"> <div class=\"panel panel-primary text-center\" id=\"bedroom\"> <div class=\"panel-heading\">Bedroom<\/div> <div class=\"panel-body\"> <div class=\"row\"> <div class=\"col-xs-6\"> <div>Temperature<\/div> <div> <span id=\"bedroom-temperature\"><\/span> &#176;C <script>addTextListener(\"bedroom-temperature\",\"dhtSensor_temperature\");<\/script> <\/div> <\/div> <div class=\"col-xs-6\"> <div>Humidity<\/div> <div> <span id=\"bedroom-humidity\"><\/span> %RH <script>addTextListener(\"bedroom-humidity\",\"dhtSensor_humi"));
			castedEvent->client->print(F("dity\");<\/script> <\/div> <\/div> <\/div> <div>Light<\/div> <div> <span id=\"bedroom-light\"><\/span> <script>addTextListener(\"bedroom-light\",\"output5\");<\/script> <\/div> <button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('toggleLight')\"> <span class=\"glyphicon glyphicon-flash\"><\/span> LIGHT <\/button> <\/div> <\/div> <\/div> <\/div> <\/div> <\/body>"));
			return;
	//	} else if (strcmp_P(command, PSTR("getState")) == 0) {
	//		castedEvent->server->httpSuccess();
	//		printStateAsJson(castedEvent->client);
		} else if (strcmp_P(command, PSTR("toggleLight")) == 0) {
			{
				output5.toggleHighLow();
			}
		}
	
		castedEvent->server->httpSuccess();
		printStateAsJson(castedEvent->client);
	}
	

public:
	virtual ~ApplicationGen() { }

	virtual void setup() {
		input2.pin = 2;
		input2.setup();
		
		output5.pin = 5;
		output5.setup();
		
		httpServer.port = 80;
		httpServer.setup();
		
		dhtSensor.pin = A0;
		dhtSensor.setup();
		
		input2.onValueChanged = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::input2_onValueChanged);
		httpServer.onCommandReceived = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_onCommandReceived);
	}
	
	virtual void loop() {
		input2.loop();
		httpServer.loop();
		dhtSensor.loop();
	}
	
	void printStateAsJson(Print* print) {
		print->print(F("{"));
	
		input2.printStateAsJson(F("input2"), print);
		print->print(F(","));
		output5.printStateAsJson(F("output5"), print);
		print->print(F(","));
		dhtSensor.printStateAsJson(F("dhtSensor"), print);
		print->print(F(","));

		print->print(F("\"FREE_MEM\": "));
		print->print(freeRam());
		print->print(F("}"));
	}	
	
};


#define SHOULD_INCLUDE_CUSTOM_CODE
#include "CustomCode.h"

ApplicationGen* app = new ApplicationCustom();

void setup() {
	app->setup();
}

void loop() {
	app->loop();
}