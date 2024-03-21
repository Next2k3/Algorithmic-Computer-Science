public class Kolo extends Figura{
    private double promien;
    public Kolo(double promien){
        super("kolo");
        this.promien =promien;
    }
    public double obliczPole(){
        return Math.PI*promien*promien;
    }
    public double obliczObwod(){
        return 2*Math.PI*promien;
    }

}
