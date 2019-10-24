package ch.heigvd.res.lab00;

/**
 * Created by Thomas on 28.02.2018.
 */
public class Cornet implements IInstrument {
    @Override
    public String play() {
        return "pouet";
    }

    @Override
    public int getSoundVolume() {
        return 42;
    }

    @Override
    public String getColor() {
        return "gold";
    }
}
