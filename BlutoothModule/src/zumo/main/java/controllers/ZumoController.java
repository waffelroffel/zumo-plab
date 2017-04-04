package zumo.main.java.controllers;

import zumo.main.java.application.PLabSerial;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.text.Text;

public class ZumoController {
	
	private PLabSerial serialConnection = new PLabSerial();
	
	@FXML
	private Text lastState;
	@FXML
	private Text lastMessageText;
	@FXML
	private Text secondLastMessageText;
	@FXML
	private Text thirdLastMessageText;
	@FXML
	private Text fourthLastMessageText;
	@FXML
	private Text fifthLastMessageText;
	@FXML
	private Button exitButton;

	
	
	@FXML
	void initialize() {
		serialConnection.closePort();
		serialConnection.openPLabPort();
		
		System.out.println(serialConnection.getOpenPortName());
		serialConnection.addListener(this, "messageRecieved");
	}
	
	public void messageRecieved(String message, int value) {
		lastMessageText.setText(message);
	}
	
	
	@FXML
	public void disconnect() {
		System.out.println("Port closed");
		serialConnection.closePort();
	}
	
	
	@FXML
	public void reconnect() {
		serialConnection.closePort();
		serialConnection.openPLabPort();
		
		System.out.println(serialConnection.getOpenPortName());
		serialConnection.addListener(this, "messageRecieved");
	}

}
