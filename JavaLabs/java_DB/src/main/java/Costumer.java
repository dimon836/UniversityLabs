import Database.Database;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;

public class Costumer {

    public static void main(String[] args) {
        String url = "jdbc:sqlite:hotel.sqlite";
        String forName = "org.sqlite.JDBC";

        Database database = Database.getDatabase();
        database.setStatementAndConn(url, forName);
        database.addCostumer();
        database.close();
    }

}
