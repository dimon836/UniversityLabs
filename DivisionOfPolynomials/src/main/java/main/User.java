package main;

import Command.Command;

public class User {
    Command inputCommand;

    public User(Command inputCommand) {
        this.inputCommand = inputCommand;
    }

    public void inputRecord() {
        inputCommand.execute();
    }
}
