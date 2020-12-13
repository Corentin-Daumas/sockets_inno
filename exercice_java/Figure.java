abstract public class Figure {
    String type;
    Figure(String t){
        this.type = t;
    }
    public abstract double aire();
    @Override
    public String toString(){
        return "c'est un " + this.type;
    }
}