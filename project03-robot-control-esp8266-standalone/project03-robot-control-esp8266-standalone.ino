#include <ESP8266NativeNetworkAdapter.h>
#include <ESP8266WiFi.h>
#include <FlowerPlatformArduinoRuntime.h>
#include <MotorController.h>
#include <HttpServer.h>

class ApplicationGen {
protected:
	HttpServer httpServer1;
	MotorController motorController1;
	MotorController motorController2;
	ESP8266NativeNetworkAdapter eSP8266NativeNetworkAdapter1;

	virtual void httpServer_onCommandReceived(Event* event) {
		HttpCommandEvent* castedEvent = (HttpCommandEvent*) event;
		
		char command[32];
		castedEvent->server->getCommandFromUrl(castedEvent->url, command);
		bool urlFound = false;
		
		BufferedPrint out(castedEvent->client);
		
		if (strcmp_P(command, PSTR("")) == 0) {
			urlFound = true;
			castedEvent->server->httpSuccess(&out, HttpServer::CONTENT_TYPE_HTML);
			out.write_P(PSTR("<!DOCTYPE html><html><head><meta charset=\"ISO-8859-1\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><script src=\"http://code.jquery.com/jquery-1.11.2.min.js\"></script><link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css\"><script src"));
			out.write_P(PSTR("=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/js/bootstrap.min.js\"></script><link rel=\"stylesheet\" href=\"http://bootswatch.com/paper/bootstrap.min.css\"><link href='http://fonts.googleapis.com/css?family=Roboto' rel='stylesheet' type='text/css'><script>var url=\"\";var bindingManager={data:{},liste"));
			out.write_P(PSTR("ners:{},activeRequests:0,addListener:function(f,b,c,a){var e=this.listeners[f];if(typeof e===\"undefined\"){e=[];this.listeners[f]=e}var d=function(){var g=bindingManager.data[f];c(b,g,a)};e.push(d);d()},set:function(d,c){if(this.data[d]!==c){this.data[d]=c;var b=this.listeners[d];if(typeof b!==\"undef"));
			out.write_P(PSTR("ined\"&&b!==null){for(var a=0;a<b.length;a++){b[a]()}}}}};var toggleClass=function(d,b,c){for(var e in c){var a=c[e];if(e!=b){d.parent().removeClass(a)}}if(c[b]){d.parent().addClass(c[b])}};var setText=function(c,a,b){if(typeof b!==\"undefined\"&&b[a]){a=b[a]}c.text(a)};var invoke=function(c,b,a){bindi"));
			out.write_P(PSTR("ngManager.activeRequests++;$.ajax({url:url+c,success:function(e){bindingManager.activeRequests--;for(var d in e){bindingManager.set(d,e[d])}if(b){b()}},error:function(){bindingManager.activeRequests--;if(a){a()}},timeout:10000})};$(function(){$(\"[bindToProperty]\").each(function(){var b=$(this);var d"));
			out.write_P(PSTR("=b.attr(\"bindToProperty\");var c=b.attr(\"textToggler\");if(c){c=JSON.parse(c)}bindingManager.addListener(d,b,setText,c);var a=b.attr(\"classToggler\");if(a){a=JSON.parse(a);bindingManager.addListener(d,b,toggleClass,a)}});setInterval(function(){if(bindingManager.activeRequests>0){return}invoke(\"getState"));
			out.write_P(PSTR("\")},1000)});</script><style>.content{font-size:21px;font-weight:300;line-height:1.4}</style></head><body class=\"content\"><br/><div class=\"container-fluid\"><div class=\"row\"><div class=\"col-md-4\"><div class=\"panel panel-primary text-center\"><div class=\"panel-heading\"></div><div class=\"panel-body\"><div"));
			out.write_P(PSTR(" class=\"row\"><div class=\"col-xs-4\"><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('fl')\"> FL </button></div><div class=\"col-xs-4\"><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('f')\"><span class=\"glyphicon glyphicon-arrow-up\"></span></button></div><div class=\""));
			out.write_P(PSTR("col-xs-4\"><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('fr')\"> FR </button></div></div><div class=\"row\"><div class=\"col-xs-4\"><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('l')\"><span class=\"glyphicon glyphicon-arrow-left\"></span></button></div><div class=\""));
			out.write_P(PSTR("col-xs-4\"><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('s')\"><span class=\"glyphicon glyphicon-stop\"></span></button></div><div class=\"col-xs-4\"><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('r')\"><span class=\"glyphicon glyphicon-arrow-right\"></span></button"));
			out.write_P(PSTR("></div></div><div class=\"row\"><div class=\"col-xs-4\"><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('bl')\"> BL </button></div><div class=\"col-xs-4\"><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('b')\"><span class=\"glyphicon glyphicon-arrow-down\"></span></button"));
			out.write_P(PSTR("></div><div class=\"col-xs-4\"><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('br')\"> BR </button></div></div></div></div></div></div><div class=\"row\"><div class=\"col-md-12\"><span class=\"label label-default\"><span class=\"glyphicon glyphicon-dashboard\"></span> Free memory (SRAM): <s"));
			out.write_P(PSTR("pan bindToProperty=\"FREE_MEM\"></span> bytes</span></div></div></div></body>"));
			out.flush();
			return;
		} else if (strcmp_P(command, PSTR("getState")) == 0) {
			urlFound = true;
		} else if (strcmp_P(command, PSTR("f")) == 0) {
			urlFound = true;
		} else if (strcmp_P(command, PSTR("b")) == 0) {
			urlFound = true;
		} else if (strcmp_P(command, PSTR("s")) == 0) {
			urlFound = true;
		} else if (strcmp_P(command, PSTR("l")) == 0) {
			urlFound = true;
		} else if (strcmp_P(command, PSTR("r")) == 0) {
			urlFound = true;
		} else if (strcmp_P(command, PSTR("fl")) == 0) {
			urlFound = true;
		} else if (strcmp_P(command, PSTR("fr")) == 0) {
			urlFound = true;
		} else if (strcmp_P(command, PSTR("bl")) == 0) {
			urlFound = true;
		} else if (strcmp_P(command, PSTR("br")) == 0) {
			urlFound = true;
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
		
		uint8_t ipAddress[] = { 192, 168, 100, 253 };
		memcpy(httpServer1.ipAddress, ipAddress, 4);
		httpServer1.port = 80;

		motorController1.controlPin1 = 4;
		motorController1.controlPin2 = 5;

		motorController2.controlPin1 = 12;
		motorController2.controlPin2 = 13;

		eSP8266NativeNetworkAdapter1.ssid = "wifi-work";
		eSP8266NativeNetworkAdapter1.password = "wifi-work-pass-123";
		eSP8266NativeNetworkAdapter1.httpServer = &httpServer1;


		httpServer1.setup();
		motorController1.setup();
		motorController2.setup();
		eSP8266NativeNetworkAdapter1.setup();

		httpServer1.onCommandReceived = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_onCommandReceived);
	}
	
	virtual void loop() {
		eSP8266NativeNetworkAdapter1.loop();
	}
	
	void printStateAsJson(Print* print) {
		print->print(F("{"));
	

		write_P(print, PSTR("\"FREE_MEM\": "));
		print->print(freeRam());
		print->print("}");
	}

};


#include "CustomCode.h"

ApplicationCustom app;

void setup() {
	app.setup();
}

void loop() {
	app.loop();
}
