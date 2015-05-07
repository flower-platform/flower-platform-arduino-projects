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

class ApplicationGen : public ApplicationBase {
protected:
	Input* toggle1;
	Input* toggle2;
	Output* led13;
	Output* relay1;
	Output* ledRYG;
	Output* ledBlue;
	Output* relay2;
	Output* relay3;
	UpdatesBuffer* updatesBuffer;
	HttpServer* httpServer;
	Timer* timer1;
	Timer* timerLedBlue;
	Timer* timerDan;

	virtual void toggle1_VALUE_CHANGED_EVENT(Event* event) {
		ValueChangedEvent* castedEvent = (ValueChangedEvent*) event;
		{
			relay1->toggleHighLow();
		}
		{
//			String key = "toggle1";
//			int value = castedEvent->currentValue;
//			updatesBuffer->updateEntry(key, value);
		}
	}
	virtual void toggle2_VALUE_CHANGED_EVENT(Event* event) {
		ValueChangedEvent* castedEvent = (ValueChangedEvent*) event;
		if (castedEvent->currentValue == HIGH) {
			relay1->toggleHighLow();
		}
		if (castedEvent->currentValue == HIGH) {
			ledBlue->toggleHighLow();
		}
		if (castedEvent->currentValue == HIGH) {
			relay2->toggleHighLow();
		}
		if (castedEvent->currentValue == HIGH) {
			ledRYG->toggleHighLow();
		}
		{
//			String key = "toggle2";
//			int value = castedEvent->currentValue;
//			updatesBuffer->updateEntry(key, value);
		}
	}
	virtual void relay1_VALUE_CHANGED_EVENT(Event* event) {
		ValueChangedEvent* castedEvent = (ValueChangedEvent*) event;
		{
//			String key = "relay1";
//			int value = castedEvent->currentValue;
//			updatesBuffer->updateEntry(key, value);
		}
	}
	virtual void httpServer_getPage(Event* event) {
		HttpCommandEvent* castedEvent = (HttpCommandEvent*) event;
		{
			castedEvent->server->httpSuccess("text/html");
			castedEvent->client->print(F("<!DOCTYPE html> <html> <head> <meta charset=\"ISO-8859-1\"> <script src=\"http:\/\/code.jquery.com\/jquery-1.11.2.min.js\"><\/script> <link rel=\"stylesheet\" href=\"https:\/\/maxcdn.bootstrapcdn.com\/bootstrap\/3.3.4\/css\/bootstrap.min.css\"> <script src=\"https:\/\/maxcdn.bootstrapcdn.com\/bootstrap\/3.3.4\/js\/bootstrap.min.js\"><\/script> <link rel=\"stylesheet\" href=\"http:\/\/bootswatch.com\/paper\/bootstrap.min.css\"> <link href='http:\/\/fonts.googleapis.com\/css?family=Roboto' rel='stylesheet' type='text\/css'> <script>var url=\"\";var bindingManager={data:{temperature:25,humidity:25},listeners:{},addListener:function(c,b){var a=this.listeners[c];if(typeof a===\"undefined\"){a=[];this.listeners[c]=a}a.push(b)},set:function(d,c){if(this.data[d]!==c){this.data[d]=c;var b=this.listeners[d];if(typeof b!==\"undefined\"&&b!==null){for(var a=0;a<b.length;a++){b[a]()}}}}};var addTextListener=function(d,c,a){var b=function(){var e=$(\"#\"+d);var f=bindingManager.data[c];if(typeof a!==\"undefined\"){f=a[f]}e.text(f)};bindingManager."));
			castedEvent->client->print(F("addListener(c,b);b()};var addClassListener=function(d,c,a){var b=function(){var f=$(\"#\"+d);var h=bindingManager.data[c];for(var g in a){var e=a[g];if(g==h){f.addClass(e)}else{f.removeClass(e)}}};bindingManager.addListener(c,b);b()};var invoke=function(a){$.get(url+a,function(c){for(var b in c){bindingManager.set(b,c[b])}})};var refresh=function(){bindingManager.set(\"temperature\",(bindingManager.data.temperature-1)%50);bindingManager.set(\"humidity\",(bindingManager.data.humidity+1)%50);invoke(\"getUpdates\")};setInterval(function(){refresh()},1000);<\/script> <\/head> <body> <br\/> <div class=\"container-fluid lead\"> <div class=\"row\"> <div class=\"col-md-3\"> <div class=\"panel panel-primary text-center\" id=\"bedroom\"> <div class=\"panel-heading\">Bedroom<\/div> <div class=\"panel-body\"> <div class=\"row\"> <div class=\"col-xs-6\"> <div>Temperature<\/div> <div> <span id=\"bedroom-temperature\"><\/span> &#176;C <script>addTextListener(\"bedroom-temperature\",\"temperature\");<\/script> <\/div> <\/div> <div class=\"col"));
			castedEvent->client->print(F("-xs-6\"> <div>Humidity<\/div> <div> <span id=\"bedroom-humidity\"><\/span> %RH <script>addTextListener(\"bedroom-humidity\",\"humidity\");<\/script> <\/div> <\/div> <\/div> <div>Light<\/div> <div> <span id=\"bedroom-light\"><\/span> <script>addTextListener(\"bedroom-light\",\"relay1\");<\/script> <\/div> <button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('relay1Toggle')\"> <span class=\"glyphicon glyphicon-flash\"><\/span> LIGHT <\/button> <\/div> <\/div> <\/div> <div class=\"col-md-3\"> <div class=\"panel panel-primary text-center\" id=\"bathroom\"> <div class=\"panel-heading\">Bathroom<\/div> <div class=\"panel-body\"> <div class=\"row\"> <div class=\"col-xs-6\"> <div>Temperature<\/div> <div> <span id=\"bathroom-temperature\"><\/span> &#176;C <script>addTextListener(\"bathroom-temperature\",\"temperature\");<\/script> <\/div> <\/div> <div class=\"col-xs-6\"> <div>Humidity<\/div> <div> <span id=\"bathroom-humidity\"><\/span> %RH <script>addTextListener(\"bathroom-humidity\",\"humidity\");<\/script> <\/div> <\/div> <\/div> <div>Light<\/div>"));
			castedEvent->client->print(F(" <div> <span id=\"bathroom-light\"><\/span> <script>addTextListener(\"bathroom-light\",\"relay1\");<\/script> <\/div> <button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('relay1Toggle')\"> <span class=\"glyphicon glyphicon-flash\"><\/span> LIGHT <\/button> <\/div> <\/div> <\/div> <div class=\"col-md-3\"> <div class=\"panel panel-primary text-center\" id=\"kitchen\"> <div class=\"panel-heading\">Kitchen<\/div> <div class=\"panel-body\"> <div class=\"row\"> <div class=\"col-xs-6\"> <div>Temperature<\/div> <div> <span id=\"kitchen-temperature\"><\/span> &#176;C <script>addTextListener(\"kitchen-temperature\",\"temperature\");<\/script> <\/div> <\/div> <div class=\"col-xs-6\"> <div>Humidity<\/div> <div> <span id=\"kitchen-humidity\"><\/span> %RH <script>addTextListener(\"kitchen-humidity\",\"humidity\");<\/script> <\/div> <\/div> <\/div> <div>Light<\/div> <div> <span id=\"kitchen-light\"><\/span> <script>addTextListener(\"kitchen-light\",\"relay1\");<\/script> <\/div> <button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('relay"));
			castedEvent->client->print(F("1Toggle')\"> <span class=\"glyphicon glyphicon-flash\"><\/span> LIGHT <\/button> <\/div> <\/div> <\/div> <div class=\"col-md-3\"> <div class=\"panel panel-primary text-center\" id=\"dining-room\"> <div class=\"panel-heading\">Dining Room<\/div> <div class=\"panel-body\"> <div class=\"row\"> <div class=\"col-xs-6\"> <div>Temperature<\/div> <div> <span id=\"dining-room-temperature\"><\/span> &#176;C <script>addTextListener(\"dining-room-temperature\",\"temperature\");<\/script> <\/div> <\/div> <div class=\"col-xs-6\"> <div>Humidity<\/div> <div> <span id=\"dining-room-humidity\"><\/span> %RH <script>addTextListener(\"dining-room-humidity\",\"humidity\");<\/script> <\/div> <\/div> <\/div> <div>Light<\/div> <div> <span id=\"dining-room-light\"><\/span> <script>addTextListener(\"dining-room-light\",\"relay1\");<\/script> <\/div> <button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('relay1Toggle')\"> <span class=\"glyphicon glyphicon-flash\"><\/span> LIGHT <\/button> <\/div> <\/div> <\/div> <\/div> <div class=\"row\"> <div class=\"col-md-4\"> <div "));
			castedEvent->client->print(F("class=\"panel panel-primary text-center\"> <div class=\"panel-heading\">Blinker releu<\/div> <div class=\"panel-body\"> <button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('timer1Start')\"> <span class=\"glyphicon glyphicon-play\"><\/span> START <\/button> <button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('timer1Stop')\"> <span class=\"glyphicon glyphicon-stop\"><\/span> STOP <\/button> <\/div> <\/div> <\/div> <div class=\"col-md-4\"> <div class=\"panel panel-primary text-center\"> <div class=\"panel-heading\">Panel with text<\/div> <div class=\"panel-body\"> <div>Salut. Acesta este un text.<\/div> <div>Salut. Acesta este un text.<\/div> <\/div> <\/div> <\/div> <div class=\"col-md-4\"> <div class=\"panel panel-primary text-center\"> <div class=\"panel-heading\">Blinker led albastru<\/div> <div class=\"panel-body\"> <button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('ledBlueBlinkStart')\"> <span class=\"glyphicon glyphicon-play\"><\/span> START <\/button> <button class=\"btn btn-block bt"));
			castedEvent->client->print(F("n-lg\" type=\"button\" onclick=\"invoke('ledBlueBlinkStop')\"> <span class=\"glyphicon glyphicon-stop\"><\/span> STOP <\/button> <\/div> <\/div> <\/div> <\/div> <div class=\"row\"> <div class=\"col-md-4\"> <div class=\"panel panel-primary text-center\"> <div class=\"panel-heading\">Blinker releu<\/div> <div class=\"panel-body\"> <button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('timer1Start')\"> <span class=\"glyphicon glyphicon-play\"><\/span> START <\/button> <button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('timer1Stop')\"> <span class=\"glyphicon glyphicon-stop\"><\/span> STOP <\/button> <\/div> <\/div> <\/div> <div class=\"col-md-4\"> <div class=\"panel panel-primary text-center\"> <div class=\"panel-heading\">Panel with text<\/div> <div class=\"panel-body\"> <div>Salut. Acesta este un text.<\/div> <div>Salut. Acesta este un text.<\/div> <\/div> <\/div> <\/div> <div class=\"col-md-4\"> <div class=\"panel panel-primary text-center\"> <div class=\"panel-heading\">Blinker led albastru<\/div> <div class=\"pan"));
			castedEvent->client->print(F("el-body\"> <button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('ledBlueBlinkStart')\"> <span class=\"glyphicon glyphicon-play\"><\/span> START <\/button> <button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('ledBlueBlinkStop')\"> <span class=\"glyphicon glyphicon-stop\"><\/span> STOP <\/button> <\/div> <\/div> <\/div> <\/div> <div class=\"row\"> <div class=\"col-md-4\"> <div class=\"panel panel-primary text-center\"> <div class=\"panel-heading\">Test Dan<\/div> <div class=\"panel-body\"> <button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('ledOn1Sec')\"> <span class=\"glyphicon glyphicon-play\"><\/span> Led on 1 sec <\/button> <button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('releuDanOn')\"> <span class=\"glyphicon glyphicon-stop\"><\/span> Releu ON <\/button> <button class=\"btn btn-block btn-lg\" type=\"button\" onclick=\"invoke('releuDanOff')\"> <span class=\"glyphicon glyphicon-play\"><\/span> Releu OFF <\/button> <\/div> <\/div> <\/div> <\/div> <\/div> <\/body>"));
		}
	}
	virtual void httpServer_getUpdates(Event* event) {
		HttpCommandEvent* castedEvent = (HttpCommandEvent*) event;
		{
//			castedEvent->server->httpSuccess("application/json");
//			castedEvent->client->print(updatesBuffer->getEntriesAsJson());
		}
	}
	virtual void httpServer_relay1Toggle(Event* event) {
		HttpCommandEvent* castedEvent = (HttpCommandEvent*) event;
		{
			relay1->toggleHighLow();
		}
	}
	virtual void httpServer_timer1Start(Event* event) {
		HttpCommandEvent* castedEvent = (HttpCommandEvent*) event;
		{
			timer1->start();
		}
	}
	virtual void httpServer_timer1Stop(Event* event) {
		HttpCommandEvent* castedEvent = (HttpCommandEvent*) event;
		{
			timer1->stop();
		}
	}
	virtual void httpServer_ledBlueBlinkStart(Event* event) {
		HttpCommandEvent* castedEvent = (HttpCommandEvent*) event;
		{
			timerLedBlue->start();
		}
	}
	virtual void httpServer_ledBlueBlinkStop(Event* event) {
		HttpCommandEvent* castedEvent = (HttpCommandEvent*) event;
		{
			timerLedBlue->stop();
		}
	}
	virtual void httpServer_ledOn1Sec(Event* event) {
		HttpCommandEvent* castedEvent = (HttpCommandEvent*) event;
		{
			timerDan->start();
		}
		{
			ledBlue->setHigh();
		}
	}
	virtual void httpServer_releuDanOn(Event* event) {
		HttpCommandEvent* castedEvent = (HttpCommandEvent*) event;
		{
			relay3->setHigh();
		}
	}
	virtual void httpServer_releuDanOff(Event* event) {
		HttpCommandEvent* castedEvent = (HttpCommandEvent*) event;
		{
			relay3->setLow();
		}
	}
	virtual void timer1_TIMER_EVENT(Event* event) {
		TimerEvent* castedEvent = (TimerEvent*) event;
		{
			relay3->toggleHighLow();
		}
	}
	virtual void timer1_TIMER_COMPLETE_EVENT(Event* event) {
		TimerEvent* castedEvent = (TimerEvent*) event;
		{
			relay2->setLow();
		}
	}
	virtual void timerLedBlue_TIMER_EVENT(Event* event) {
		TimerEvent* castedEvent = (TimerEvent*) event;
		{
			ledBlue->toggleHighLow();
		}
	}
	virtual void timerDan_TIMER_COMPLETE_EVENT(Event* event) {
		TimerEvent* castedEvent = (TimerEvent*) event;
		{
			ledBlue->setLow();
		}
	}

public:
	ApplicationGen() : ApplicationBase(16) { }
	virtual ~ApplicationGen() { }

