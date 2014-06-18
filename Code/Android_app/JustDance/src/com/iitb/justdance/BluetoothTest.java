package com.iitb.justdance;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Set;
import java.util.UUID;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class BluetoothTest extends Activity {

	final String TAG = "BluetoothDebug";

	TextView mStatusText;
	Button mConnect, mSend, mDisconnect;
	EditText mInputText;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_bluetooth_test);

		mStatusText = (TextView) findViewById(R.id.status);
		mInputText = (EditText) findViewById(R.id.characterToSend);

		mConnect = (Button) findViewById(R.id.connect);
		mConnect.setOnClickListener(connect);
		mSend = (Button) findViewById(R.id.send);
		mSend.setOnClickListener(send);
		mDisconnect = (Button) findViewById(R.id.disconnect);
		mDisconnect.setOnClickListener(disconnect);

		mSend.setEnabled(false);
		status("Not Connected");

		mBluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
		if (!mBluetoothAdapter.isEnabled()) {
			Intent enableBluetooth = new Intent(
					BluetoothAdapter.ACTION_REQUEST_ENABLE);
			startActivityForResult(enableBluetooth, 0);
		}
	}

	BluetoothAdapter mBluetoothAdapter = null;
	final String MAC_ADDRESS = "00:19:A4:02:C6:7E";
	BluetoothSocket mmSocket = null;
	private OutputStream mmOutputStream;
	private InputStream mmInputStream;

	private boolean connectToFirebird() {
		// TODO Auto-generated method stub

		BluetoothDevice mmDevice = null;

		Set<BluetoothDevice> pairedDevices = mBluetoothAdapter
				.getBondedDevices();
		if (pairedDevices.size() > 0) {
			for (BluetoothDevice device : pairedDevices) {
				if (device.getName().equals("BlueLink"))
				{
					mmDevice = device;
					break;
				}
			}
		}
		if (mmDevice == null) {
			status("Not found in paired devices. Searching..");

			try {
				mmDevice = mBluetoothAdapter.getRemoteDevice(MAC_ADDRESS);
			} catch (IllegalArgumentException e) {
				status("Invalid address");
				return false;
			}
		}
		else
		{
			status("Device Found in paired devices.");
		}
		
		try {
			UUID uuid = UUID.fromString("00001101-0000-1000-8000-00805f9b34fb"); // Standard
																					// SerialPortService
																					// ID
			mmSocket = mmDevice.createRfcommSocketToServiceRecord(uuid);
			mmSocket.connect();
			mmOutputStream = mmSocket.getOutputStream();
			mmInputStream = mmSocket.getInputStream();
			
		} catch (IOException e) {
			status("IO failed");
			return false;
		}
		return true;
	}

	protected boolean checkConnection() {
		// TODO Auto-generated method stub
		
		return true;
	}

	private boolean sendString(String string){
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
	
	private boolean disconnect()
	{
		try {
			mmSocket.close();
		} catch (IOException e) {
			e.printStackTrace();
			status("Disconnect failed");
			return false;
		}
		status("Disconnected");
		return true;
	}

	private OnClickListener connect = new OnClickListener() {

		@Override
		public void onClick(View v) {
			status("Connecting");
			if (connectToFirebird())
				status("Connection Successful");
			else {
				status("Connection Failed");
				return;
			}
			setEnableCommunicationControls(true);
			switchToPlayActivity();
		}
	};

	private OnClickListener send = new OnClickListener() {

		@Override
		public void onClick(View v) {
			if (!checkConnection()) {
				status("Not connected!");
				return;
			}

			if (sendString(mInputText.getText().toString()))
				status("Data sent: " + mInputText.getText() + "|" + mInputText.getText().toString().getBytes().length);
			else
				status("Sending failed");
		}

	};

	private OnClickListener disconnect = new OnClickListener() {
		
		@Override
		public void onClick(View v) {
			// TODO Auto-generated method stub
			if (disconnect())
				status("Disconnected successfully");
			else
				status("Disconnection failed");
		}
	};

	protected void setEnableCommunicationControls(boolean enable) {
		mSend.setEnabled(enable);
		mInputText.setEnabled(true);
	}

	protected void switchToPlayActivity() {
		Intent intent = new Intent(this, MainActivity.class);
//		intetn
		
	}

	protected void status(String string) {
		mStatusText.setText(string);
		Log.d(TAG, string);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.activity_bluetooth_test, menu);
		return true;
	}

}
