#include <IRCommand.h>
#include <Ethernet.h>
#include <FlowerPlatformArduinoRuntime.h>
#include <SPI.h>
#include <HttpServer.h>
#include <IRremote.h>

class ApplicationGen {
protected:
	HttpServer httpServer1;
	IRCommand acOff;
	IRCommand acOn24;
	IRCommand acFanHigh;

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
			castedEvent->client->print(F("ners:{},activeRequests:0,addListener:function(f,b,c,a){var e=this.listeners[f];if(typeof e===\"undefined\"){e=[];this.listeners[f]=e}var d=function(){var g=bindingManager.data[f];c(b,g,a)};e.push(d);d()},set:function(d,c){if(this.data[d]!==c){this.data[d]=c;var b=this.listeners[d];if(typeof b!==\"undef"));
			castedEvent->client->print(F("ined\"&&b!==null){for(var a=0;a<b.length;a++){b[a]()}}}}};var toggleClass=function(d,b,c){for(var e in c){var a=c[e];if(e!=b){d.parent().removeClass(a)}}if(c[b]){d.parent().addClass(c[b])}};var setText=function(c,a,b){if(typeof b!==\"undefined\"&&b[a]){a=b[a]}c.text(a)};var invoke=function(c,b,a){bindi"));
			castedEvent->client->print(F("ngManager.activeRequests++;$.get(url+c,function(e){bindingManager.activeRequests--;for(var d in e){bindingManager.set(d,e[d])}if(b){b()}}).fail(function(){bindingManager.activeRequests--;if(a){a()}})};setInterval(function(){if(bindingManager.activeRequests>0){return}invoke(\"getState\")},1000);$(funct"));
			castedEvent->client->print(F("ion(){$(\"[bindToProperty]\").each(function(){var b=$(this);var d=b.attr(\"bindToProperty\");var c=b.attr(\"textToggler\");if(c){c=JSON.parse(c)}bindingManager.addListener(d,b,setText,c);var a=b.attr(\"classToggler\");if(a){a=JSON.parse(a);bindingManager.addListener(d,b,toggleClass,a)}})});<\/script><style>."));
			castedEvent->client->print(F("content{font-size:21px;font-weight:300;line-height:1.4}<\/style><\/head><body class=\"content\"><br\/><div class=\"container-fluid\"><div class=\"row\"><div class=\"col-md-12\"><span class=\"label label-default\"><span class=\"glyphicon glyphicon-dashboard\"><\/span> Free memory (SRAM): <span bindToProperty=\"FREE_M"));
			castedEvent->client->print(F("EM\"><\/span> bytes<\/span><\/div><\/div><\/div><\/body>"));
			return;
		} else if (strcmp_P(command, PSTR("getState")) == 0) {
			urlFound = true;
		} else if (strcmp_P(command, PSTR("acOff")) == 0) {
			urlFound = true;
			{
				acOff.send();
			}
		} else if (strcmp_P(command, PSTR("ac24On")) == 0) {
			urlFound = true;
			{
				acOn24.send();
			}
		} else if (strcmp_P(command, PSTR("acFanHigh")) == 0) {
			urlFound = true;
			{
				acFanHigh.send();
			}
		}
		
		if (urlFound) {
			castedEvent->server->httpSuccess();
			printStateAsJson(castedEvent->client);
		} else {
			castedEvent->server->httpError404();
		}
	}
	
public:
	virtual ~ApplicationGen() { }

	virtual void setup() {
		pinMode(SS, OUTPUT);
		
		uint8_t macAddress[] = { 0xAA, 0xBA, 0xC1, 0xDD, 0xEE, 0xF2 };
		uint8_t ipAddress[] = { 192, 168, 100, 253 };
		memcpy(httpServer1.macAddress, macAddress, 6);
		memcpy(httpServer1.ipAddress, ipAddress, 4);
		httpServer1.port = 80;
		httpServer1.setup();

		acOff.name = "acOff";
		acOff.setup();

		acOn24.name = "acOn24";
		acOn24.setup();

		acFanHigh.name = "acFanHigh";
		acFanHigh.setup();

		httpServer1.onCommandReceived = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_onCommandReceived);
	}
	
	virtual void loop() {
		httpServer1.loop();
	}
	
	void printStateAsJson(Print* print) {
		print->print(F("{"));
	

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
