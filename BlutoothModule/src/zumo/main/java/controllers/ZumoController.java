package zumo.main.java.controllers;

import zumo.main.java.application.PLabSerial;
import java.util.Stack;

import javafx.fxml.FXML;
import javafx.scene.text.Text;

public class ZumoController {
	
	private PLabSerial serialConnection = new PLabSerial();
	private Stack<String> messages = new Stack<>();
	
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
	void initialize() {
		serialConnection.closePort();
		serialConnection.openPLabPort();
		
		System.out.println(serialConnection.getOpenPortName());
		serialConnection.addListener(this, "messageRecieved");
	}
	
	public void messageRecieved(String message, int value) {
		if (message.length() > 0) {
			messages.add(message);
		}
		
		update();
	}
	
	private void update() {
		try {
			lastMessageText.setText(messages.get(0));
		}
		catch (ArrayIndexOutOfBoundsException e) {
			lastMessageText.setText("");
		}

		
		try {
			secondLastMessageText.setText(messages.get(1));
		}	
		catch (ArrayIndexOutOfBoundsException e) {
			secondLastMessageText.setText("");
		}
		
		
		try {
			thirdLastMessageText.setText(messages.get(2));
		}	
		catch (ArrayIndexOutOfBoundsException e) {
			thirdLastMessageText.setText("");
		}
		
		
		try {
			fourthLastMessageText.setText(messages.get(3));
		}	
		catch (ArrayIndexOutOfBoundsException e) {
			fourthLastMessageText.setText("");
		}
		
		
		try {
			fifthLastMessageText.setText(messages.get(4));
		}	
		catch (ArrayIndexOutOfBoundsException e) {
			fifthLastMessageText.setText("");
		}
		
	}
	
	
	

}
