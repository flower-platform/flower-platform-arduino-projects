#include <dht.h>

#include <Ethernet.h>
#include <SPI.h>
#include <SD.h>

#include <FlowerPlatformArduinoRuntime.h>
#include <DHTSensor.h>
#include <Output.h>
#include <UpdatesBuffer.h>
#include <HttpServer.h>

#include <Input.h>
#include <Timer.h>
#include <LoggerSD.h>

class ApplicationGen {
protected:
	Input input2;
	Output output5;
	HttpServer httpServer;
	DHTSensor dhtSensor;
	Output blueLed;
	Timer blueLedTimer;
	LoggerSD<int> loggerTemperature;

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
		bool urlFound = false;
		
		if (strcmp_P(command, PSTR("")) == 0) {
			urlFound = true;
			castedEvent->server->httpSuccess(HttpServer::CONTENT_TYPE_HTML);
			castedEvent->client->print(F("<!DOCTYPE html> <html> <head> <meta charset=\"ISO-8859-1\"> <script src=\"http:\/\/code.jquery.com\/jquery-1.11.2.min.js\"><\/script> <link rel=\"stylesheet\" href=\"https:\/\/maxcdn.bootstrapcdn.com\/bootstrap\/3.3.4\/css\/bootstrap.min.css\"> <script src=\"https:\/\/maxcdn.bootstrapcdn.com\/bootstrap\/3.3.4\/js\/bootstrap"));
			castedEvent->client->print(F(".min.js\"><\/script> <link rel=\"stylesheet\" href=\"http:\/\/bootswatch.com\/paper\/bootstrap.min.css\"> <link href='http:\/\/fonts.googleapis.com\/css?family=Roboto' rel='stylesheet' type='text\/css'> <script>var url=\"\";var bindingManager={data:{temperature:25,humidity:25},listeners:{},addListener:function(c,b)"));
			castedEvent->client->print(F("{var a=this.listeners[c];if(typeof a===\"undefined\"){a=[];this.listeners[c]=a}a.push(b)},set:function(d,c){if(this.data[d]!==c){this.data[d]=c;var b=this.listeners[d];if(typeof b!==\"undefined\"&&b!==null){for(var a=0;a<b.length;a++){b[a]()}}}}};var addTextListener=function(d,c,a){var b=function(){var "));
			castedEvent->client->print(F("e=$(\"#\"+d);var f=bindingManager.data[c];if(typeof a!==\"undefined\"){f=a[f]}e.text(f)};bindingManager.addListener(c,b);b()};var addClassListener=function(d,c,a){var b=function(){var f=$(\"#\"+d);var h=bindingManager.data[c];for(var g in a){var e=a[g];if(g==h){f.addClass(e)}else{f.removeClass(e)}}};bindi"));
			castedEvent->client->print(F("ngManager.addListener(c,b);b()};var invoke=function(a){$.get(url+a,function(c){for(var b in c){bindingManager.set(b,c[b])}})};var refresh=function(){invoke(\"getState\")};setInterval(function(){refresh()},1000);<\/script> <\/head> <body> <br\/> <div class=\"container-fluid lead\"> <div class=\"row\"> <div cl"));
			castedEvent->client->print(F("ass=\"col-md-3\"> <div class=\"panel panel-primary text-center\" id=\"bedroom\"> <div class=\"panel-heading\">Bedroom<\/div> <div class=\"panel-body\"> <div class=\"row\"> <div class=\"col-xs-6\"> <div>Temperature<\/div> <div> <span id=\"bedroom-temperature\"><\/span> &#176;C <script>addTextListener(\"bedroom-temperatu"));
			castedEvent->client->print(F("re\",\"dhtSensor_temperature\");<\/script> <\/div> <\/div> <div class=\"col-xs-6\"> <div>Humidity<\/div> <div> <span id=\"bedroom-humidity\"><\/span> %RH <script>addTextListener(\"bedroom-humidity\",\"dhtSensor_humidity\");<\/script> <\/div> <\/div> <\/div> <div>Light<\/div> <div> <span id=\"bedroom-light\"><\/span> <scrip"));
			castedEvent->client->print(F("t>addTextListener(\"bedroom-light\",\"output5\");<\/script> <\/div> <button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('toggleLight')\"> <span class=\"glyphicon glyphicon-flash\"><\/span> LIGHT <\/button> <div> <span id=\"bedroom-freeRam\"><\/span> bytes free RAM <script>addTextListener(\"bedroom-f"));
			castedEvent->client->print(F("reeRam\",\"FREE_MEM\");<\/script> <\/div> <\/div> <\/div> <\/div> <\/div> <div class=\"row\"><div class=\"lead col-md-12\"><span class=\"label label-default\"><span class=\"glyphicon glyphicon-dashboard\"><\/span> Free memory (SRAM): <span id=\"FREE_MEM\"><\/span> bytes<\/label><\/div> <script>addTextListener(\"FREE_MEM\",\""));
			castedEvent->client->print(F("FREE_MEM\");<\/script> <\/div> <\/body>"));
			return;
		} else if (strcmp_P(command, PSTR("getState")) == 0) {
			urlFound = true;
		} else if (strcmp_P(command, PSTR("toggleLight")) == 0) {
			urlFound = true;
			{
				output5.toggleHighLow();
			}
		}
		
		if (urlFound) {
			castedEvent->server->httpSuccess();
			printStateAsJson(castedEvent->client);
		} else {
			castedEvent->server->httpError404();
		}
	}
	
	virtual void dhtSensor_onTemperatureChanged(Event* event) {
		ValueChangedEvent* castedEvent = (ValueChangedEvent*) event;
		{
			int value = castedEvent->currentValue;
			loggerTemperature.log(value);
		}
	}
	
	virtual void blueLedTimer_onTimer(Event* event) {
		TimerEvent* castedEvent = (TimerEvent*) event;
		{
			blueLed.toggleHighLow();
		}
	}

public:
	virtual ~ApplicationGen() { }

	virtual void setup() {
		input2.pin = 2;
		input2.setup();
		
		output5.pin = 5;
		output5.setup();
		
		uint8_t macAddress[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
		uint8_t ipAddress[] = { 192, 168, 100, 253 };
		memcpy(httpServer.macAddress, macAddress, 6);
		memcpy(httpServer.ipAddress, ipAddress, 4);
		httpServer.port = 80;
		httpServer.setup();
		
		dhtSensor.pin = A0;
		dhtSensor.setup();
		
		blueLed.pin = 8;
		blueLed.setup();
		
		blueLedTimer.delay = 500;
		blueLedTimer.repeatCount = 0;
		blueLedTimer.autoStart = true;
		blueLedTimer.setup();
		
		loggerTemperature.slaveSelectPin = 4;
		loggerTemperature.timeInterval = 3000;
		loggerTemperature.setup();
		
		input2.onValueChanged = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::input2_onValueChanged);
		httpServer.onCommandReceived = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_onCommandReceived);
		dhtSensor.onTemperatureChanged = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::dhtSensor_onTemperatureChanged);
		
		blueLedTimer.onTimer = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::blueLedTimer_onTimer);
	}
	
	virtual void loop() {
		input2.loop();
		httpServer.loop();
		dhtSensor.loop();
		blueLedTimer.loop();
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