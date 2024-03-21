
public class Test{
    public static void main(String[] args){
        switch(args[0]){
            case "o": {
                double promien;
                try {
                    promien = Double.parseDouble(args[1]);
                } catch (NumberFormatException e) {
                    System.out.println(args[1] + " - Nieprawidłowy zakres");
                    return;
                }
                Kolo kolo=new Kolo(promien);
                System.out.println("Pole kola:" + kolo.obliczPole());
                System.out.println("Obwod kola:" + kolo.obliczObwod());
            }break;
            case "c":{
                double bok1, bok2, bok3, bok4, kat;
                try {
                    bok1 = Double.parseDouble(args[1]);
                    bok2 = Double.parseDouble(args[2]);
                    bok3 = Double.parseDouble(args[3]);
                    bok4 = Double.parseDouble(args[4]);
                    kat = Double.parseDouble(args[5]);
                } catch (NumberFormatException e) {
                    System.out.println(args[1] + "lub"+ args[2] + "lub"+ args[3] + "lub"+args[4] + "lub" + args[5]+   " - Nieprawidłowy zakres");
                    return;
                }
                if(bok1==bok2 && bok2==bok3 && bok3==bok4 && kat==90){
                    Kwadrat kwadrat=new Kwadrat(bok1);
                    System.out.println("Pole kwadratu:" + kwadrat.obliczPole());
                    System.out.println("Obwod kwadratu:" + kwadrat.obliczObwod());
                }
                else if(kat==90){
                    if(bok1==bok3 && bok2==bok4){
                        Prostokat prostokat =new Prostokat(bok1,bok2);
                        System.out.println("Pole prostokata:" + prostokat.obliczPole());
                        System.out.println("Obwod prostokata:" + prostokat.obliczObwod());
                    }
                    if(bok1==bok2 && bok3==bok4){
                        Prostokat prostokat =new Prostokat(bok1,bok3);
                        System.out.println("Pole prostokata:" + prostokat.obliczPole());
                        System.out.println("Obwod prostokata:" + prostokat.obliczObwod());
                    }
                }
                else if(bok1==bok2 && bok2==bok3 && bok3==bok4 && kat>0 && kat<90){
                    Romb romb=new Romb(bok1,kat);
                    System.out.println("Pole rombu:" + romb.obliczPole());
                    System.out.println("Obwod rombu:" + romb.obliczObwod());
                }
            }break;
            case "p": {
                double bok1;
                try {
                    bok1 = Double.parseDouble(args[1]);
                } catch (NumberFormatException e) {
                    System.out.println(args[1] + " - Nieprawidłowy zakres");
                    return;
                }
                Pieciokat pieciokat = new Pieciokat(bok1);
                System.out.println("Pole pieciokatu:" + pieciokat.obliczPole());
                System.out.println("Obwod pieciokatu:" + pieciokat.obliczObwod());
            }break;
            case "s":{
                double bok1;
                try {
                    bok1 = Double.parseDouble(args[1]);
                } catch (NumberFormatException e) {
                    System.out.println(args[1] + " - Nieprawidłowy zakres");
                    return;
                }
                Szesciokat szesciokat = new Szesciokat(bok1);
                System.out.println("Pole szescianu:" + szesciokat.obliczPole());
                System.out.println("Obwod szescianu:" + szesciokat.obliczObwod());
            }
        }
    }
}
