package commands;

import entities.Hero;

public class MoveCommand implements Command {

    private Hero hero;
    private Hero.Direction direction;

    public MoveCommand(Hero hero, Hero.Direction direction) {
        this.hero = hero;
        this.direction = direction;
    }

    @Override
    public void undo() {
        this.hero.reverseMove(this.direction);
    }

    @Override
    public void execute() {
        this.hero.move(this.direction);
    }

    // implement the move command
    /*  - MoveCommand(Hero, Direction)
        - void undo()
        - void execute()
        - maybe helper method for undo ?
    */
}
