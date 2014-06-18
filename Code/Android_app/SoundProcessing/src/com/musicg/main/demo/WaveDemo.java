/*
 * Copyright (C) 2012 Jacquet Wong
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.musicg.main.demo;

import com.iitb.beatdetector.BeatDetector;
import com.musicg.wave.Wave;
import com.musicg.wave.WaveFileManager;

public class WaveDemo {

	public static void main(String[] args) {

		String filename = "HexapodTracks/simple_long.wav";
		String outFolder="out";
		
		// create a wave object
		Wave wave = new Wave(filename);
		BeatDetector beatDetector = new BeatDetector(wave);
		// print the wave header and info
		System.out.println(wave);
		System.out.println("read wavfile");
		beatDetector.findEnergyMaximas();
		beatDetector.findTempo();
		//System.out.println("here");
		int period = beatDetector.getNumOfBeatsInPeriod();
		System.out.println("period:"+period);
		int start_location = beatDetector.getStartChunkLocation();
		System.out.println("start_chunk:"+start_location);
		
		int start_location_samples = beatDetector.getStartSampleLocation();
		System.out.println("start_sample:"+start_location_samples);
		
		System.out.println("period in chunks :"+beatDetector.getPeriodInChunks());
		System.out.println("period in samples :"+beatDetector.getPeriodInSamples());
		beatDetector.printAmplitudes("energies.txt");
		beatDetector.printChunkEnergies("chunk energies");
		beatDetector.printThresholdedChunkEnergies("thresh");
		beatDetector.printThinnedChunkEnergies("thinned");
		
		// trim the wav
		//wave.leftTrim(1);
		//wave.rightTrim(0.5F);

		// save the trimmed wav
		WaveFileManager waveFileManager=new WaveFileManager(wave);
		//waveFileManager.saveWaveAsFile(outFolder+"/out.wav");
	}
}