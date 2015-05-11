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

class ApplicationGen {
protected:
	Input* input2;
	Output* output5;
	UpdatesBuffer* updatesBuffer;

	virtual void input2_false(Event* event) {
		onValueChanged(ValueChangedEvent)* castedEvent = (onValueChanged(ValueChangedEvent)*) event;
		{
			output5->toggleHighLow();
		}
		{
			const char* key = "input2";
			int value = castedEvent->currentValue;
			updatesBuffer->updateEntry(key, value);
		}
	}

public:
	virtual ~ApplicationGen() { }

	virtual void setup() {
		input2 = new Input();
		input2->pin = 2;
		
		output5 = new Output(5);
		
		updatesBuffer = new UpdatesBuffer(16);
		
	}
	
	virtual void loop() {
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