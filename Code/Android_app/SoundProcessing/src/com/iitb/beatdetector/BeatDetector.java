/*!
 * \class BeatDetector The class useful for beat and tempo detection.
 * 
 * Our main aim is performing beat detection and period/tempo detection compatible with Android OS.
 * The entire code has been implemented in JAVA with minimal external library requirements.
 * The computations performed are also very less demanding and are supposed to be pseudo-real time ,
 * so that the beat detection on the song is performed in quite a less time. <br>
 * 
 * The algorithm is given below: <br>
 * <ol>
 * <li> finding average chunk energies</li>
 * <li> thresholding the chunk energies </li>                                   
 * <li> performing thinning to obtain the beat locations</li>
 * </ol>
 * 
 * The only external construct it uses if Wave class from the Musicg library.
 * 
 * 
 */



package com.iitb.beatdetector;

import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

import com.musicg.wave.Wave;
import com.musicg.wave.WaveHeader;

public class BeatDetector {
	/// total number of samples in the song 
	private int numOfSamples;
	
	/// the array of amplitudes for every sample
	private short[] amplitudes;
	
	/// the array containing the avg energy in a chunk of samples 
	private double[] chunkEnergyArray;
	
	///the array obtained after thresholding the chunk energies
	private double[] thresholdedChunkEnergy;
	
	///the array obtained after performing thinning on the thresholded array 
	private short[] thinnedChunkEnergy;
	
	///the array holds the location corresponding to the beats ( start of a beat)
	private int[] beatChunkLocations;
	
	/// number of total beats detected in the song
	private int numOfBeats;
	
	/// number of beats in a period ( period represents the repetition period of the song)
	private int numOfBeatsInPeriod;
	
	/// the sampling rate of the song.
	private int samplingRate;
	
	/// the total number of chunks in the song.
	private int numOfChunks;
	
	///size of a chunk : represents the number of samples in a chunk.
	private int sizeOfChunk;
	
	/// the maximum frequency of beats possible in a song. ( eg: 10 beats per sec. at max)
	private int maxBeatFreq;
	
	///the chunk index which corresponds to the first beat, also the start of the first period.
	private int startChunkLocation;
	
	/// the period/tempo of the song as the number of chunks
	private int periodInChunks;
	
	/// the period in terms of number of samples.
	private int periodInSamples;
	

	/*
	 * The default Constructor
	 * Just initialises a few data members.
	 */
	public BeatDetector() {
		numOfSamples = 0;
		amplitudes = new short[numOfSamples];
		numOfBeats = 0;
	}

	
	/*! Constructor
	 * 
	 * The constructor takes in input  Wave class object and initialises the data members
	 * \param wave A Wave type object
	 * 
	 */
	public BeatDetector(Wave wave) {
		amplitudes = wave.getSampleAmplitudes();
		byte[] bytes = wave.getBytes();
		WaveHeader wave_header = wave.getWaveHeader();
		samplingRate = wave_header.getSampleRate();
		int bytePerSample = wave_header.getBitsPerSample() / 8;
		numOfSamples = (int) bytes.length / bytePerSample;
		numOfBeats = 0;
	}
   
	
	/*! find the enrgy maximas in the spectrum. That is the beat locations in the spectrum,
	 * 
	 * The high-level function calls other member functions of the class
	 * to find the beat locations. It performs operations like:
	 * <ol>
	 * <li> finding average chunk energies</li>
	 * <li> thresholding the chunk energies </li> 
	 * <li> performing thinning to obtain the beat locations</li>
	 * </ol>
	 */
	public void findEnergyMaximas() {
		setSizeOfChunk();
		setNumOfChunks();
		initialiseChunkEnergyArray();
		setChunkEnergyArray();
		thresholdChunkEnergies();
		thinThresholdedChunkEnergies();
	}

