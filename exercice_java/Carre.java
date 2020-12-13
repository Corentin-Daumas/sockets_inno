public class Carre extends Figure {
    int cote;
    Carre (int c){
        super("Carre");
        this.cote = c;
    }
    public double aire() {
        return this.cote * this.cote;
    }
}