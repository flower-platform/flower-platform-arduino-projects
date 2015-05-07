#include <Arduino.h>
#include <DHTSensor.h>
#include <EthernetClient.h>
#include <FlowerPlatformArduinoRuntime.h>
#include <HardwareSerial.h>
#include <HttpServer.h>
#include <Input.h>
#include <LoggerSD.h>
#include <Output.h>
#include <pins_arduino.h>
#include <stdbool.h>
#include <string.h>
#include <Timer.h>
#include <UpdatesBuffer.h>
#include <WString.h>

class ApplicationGen {
protected:
	Input* doorSwitch;
	Input* lightSwitch;
	Output* doorRelay;
	Output* light;
	Output* pwmLed;
	DHTSensor* dhtSensor;
	HttpServer* httpServer;
	UpdatesBuffer* updatesBuffer;
	Timer* timer;
	LoggerSD<int>* logger;

	virtual void doorSwitch_ValueChanged_Handler(Event* event) {
		ValueChangedEvent* valueChangedEvent = (ValueChangedEvent*) event;

		if (valueChangedEvent->currentValue == LOW) {
			doorRelay->toggleHighLow();
		}

		updatesBuffer->updateEntry("doorSwitch", valueChangedEvent->currentValue);
	}

	virtual void lightSwitch_ValueChanged_Handler(Event* event) {
		ValueChangedEvent* valueChangedEvent = (ValueChangedEvent*) event;

		if (valueChangedEvent->currentValue == LOW) {
			light->toggleHighLow();
			int value = millis() % 256;
			pwmLed->setValue(value);
		}

		updatesBuffer->updateEntry("lightSwitch", valueChangedEvent->currentValue);
	}

	void doorRelay_ValueChanged_Handler(Event* event) {
		ValueChangedEvent* valueChangedEvent = (ValueChangedEvent*) event;
		updatesBuffer->updateEntry("doorRelay", valueChangedEvent->currentValue);
	}

	void light_ValueChanged_Handler(Event* event) {
		ValueChangedEvent* valueChangedEvent = (ValueChangedEvent*) event;
		updatesBuffer->updateEntry("light", valueChangedEvent->currentValue);
	}

	void dhtSensor_TemperatureChanged_Handler(Event* event) {
		ValueChangedEvent* valueChangedEvent = (ValueChangedEvent*) event;
//		Serial.print("Temperature changed from "); Serial.print(valueChangedEvent->previousValue); Serial.print(" to "); Serial.println(valueChangedEvent->currentValue);
		updatesBuffer->updateEntry("dhtSensor_temperature", valueChangedEvent->currentValue);
		logger->log(valueChangedEvent->currentValue);
	}

	void dhtSensor_HumidityChanged_Handler(Event* event) {
		ValueChangedEvent* valueChangedEvent = (ValueChangedEvent*) event;
//		Serial.print("Humidity changed from "); Serial.print(valueChangedEvent->previousValue); Serial.print(" to "); Serial.println(valueChangedEvent->currentValue);
		updatesBuffer->updateEntry("dhtSensor_humidity", valueChangedEvent->currentValue);
	}

	void myInput_ValueChanged_Handler(Event* event) {
		doorRelay->setHigh();
	}

