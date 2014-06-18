package com.iitb.justdance;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.media.AudioTrack.OnPlaybackPositionUpdateListener;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.webkit.MimeTypeMap;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.ToggleButton;

import com.iitb.beatdetector.BeatDetector;
import com.musicg.wave.Wave;

/**
 * Starting activity for JustDance
 * 
 * @author Manas
 * 
 */
public class MainActivity extends Activity {

	final int ACTIVITY_CHOOSE_FILE = 1;

	final boolean USE_BUFFERING = false;

	/**
	 * Stack for storing the beat locations on which hexapod is to be signalled
	 * to perform step
	 */
	private Stack<Integer> beats = new Stack<Integer>();

	/**
	 * BeatDetector object for the currently selected input song
	 */
	private BeatDetector beatDetector;

	/**
	 * Wave object for the currently selected input song
	 */
	private Wave wave;

	AudioTrack track = null;
	final String TAG = "DebugData";

	/** Objects for UI elements */

	TextView mStatusText;
	ToggleButton mBeatToggleButton;
	Button mChooseFileButton;
	TextView mInputFileText;
	Button mPlayPauseButton, mStartButton;
	Button mConnect, mDisconnect;
	Spinner mSpinnerMoveChooser, mSpinnerFileChooser;

	/** Directory where the dance tracks are stored */
	String songDir = Environment.getExternalStorageDirectory().getPath()
			+ "/HexapodTracks/";

	boolean connected = false;

	/** CommunicationModule object used for communicating with Hexapod */
	CommunicationModule comm;

	/** list of all dance moves */
	DanceMove danceMoves[];

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		/**
		 * Populate UI objects and set adapters for spinners
		 */

		mBeatToggleButton = (ToggleButton) findViewById(R.id.beatDisplayToggleButton);
		mChooseFileButton = (Button) findViewById(R.id.chooseFileButton);
		mChooseFileButton.setOnClickListener(chooseFile);
		mInputFileText = (TextView) findViewById(R.id.InputFileText);
		mPlayPauseButton = (Button) findViewById(R.id.playPauseButton);
		mPlayPauseButton.setOnClickListener(PlayPause);

		mStartButton = (Button) findViewById(R.id.startButton);
		mStartButton.setOnClickListener(Start);
		mStatusText = (TextView) findViewById(R.id.status);

		mConnect = (Button) findViewById(R.id.connect);
		mConnect.setOnClickListener(connect);
		mDisconnect = (Button) findViewById(R.id.disconnect);
		mDisconnect.setOnClickListener(disconnect);
		mDisconnect.setEnabled(false);

		mSpinnerMoveChooser = (Spinner) findViewById(R.id.moveChooser);
		ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(
				this, R.array.moves, android.R.layout.simple_spinner_item);
		adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

		mSpinnerMoveChooser.setAdapter(adapter);

		File songsDir = new File(songDir);

		boolean result = false;
		result = songsDir.mkdirs();

		if (songsDir.isDirectory() || result == true) {
			List<String> songList = new ArrayList<String>();
			mSpinnerFileChooser = (Spinner) findViewById(R.id.fileChooser);
			for (File file : songsDir.listFiles()) {
				if (file.getName().endsWith(".wav"))
					songList.add(file.getName());
			}
			if (songList.size() > 0) {
				ArrayAdapter<String> adapterFiles = new ArrayAdapter<String>(
						this, android.R.layout.simple_spinner_item, songList);
				adapterFiles
						.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
				mSpinnerFileChooser.setAdapter(adapterFiles);
				mSpinnerFileChooser.setOnItemSelectedListener(FileSelected);
			} else
				switchToManualFileMode();
		} else {
			switchToManualFileMode();
		}

		/**
		 * populate list of dance moves
		 */
		danceMoves = DanceMove.generateMoves();

		SetPlaybackButtonsEnable(false);

