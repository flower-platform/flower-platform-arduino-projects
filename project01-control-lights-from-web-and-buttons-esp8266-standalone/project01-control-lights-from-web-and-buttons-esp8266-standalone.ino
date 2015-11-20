#include <ESP8266NativeNetworkAdapter.h>
#include <ESP8266WiFi.h>
#include <FlowerPlatformArduinoRuntime.h>
#include <HttpServer.h>
#include <Output.h>

class ApplicationGen {
protected:
	Output output12;
	Output output14;
	HttpServer httpServer;
	ESP8266NativeNetworkAdapter eSP8266NativeNetworkAdapter;

	virtual void httpServer_onCommandReceived(Event* event) {
		HttpCommandEvent* castedEvent = (HttpCommandEvent*) event;
		
		char command[32];
		castedEvent->server->getCommandFromUrl(castedEvent->url, command);
		bool urlFound = false;
		
		BufferedPrint out(castedEvent->client);
		
		if (strcmp_P(command, PSTR("")) == 0) {
			urlFound = true;
			castedEvent->server->httpSuccess(&out, HttpServer::CONTENT_TYPE_HTML);
			write_P(&out, PSTR("<!DOCTYPE html><html><head><meta charset=\"ISO-8859-1\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><script src=\"http://code.jquery.com/jquery-1.11.2.min.js\"></script><link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css\"><script src"));
			write_P(&out, PSTR("=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/js/bootstrap.min.js\"></script><link rel=\"stylesheet\" href=\"http://bootswatch.com/paper/bootstrap.min.css\"><link href='http://fonts.googleapis.com/css?family=Roboto' rel='stylesheet' type='text/css'><script>var url=\"\";var bindingManager={data:{},liste"));
			write_P(&out, PSTR("ners:{},activeRequests:0,addListener:function(f,b,c,a){var e=this.listeners[f];if(typeof e===\"undefined\"){e=[];this.listeners[f]=e}var d=function(){var g=bindingManager.data[f];c(b,g,a)};e.push(d);d()},set:function(d,c){if(this.data[d]!==c){this.data[d]=c;var b=this.listeners[d];if(typeof b!==\"undef"));
			write_P(&out, PSTR("ined\"&&b!==null){for(var a=0;a<b.length;a++){b[a]()}}}}};var toggleClass=function(d,b,c){for(var e in c){var a=c[e];if(e!=b){d.parent().removeClass(a)}}if(c[b]){d.parent().addClass(c[b])}};var setText=function(c,a,b){if(typeof b!==\"undefined\"&&b[a]){a=b[a]}c.text(a)};var invoke=function(c,b,a){bindi"));
			write_P(&out, PSTR("ngManager.activeRequests++;$.ajax({url:url+c,success:function(e){bindingManager.activeRequests--;for(var d in e){bindingManager.set(d,e[d])}if(b){b()}},error:function(){bindingManager.activeRequests--;if(a){a()}},timeout:10000})};$(function(){$(\"[bindToProperty]\").each(function(){var b=$(this);var d"));
			write_P(&out, PSTR("=b.attr(\"bindToProperty\");var c=b.attr(\"textToggler\");if(c){c=JSON.parse(c)}bindingManager.addListener(d,b,setText,c);var a=b.attr(\"classToggler\");if(a){a=JSON.parse(a);bindingManager.addListener(d,b,toggleClass,a)}});setInterval(function(){if(bindingManager.activeRequests>0){return}invoke(\"getState"));
			write_P(&out, PSTR("\")},1000)});</script><style>.content{font-size:21px;font-weight:300;line-height:1.4}</style></head><body class=\"content\"><br/><div class=\"container-fluid\"><div class=\"row\"><div class=\"col-md-2\"><div class=\"panel panel-primary text-center\"><div class=\"panel-heading\">Light 1</div><div class=\"panel-bod"));
			write_P(&out, PSTR("y\"><div class=\"label\"> State: <span classToggler='{\"1\":\"label-warning\",\"0\":\"label-success\"}' bindToProperty=\"output12\" textToggler='{\"1\":\"OFF\",\"0\":\"ON\"}'></span></div><div> Commands </div><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light1Toggle')\"> Toggle </button><button cla"));
			write_P(&out, PSTR("ss=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light1On')\"> Turn on </button><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light1Off')\"> Turn off </button></div></div></div><div class=\"col-md-2\"><div class=\"panel panel-primary text-center\"><div class=\"panel-heading\">L"));
			write_P(&out, PSTR("ight 2</div><div class=\"panel-body\"><div class=\"label\"> State: <span classToggler='{\"1\":\"label-warning\",\"0\":\"label-success\"}' bindToProperty=\"output14\" textToggler='{\"1\":\"OFF\",\"0\":\"ON\"}'></span></div><div> Commands </div><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light2Toggl"));
			write_P(&out, PSTR("e')\"> Toggle </button><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light2On')\"> Turn on </button><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light2Off')\"> Turn off </button></div></div></div></div><div class=\"row\"><div class=\"col-md-12\"><span class=\"lab"));
			write_P(&out, PSTR("el label-default\"><span class=\"glyphicon glyphicon-dashboard\"></span> Free memory (SRAM): <span bindToProperty=\"FREE_MEM\"></span> bytes</span></div></div></div></body>"));
			out.flush();
			return;
		} else if (strcmp_P(command, PSTR("getState")) == 0) {
			urlFound = true;
		} else if (strcmp_P(command, PSTR("light1Toggle")) == 0) {
			urlFound = true;
			{
				output12.toggleHighLow();
			}
		} else if (strcmp_P(command, PSTR("light1Off")) == 0) {
			urlFound = true;
			{
				output12.setHigh();
			}
		} else if (strcmp_P(command, PSTR("light1On")) == 0) {
			urlFound = true;
			{
				output12.setLow();
			}
		} else if (strcmp_P(command, PSTR("light2Toggle")) == 0) {
			urlFound = true;
			{
				output14.toggleHighLow();
			}
		} else if (strcmp_P(command, PSTR("light2Off")) == 0) {
			urlFound = true;
			{
				output14.setHigh();
			}
		} else if (strcmp_P(command, PSTR("light2On")) == 0) {
			urlFound = true;
			{
				output14.setLow();
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
	
public:
	virtual ~ApplicationGen() { }

	virtual void setup() {
		pinMode(SS, OUTPUT);
		digitalWrite(SS, HIGH);
		
		output12.pin = 12;
		output12.initialValue = 1;

		output14.pin = 14;
		output14.initialValue = 1;

		uint8_t ipAddress[] = { 192, 168, 100, 253 };
		memcpy(httpServer.ipAddress, ipAddress, 4);
		httpServer.port = 80;

		eSP8266NativeNetworkAdapter.ssid = "wifi-work";
		eSP8266NativeNetworkAdapter.password = "wifi-work-pass-123";
		eSP8266NativeNetworkAdapter.httpServer = &httpServer;


		output12.setup();
		output14.setup();
		httpServer.setup();
		eSP8266NativeNetworkAdapter.setup();

		httpServer.onCommandReceived = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_onCommandReceived);
	}
	
	virtual void loop() {
		eSP8266NativeNetworkAdapter.loop();
	}
	
	void printStateAsJson(Print* print) {
		print->print(F("{"));
	
		output12.printStateAsJson(F("output12"), print);
		print->print(F(","));
		output14.printStateAsJson(F("output14"), print);
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