	void httpServer_commandReceived_Handler(Event* event) {
		HttpCommandEvent* httpCommandEvent = (HttpCommandEvent*) event;

		if (strcmp(httpCommandEvent->command, "getUpdates") == 0) {
			httpCommandEvent->server->httpSuccess("application/json");
			updatesBuffer->printEntriesAsJson(httpCommandEvent->client);
		} else if (strcmp(httpCommandEvent->command, "lightOn") == 0) {
			light->setHigh();
			httpCommandEvent->server->httpSuccess("application/json");
			updatesBuffer->printEntriesAsJson(httpCommandEvent->client);
		} else if (strcmp(httpCommandEvent->command, "lightOff") == 0) {
			light->setLow();
			httpCommandEvent->server->httpSuccess("application/json");
			updatesBuffer->printEntriesAsJson(httpCommandEvent->client);
		} else if (strcmp(httpCommandEvent->command, "curtainUp") == 0) {
			doorRelay->setHigh();
			httpCommandEvent->server->httpSuccess("application/json");
			updatesBuffer->printEntriesAsJson(httpCommandEvent->client);
		} else if (strcmp(httpCommandEvent->command, "curtainDown") == 0) {
			doorRelay->setLow();
			httpCommandEvent->server->httpSuccess("application/json");
			updatesBuffer->printEntriesAsJson(httpCommandEvent->client);
		} else if (strcmp(httpCommandEvent->command, "") == 0) {
			httpCommandEvent->server->httpSuccess("text/html");
			httpCommandEvent->client->print(F("\
	<!DOCTYPE html> \n\
	<html> \n\
	<head> \n\
	<meta charset='ISO-8859-1'> \n\
	 \n\
	<script src='https://www.polymer-project.org/0.5/components/webcomponentsjs/webcomponents.js'></script> \n\
	 \n\
	<link rel='import' href='https://www.polymer-project.org/0.5/components/polymer/polymer.html'> \n\
	<link rel='import' href='https://www.polymer-project.org/0.5/components/paper-shadow/paper-shadow.html'> \n\
	<link rel='import' href='https://www.polymer-project.org/0.5/components/paper-menu-button/paper-menu-button.html'> \n\
	<link rel='import' href='https://www.polymer-project.org/0.5/components/paper-button/paper-button.html'> \n\
	<link rel='import' href='https://www.polymer-project.org/0.5/components/paper-icon-button/paper-icon-button.html'> \n\
	<link rel='import' href='https://www.polymer-project.org/0.5/components/core-icons/core-icons.html'> \n\
	<link rel='import' href='https://www.polymer-project.org/0.5/components/core-icons/image-icons.html'> \n\
	<link rel='import' href='https://www.polymer-project.org/0.5/components/paper-dropdown/paper-dropdown.html'> \n\
	<link rel='import' href='https://www.polymer-project.org/0.5/components/core-menu/core-menu.html'> \n\
	<link rel='import' href='https://www.polymer-project.org/0.5/components/paper-item/paper-item.html'> \n\
	<link rel='import' href='https://www.polymer-project.org/0.5/components/core-ajax/core-xhr.html'> \n\
	 \n\
	<link rel='stylesheet' href='http://localhost:10000/css/sky.css' shim-shadowdom> \n\
	<link rel='stylesheet' href='http://localhost:10000/css/style.css' shim-shadowdom> \n\
	 \n\
	<title>Demo Arduino</title> \n\
	</head> \n\
	<body> \n\
	 \n\
		<template is='auto-binding'> \n\
		 \n\
			<!--h1>Demo Arduino (Shmenu' lu' Batog edition)</h1--> \n\
			 \n\
			<div horizontal center-justified layout> \n\
			 \n\
				<paper-shadow class='panel' vertical layout> \n\
					 \n\
					<!-- Header --> \n\
					 \n\
					<div horizontal center layout class='toolbar'> \n\
						<paper-shadow flex horizontal center layout class='panel-header'> \n\
							<div flex></div> \n\
							<paper-menu-button> \n\
								<paper-icon-button icon='more-vert'></paper-icon-button> \n\
								<paper-dropdown class='dropdown' halign='right'> \n\
									<core-menu class='menu'> \n\
										<paper-item on-click='{{refresh}}'> \n\
											<core-icon icon='refresh'></core-icon> \n\
											Refresh \n\
										</paper-item> \n\
									</core-menu> \n\
								</paper-dropdown> \n\
							</paper-menu-button> \n\
						</paper-shadow> \n\
					</div> \n\
					 \n\
				 \n\
				 \n\
					<!-- Temperature & Humidity --> \n\
					 \n\
					<div horizontal center layout class='panel-content'> \n\
					 \n\
						<div flex vertical center layout> \n\
							<span class='label'>Temperature</span> \n\
							<span class='info'>{{data.dhtSensor_temperature}}&#176;C</span> \n\
						</div> \n\
						 \n\
						<div flex vertical center layout> \n\
							<span class='label'>Humidity</span> \n\
							<span class='info'>{{data.dhtSensor_humidity}}%</span> \n\
						</div> \n\
					 \n\
					</div> \n\
					 \n\
					<!-- Light --> \n\
			 \n\
					<div horizontal center layout class='panel-content'> \n\
						<paper-button flex raised light?='{{data.light}}' pseudo-disabled?='{{!data.light}}' on-click='{{switchLight}}'> \n\
							<core-icon icon='image:wb-incandescent'></core-icon> \n\
							Light \n\
						</paper-button> \n\
					</div> \n\
					 \n\
					<!-- Curtain --> \n\
					 \n\
					<div class='panel-content' id='curtain'> \n\
						<paper-shadow z='1' horizontal center layout> \n\
						 \n\
							<paper-button flex raised error?='{{!data.doorRelay}}' pseudo-disabled?='{{data.doorRelay}}' on-click='{{curtainDown}}'> \n\
								<core-icon icon='expand-more'></core-icon> \n\
							</paper-button> \n\
							 \n\
							<span>Curtain</span> \n\
							 \n\
							<paper-button flex raised success?='{{data.doorRelay}}' pseudo-disabled?='{{!data.doorRelay}}' on-click='{{curtainUp}}'> \n\
								<core-icon icon='expand-less'></core-icon> \n\
							</paper-button> \n\
						 \n\
						</paper-shadow> \n\
					</div> \n\
				</paper-shadow> \n\
			</div> \n\
			 \n\
			Last request @ <b><i>{{lastReq}}</i></b> \n\
			 \n\
			<core-xhr id='xhr'></core-xhr> \n\
		 \n\
		</template> \n\
		<script> \n\
		var url = './getUpdates'; \n\
		var params = {}; \n\
		var template = document.querySelector('template[is=\"auto-binding\"]'); \n\
		template.data = { \n\
			temperature: 0, \n\
			humidity: 0, \n\
			light: true, \n\
			up: true, \n\
			down: false \n\
		}; \n\
		 \n\
		template.switchLight = function() { \n\
			this.$.xhr.request({'url': this.data.light ? 'lightOff' : 'lightOn', 'callback': this.callback, 'method' : 'GET', 'responseType': 'json'} ); \n\
		}; \n\
		 \n\
		template.curtainDown = function() { \n\
			this.$.xhr.request({'url': 'curtainDown', 'callback': this.callback, 'method' : 'GET', 'responseType': 'json'} ); \n\
		}; \n\
		 \n\
		template.curtainUp = function() { \n\
			this.$.xhr.request({'url': 'curtainUp', 'callback': this.callback, 'method' : 'GET', 'responseType': 'json'} ); \n\
		}; \n\
		 \n\
		template.lastReq = 'never'; \n\
		template.response = {}; \n\
		template.callback = function(response) { \n\
			template.data = response; \n\
		} \n\
		template.refresh = function() { \n\
			this.$.xhr.request({'url': url, 'callback': this.callback, 'responseType': 'json'}); \n\
			this.lastReq = new Date().toLocaleString(); \n\
		} \n\
		 \n\
	    setInterval(function() { template.refresh() }, 1000); \n\
		</script> \n\
	 \n\
	</body> \n\
	</html> \n\
	"));
		}

	}

public:

