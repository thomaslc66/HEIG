package ch.heigvd.res.lab00;

/**
 * Created by Thomas on 28.02.2018.
 */
public class Trumpet implements IInstrument {
    @Override
    public String play() {
        return "pouet";
    }

    @Override
    public int getSoundVolume() {
        return 50;
    }

    @Override
    public String getColor() {
        return "golden";
    }
}
