public class Romb extends Czworokat{
    private double kat;
    public Romb(double bok,double kat){
        super("romb",bok,bok,bok,bok);
        this.kat=kat;
    }
    public double obliczPole(){
        return bok1*bok1*Math.sin(Math.toRadians(kat));
    }
    public double obliczObwod(){
        return 4*bok1;
    }
}
