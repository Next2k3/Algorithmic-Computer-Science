public class Figury {
    public enum Figuryzjednymparametrem implements Figurajednoparametrowa{
        KOLO{
            public double pole(double promien){
                return Math.PI*promien*promien;
            }
            public double obwod(double promien){
                return 2*Math.PI*promien;
            }
            public String nazwa(){
                return "kolo";
            }
        },
        KWADRAT{
            public double pole(double bok){
                return bok*bok;
            }
            public double obwod(double bok){
                return 4*bok;
            }
            public String nazwa(){
                return "kwadrat";
            }
        },
        PIECIOKAT_FOREMNY{
            public double pole(double bok){
                return bok*(Math.sqrt(5)+1)/2;
            }
            public double obwod(double bok){
                return bok*5;
            }
            public String nazwa(){
                return "pieciokat";
            }
        },
        SZESCIOKAT_FORMENY{
            public double pole(double bok){
                return 3*bok*bok*Math.sqrt(3)/2;
            }
            public double obwod(double bok){
                return bok*6;
            }
            public String nazwa(){
                return "szesciokat";
            }
        }
    }
    public enum FiguryZDwomaParametrami implements Figuradwuparametrowa{
        PROSTOKAT{
            public double pole(double bok1,double bok2){
                return bok1*bok2;
            }
            public double obwod(double bok1,double bok2){
                return bok1*2+bok2*2;
            }
            public String nazwa(){
                return "prosotkat";
            }
        },
        ROMB{
            public double pole(double bok1,double kat){
                return bok1*bok1*Math.sin(Math.toRadians(kat));
            }
            public double obwod(double bok1,double bok2){
                return bok1*2+ bok2*2;
            }
            public String nazwa(){
                return "romb";
            }
        }

    }
    public interface Figurajednoparametrowa{
        double pole(double a);
        double obwod(double a);
        String nazwa();
    }
    public interface Figuradwuparametrowa{
        double pole(double a,double b);
        double obwod(double a,double b);
        String nazwa();
    }
    public static void main(String[] args){

        String figura=args[0];

        double bok1,bok2,bok3,bok4,kat,promien;

        if(args.length<2){
            System.out.println("Niepoprawna liczba argumentów");
            return;
        }
        switch (figura){
            case "o":
                    try {
                        promien = Double.parseDouble(args[1]);
                    } catch (NumberFormatException e) {
                        System.out.println(args[1] + " - Nieprawidłowy argument");
                    return;
                    }
                    System.out.println(Figuryzjednymparametrem.KOLO.nazwa());
                    System.out.println("Pole: " + Figuryzjednymparametrem.KOLO.pole(promien));
                    System.out.println("Obwod: "+ Figuryzjednymparametrem.KOLO.obwod(promien));
                break;
            case "c":
                try{
                    bok1=Double.parseDouble(args[1]);
                    bok2=Double.parseDouble(args[2]);
                    bok3=Double.parseDouble(args[3]);
                    bok4=Double.parseDouble(args[4]);
                    kat=Double.parseDouble(args[5]);
                }catch(NumberFormatException e){
                    System.out.println("Nieprawidłowe argumenty");
                    return;
                }
                if(bok1==bok2 && bok2==bok3 && bok3==bok4 && kat==90){
                    System.out.println(Figuryzjednymparametrem.KWADRAT.nazwa());
                    System.out.println("Pole: "+Figuryzjednymparametrem.KWADRAT.pole(bok1));
                    System.out.println("Obwod: "+Figuryzjednymparametrem.KWADRAT.obwod(bok1));
                }
                else if(bok1==bok2 && kat>0 &&kat<90){
                    System.out.println(FiguryZDwomaParametrami.ROMB.nazwa());
                    System.out.println("Pole: "+FiguryZDwomaParametrami.ROMB.pole(bok1,kat));
                    System.out.println("Obwod: "+FiguryZDwomaParametrami.ROMB.obwod(bok1,bok2));
                }
                else if(kat==90){
                    if(bok1==bok3) {
                        System.out.println(FiguryZDwomaParametrami.PROSTOKAT.nazwa());
                        System.out.println("Pole: " + FiguryZDwomaParametrami.PROSTOKAT.pole(bok1, bok2));
                        System.out.println("Obwod: " + FiguryZDwomaParametrami.PROSTOKAT.obwod(bok1, bok2));
                    }
                    if(bok1==bok2) {
                        System.out.println(FiguryZDwomaParametrami.PROSTOKAT.nazwa());
                        System.out.println("Pole: " + FiguryZDwomaParametrami.PROSTOKAT.pole(bok1, bok3));
                        System.out.println("Obwod: " + FiguryZDwomaParametrami.PROSTOKAT.obwod(bok1, bok3));
                    }
                }
                break;
            case "p":
                try{
                    bok1=Double.parseDouble(args[1]);
                }catch(NumberFormatException e){
                    System.out.println("Nieprawidłowe argumenty");
                    return;
                }
                System.out.println(Figuryzjednymparametrem.PIECIOKAT_FOREMNY.nazwa());
                System.out.println("Pole: "+Figuryzjednymparametrem.PIECIOKAT_FOREMNY.pole(bok1));
                System.out.println("Obwod: "+Figuryzjednymparametrem.PIECIOKAT_FOREMNY.obwod(bok1));
                break;
            case "s":
                try{
                    bok1=Double.parseDouble(args[1]);
                }catch(NumberFormatException e){
                    System.out.println("Nieprawidłowe argumenty");
                    return;
                }
                System.out.println(Figuryzjednymparametrem.SZESCIOKAT_FORMENY.nazwa());
                System.out.println("Pole: "+Figuryzjednymparametrem.SZESCIOKAT_FORMENY.pole(bok1));
                System.out.println("Obwod: "+Figuryzjednymparametrem.SZESCIOKAT_FORMENY.obwod(bok1));
                break;
            default:
                System.out.println("Niprawidłowe argumenty");
        }
        }
}
