#include <Timer.h>
#include <LoggerSD.h>
#include <DHTSensor.h>
#include <Ethernet.h>
#include <FlowerPlatformArduinoRuntime.h>
#include <SD.h>
#include <DHT.h>
#include <SPI.h>
#include <HttpServer.h>
#include <Output.h>
#include <Input.h>

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
			castedEvent->client->print(F("<!DOCTYPE html><html><head><meta charset=\"ISO-8859-1\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><script src=\"http:\/\/code.jquery.com\/jquery-1.11.2.min.js\"><\/script><link rel=\"stylesheet\" href=\"https:\/\/maxcdn.bootstrapcdn.com\/bootstrap\/3.3.4\/css\/bootstrap.min.css\"><script src"));
			castedEvent->client->print(F("=\"https:\/\/maxcdn.bootstrapcdn.com\/bootstrap\/3.3.4\/js\/bootstrap.min.js\"><\/script><link rel=\"stylesheet\" href=\"http:\/\/bootswatch.com\/paper\/bootstrap.min.css\"><link href='http:\/\/fonts.googleapis.com\/css?family=Roboto' rel='stylesheet' type='text\/css'><script>var url=\"\";var bindingManager={data:{},liste"));
			castedEvent->client->print(F("ners:{},addListener:function(f,b,c,a){var e=this.listeners[f];if(typeof e===\"undefined\"){e=[];this.listeners[f]=e}var d=function(){var g=bindingManager.data[f];c(b,g,a)};e.push(d);d()},set:function(d,c){if(this.data[d]!==c){this.data[d]=c;var b=this.listeners[d];if(typeof b!==\"undefined\"&&b!==null){"));
			castedEvent->client->print(F("for(var a=0;a<b.length;a++){b[a]()}}}}};var toggleClass=function(d,b,c){for(var e in c){var a=c[e];if(e!=b){d.parent().removeClass(a)}}if(c[b]){d.parent().addClass(c[b])}};var setText=function(c,a,b){if(typeof b!==\"undefined\"&&b[a]){a=b[a]}c.text(a)};var invoke=function(a){$.get(url+a,function(c){fo"));
			castedEvent->client->print(F("r(var b in c){bindingManager.set(b,c[b])}})};setInterval(function(){invoke(\"getState\")},1000);$(function(){$(\"[bindToProperty]\").each(function(){var b=$(this);var d=b.attr(\"bindToProperty\");var c=b.attr(\"textToggler\");if(c){c=JSON.parse(c)}bindingManager.addListener(d,b,setText,c);var a=b.attr(\"clas"));
			castedEvent->client->print(F("sToggler\");if(a){a=JSON.parse(a);bindingManager.addListener(d,b,toggleClass,a)}})});<\/script><style>.content{font-size:21px;font-weight:300;line-height:1.4}<\/style><\/head><body class=\"content\"><br\/><div class=\"container-fluid\"><div class=\"row\"><div class=\"col-md-3\"><div class=\"panel panel-primary te"));
			castedEvent->client->print(F("xt-center\" id=\"bedroom\"><div class=\"panel-heading\">Bedroom<\/div><div class=\"panel-body\"><div class=\"row\"><div class=\"col-xs-6\"><div> Temperature <\/div><div id=\"temperature\"><span classToggler='{}' bindToProperty=\"dhtSensor_temperature\" textToggler='{}'><\/span><\/div><\/div><div class=\"col-xs-6\"><div> "));
			castedEvent->client->print(F("Humidity <\/div><div id=\"humidity\"><span classToggler='{}' bindToProperty=\"dhtSensor_humidity\" textToggler='{}'><\/span><\/div><\/div><\/div><div id=\"light\"> Light is <span classToggler='{\"1\":\"text-success\",\"0\":\"text-danger\"}' bindToProperty=\"output5\" textToggler='{\"1\":\"ON\",\"0\":\"OFF\"}'><\/span><\/div><butt"));
			castedEvent->client->print(F("on class=\"btn btn-block btn-lg lightButton\" type=\"button\" onclick=\"invoke('toggleLight')\"><span class=\"glyphicon glyphicon-flash\"><\/span> LIGHT <\/button><\/div><\/div><\/div><\/div><div class=\"row\"><div class=\"col-md-12\"><span class=\"label label-default\"><span class=\"glyphicon glyphicon-dashboard\"><\/spa"));
			castedEvent->client->print(F("n> Free memory (SRAM): <span bindToProperty=\"FREE_MEM\"><\/span> bytes<\/span><\/div><\/div><\/div><\/body>"));
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
		input2.isAnalog = false;
		input2.internalPullUp = true;
		input2.pollInterval = 200;
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
		blueLed.printStateAsJson(F("blueLed"), print);
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
