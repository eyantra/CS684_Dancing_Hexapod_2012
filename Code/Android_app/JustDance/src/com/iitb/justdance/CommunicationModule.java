package com.iitb.justdance;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.util.Log;

/**
 * Class for communication with Hexapod using Bluetooth
 * 
 * Provides functions for connecting, disconnecting, sending data
 * 
 * @author Manas, Ayesha
 * 
 */
public class CommunicationModule {

	/** Tag for Logcat Debug Messages */
	final String TAG = "BluetoothDebug";

	public BluetoothAdapter mBluetoothAdapter = null;

	/** Mac Address of Hexapod's bluetooth device */
	final String MAC_ADDRESS = "00:19:A4:02:C6:7E";
	BluetoothSocket mmSocket = null;

	/** Output stream for sending data to hexapod */
	private OutputStream mmOutputStream;
	private InputStream mmInputStream;

	/** Status of connection */
	public boolean connected = false;

	/**
	 * Class Constructor
	 * 
	 * @param adapter
	 *            Adapter of the android device
	 */
	public CommunicationModule(BluetoothAdapter adapter) {
		mBluetoothAdapter = adapter;
	}

	/**
	 * Finds the destination bluetooth device, creates a socket for
	 * communication, gets the output, input streams
	 * 
	 * @return true if successful
	 */
	public boolean connectToFirebird() {
		BluetoothDevice mmDevice = null;

		/**
		 * Checks if the destination device is in the list of paired Devices
		 */
		Set<BluetoothDevice> pairedDevices = mBluetoothAdapter
				.getBondedDevices();
		if (pairedDevices.size() > 0) {
			for (BluetoothDevice device : pairedDevices) {
				if (device.getName().equals("BlueLink")) {
					mmDevice = device;
					break;
				}
			}
		}
		/**
		 * If device is not found, search for the device
		 */
		if (mmDevice == null) {
			status("Not found in paired devices. Searching..");

			try {
				mmDevice = mBluetoothAdapter.getRemoteDevice(MAC_ADDRESS);
			} catch (IllegalArgumentException e) {
				status("Invalid address");
				return false;
			}
		} else {
			status("Device Found in paired devices.");
		}

		/**
		 * Create Socket for communication and obtain input, output streams
		 */
		try {
			/** Standard SerialPortService ID */
			UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb");
			mmSocket = mmDevice.createRfcommSocketToServiceRecord(uuid);
			mmSocket.connect();
			mmOutputStream = mmSocket.getOutputStream();
			mmInputStream = mmSocket.getInputStream();

		} catch (IOException e) {
			status("IO failed");
			return false;
		}

		connected = true;
		return true;
	}

	/**
	 * Checks if connection is successful. This function needs to be developed
	 * further to send test data to actually verify the connection
	 * 
	 * @return true if connected
	 */
	protected boolean checkConnection() {
		// TODO Auto-generated method stub

		return connected;
	}

	/**
	 * Send a string to Hexapod
	 * 
	 * @param string
	 *            message to be sent
	 * @return true if successful
	 */
	public boolean sendString(String string) {
		if (!connected)
			return false;
		try {
			mmOutputStream.write(string.getBytes());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			status("Sending failed.");
			return false;
		}
		return true;
	}

	/**
	 * Send a character to Hexapod
	 * 
	 * @param character
	 *            character to be sent
	 * @return true if successful
	 */
	public boolean sendChar(char character) {
		if (!connected)
			return false;
		try {
			mmOutputStream.write(character);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			status("Sending failed.");
			return false;
		}
		return true;
	}

	/**
	 * Disconnect from the hexapod
	 * @return true if successful
	 */
	public boolean disconnect() {
		try {
			mmSocket.close();
		} catch (IOException e) {
			e.printStackTrace();
			status("Disconnect failed");
			return false;
		}
		status("Disconnected");
		connected = false;
		return true;
	}

	// A functon for printing debug messages
	public void status(String message) {
		Log.d(TAG, message);
	}

}