		/**
		 * Check if bluetooth is enabled. Try to enable if it is not.
		 */
		comm = new CommunicationModule(BluetoothAdapter.getDefaultAdapter());
		if (!comm.mBluetoothAdapter.isEnabled()) {
			Intent enableBluetooth = new Intent(
					BluetoothAdapter.ACTION_REQUEST_ENABLE);
			startActivityForResult(enableBluetooth, 0);
		}

	}

	/**
	 * Event Handler for handling Dance Track selection
	 */
	private OnItemSelectedListener FileSelected = new OnItemSelectedListener() {

		@Override
		public void onItemSelected(AdapterView<?> adapterView, View view,
				int i, long l) {
			// status((String)mSpinnerFileChooser.getSelectedItem());
			initialize(songDir + (String) mSpinnerFileChooser.getSelectedItem());
		}

		@Override
		public void onNothingSelected(AdapterView<?> arg0) {
			// TODO Auto-generated method stub

		}
	};

	/**
	 * show interface for choosing file manually
	 */
	private void switchToManualFileMode() {
		status("No tracks found. Choose manually");
		mChooseFileButton.setVisibility(View.VISIBLE);
		mSpinnerFileChooser.setVisibility(View.GONE);
	}

	/**
	 * Enable or disable audio playback buttons
	 * 
	 * @param enable
	 *            enable for the UI controls
	 */
	private void SetPlaybackButtonsEnable(boolean enable) {
		mPlayPauseButton.setEnabled(enable);
		mStartButton.setEnabled(enable);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}

	/**
	 * Event Handler for connecting to hexapod
	 */
	private OnClickListener connect = new OnClickListener() {

		@Override
		public void onClick(View v) {
			if (comm.connectToFirebird()) {
				status("Connected");
				connected = true;

				mConnect.setEnabled(false);
				mDisconnect.setEnabled(true);
			} else {
				status("Connection Failed");
			}
		}
	};

	/**
	 * Event Handler for disconnecting from the hexapod
	 */
	private OnClickListener disconnect = new OnClickListener() {

		@Override
		public void onClick(View v) {
			comm.disconnect();

			mConnect.setEnabled(true);
			mDisconnect.setEnabled(false);
			status("Disconnected");
		}
	};

	/**
	 * Event Handler for choosing file manually
	 */
	private OnClickListener chooseFile = new OnClickListener() {

		@Override
		public void onClick(View v) {
			// Open chosen file dialog.

			// if successful, enable play/pause, restart buttons.
			Intent chooseFile;
			Intent intent;
			chooseFile = new Intent(Intent.ACTION_GET_CONTENT);
			chooseFile.setType("file/*");
			// String type =
			// MimeTypeMap.getSingleton().getMimeTypeFromExtension("wav");
			// chooseFile.setType(type);

			intent = Intent.createChooser(chooseFile, "Choose a wav file");
			startActivityForResult(intent, ACTIVITY_CHOOSE_FILE);
		}
	};

	/**
	 * Event Handler for playing/pausing audio playback
	 */
	private OnClickListener PlayPause = new OnClickListener() {

		@Override
		public void onClick(View v) {
			if (track.getPlayState() == AudioTrack.PLAYSTATE_PLAYING)
				track.pause();
			else {
				track.play();
			}
		}
	};

	/**
	 * Event Handler for initializing communication, scheduling dance steps and
	 * starting Audio Playback
	 */
	private OnClickListener Start = new OnClickListener() {

		@Override
		public void onClick(View v) {
			// track.flush();
			// resetTrack();

			/** Schedule dance moves */
			int arg_int = updateBeatStackForDanceMove();
			char argumentToSend = (char) arg_int;
			status("Selected Step Duration: " + arg_int);
			/**
			 * Send dance move id and argument if required to Hexapod
			 */
			if (connected) {
				comm.sendChar(Scheduler.currentDanceMove.getMoveId());
				if (argumentToSend != 0)
					comm.sendChar(argumentToSend);
			}

			/** Set marker for first beat location */
			setInitialMarker();
			if (track.getPlayState() == AudioTrack.PLAYSTATE_PLAYING)
				track.pause();
			track.setPlaybackHeadPosition(1);

			track.play();
		}
	};

	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		switch (requestCode) {
		case ACTIVITY_CHOOSE_FILE:
			if (resultCode != RESULT_OK)
				Toast.makeText(getApplicationContext(),
						"Please choose the file again", Toast.LENGTH_SHORT)
						.show();
			else {
				String path = data.getData().getPath();
				if (!MimeTypeMap.getFileExtensionFromUrl(path).toLowerCase()
						.contentEquals("wav")) {
					Toast.makeText(getApplicationContext(),
							"Only wav file supported", Toast.LENGTH_LONG)
							.show();
					return;
				}
				mInputFileText.setText(path);

				try {
					@SuppressWarnings({ "unused", "resource" })
					InputStream is = new FileInputStream(path);
				} catch (FileNotFoundException e2) {
					e2.printStackTrace();
					Toast.makeText(getApplicationContext(), "File Not Found!",
							Toast.LENGTH_SHORT).show();
					return;
				}

				initialize(path);
			}
		}

	}

	private void initialize(String path) {
		createAudioTrack(path);
		detectBeats();
		SetPlaybackButtonsEnable(true);
	}

	protected void resetTrack() {
		track = new AudioTrack(AudioManager.STREAM_MUSIC, wave.getWaveHeader()
				.getSampleRate(), AudioFormat.CHANNEL_CONFIGURATION_DEFAULT,
				AudioFormat.ENCODING_PCM_16BIT, (int) (wave.getWaveHeader()
						.getChunkSize() / 2), AudioTrack.MODE_STATIC); // Change
																		// mode
																		// to
																		// stream
																		// if
																		// dynamic
																		// data

		writeAudioToTrack(track, beatDetector);
	}

	/**
	 * extracts audio data from the path specified and creates Audio Track
	 * object with the audio data for playback
	 * 
	 * @param path
	 *            absolute path of the audio file
	 */
	private void createAudioTrack(String path) {
		// create a wave object
		wave = new Wave(path);

		Log.i("debug", wave.getWaveHeader().toString());

		// create BeatDetector object for the Wave
		beatDetector = new BeatDetector(wave);

		Log.i("debug", "No of samples: " + beatDetector.getNumOfSamples());

		/** Clear the current AudioTrack object if not null */
		if (track != null) {
			track.pause();
			track.flush();
			track.release();
		}

		/** Choose static or streaming object */

		if (!USE_BUFFERING) {
			track = new AudioTrack(
					AudioManager.STREAM_MUSIC,
					wave.getWaveHeader().getSampleRate(),
					wave.getWaveHeader().getChannels() == 1 ? AudioFormat.CHANNEL_CONFIGURATION_MONO
							: AudioFormat.CHANNEL_CONFIGURATION_STEREO,
					AudioFormat.ENCODING_PCM_16BIT, (int) (wave.size()),
					AudioTrack.MODE_STATIC);
			writeAudioToTrack(track, beatDetector);
		} else {
			track = new AudioTrack(AudioManager.STREAM_MUSIC, wave
					.getWaveHeader().getSampleRate(),
					AudioFormat.CHANNEL_CONFIGURATION_DEFAULT,
					AudioFormat.ENCODING_PCM_16BIT, (int) (wave.getWaveHeader()
							.getChunkSize() / 2), AudioTrack.MODE_STREAM); // Change
																			// mode
																			// to
																			// stream
																			// if
																			// dynamic
																			// data
			writeBufferToTrack();
			writeBufferToTrack();
			track.setPositionNotificationPeriod(BUFFER_LENGTH);
		}

	}

	/**
	 * writes audio data contained in beatDetector into audioTrack
	 * 
	 * @param track2
	 *            AudioTrack object in which data is to be written
	 * @param beatDetector2
	 *            BeatDetector object containing audio data
	 */
	private void writeAudioToTrack(AudioTrack track2, BeatDetector beatDetector2) {
		short[] audioData = beatDetector2.getAmplitudes();
		track2.write(audioData, 0, audioData.length);
	}

	final int BUFFER_LENGTH = 441000;
	int writeEnd = 0;

	/** Writes next buffer to the audio track */
	private void writeBufferToTrack() {
		track.write(beatDetector.getAmplitudes(), writeEnd, BUFFER_LENGTH);
		writeEnd += BUFFER_LENGTH;
		Log.d(TAG, "Write head: " + writeEnd);
	}

	/**
	 * Detects beats in the selected song
	 */
	private void detectBeats() {
		beatDetector.findEnergyMaximas();
		beatDetector.findTempo();
		// beatDetector.printThresholdedChunkEnergies("");
		track.setPlaybackPositionUpdateListener(PositionReached);
	}

	/**
	 * schedules the steps on the beats detected in the songs
	 * 
	 * @return argument to be sent to Hexapod if any
	 */
	private int updateBeatStackForDanceMove() {
		int moveIndex = mSpinnerMoveChooser.getSelectedItemPosition();
		return Scheduler.scheduleSteps(beats, danceMoves[moveIndex],
				beatDetector);
	}

	private void setInitialMarker() {
		int frame = beats.pop();
		track.setNotificationMarkerPosition(frame);
		status("Marker Set");
	}

	/**
	 * Event Handler when the audio playback reaches a location on which step is to be performed
	 * Sends the necessary message to Hexapod to signal next step
	 */
	private OnPlaybackPositionUpdateListener PositionReached = new OnPlaybackPositionUpdateListener() {
		@Override
		public void onPeriodicNotification(AudioTrack track) {
			writeBufferToTrack();
		}

		@Override
		public void onMarkerReached(AudioTrack track) {
			notifyBeat();
			/**
			 * Send signal to hexapod
			 * Set marker for next beat if available, else stop
			 */
			if (!beats.isEmpty()) {
				int frame = beats.pop();
				if (track.setNotificationMarkerPosition(frame) != AudioTrack.SUCCESS)
					status("Marker setting failed.");
				status("Beat# :" + beats.size() + " | next:" + frame
						+ " |current head: " + track.getPlaybackHeadPosition());

			} else {
				Toast.makeText(getApplicationContext(), "Finished",
						Toast.LENGTH_SHORT).show();

				track.pause();
				// track.stop();
				// track.flush();
				// track.release();
				if (connected)
					sendResetCommand();
				status("Finished");
			}
		}

	};

	/**
	 * Displays beat indication on UI
	 * Sends signal to hexapod if connected
	 */
	private void notifyBeat() {
		mBeatToggleButton.toggle();
		if (connected)
			comm.sendChar('y');
	}
	
	/**
	 * Sends reset command to Hexapod
	 */
	protected void sendResetCommand() {
		if (Scheduler.currentDanceMove.getMoveId() != 'f')
			comm.sendChar('z');
	}

	public void testBluetooth(View view) {
		Intent intent = new Intent(this, BluetoothTest.class);
		startActivity(intent);
	}

	/**
	 * A function to display/log Debug messages
	 * @param string message to display/log
	 */
	protected void status(String string) {
		mStatusText.setText(string);
		Log.d(TAG, string);
	}
}
