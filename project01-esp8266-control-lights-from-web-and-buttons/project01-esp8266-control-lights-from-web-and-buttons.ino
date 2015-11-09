#include <ESP8266NetworkAdapter.h>
#include <FlowerPlatformArduinoRuntime.h>
#include <HttpServer.h>
#include <Output.h>
#include <Input.h>

class ApplicationGen {
protected:
	Output output8;
	Output output9;
	HttpServer httpServer;
	Input input4;
	Input input5;
	ESP8266NetworkAdapter eSP8266NetworkAdapter;

	virtual void httpServer_onCommandReceived(Event* event) {
		HttpCommandEvent* castedEvent = (HttpCommandEvent*) event;
		
		char command[32];
		castedEvent->server->getCommandFromUrl(castedEvent->url, command);
		bool urlFound = false;
		
		BufferedPrint out(castedEvent->client);
		
		if (strcmp_P(command, PSTR("")) == 0) {
			urlFound = true;
			castedEvent->server->httpSuccess(&out, HttpServer::CONTENT_TYPE_HTML);
			write_P(&out, PSTR("<!DOCTYPE html><html><head><meta charset=\"ISO-8859-1\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><script src=\"http:\/\/code.jquery.com\/jquery-1.11.2.min.js\"><\/script><link rel=\"stylesheet\" href=\"https:\/\/maxcdn.bootstrapcdn.com\/bootstrap\/3.3.4\/css\/bootstrap.min.css\"><script src"));
			write_P(&out, PSTR("=\"https:\/\/maxcdn.bootstrapcdn.com\/bootstrap\/3.3.4\/js\/bootstrap.min.js\"><\/script><link rel=\"stylesheet\" href=\"http:\/\/bootswatch.com\/paper\/bootstrap.min.css\"><link href='http:\/\/fonts.googleapis.com\/css?family=Roboto' rel='stylesheet' type='text\/css'><script>var url=\"\";var bindingManager={data:{},liste"));
			write_P(&out, PSTR("ners:{},activeRequests:0,addListener:function(f,b,c,a){var e=this.listeners[f];if(typeof e===\"undefined\"){e=[];this.listeners[f]=e}var d=function(){var g=bindingManager.data[f];c(b,g,a)};e.push(d);d()},set:function(d,c){if(this.data[d]!==c){this.data[d]=c;var b=this.listeners[d];if(typeof b!==\"undef"));
			write_P(&out, PSTR("ined\"&&b!==null){for(var a=0;a<b.length;a++){b[a]()}}}}};var toggleClass=function(d,b,c){for(var e in c){var a=c[e];if(e!=b){d.parent().removeClass(a)}}if(c[b]){d.parent().addClass(c[b])}};var setText=function(c,a,b){if(typeof b!==\"undefined\"&&b[a]){a=b[a]}c.text(a)};var invoke=function(c,b,a){bindi"));
			write_P(&out, PSTR("ngManager.activeRequests++;$.get(url+c,function(e){bindingManager.activeRequests--;for(var d in e){bindingManager.set(d,e[d])}if(b){b()}}).fail(function(){bindingManager.activeRequests--;if(a){a()}})};$(function(){$(\"[bindToProperty]\").each(function(){var b=$(this);var d=b.attr(\"bindToProperty\");var"));
			write_P(&out, PSTR(" c=b.attr(\"textToggler\");if(c){c=JSON.parse(c)}bindingManager.addListener(d,b,setText,c);var a=b.attr(\"classToggler\");if(a){a=JSON.parse(a);bindingManager.addListener(d,b,toggleClass,a)}});setInterval(function(){if(bindingManager.activeRequests>0){return}invoke(\"getState\")},1000)});<\/script><style>."));
			write_P(&out, PSTR("content{font-size:21px;font-weight:300;line-height:1.4}<\/style><\/head><body class=\"content\"><br\/><div class=\"container-fluid\"><div class=\"row\"><div class=\"col-md-6\"><div class=\"panel panel-primary text-center\"><div class=\"panel-heading\">Light 1<\/div><div class=\"panel-body\"><div> State: <span classTo"));
			write_P(&out, PSTR("ggler='{\"1\":\"text-warning\",\"0\":\"text-success\"}' bindToProperty=\"output8\" textToggler='{\"1\":\"OFF\",\"0\":\"ON\"}'><\/span><\/div><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light1Toggle')\"> Toggle <\/button><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light1On')"));
			write_P(&out, PSTR("\"> Turn on <\/button><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light1Off')\"> Turn off <\/button><\/div><\/div><\/div><div class=\"col-md-6\"><div class=\"panel panel-primary text-center\"><div class=\"panel-heading\">Light 2<\/div><div class=\"panel-body\"><div> State: <span classToggler"));
			write_P(&out, PSTR("='{\"1\":\"text-warning\",\"0\":\"text-success\"}' bindToProperty=\"output9\" textToggler='{\"1\":\"OFF\",\"0\":\"ON\"}'><\/span><\/div><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light2Toggle')\"> Toggle <\/button><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light2On')\"> Tu"));
			write_P(&out, PSTR("rn on <\/button><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light2Off')\"> Turn off <\/button><\/div><\/div><\/div><\/div><div class=\"row\"><div class=\"col-md-12\"><span class=\"label label-default\"><span class=\"glyphicon glyphicon-dashboard\"><\/span> Free memory (SRAM): <span bindToPro"));
			write_P(&out, PSTR("perty=\"FREE_MEM\"><\/span> bytes<\/span><\/div><\/div><\/div><\/body>"));
			out.flush();
			return;
		} else if (strcmp_P(command, PSTR("getState")) == 0) {
			urlFound = true;
		} else if (strcmp_P(command, PSTR("light1Toggle")) == 0) {
			urlFound = true;
			{
				output8.toggleHighLow();
			}
		} else if (strcmp_P(command, PSTR("light1On")) == 0) {
			urlFound = true;
			{
				output8.setLow();
			}
		} else if (strcmp_P(command, PSTR("light1Off")) == 0) {
			urlFound = true;
			{
				output8.setHigh();
			}
		} else if (strcmp_P(command, PSTR("light2Toggle")) == 0) {
			urlFound = true;
			{
				output9.toggleHighLow();
			}
		} else if (strcmp_P(command, PSTR("light2On")) == 0) {
			urlFound = true;
			{
				output9.setLow();
			}
		} else if (strcmp_P(command, PSTR("light2Off")) == 0) {
			urlFound = true;
			{
				output9.setHigh();
			}
		}
		
		if (urlFound) {
			castedEvent->server->httpSuccess(&out);
			printStateAsJson(&out);
		} else {
			castedEvent->server->httpError404(&out);
		}
		out.flush();
	}
	
