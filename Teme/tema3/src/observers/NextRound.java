/**
 * Constantin Mihai - 321CD
 */

package observers;

import simulation.Hospital;

import java.util.Observable;
import java.util.Observer;

public class NextRound implements Observer {

    /**
     * @param o   the observable object, i.e. the hospital
     * @param arg unused
     */
    @Override
    public void update(Observable o, Object arg) {
        Hospital hospital = (Hospital) o;
        hospital.setNumberOfRound(hospital.getNumberOfRound() + 1);
    }
}
