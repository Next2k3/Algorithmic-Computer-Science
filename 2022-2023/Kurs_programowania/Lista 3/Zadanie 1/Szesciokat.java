public class Szesciokat extends Figura{
    private double bok;
    public Szesciokat(double bok){
        super("szesciokat");
        this.bok=bok;
    }
    public double obliczPole(){
        return bok*bok*Math.sqrt(3)/4;
    }
    public double obliczObwod(){
        return bok*6;
    }
}
