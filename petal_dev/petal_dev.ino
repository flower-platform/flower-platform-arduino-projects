#include <Arduino.h>
#include <DHTSensor.h>
#include <EthernetClient.h>
#include <FlowerPlatformArduinoRuntime.h>
#include <HardwareSerial.h>
#include <HttpServer.h>
#include <Input.h>
//#include <LoggerSD.h>
#include <Output.h>
#include <pins_arduino.h>
#include <stdbool.h>
#include <string.h>
#include <Timer.h>
#include <UpdatesBuffer.h>

#include <dht.h>
//#include <SD.h>
#include <Ethernet.h>
#include <SPI.h>

class ApplicationGen {
protected:
	Input doorSwitch;
	Input lightSwitch;
	Output doorRelay;
	Output light;
	Output pwmLed;
	DHTSensor dhtSensor;
	HttpServer httpServer;
	UpdatesBuffer updatesBuffer;
	Timer timer;
//	LoggerSD<int>* logger;

	virtual void doorSwitch_ValueChanged_Handler(Event* event) {
		ValueChangedEvent* valueChangedEvent = (ValueChangedEvent*) event;

		if (valueChangedEvent->currentValue == LOW) {
			doorRelay.toggleHighLow();
		}

		updatesBuffer.updateEntry("doorSwitch", valueChangedEvent->currentValue);
	}

	virtual void lightSwitch_ValueChanged_Handler(Event* event) {
		ValueChangedEvent* valueChangedEvent = (ValueChangedEvent*) event;

		if (valueChangedEvent->currentValue == LOW) {
			light.toggleHighLow();
			int value = millis() % 256;
			pwmLed.setValue(value);
		}

		updatesBuffer.updateEntry("lightSwitch", valueChangedEvent->currentValue);
	}

	void doorRelay_ValueChanged_Handler(Event* event) {
		ValueChangedEvent* valueChangedEvent = (ValueChangedEvent*) event;
		updatesBuffer.updateEntry("doorRelay", valueChangedEvent->currentValue);
	}

	void light_ValueChanged_Handler(Event* event) {
		ValueChangedEvent* valueChangedEvent = (ValueChangedEvent*) event;
		updatesBuffer.updateEntry("light", valueChangedEvent->currentValue);
	}

	void dhtSensor_TemperatureChanged_Handler(Event* event) {
		ValueChangedEvent* valueChangedEvent = (ValueChangedEvent*) event;
//		Serial.print("Temperature changed from "); Serial.print(valueChangedEvent->previousValue); Serial.print(" to "); Serial.println(valueChangedEvent->currentValue);
		updatesBuffer.updateEntry("dhtSensor_temperature", valueChangedEvent->currentValue);
//		logger->log(valueChangedEvent->currentValue);
	}

	void dhtSensor_HumidityChanged_Handler(Event* event) {
		ValueChangedEvent* valueChangedEvent = (ValueChangedEvent*) event;
//		Serial.print("Humidity changed from "); Serial.print(valueChangedEvent->previousValue); Serial.print(" to "); Serial.println(valueChangedEvent->currentValue);
		updatesBuffer.updateEntry("dhtSensor_humidity", valueChangedEvent->currentValue);
	}

	void myInput_ValueChanged_Handler(Event* event) {
		doorRelay.setHigh();
	}

	void httpServer_commandReceived_Handler(Event* event) {
		HttpCommandEvent* httpCommandEvent = (HttpCommandEvent*) event;

		if (strcmp(httpCommandEvent->command, "getUpdates") == 0) {
			httpCommandEvent->server->httpSuccess("application/json");
			updatesBuffer.printEntriesAsJson(httpCommandEvent->client);
		} else if (strcmp(httpCommandEvent->command, "lightOn") == 0) {
			light.setHigh();
			httpCommandEvent->server->httpSuccess("application/json");
			updatesBuffer.printEntriesAsJson(httpCommandEvent->client);
		} else if (strcmp(httpCommandEvent->command, "lightOff") == 0) {
			light.setLow();
			httpCommandEvent->server->httpSuccess("application/json");
			updatesBuffer.printEntriesAsJson(httpCommandEvent->client);
		} else if (strcmp(httpCommandEvent->command, "curtainUp") == 0) {
			doorRelay.setHigh();
			httpCommandEvent->server->httpSuccess("application/json");
			updatesBuffer.printEntriesAsJson(httpCommandEvent->client);
		} else if (strcmp(httpCommandEvent->command, "curtainDown") == 0) {
			doorRelay.setLow();
			httpCommandEvent->server->httpSuccess("application/json");
			updatesBuffer.printEntriesAsJson(httpCommandEvent->client);
		} else if (strcmp(httpCommandEvent->command, "") == 0) {
			httpCommandEvent->server->httpSuccess("text/html");
			httpCommandEvent->client->print(F("Please use the generated local HTML file"));
		}

	}

public:
	ApplicationGen() : doorRelay(10), light(10), pwmLed(10), updatesBuffer(10), timer(true) {}
	virtual ~ApplicationGen() { }

	virtual void setup() {

//		doorSwitch = new Input();
//		doorSwitch->pin = 2;
//		doorSwitch->setup();
//
//		lightSwitch = new Input();
//		lightSwitch->pin = 3;
//		lightSwitch->setup();
//
//		dhtSensor = new DHTSensor();
//		dhtSensor->pin = A0;
//		dhtSensor->pollInterval = 1000;
//		dhtSensor->setup();
//
//		light = new Output(13);
//
//		pwmLed = new Output(45);
//		pwmLed->isPwm = true;
//
//		doorRelay = new Output(6);
//
//		httpServer = new HttpServer();
//		httpServer->setup();
//
//		updatesBuffer = new UpdatesBuffer(16);
//
//		timer = new Timer(true);
//		timer->delay = 1500;
//		timer->repeatCount = 5;
//
//		doorSwitch->valueChangedListener = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::doorSwitch_ValueChanged_Handler);
//
//		lightSwitch->valueChangedListener = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::lightSwitch_ValueChanged_Handler);
//
//		light->valueChangedListener = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::light_ValueChanged_Handler);
//
//		doorRelay->valueChangedListener = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::doorRelay_ValueChanged_Handler);
//
//		dhtSensor->temperatureChangedListener = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::dhtSensor_TemperatureChanged_Handler);
//		dhtSensor->humidityChangedListener =  new DelegatingListener<ApplicationGen>(this, &ApplicationGen::dhtSensor_HumidityChanged_Handler);
//
//		httpServer->commandReceivedListener = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_commandReceived_Handler);

//		logger = new LoggerSD<int>(4, "temp.txt");
//		logger->timeInterval = 3 * 1000;

	}

	virtual void loop() {
		doorSwitch.loop();
		lightSwitch.loop();
		dhtSensor.loop();
		httpServer.loop();
		timer.loop();
	}

};

class Application : public ApplicationGen {
public:

	void setup() {
		Serial.begin(9600);
		ApplicationGen::setup();
		timer.start();
	}


protected:

	virtual void doorSwitch_ValueChanged_Handler(ValueChangedEvent* event) {
		ApplicationGen::doorSwitch_ValueChanged_Handler(event);
//		Serial.println("event fired2");
	}

};

ApplicationGen app;

void setup() {
	app.setup();
}

void loop() {
	app.loop();
}

