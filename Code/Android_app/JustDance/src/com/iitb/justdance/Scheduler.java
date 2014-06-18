package com.iitb.justdance;

import java.util.Stack;

import com.iitb.beatdetector.BeatDetector;

/**
 * \class Scheduler
 * \brief A static class for scheduling dance steps on beats
 * 
 * This class provides functions for allotting beats to selected dance move
 * based on the move's characteristics like Type, MinStepDuration etc.
 */

/**
 * \file Scheduler.java
 * 
 * Author: Manas, Kedar
 */

public class Scheduler {

	public static DanceMove currentDanceMove;/// DanceMove which is currently
											/// processed.

	// ! schedules dance steps in the specified dance move as per the beats in
	// the song
	/**
	 * \param beatDetector BeatDetector object for the input song. It contains
	 * the positions of beats in the songs. 
	 * \param move DanceMove object for the
	 * dance move to be scheduled. 
	 * \param beats Beats on which steps have to be
	 * performed. (Output)
	 * \return Argument to be sent to hexapod (default = 0)
	 */
	public static int scheduleSteps(Stack<Integer> beats, DanceMove move,
			BeatDetector beatDetector) {
		beats.clear(); // clear stack.
		currentDanceMove = move;

		// Check type of the dance move
		if (move.getMoveType() == DanceMove.BY_BEAT) {
			int min_step_time = move.getMinStepTime(); // in millisec.
			int num_of_beats = beatDetector.getNumOfBeats(); // Number of beats
			int beat_location = 0;

			// Add all beats to the output stack as long as time difference
			// constraint of the dance move is satisfied
			for (int i = num_of_beats - 1; i >= 0; i--) {
				beat_location = beatDetector.getBeatLocationInSamples(i);
				if (beat_location > 100 * beatDetector.getSamplingRate() / 1000)
					beats.push(beat_location);
			}
		}

		if (move.getMoveType() == DanceMove.BY_PERIOD) {

			int period = beatDetector.getPeriodInSamples();
			int min_step_time = move.getMinStepTime(); // Minimum step time in
														// millisec.

			// Minimum samples required between adjacent steps
			int min_step_samples = min_step_time
					* (beatDetector.getSamplingRate()) / 1000;

			// Decide the division of period for steps (2/4/6/8/...) based on
			// period length and minimum step samples.
			double ratio = (double) period / min_step_samples;
			double log_ratio = Math.log(ratio) / Math.log(2);
			int beats_per_period = (int) Math.pow(2, (Math.floor(log_ratio)));

			int delta = period / beats_per_period; // Samples between adjacent
													// steps.
			int start_location = beatDetector.getStartSampleLocation(); // First
																		// beat
																		// location
			int num_of_periods = (beatDetector.getNumOfSamples() - start_location)
					/ period; // Number of periods in the song

			// End location based on when last period ends
			int end_location = start_location + period * num_of_periods;
			int current_location_temp = end_location;

			// Add the step location from start to end with intervals of delta
			while (current_location_temp >= start_location) {
				if (current_location_temp > 100 * beatDetector
						.getSamplingRate() / 1000)
					beats.push(current_location_temp);
				current_location_temp = current_location_temp - delta;
			}
		}

		if (move.getMoveType() == DanceMove.SMOOTH) {

			int period_ms = beatDetector.getPeriodInSamples() * 1000
					/ beatDetector.getSamplingRate();

			int period = beatDetector.getPeriodInSamples();
			int min_step_time = move.getMinStepTime(); // in millisec.
			int min_step_samples = min_step_time
					* (beatDetector.getSamplingRate()) / 1000;

			// Find the number of periods required to complete the smooth move
			double ratio = (double) min_step_samples / period;
			int num_of_periods_for_step = (int) Math.ceil(ratio);
			int step_period = num_of_periods_for_step * period;

			int start_location = beatDetector.getStartSampleLocation();
			int num_of_step_periods = (beatDetector.getNumOfSamples() - start_location)
					/ (step_period);
			int end_location = start_location + step_period
					* num_of_step_periods;
			int current_location_temp = end_location;
			int delta = step_period;

			// Add step at intervals of delta from start to end
			while (current_location_temp >= start_location) {
				beats.push(current_location_temp);
				current_location_temp = current_location_temp - delta;
			}

			/*
			 * Period for performing step is greater than period of the beats.
			 * Say it is k times. Thus, move should be repeated after k periods.
			 * Therefore a value corresponding to the period of step has to be
			 * sent to the hexapod so that it can adjust the speed of its smooth
			 * move.
			 */
			// Compute value to be sent to the hexapod
			// Value sent is 0.9 times the actual period so that the hexapod
			// finishes the step before the next one
			int period_to_be_sent_ms = (int) (0.9 * step_period * 1000 / beatDetector
					.getSamplingRate());

			// 65 -> 8 seconds
			// 35 -> 3 seconds
			int bluetooth_val = ((period_to_be_sent_ms - 3000) * (65 - 15)
					/ (8000 - 3000) + 15);
			
			//Value that is returned is finally set as the timer time period in hexapod
			// It is required to be a multiple of 5
			return bluetooth_val / 5 * 5;

		}
		return 0;
	}
}
