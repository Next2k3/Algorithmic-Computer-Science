public class Pieciokat extends Figura{
    private double bok;
    public Pieciokat(double bok){
        super("pieciokat");
        this.bok=bok;
    }
    public double obliczPole(){
        return bok*(Math.sqrt(5)+1)/2;
    }
    public double obliczObwod(){
        return bok*5;
    }
}