This readme provides information about using the source code of Just Dance Android application 

Requirements:

Windows or Linux
Eclipse with ADT plugin
Android SDK with Android 2.3.3 platform tools


Usage:

1. Launch eclipse
2. Select Import from File menu.
3. Select Existing projects into workspace in General category
4. Click on browse button for selecting the root directory. Choose the directory of this readme.
5. Check both JustDance and SoundProcessing. Also check copy to workspace. Press Import.


Troubleshooting:

-- Project Dependency
		To resolve project dependency issue, select the Java build path under Just Dance project's properties.
	Under projects tab, check Sound Processing and move it to the top of the list.

-- Emulator issues
		Android emulator does not support bluetooth related capabilities.
	To test the code apart from bluetooth, comment the code at the end of OnCreate function which is responsible
	for enabling the bluetooth. Note that the application would still crash if Connect button is pressed.