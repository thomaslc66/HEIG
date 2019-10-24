/**
 * @File        : Utils.java
 * @Author(s)   : Michael Brouchoud & Thomas Lechaire
 * @Date        : 19.03.2018
 *
 * @Goal        : Util tools
 *
 * @Comment(s)  : -
 *
 */

import java.util.Random;

public class Utils {
    private final static Random random = new Random();

    /**
     * Give a number between [0, maxVal[
     * @param maxVal The max value
     * @return A number between [0, maxVal[
     */
    public static int getRandomInt(int maxVal) {
        return random.nextInt(maxVal);
    }

    /**
     * Give a number between [minVal, maxVal[
     * @param minVal The min value
     * @param maxVal The max value
     * @return A number between [minVal, maxVal[
     */
    public static int getRandomInt(int minVal, int maxVal) {
        return random.nextInt(maxVal-minVal) + minVal;
    }

    /**
     * Give a number between -32768 and 32768
     * @return A number between -32768 and 32768
     */
    public static int getRandomPosNegNumber() {
        return random.nextInt(65536)-32768;
    }

    /**
     * Give randomly -1 or 1
     * @return -1 or 1
     */
    public static int getRandomOnePosNeg() {
        return getRandomPosNegNumber() >= 0 ? 1 : -1;
    }
}
