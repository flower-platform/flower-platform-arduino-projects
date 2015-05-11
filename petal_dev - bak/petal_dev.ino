#include <avr/pgmspace.h>
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
#include <Timer.h>
#include <WString.h>

class ApplicationGen {
protected:
	Input doorSwitch;
	Input lightSwitch;
	Output doorRelay;
	Output light;
	Output pwmLed;
	DHTSensor dhtSensor;
	HttpServer httpServer;
	Timer timer;
	LoggerSD<int> logger;

	void printStateAsJson(Print* print) {
		print->print(F("{"));

		lightSwitch.printStateAsJson(F("lightSwitch"), print);
		print->print(F(","));
		light.printStateAsJson(F("light"), print);
		print->print(F(","));
		dhtSensor.printStateAsJson(F("dhtSensor"), print);
		print->print(F(","));

		print->print(F("\"FREE_MEM\": "));
		print->print(freeRam());
		print->print(F("}"));
	}

	virtual void doorSwitch_ValueChanged_Handler(Event* event) {
		ValueChangedEvent* valueChangedEvent = (ValueChangedEvent*) event;

		if (valueChangedEvent->currentValue == LOW) {
			doorRelay.toggleHighLow();
		}
	}

	virtual void lightSwitch_ValueChanged_Handler(Event* event) {
		ValueChangedEvent* valueChangedEvent = (ValueChangedEvent*) event;

		if (valueChangedEvent->currentValue == LOW) {
			light.toggleHighLow();
			int value = millis() % 256;
			pwmLed.setValue(value);
		}
	}

	void dhtSensor_TemperatureChanged_Handler(Event* event) {
		ValueChangedEvent* valueChangedEvent = (ValueChangedEvent*) event;
//		Serial.print("Temperature changed from "); Serial.print(valueChangedEvent->previousValue); Serial.print(" to "); Serial.println(valueChangedEvent->currentValue);
		logger.log(valueChangedEvent->currentValue);
	}

	void myInput_ValueChanged_Handler(Event* event) {
		doorRelay.setHigh();
	}

	void httpServer_commandReceived_Handler(Event* event) {
		HttpCommandEvent* httpCommandEvent = (HttpCommandEvent*) event;

		if (strcmp_P(httpCommandEvent->command, PSTR("getUpdates")) == 0) {
			httpCommandEvent->server->httpSuccess();
			printStateAsJson(httpCommandEvent->client);
		} else if (strcmp_P(httpCommandEvent->command, PSTR("lightOn")) == 0) {
			light.setHigh();
			httpCommandEvent->server->httpSuccess();
			printStateAsJson(httpCommandEvent->client);
		} else if (strcmp_P(httpCommandEvent->command, PSTR("lightOff")) == 0) {
			light.setLow();
			httpCommandEvent->server->httpSuccess();
			printStateAsJson(httpCommandEvent->client);
		} else if (strcmp_P(httpCommandEvent->command, PSTR("curtainUp")) == 0) {
			doorRelay.setHigh();
			httpCommandEvent->server->httpSuccess();
			printStateAsJson(httpCommandEvent->client);
		} else if (strcmp_P(httpCommandEvent->command, PSTR("curtainDown")) == 0) {
			doorRelay.setLow();
			httpCommandEvent->server->httpSuccess();
			printStateAsJson(httpCommandEvent->client);
		} else if (strcmp_P(httpCommandEvent->command, "") == 0) {
			httpCommandEvent->server->httpSuccess(HttpServer::CONTENT_TYPE_HTML);
			httpCommandEvent->client->print(F("Please use local generated HTML file."));
		}
	}

public:

	virtual ~ApplicationGen() { }

	virtual void setup() {
		doorSwitch.pin = 2;
		doorSwitch.setup();

		lightSwitch.pin = 3;
		lightSwitch.setup();

		dhtSensor.pin = A0;
		dhtSensor.pollInterval = 1000;
		dhtSensor.setup();

		light.pin = 13;
		light.setup();

		pwmLed.pin = 45;
		pwmLed.isPwm = true;
		pwmLed.setup();

		doorRelay.pin = 6;
		doorRelay.setup();

		httpServer.setup();

		timer.autostart = true;
		timer.delay = 1500;
		timer.repeatCount = 5;
		timer.setup();

		doorSwitch.valueChangedListener = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::doorSwitch_ValueChanged_Handler);

		lightSwitch.valueChangedListener = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::lightSwitch_ValueChanged_Handler);

		dhtSensor.temperatureChangedListener = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::dhtSensor_TemperatureChanged_Handler);

		httpServer.commandReceivedListener = new DelegatingListener<ApplicationGen>(this, &ApplicationGen::httpServer_commandReceived_Handler);

		logger.slaveSelectPin = 4;
		logger.fileName = "temp.txt";
		logger.timeInterval = 3 * 1000;
		logger.setup();

	}

	virtual void loop() {
		doorSwitch.loop();
		lightSwitch.loop();
		dhtSensor.loop();
		httpServer.loop();
		timer.loop();
		logger.loop();
	}

};

class Application : public ApplicationGen {
public:

	void setup() {
		Serial.begin(9600);
		ApplicationGen::setup();
	}


protected:

	virtual void doorSwitch_ValueChanged_Handler(ValueChangedEvent* event) {
		ApplicationGen::doorSwitch_ValueChanged_Handler(event);
//		Serial.println("event fired2");
	}

};

Application app;

void setup() {
	app.setup();
}

void loop() {
	app.loop();
}

