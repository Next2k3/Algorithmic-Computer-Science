public class Prostokat extends Czworokat{
    public Prostokat(double bok1,double bok2){
        super("prostokat",bok1,bok2,bok1,bok2);
    }
    public double obliczPole(){
        return bok1*bok2;
    }
    public double obliczObwod(){
        return bok1+bok2+bok3+bok4;
    }
}