	virtual void input4_onValueChanged(Event* event) {
		ValueChangedEvent* castedEvent = (ValueChangedEvent*) event;
		if (castedEvent->currentValue == LOW) {
			output8.toggleHighLow();
		}
	}
	
	virtual void input5_onValueChanged(Event* event) {
		ValueChangedEvent* castedEvent = (ValueChangedEvent*) event;
		if (castedEvent->currentValue == LOW) {
			output9.toggleHighLow();
		}
	}
	
public:
	virtual ~ApplicationGen() { }

	virtual void setup() {
		pinMode(SS, OUTPUT);
		digitalWrite(SS, HIGH);
		
		output8.pin = 8;
		output8.initialValue = 1;

		output9.pin = 9;
		output9.initialValue = 1;

		uint8_t ipAddress[] = { 192, 168, 100, 253 };
		memcpy(httpServer.ipAddress, ipAddress, 4);
		httpServer.port = 80;

		input4.pin = 4;
		input4.internalPullUp = true;
		input4.pollInterval = 200;

		input5.pin = 5;
		input5.internalPullUp = true;
		input5.pollInterval = 200;

		eSP8266NetworkAdapter.ssid = "wifi-work";
		eSP8266NetworkAdapter.password = "wifi-work-pass-123";
		eSP8266NetworkAdapter.httpServer = &httpServer;


		output8.setup();
		output9.setup();
		httpServer.setup();
		input4.setup();
		input5.setup();
		eSP8266NetworkAdapter.setup();

		httpServer.onCommandReceived = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_onCommandReceived);
		input4.onValueChanged = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::input4_onValueChanged);
		input5.onValueChanged = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::input5_onValueChanged);
	}
	
	virtual void loop() {
		input4.loop();
		input5.loop();
		eSP8266NetworkAdapter.loop();
	}
	
	void printStateAsJson(Print* print) {
		print->print(F("{"));
	
		output8.printStateAsJson(F("output8"), print);
		print->print(F(","));
		output9.printStateAsJson(F("output9"), print);
		print->print(F(","));
		input4.printStateAsJson(F("input4"), print);
		print->print(F(","));
		input5.printStateAsJson(F("input5"), print);
		print->print(F(","));

		write_P(print, PSTR("\"FREE_MEM\": "));
		print->print(freeRam());
		print->print("}");
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
