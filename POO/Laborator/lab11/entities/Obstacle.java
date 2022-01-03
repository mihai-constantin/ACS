package entities;

public class Obstacle {

    protected int posx;
    protected int posy;

    public Obstacle(int posx, int posy) {
        this.posx = posx;
        this.posy = posy;
    }

    public int getPosx() {
        return posx;
    }

    public void setPosx(int posx) {
        this.posx = posx;
    }

    public int getPosy() {
        return posy;
    }

    public void setPosy(int posy) {
        this.posy = posy;
    }
}
