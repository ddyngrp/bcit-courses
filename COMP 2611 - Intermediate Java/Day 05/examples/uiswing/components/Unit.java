/*
 * Works in 1.1+Swing, 1.4, and all releases in between.
 * Used by the Converter example.
*/
public class Unit {
    String description;
    double multiplier;

    Unit(String description, double multiplier) {
        super();
        this.description = description;
        this.multiplier = multiplier;
    }

    public String toString() {
        String s = "Meters/" + description + " = " + multiplier;
        return s;
    }
}
