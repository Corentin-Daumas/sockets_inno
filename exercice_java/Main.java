import java.util.ArrayList;
public class Main {
    public static void main(String[] args){
        Figure cercle = new Cercle(5);
        Figure carre = new Carre(5);

        ArrayList<Figure> figures = new ArrayList<Figure>();
        figures.add(cercle);
        figures.add(carre);

        // for(int i = 0; i<figures.size(); i++) {
        //     System.out.println(figures.get(i) + " et son aire est " + figures.get(i).aire());
        // }
        for(Figure f : figures) { // parcourir une liste differement
            System.out.println(f);
        }

    }
}
