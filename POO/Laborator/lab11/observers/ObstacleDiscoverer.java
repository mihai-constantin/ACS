package observers;

import entities.Hero;
import entities.Obstacle;
import game.GameState;

import java.util.Observable;
import java.util.Observer;

public class ObstacleDiscoverer implements Observer {
    @Override
    public void update(Observable o, Object arg) {
        GameState gs = (GameState) o;

        for (Hero h : gs.getParty()) {
            for (Obstacle obstacle : gs.getObstacles())

                if (h.getPosx() == obstacle.getPosx() &&
                        h.getPosy() == obstacle.getPosy()) {
                    System.out.println(h.getPosx() + " " + h.getPosy() + " Can't move there !");
                    gs.undo();
                    break;
                }
        }
    }
}
