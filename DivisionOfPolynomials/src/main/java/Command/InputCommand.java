package Command;

import mvc.Controller;

public class InputCommand implements Command {
    Controller controller;

    public InputCommand(Controller controller) {
        this.controller = controller;
    }

    @Override
    public void execute() {
        controller.input();
    }
}