	virtual ~ApplicationGen() { }

	virtual void setup() {

		doorSwitch = new Input();
		doorSwitch->pin = 2;
		doorSwitch->setup();

		lightSwitch = new Input();
		lightSwitch->pin = 3;
		lightSwitch->setup();

		dhtSensor = new DHTSensor();
		dhtSensor->pin = A0;
		dhtSensor->pollInterval = 1000;
		dhtSensor->setup();

		light = new Output(13);

		pwmLed = new Output(45);
		pwmLed->isPwm = true;

		doorRelay = new Output(6);

		httpServer = new HttpServer();
		httpServer->setup();

		updatesBuffer = new UpdatesBuffer(16);

		timer = new Timer(true);
		timer->delay = 1500;
		timer->repeatCount = 5;

		doorSwitch->valueChangedListener = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::doorSwitch_ValueChanged_Handler);

		lightSwitch->valueChangedListener = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::lightSwitch_ValueChanged_Handler);

		light->valueChangedListener = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::light_ValueChanged_Handler);

		doorRelay->valueChangedListener = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::doorRelay_ValueChanged_Handler);

		dhtSensor->temperatureChangedListener = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::dhtSensor_TemperatureChanged_Handler);
		dhtSensor->humidityChangedListener =  new DelegatingListener<ApplicationGen>(this, &ApplicationGen::dhtSensor_HumidityChanged_Handler);

		httpServer->commandReceivedListener = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_commandReceived_Handler);

		logger = new LoggerSD<int>(4, "temp.txt");
		logger->timeInterval = 3 * 1000;

	}

	virtual void loop() {
		doorSwitch->loop();
		lightSwitch->loop();
		dhtSensor->loop();
		httpServer->loop();
		timer->loop();
	}

};

class Application : public ApplicationGen {
public:

	void setup() {
		Serial.begin(9600);
		ApplicationGen::setup();
		timer->start();
	}


protected:

	virtual void doorSwitch_ValueChanged_Handler(ValueChangedEvent* event) {
		ApplicationGen::doorSwitch_ValueChanged_Handler(event);
//		Serial.println("event fired2");
	}

};

ApplicationGen* app = new Application();

void setup() {
	app->setup();
}

void loop() {
	app->loop();
}

