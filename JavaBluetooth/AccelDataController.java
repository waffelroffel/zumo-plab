package zumo.main.java.controllers;

import zumo.main.java.application.PLabSerial;

public class AccelDataController {
	private PLabSerial serialConnection = new PLabSerial();

	void initialize() {
		serialConnection.closePort();
		serialConnection.openPLabPort();
		System.out.println(serialConnection.getOpenPortName());
		serialConnection.addListener(this, "messageRecieved");
	}

	public void messageRecieved(String message, int value) {
		System.out.println(message);
	}

}
