package Database;

import java.sql.*;
import java.time.LocalDate;
import java.util.ArrayList;
import java.util.Scanner;

import static java.lang.Thread.sleep;

public class Database {
    private static Database database;
    public Connection conn;
    public Statement statement;

    public static Database getDatabase() {
        if (database == null)
            return new Database();
        return database;
    }

    private Database() {}

    public void setStatementAndConn(String url, String forName) {
        try {
            Class.forName(forName);
            conn = DriverManager.getConnection(url);
            statement = conn.createStatement();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void addCostumer() {
        try {
            PreparedStatement ps = null;
            while(true) {
                String sql = "INSERT INTO Costumer "
                        + "(floor, full_name, room_id, start_vacation, duration, end_vacation) values ";
                Scanner in = new Scanner(System.in);
//                System.out.print(" Entering in hotel.");  sleep(1000);
//                System.out.print(".");                    sleep(1000);
//                System.out.println(".");                  sleep(1000);
                System.out.print("(W) Hi! Do you wanna stay here for some days?\n--- ");
                String answers = in.nextLine();
                String full_name, bed_type;
                int floor, duration, room_id = 100;
                if (answers.contains("Yes") || answers.contains("yes")) {
                    System.out.print("(W) How many days you want to stay here? \n--- ");
                    duration = in.nextInt();
                    System.out.print("(W) Your name and surname? \n--- ");
                    in.nextLine();
                    full_name = in.nextLine();
                    System.out.println("(W) What floor you want to choose?");
                    System.out.println("(1) 100$ - single bed, 150$ - double bed");
                    System.out.println("(2) 200$ - single bed, 250$ - double bed");
                    System.out.println("(3) 300$ - single bed, 350$ - double bed");
                    System.out.print("(4) 400$ - single bed, 450$ - double bed\n--- ");
                    floor = in.nextInt();
                    System.out.print("(W) And choose bed type please\n--- ");
                    in.nextLine();
                    bed_type = in.nextLine();
//                    System.out.print("(W) Okay, one second.");    sleep(1000);
//                    System.out.print(".");                        sleep(1000);
//                    System.out.println(".");                      sleep(1000);

                    String gettingVacantRoom;
                    String help;
                    if (floor == 1) {
                        gettingVacantRoom = "Select vacant from floor_1";
                        help = "UPDATE floor_1" +
                                " SET vacant = 'busy room'" +
                                " WHERE id_room = ?";
                    }
                    else if (floor == 2) {
                        gettingVacantRoom = "Select vacant from floor_2";
                        help = "UPDATE floor_2" +
                                " SET vacant = 'busy room'" +
                                " WHERE id_room = ?";
                    }
                    else if (floor == 3) {
                        gettingVacantRoom = "Select vacant from floor_3";
                        help = "UPDATE floor_3" +
                                " SET vacant = 'busy room'" +
                                " WHERE id_room = ?";
                    }
                    else {
                        gettingVacantRoom = "Select vacant from floor_4";
                        help = "UPDATE floor_4" +
                                " SET vacant = 'busy room'" +
                                " WHERE id_room = ?";
                    }
                    ResultSet resultSet = statement.executeQuery(gettingVacantRoom);
                    ps = conn.prepareStatement(help);
                    int i;
                    if (bed_type.contains("double")) {
                        i = 0;
                    }
                    else if (bed_type.contains("single")) {
                        i = -1;
                    } else i = 0;
                    while (i != 100) {
                        i += 2;
                        if (resultSet.next()) {
                            if (resultSet.getString(1).equals("free room")) {
                                room_id = i;
                                break;
                            }
                        } else break;
                    }
                    ps.setInt(1, i);
                    System.out.println(ps.executeUpdate() + "rows changed");
                    LocalDate start_vacation = java.time.LocalDate.now();
                    answers = "(" + floor + ','
                            + "'" + full_name + "'" + ','
                            + room_id + ','
                            + "'" + start_vacation + "'" + ','
                            + duration + ','
                            + "'" + start_vacation.plusDays(duration) + "');";
                    sql += answers;
                    statement.execute(sql);
                    System.out.println("(W) You have been added, your room is #" + room_id + " on " + floor + "floor!");
                    System.out.println("(W) Have a nice day!");
                }
                else {
                    System.out.println("Have a nice day!");
                    break;
                }
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void close() {
        try {
            conn.close();
        } catch (SQLException throwable) {
            throwable.printStackTrace();
        }
    }

}
