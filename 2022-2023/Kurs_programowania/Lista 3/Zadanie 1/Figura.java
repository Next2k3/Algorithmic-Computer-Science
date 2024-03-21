interface interface_Figura{
    double obliczObwod();
    double obliczPole();
}
public abstract class Figura implements interface_Figura {
    private String nazwa;
    public Figura(String nazwa){
        this.nazwa=nazwa;
    }
    public String getNazwa(){
        return nazwa;
    }

}
