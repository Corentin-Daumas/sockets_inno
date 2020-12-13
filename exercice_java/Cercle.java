public class Cercle extends Figure {
    int rayon;
    Cercle (int r){
        super("Cercle");
        this.rayon = r;
    }
    public double aire() {
        return 3.14 * this.rayon * this.rayon;
    }
    public String toString() {
        return "je suis un cercle d'aire" + this.aire();
    }
}