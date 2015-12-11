#include <Ethernet.h>
#include <FlowerPlatformArduinoRuntime.h>
#include <SPI.h>
#include <HttpServer.h>
#include <EthernetNetworkAdapter.h>
#include <Output.h>
#include <Input.h>

class ApplicationGen {
protected:
	Input input1;
	Input input2;
	Output output1;
	Output output2;
	HttpServer httpServer1;
	EthernetNetworkAdapter ethernetNetworkAdapter1;

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
			out.write_P(PSTR("\")},1000)});</script><style>.content{font-size:21px;font-weight:300;line-height:1.4}</style></head><body class=\"content\"><br/><div class=\"container-fluid\"><div class=\"row\"><div class=\"col-md-2\"><div class=\"panel panel-primary text-center\"><div class=\"panel-heading\">Light 1</div><div class=\"panel-bod"));
			out.write_P(PSTR("y\"><div class=\"label\"> State: <span classToggler='{\"1\":\"label-warning\",\"0\":\"label-success\"}' bindToProperty=\"output1\" textToggler='{\"1\":\"OFF\",\"0\":\"ON\"}'></span></div><div> Commands: </div><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light1Toggle')\"> Toggle </button><button cla"));
			out.write_P(PSTR("ss=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light1On')\"> Turn On </button><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light1Off')\"> Turn Off </button></div></div></div><div class=\"col-md-2\"><div class=\"panel panel-primary text-center\"><div class=\"panel-heading\">L"));
			out.write_P(PSTR("ight 2</div><div class=\"panel-body\"><div class=\"label\"> State: <span classToggler='{\"1\":\"label-warning\",\"0\":\"label-success\"}' bindToProperty=\"output2\" textToggler='{\"1\":\"OFF\",\"0\":\"ON\"}'></span></div><div> Commands: </div><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light2Toggl"));
			out.write_P(PSTR("e')\"> Toggle </button><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light2On')\"> Turn On </button><button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('light2Off')\"> Turn Off </button></div></div></div></div><div class=\"row\"><div class=\"col-md-12\"><span class=\"lab"));
			out.write_P(PSTR("el label-default\"><span class=\"glyphicon glyphicon-dashboard\"></span> Free memory (SRAM): <span bindToProperty=\"FREE_MEM\"></span> bytes</span></div></div></div></body>"));
			out.flush();
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
		
		input1.pin = 8;
		input1.internalPullUp = true;
		input1.pollInterval = 200;

		input2.pin = 9;
		input2.internalPullUp = true;
		input2.pollInterval = 200;

		output1.pin = 2;
		output1.initialValue = 1;

		output2.pin = 3;
		output2.initialValue = 1;

		uint8_t ipAddress[] = { 192, 168, 100, 91 };
		memcpy(httpServer1.ipAddress, ipAddress, 4);
		httpServer1.port = 80;

		uint8_t macAddress[] = { 0x0E, 0xBB, 0xCC, 0xD5, 0xE2, 0xF4 };
		memcpy(ethernetNetworkAdapter1.macAddress, macAddress, 6);
		ethernetNetworkAdapter1.httpServer = &httpServer1;


		input1.setup();
		input2.setup();
		output1.setup();
		output2.setup();
		httpServer1.setup();
		ethernetNetworkAdapter1.setup();

		input1.onValueChanged = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::input1_onValueChanged);
		input2.onValueChanged = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::input2_onValueChanged);
		httpServer1.onCommandReceived = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_onCommandReceived);
	}
	
	virtual void loop() {
		input1.loop();
		input2.loop();
		ethernetNetworkAdapter1.loop();
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

		write_P(print, PSTR("\"FREE_MEM\": "));
		print->print(freeRam());
		print->print("}");
	}

};


ApplicationGen* app = new ApplicationGen();

void setup() {
	app->setup();
}

void loop() {
	app->loop();
}
