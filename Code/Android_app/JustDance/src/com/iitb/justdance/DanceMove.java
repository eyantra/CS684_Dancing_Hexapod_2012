package com.iitb.justdance;

/**
 * \class DanceMove \brief A class to store dance move's characteristics
 * 
 * This class stores the specifications of a dance move which would be necessary
 * for scheduling the dance steps of the move on beats
 * 
 */
public class DanceMove {
	public final static int BY_BEAT = 0; // / Step at every beat
	public final static int BY_PERIOD = 1; // / Steps distributed evenly over a
											// period
	public final static int SMOOTH = 2; // / Step covers one or more than one
										// period

	private int moveType; // / type of the dance moves
	private int minStepTime; // / minimum time difference in milliseconds
								// between adjacent steps
	private int numberOfSteps; // / number of steps in the move
	private char moveId; // / id of the dance move

	/**
	 * @return type of dance move
	 */
	public int getMoveType() {
		return moveType;
	}

	/**
	 * 
	 * @return minimum time difference in milliseconds between adjacent steps
	 */
	public int getMinStepTime() {
		return minStepTime;
	}

	/**
	 * 
	 * @return number of steps in the move
	 */
	public int getNumberOfSteps() {
		return numberOfSteps;
	}

	/**
	 * 
	 * @return id of the dance move
	 */
	public char getMoveId() {
		return moveId;
	}

	/**
	 * Class constructor
	 * 
	 * @param move_id
	 *            id of the dance move
	 * @param move_type
	 *            type of the dance move
	 * @param min_step_time
	 *            time difference in milliseconds between adjacent steps
	 * @param number_of_steps
	 *            number of steps in the move
	 */
	public DanceMove(char move_id, int move_type, int min_step_time,
			int number_of_steps) {
		moveId = move_id;
		moveType = move_type;
		minStepTime = min_step_time;
		numberOfSteps = number_of_steps;
	}

	/**
	 * Generates default set of moves
	 * 
	 * @return array of dance moves
	 */
	public static DanceMove[] generateMoves() {
		int numberOfMoves = 8;
		DanceMove moves[] = new DanceMove[10];
		moves[0] = new DanceMove('a', BY_BEAT, 100, 2); // kick_by_beat
		moves[1] = new DanceMove('b', BY_PERIOD, 200, 2); // kick_by_period
		moves[2] = new DanceMove('c', BY_PERIOD, 300, 2); // zhigzhig flat
		moves[3] = new DanceMove('d', BY_BEAT, 100, 8); // leg raise
		moves[4] = new DanceMove('e', BY_BEAT, 400, 8); // Hands Air Needs a
														// song
		moves[5] = new DanceMove('g', SMOOTH, 5000, 1); // slow Motion
		moves[6] = new DanceMove('f', BY_BEAT, 200, 8); // Zhigzhig rise +
														// finale

		return moves;
	}
}
