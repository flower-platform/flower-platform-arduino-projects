#include <avr/pgmspace.h>
#include <Arduino.h>
#include <Client.h>
#include <ESP8266NetworkAdapter.h>
#include <FlowerPlatformArduinoRuntime.h>
#include <HardwareSerial.h>
#include <HttpServer.h>
#include <IRCommand.h>
#include <IRLearner.h>
#include <pins_arduino.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <WString.h>

class ApplicationGen {
protected:
	ESP8266NetworkAdapter esp8266NetworkAdapter;
	HttpServer httpServer;
	IRCommand acOff;
	IRLearner iRLearner1;
	IRCommand acOn24;
	IRCommand acFanHigh;

	virtual void httpServer_onCommandReceived(Event* event) {
		HttpCommandEvent* castedEvent = (HttpCommandEvent*) event;
		
		char command[32];
		castedEvent->server->getCommandFromUrl(castedEvent->url, command);
		bool urlFound = false;

		BufferedPrint out(castedEvent->client);

		if (strcmp_P(command, PSTR("")) == 0) {
			urlFound = true;
<<<<<<< HEAD
			castedEvent->server->httpSuccess(&out, HttpServer::CONTENT_TYPE_HTML);
			write_P(&out, PSTR("<!DOCTYPE html><html><head><meta charset=\"ISO-8859-1\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><script src=\"http:\/\/code.jquery.com\/jquery-1.11.2.min.js\"><\/script><link rel=\"stylesheet\" href=\"https:\/\/maxcdn.bootstrapcdn.com\/bootstrap\/3.3.4\/css\/bootstrap.min.css\"><script src"));
			write_P(&out, PSTR("=\"https:\/\/maxcdn.bootstrapcdn.com\/bootstrap\/3.3.4\/js\/bootstrap.min.js\"><\/script><link rel=\"stylesheet\" href=\"http:\/\/bootswatch.com\/paper\/bootstrap.min.css\"><link href='http:\/\/fonts.googleapis.com\/css?family=Roboto' rel='stylesheet' type='text\/css'><script>var url=\"\";var bindingManager={data:{},liste"));
			write_P(&out, PSTR("ners:{},activeRequests:0,addListener:function(f,b,c,a){var e=this.listeners[f];if(typeof e===\"undefined\"){e=[];this.listeners[f]=e}var d=function(){var g=bindingManager.data[f];c(b,g,a)};e.push(d);d()},set:function(d,c){if(this.data[d]!==c){this.data[d]=c;var b=this.listeners[d];if(typeof b!==\"undef"));
			write_P(&out, PSTR("ined\"&&b!==null){for(var a=0;a<b.length;a++){b[a]()}}}}};var toggleClass=function(d,b,c){for(var e in c){var a=c[e];if(e!=b){d.parent().removeClass(a)}}if(c[b]){d.parent().addClass(c[b])}};var setText=function(c,a,b){if(typeof b!==\"undefined\"&&b[a]){a=b[a]}c.text(a)};var invoke=function(c,b,a){bindi"));
			write_P(&out, PSTR("ngManager.activeRequests++;$.get(url+c,function(e){bindingManager.activeRequests--;for(var d in e){bindingManager.set(d,e[d])}if(b){b()}}).fail(function(){bindingManager.activeRequests--;if(a){a()}})};$(function(){$(\"[bindToProperty]\").each(function(){var b=$(this);var d=b.attr(\"bindToProperty\");var"));
			write_P(&out, PSTR(" c=b.attr(\"textToggler\");if(c){c=JSON.parse(c)}bindingManager.addListener(d,b,setText,c);var a=b.attr(\"classToggler\");if(a){a=JSON.parse(a);bindingManager.addListener(d,b,toggleClass,a)}});setInterval(function(){if(bindingManager.activeRequests>0){return}invoke(\"getState\")},1000)});<\/script><style>."));
			write_P(&out, PSTR("content{font-size:21px;font-weight:300;line-height:1.4}<\/style><\/head><body class=\"content\"><br\/><div class=\"container-fluid\"><div class=\"row\"><div class=\"col-md-3\"><div class=\"panel panel-primary text-center\"><div class=\"panel-heading\"><\/div><div class=\"panel-body\"><button class=\"btn btn-block btn-"));
			write_P(&out, PSTR("lg\" type=\"button\" onclick=\"var cmd=window.prompt('Enter command name and push the desired button on the IR remote after pressing OK:'); if (!cmd) return; invoke('irLearnCommand?name='+cmd, function() { alert('Command saved'); }, function() { alert('Error saving command'); });\"> Learn IR command <\/bu"));
			write_P(&out, PSTR("tton><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('acOff')\"> AC OFF <\/button><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('acOn24')\"> AC ON 24C <\/button><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('acFanHigh')\"> acFanHigh <\/button><\/"));
			write_P(&out, PSTR("div><\/div><\/div><\/div><div class=\"row\"><div class=\"col-md-12\"><span class=\"label label-default\"><span class=\"glyphicon glyphicon-dashboard\"><\/span> Free memory (SRAM): <span bindToProperty=\"FREE_MEM\"><\/span> bytes<\/span><\/div><\/div><\/div><\/body>"));
			out.flush();
=======
			castedEvent->server->httpSuccess(HttpServer::CONTENT_TYPE_HTML);
			castedEvent->client->print(F("<!DOCTYPE html><html><head><meta charset=\"ISO-8859-1\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><script src=\"http:\/\/code.jquery.com\/jquery-1.11.2.min.js\"><\/script><link rel=\"stylesheet\" href=\"https:\/\/maxcdn.bootstrapcdn.com\/bootstrap\/3.3.4\/css\/bootstrap.min.css\"><script src"));
			castedEvent->client->print(F("=\"https:\/\/maxcdn.bootstrapcdn.com\/bootstrap\/3.3.4\/js\/bootstrap.min.js\"><\/script><link rel=\"stylesheet\" href=\"http:\/\/bootswatch.com\/paper\/bootstrap.min.css\"><link href='http:\/\/fonts.googleapis.com\/css?family=Roboto' rel='stylesheet' type='text\/css'><script>var url=\"\";var bindingManager={data:{},liste"));
			castedEvent->client->print(F("ners:{},activeRequests:0,addListener:function(f,b,c,a){var e=this.listeners[f];if(typeof e===\"undefined\"){e=[];this.listeners[f]=e}var d=function(){var g=bindingManager.data[f];c(b,g,a)};e.push(d);d()},set:function(d,c){if(this.data[d]!==c){this.data[d]=c;var b=this.listeners[d];if(typeof b!==\"undef"));
			castedEvent->client->print(F("ined\"&&b!==null){for(var a=0;a<b.length;a++){b[a]()}}}}};var toggleClass=function(d,b,c){for(var e in c){var a=c[e];if(e!=b){d.parent().removeClass(a)}}if(c[b]){d.parent().addClass(c[b])}};var setText=function(c,a,b){if(typeof b!==\"undefined\"&&b[a]){a=b[a]}c.text(a)};var invoke=function(c,b,a){bindi"));
			castedEvent->client->print(F("ngManager.activeRequests++;$.get(url+c,function(e){bindingManager.activeRequests--;for(var d in e){bindingManager.set(d,e[d])}if(b){b()}}).fail(function(){bindingManager.activeRequests--;if(a){a()}})};setInterval(function(){if(bindingManager.activeRequests>0){return}invoke(\"getState\")},1000);$(funct"));
			castedEvent->client->print(F("ion(){$(\"[bindToProperty]\").each(function(){var b=$(this);var d=b.attr(\"bindToProperty\");var c=b.attr(\"textToggler\");if(c){c=JSON.parse(c)}bindingManager.addListener(d,b,setText,c);var a=b.attr(\"classToggler\");if(a){a=JSON.parse(a);bindingManager.addListener(d,b,toggleClass,a)}})});<\/script><style>."));
			castedEvent->client->print(F("content{font-size:21px;font-weight:300;line-height:1.4}<\/style><\/head><body class=\"content\"><br\/><div class=\"container-fluid\"><div class=\"row\"><div class=\"col-md-3\"><div class=\"panel panel-primary text-center\"><div class=\"panel-heading\"><\/div><div class=\"panel-body\"><button class=\"btn btn-block btn-"));
			castedEvent->client->print(F("lg\" type=\"button\" onclick=\"var cmd=window.prompt('Enter command name and push the desired button on the IR remote after pressing OK:'); if (!cmd) return; invoke('irLearnCommand?name='+cmd, function() { alert('Command saved'); }, function() { alert('Error saving command'); });\"> Learn IR command <\/bu"));
			castedEvent->client->print(F("tton><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('acOff')\"> AC OFF <\/button><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('acOn24')\"> AC ON 24C <\/button><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('acFanHigh')\"> acFanHigh <\/button><\/"));
			castedEvent->client->print(F("div><\/div><\/div><\/div><div class=\"row\"><div class=\"col-md-12\"><span class=\"label label-default\"><span class=\"glyphicon glyphicon-dashboard\"><\/span> Free memory (SRAM): <span bindToProperty=\"FREE_MEM\"><\/span> bytes<\/span><\/div><\/div><\/div><\/body>"));
>>>>>>> refs/remotes/origin/master
			return;
		} else if (strcmp_P(command, PSTR("getState")) == 0) {
			urlFound = true;
		} else if (strcmp_P(command, PSTR("irLearnCommand")) == 0) {
			urlFound = true;
			{
				char name[32];
				castedEvent->server->getParameterValueFromUrl(castedEvent->url, "name", name);
				if (!iRLearner1.capture(name)) {
					castedEvent->server->httpError404(&out);
					out.flush();
					return;
				}
			}
		} else if (strcmp_P(command, PSTR("acOff")) == 0) {
			urlFound = true;
			{
				acOff.send();
			}
		} else if (strcmp_P(command, PSTR("acOn24")) == 0) {
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
			castedEvent->server->httpSuccess(&out);
			printStateAsJson(&out);
			out.flush();
		} else {
			castedEvent->server->httpError404(&out);
		}
	}
	
public:
	virtual ~ApplicationGen() { }

