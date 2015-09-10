#include <Ethernet.h>
#include <FlowerPlatformArduinoRuntime.h>
#include <SPI.h>
#include <HttpServer.h>
#include <Output.h>
#include <Input.h>

class ApplicationGen {
protected:
	Input input1;
	Input input2;
	Output output1;
	Output output2;
	HttpServer httpServer1;

	virtual void input1_onValueChanged(Event* event) {
		ValueChangedEvent* castedEvent = (ValueChangedEvent*) event;
		if (castedEvent->currentValue == HIGH) {
			output1.toggleHighLow();
		}
	}
	
	virtual void input2_onValueChanged(Event* event) {
		ValueChangedEvent* castedEvent = (ValueChangedEvent*) event;
		if (castedEvent->currentValue == HIGH) {
			output2.toggleHighLow();
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
			castedEvent->client->print(F("sToggler\");if(a){a=JSON.parse(a);bindingManager.addListener(d,b,toggleClass,a)}})});<\/script><style>.content{font-size:21px;font-weight:300;line-height:1.4}<\/style><\/head><body class=\"content\"><br\/><div class=\"container-fluid\"><div class=\"row\"><div class=\"col-md-2\"><div class=\"panel panel-primary te"));
			castedEvent->client->print(F("xt-center\"><div class=\"panel-heading\">Light 1<\/div><div class=\"panel-body\"><div class=\"label\"> State: <span classToggler='{\"1\":\"label-warning\",\"0\":\"label-success\"}' bindToProperty=\"output1\" textToggler='{\"1\":\"OFF\",\"0\":\"ON\"}'><\/span><\/div><div> Commands: <\/div><button class=\"btn btn-block btn-lg\" typ"));
			castedEvent->client->print(F("e=\"button\" onclick=\"invoke('light1Toggle')\"> Toggle <\/button><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light1On')\"> Turn On <\/button><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light1Off')\"> Turn Off <\/button><\/div><\/div><\/div><div class=\"col-md-2\"><"));
			castedEvent->client->print(F("div class=\"panel panel-primary text-center\"><div class=\"panel-heading\">Light 2<\/div><div class=\"panel-body\"><div class=\"label\"> State: <span classToggler='{\"1\":\"label-warning\",\"0\":\"label-success\"}' bindToProperty=\"output2\" textToggler='{\"1\":\"OFF\",\"0\":\"ON\"}'><\/span><\/div><div> Commands: <\/div><button"));
			castedEvent->client->print(F(" class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light2Toggle')\"> Toggle <\/button><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light2On')\"> Turn On <\/button><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light2Off')\"> Turn Off <\/button><\/div><\/"));
			castedEvent->client->print(F("div><\/div><\/div><div class=\"row\"><div class=\"col-md-12\"><span class=\"label label-default\"><span class=\"glyphicon glyphicon-dashboard\"><\/span> Free memory (SRAM): <span bindToProperty=\"FREE_MEM\"><\/span> bytes<\/span><\/div><\/div><\/div><\/body>"));
			return;
		} else if (strcmp_P(command, PSTR("getState")) == 0) {
			urlFound = true;
		} else if (strcmp_P(command, PSTR("light1Toggle")) == 0) {
			urlFound = true;
			{
				output1.toggleHighLow();
			}
		} else if (strcmp_P(command, PSTR("light1Off")) == 0) {
			urlFound = true;
			{
				output1.setHigh();
			}
		} else if (strcmp_P(command, PSTR("light1On")) == 0) {
			urlFound = true;
			{
				output1.setLow();
			}
		} else if (strcmp_P(command, PSTR("light2Toggle")) == 0) {
			urlFound = true;
			{
				output2.toggleHighLow();
			}
		} else if (strcmp_P(command, PSTR("light2Off")) == 0) {
			urlFound = true;
			{
				output2.setHigh();
			}
		} else if (strcmp_P(command, PSTR("light2On")) == 0) {
			urlFound = true;
			{
				output2.setLow();
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
		input1.pin = 8;
		input1.internalPullUp = true;
		input1.pollInterval = 200;
		input1.setup();

		input2.pin = 9;
		input2.internalPullUp = true;
		input2.pollInterval = 200;
		input2.setup();

		output1.pin = 2;
		output1.initialValue = 1;
		output1.setup();

		output2.pin = 3;
		output2.initialValue = 1;
		output2.setup();

		uint8_t macAddress[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55 };
		uint8_t ipAddress[] = { 192, 168, 100, 91 };
		memcpy(httpServer1.macAddress, macAddress, 6);
		memcpy(httpServer1.ipAddress, ipAddress, 4);
		httpServer1.port = 80;
		httpServer1.setup();

		input1.onValueChanged = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::input1_onValueChanged);
		input2.onValueChanged = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::input2_onValueChanged);
		httpServer1.onCommandReceived = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_onCommandReceived);
	}
	
	virtual void loop() {
		input1.loop();
		input2.loop();
		httpServer1.loop();
	}
	
	void printStateAsJson(Print* print) {
		print->print(F("{"));
	
		input1.printStateAsJson(F("input1"), print);
		print->print(F(","));
		input2.printStateAsJson(F("input2"), print);
		print->print(F(","));
		output1.printStateAsJson(F("output1"), print);
		print->print(F(","));
		output2.printStateAsJson(F("output2"), print);
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