	virtual void setup() {
		toggle1 = new Input();
		toggle1->pin = 2;
		addComponent(toggle1);
		
		toggle2 = new Input();
		toggle2->pin = 3;
		addComponent(toggle2);
		
		led13 = new Output(13);
		
		relay1 = new Output(5);
		
		ledRYG = new Output(9);
		
		ledBlue = new Output(8);
		
		relay2 = new Output(6);
		
		relay3 = new Output(7);
		
		updatesBuffer = new UpdatesBuffer(16);
		
		httpServer = new HttpServer();
		addComponent(httpServer);
		
		timer1 = new Timer(false);
		timer1->delay = 500;
		timer1->repeatCount = 0;
		addComponent(timer1);
		
		timerLedBlue = new Timer(false);
		timerLedBlue->delay = 500;
		timerLedBlue->repeatCount = 0;
		addComponent(timerLedBlue);
		
		timerDan = new Timer(false);
		timerDan->delay = 1000;
		timerDan->repeatCount = 1;
		addComponent(timerDan);
		
		toggle1->addEventListener(Input::VALUE_CHANGED_EVENT, new DelegatingListener<ApplicationGen>(this, &ApplicationGen::toggle1_VALUE_CHANGED_EVENT));
		toggle2->addEventListener(Input::VALUE_CHANGED_EVENT, new DelegatingListener<ApplicationGen>(this, &ApplicationGen::toggle2_VALUE_CHANGED_EVENT));
		relay1->addEventListener(Output::VALUE_CHANGED_EVENT, new DelegatingListener<ApplicationGen>(this, &ApplicationGen::relay1_VALUE_CHANGED_EVENT));
		httpServer->addUrlHandler("", new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_getPage));
		httpServer->addUrlHandler("getUpdates", new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_getUpdates));
		httpServer->addUrlHandler("relay1Toggle", new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_relay1Toggle));
		httpServer->addUrlHandler("timer1Start", new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_timer1Start));
		httpServer->addUrlHandler("timer1Stop", new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_timer1Stop));
		httpServer->addUrlHandler("ledBlueBlinkStart", new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_ledBlueBlinkStart));
		httpServer->addUrlHandler("ledBlueBlinkStop", new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_ledBlueBlinkStop));
		httpServer->addUrlHandler("ledOn1Sec", new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_ledOn1Sec));
		httpServer->addUrlHandler("releuDanOn", new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_releuDanOn));
		httpServer->addUrlHandler("releuDanOff", new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_releuDanOff));
		timer1->addEventListener(Timer::TIMER_EVENT, new DelegatingListener<ApplicationGen>(this, &ApplicationGen::timer1_TIMER_EVENT));
		timer1->addEventListener(Timer::TIMER_COMPLETE_EVENT, new DelegatingListener<ApplicationGen>(this, &ApplicationGen::timer1_TIMER_COMPLETE_EVENT));
		timerLedBlue->addEventListener(Timer::TIMER_EVENT, new DelegatingListener<ApplicationGen>(this, &ApplicationGen::timerLedBlue_TIMER_EVENT));
		timerDan->addEventListener(Timer::TIMER_COMPLETE_EVENT, new DelegatingListener<ApplicationGen>(this, &ApplicationGen::timerDan_TIMER_COMPLETE_EVENT));
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