	virtual void setup() {
		pinMode(SS, OUTPUT);
		digitalWrite(SS, HIGH);

		esp8266NetworkAdapter.ssid = "wifi-work";
		esp8266NetworkAdapter.password = "wifi-work-pass-123";
		esp8266NetworkAdapter.httpServer = &httpServer;

		uint8_t ipAddress[] = { 192, 168, 100, 253 };
		memcpy(httpServer.ipAddress, ipAddress, 4);
		httpServer.port = 80;

		acOff.name = "acOff";

<<<<<<< HEAD
		iRLearner1.pin = 2;
=======
		iRLearner1.pin = A2;
>>>>>>> refs/remotes/origin/master

		acOn24.name = "acOn24";

		acFanHigh.name = "acFanHigh";


		httpServer.setup();
		acOff.setup();
		iRLearner1.setup();
		acOn24.setup();
		acFanHigh.setup();
		esp8266NetworkAdapter.setup();

		httpServer.onCommandReceived = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_onCommandReceived);

	}
	
	virtual void loop() {
		esp8266NetworkAdapter.loop();
	}
	
	void printStateAsJson(Print* print) {
		BufferedPrint out(print);
		print->print("{");


		write_P(print, PSTR("\"FREE_MEM\": "));
		print->print(freeRam());
		print->print("}");
	}

};


#define SHOULD_INCLUDE_CUSTOM_CODE
#include "CustomCode.h"

ApplicationGen* app = new ApplicationCustom();

void setup() {
	Serial.begin(115200);
	app->setup();
	Serial.print("setup ready "); Serial.println(freeRam());
}

void loop() {
	app->loop();
}