	/*! prints the amplitude per sample to a file
	 * 
	 * The function is useful for debugging purpose, and writes the amplitudes 
	 * for every sample to a file
	 * \param fileName the name of the file to whihc the data is to be written
	 * 
	 */
	public void printAmplitudes(String fileName) {

		try {
			FileWriter fw = new FileWriter(fileName);
			PrintWriter pw = new PrintWriter(fw);
			for (int i = 0; i < numOfSamples; i++) {
				pw.println(amplitudes[i]);
			}
			pw.close();
			fw.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	
	
	/*! sets the number of chunks in the song 
	 * 
	 * sets the number of chunks in the song base don the chunk size
	 */
	public void setNumOfChunks() {
		numOfChunks = (int) numOfSamples / sizeOfChunk;
		//System.out.println("set num of chunks:"+numOfChunks);
	}

	
	/*! sets the size of the chunk ( to perform averaging)
	 * 
	 * the size of the chunk is 200 samples for a sampling rate of 44100.
	 * this corresponds to 5ms in the time domain. For other sampling rates,
	 * The chunk size if appropriately scaled to represent 5 ms window.
	 */
	public void setSizeOfChunk() {
		
		double temp = (double) (200 * samplingRate / 44100);
		//System.out.println("sampling rate:"+samplingRate);
		//System.out.println("temp:"+temp);
		sizeOfChunk = (int) temp;
		//System.out.println("set size of chunks:"+sizeOfChunk);
	}

	
	/*! creates and initialises the array holding the average chunk energies
	 * 
	 */
	public void initialiseChunkEnergyArray() {
		chunkEnergyArray = new double[numOfChunks];
	}

	
	
	/*! fills up the chunk energy array
	 * 
	 * Finds the average energy of consecutive sizeOfChunk samples and
	 * fills it as the corresponding average chunk energy in the array, 
	 */
	public void setChunkEnergyArray() {
		double temp_sum = 0;
		double temp = 0;
		for (int i = 0; i < numOfChunks; i++) {
			temp_sum = 0;

			for (int j = 0; j < sizeOfChunk; j++) {
				temp = amplitudes[i * sizeOfChunk + j];
				temp_sum = temp_sum + temp * temp;
			}
			temp_sum = (double) temp_sum / sizeOfChunk;
			chunkEnergyArray[i] = temp_sum / 30000;
		}
	}

	
	
	/*! prints the avg chunk energies per chunk to a file
	 * 
	 * The function is useful for debugging purpose, and writes the avg chunk energy 
	 * for every chunk to a file
	 * \param fileName the name of the file to whihc the data is to be written
	 * 
	 */
	public void printChunkEnergies(String fileName) {
		try {
			//System.out.println("no of chunks : " + numOfChunks);
			FileWriter fw = new FileWriter(fileName);
			PrintWriter pw = new PrintWriter(fw);
			for (int i = 0; i < numOfChunks; i++) {
				pw.println(chunkEnergyArray[i]);
			}

			pw.close();
			fw.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	/*! perform thresholding on the avg chunk energy array to find probable beat locations
	 * 
	 * We normally classify a beat as a sudden enrgy maxima in the energy-time plot of the song
	 * Note that this is a very simple representation of a beat and may fail when vocals are present.
	 * But for now we assume we are dealing with songs involving simple drum/ percussion instrument strikes
	 * So, we can safely assume that beat represent energy maximas.
	 * To find the probably beat location, we threshold the average chunk energy array with a threshold <br> 
	 * threshold = maximum_chunk_energy/thresholdFactor. where thresholdFactor can be varied.
	 * We consider thresholdFactor = 4.
	 * 
	 * \return void 
	 */
	public void thresholdChunkEnergies() {
		double max_energy = 0;
		for (int k = 0; k < numOfChunks; k++) {
			if (chunkEnergyArray[k] > max_energy )
				max_energy = chunkEnergyArray[k];
		}
		int thresholdFactor = 4; 
		// the factor with which we threshold corresponding to the the maximum energy 
		thresholdedChunkEnergy = new double[numOfChunks];
		for (int j = 0; j < numOfChunks; j++) {
			if (chunkEnergyArray[j] > max_energy/thresholdFactor)
				thresholdedChunkEnergy[j] = (double) chunkEnergyArray[j]/ max_energy;
		}

	}

	/*! prints the thresholded chunk energies per chunk to a file
	 * 
	 * The function is useful for debugging purpose, and writes the thresholded chunk energy 
	 * for every chunk to a file
	 * \param fileName the name of the file to which the data is to be written
	 * 
	 */
	public void printThresholdedChunkEnergies(String fileName) {
		try {
			//System.out.println("num of chunks: " + numOfChunks);
			FileWriter fw = new FileWriter(fileName);
			PrintWriter pw = new PrintWriter(fw);
			for (int i = 0; i < numOfChunks; i++) {
				pw.println(thresholdedChunkEnergy[i]);
			}

			pw.close();
			fw.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	
	/*! perform thinning on the thresholded chunk energy array.
	 * 
	 * Once we have thresholded the chunk energy array, we have removed the spurius energy peaks,
	 * As it happens, for a single beat, there are multiple chunks which result in average energies 
	 * higher than the threshold. In such case, we need to consider consecutive, or nearby peaks 
	 * as a single beat.For this we employ the factor maxBeatFreq, which represents 
	 * the maximum number of beats which can occur in a second. So, in a way it represents 
	 * the minimum number of chunks which should be present between consecutive beat locations.
	 * We use this information to perform thinning. The algorithm is described below: <br>
	 * <ol>
	 * <li>Detect the sample which has a non-zero value in the thresholded chunk energy array</li>
	 * <li>Tag the chunk as the first beat location</li>
	 * <li>Check for the next beat only after the number of samples corresp to maxBeatFreq</li>
	 * <li>Go to step 1 and continue until you have found all the beats.</li>
	 */
	public void thinThresholdedChunkEnergies() {
		maxBeatFreq = 10; // i.e there can be at max 10 beats in a seconds.
		thinnedChunkEnergy = new short[numOfChunks];
		int num_samples_min_beat = samplingRate / maxBeatFreq;
		int num_chunks_min_beat = num_samples_min_beat / sizeOfChunk;
//		System.out.println("the num of chunks min beat :" + num_chunks_min_beat);
		int current_beat_index = -1;
		for (int j = 0; j < numOfChunks; j++) {
			if (j > current_beat_index) {
				if (thresholdedChunkEnergy[j] > 0) {
					thinnedChunkEnergy[j] = 1;
					current_beat_index = j;
					current_beat_index = current_beat_index + num_chunks_min_beat;
//					System.out.println("a :" + current_beat_index);
//					System.out.println("k : " + j);
				}
			}
		}
	}
	
	
	/*! finds the number of beats in the song by counting non-zero values in the thinned chunk energy array
	 * 
	 */
	public void findNumberOfBeats(){
		for(int i = 0 ; i < numOfChunks; i++){
			if(thinnedChunkEnergy[i] == 1){
				numOfBeats = numOfBeats + 1;
			}
		}
		//System.out.println("num of beats:"+numOfBeats);
	}
	
	
	/*! creates and initialises the array which holds the chunk location of the beats.
	 *
	 */
	public void initialiseBeatChunkLocations(){
		beatChunkLocations = new int[numOfBeats];
	}

	/*! finds the location of beats and fills up the beatChunkLocation array 
	  * 
	  * The beats correspond to non-zero values in the thinnedChunkEnergy array. 
	  */
	public void findBeatChunkLocations(){
		int count = 0;
		for(int i = 0 ; i < numOfChunks; i++){
			if(thinnedChunkEnergy[i] == 1){
				beatChunkLocations[count] = i;
				count = count + 1;
			}
		}
	}
	
	
	
	/*! Finds the period of the song in terms of the number of beats in a period
	 * 
	 * Note that our aims of beatDetection were: finding the beat locations 
	 * and also finding the tempo of the song. We have already obtained the beatLocations.
	 * Now we need to find the tempo of the song.
	 * The algorithm which we use is autocorrelation of the beat location array, the location of minima
	 * under a threshold gives the period. The algorithm is best explained by the figure given below:
	 * 
	 * TODO: INSERT a FIGURE HERE of the matlab simulation
	 * The algorithm is explained in detail below:<br>
	 * <ol>
	 * <li> </li>
	 * <li> </li>
	 * </ol>
	 */
	public void findNumOfBeatsInPeriod(){
		int max_num_beats_for_period = 10;
		double period_threshold = 50; // period threshold
		double[] stdev_array = new double[max_num_beats_for_period]; 
		for(int i = 0 ; i < max_num_beats_for_period ; i++){
			double sum_squared = 0;
			double sum = 0;
			for(int j = 0 ; j < numOfBeats-max_num_beats_for_period ; j++){
				sum_squared = sum_squared + (beatChunkLocations[j+i+1] - beatChunkLocations[j])*(beatChunkLocations[j+i+1] - beatChunkLocations[j]);
				sum = sum + (beatChunkLocations[j+i+1] - beatChunkLocations[j]);
				
			}
			sum = sum/(numOfBeats-max_num_beats_for_period);
			 sum_squared = sum_squared/(numOfBeats-max_num_beats_for_period);
			stdev_array[i] = sum_squared - sum*sum;
			//System.out.println("stdev_array["+i+"] : " + stdev_array[i] );
		}
		
		for(int k = 0 ; k < max_num_beats_for_period ; k++){
			if(stdev_array[k] < period_threshold){
				numOfBeatsInPeriod = (k+1);
				break;
			}
		}
		
	}
	
	/*! Returns the number of beats in a period
	 * 
	 * \return numOfBeatsInPeriod
	 */
	public int getNumOfBeatsInPeriod(){
		return numOfBeatsInPeriod;
	}
	
	
	/*! sets the start chunk location, represents the start of the first period
	 * 
	 * \return numOfBeatsInPeriod
	 */
	public void setStartChunkLocation(){
		startChunkLocation = beatChunkLocations[0];
	}

	
	/*! sets the period int terms of number of chunks
	 * 
	 * We have already found the period in terms of numbe rof beats. Using the beat locations,
	 * we find the period in terms of number of chunks
	 */
	public void setperiodInChunks(){
		periodInChunks = beatChunkLocations[numOfBeatsInPeriod] - startChunkLocation;
	}
	
	/*! finds the tempo in the song.
	 * 
	 * The function calls member functions to find the chunk beat locations.
	 */
	public void findTempo(){
		findNumberOfBeats();
		initialiseBeatChunkLocations();
		findBeatChunkLocations();
		findNumOfBeatsInPeriod();
		setStartChunkLocation();
		setperiodInChunks();
	}
		
	
	
	
	/*! prints the thinned chunk energies per chunk to a file
	 * 
	 * The function is useful for debugging purpose, and writes the thinned chunk energy 
	 * for every chunk to a file
	 * \param fileName the name of the file to which the data is to be written
	 * 
	 */
	public void printThinnedChunkEnergies(String fileName) {
		try {
			//System.out.println("num of chunks: " + numOfChunks);
			FileWriter fw = new FileWriter(fileName);
			PrintWriter pw = new PrintWriter(fw);
			for (int i = 0; i < numOfChunks; i++) {
				pw.println(thinnedChunkEnergy[i]);
			}

			pw.close();
			fw.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	
	
	public short[] getThinnedChunkEnergy() {
		return thinnedChunkEnergy;
	}

	public int getNumOfSamples() {
		return numOfSamples;
	}

	public short[] getAmplitudes() {
		return amplitudes;
	}

	public int getSamplingRate() {
		return samplingRate;
	}

	public int getNumOfChunks() {
		return numOfChunks;
	}

	public int getSizeOfChunk() {
		return sizeOfChunk;
	}

	
	public int getStartChunkLocation() {
		return startChunkLocation;
	}

	public int getPeriodInChunks() {
		return periodInChunks;
	}
	
	
	public int getStartSampleLocation() {
		return (startChunkLocation*sizeOfChunk);
	}

	public int getPeriodInSamples() {
		return (periodInChunks*sizeOfChunk);
	}

	// 0th beat ---- first beat.
	public int getBeatLocationInSamples(int beat_number){
		int location = sizeOfChunk*beatChunkLocations[beat_number];
		return location;
	}

	public int getNumOfBeats() {
		return numOfBeats;
	}
	
	
	
}
