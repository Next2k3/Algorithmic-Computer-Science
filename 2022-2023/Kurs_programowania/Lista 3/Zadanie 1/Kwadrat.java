public class Kwadrat extends Czworokat{
    public Kwadrat(double bok){
        super("kwadrat",bok,bok,bok,bok);
    }
    public double obliczPole(){
        return bok1*bok1;
    }
    public double obliczObwod(){
        return 4*bok1;
    }
}
