package db;
import java.io.File;
import java.sql.*;
import java.util.Vector;

import javax.swing.JButton;

public class DB {
    String driver = "com.mysql.jdbc.Driver";
    String url = "jdbc:mysql://127.0.0.1/mail";
    String user = "root"; 
    String password = "123456";
    
    Connection conn;
    Statement statement;
    ResultSet rs;
    
	public void Connect() throws ClassNotFoundException, SQLException
	{
		Class.forName(driver);
        conn = DriverManager.getConnection(url, user, password);
        if(!conn.isClosed()) 
         System.out.println("Succeeded connecting to the Database!");
	}
	
	public void FindUser(String username) throws ClassNotFoundException, SQLException
	{
		Connect();
	    statement = conn.createStatement();
		String sql = "select * from user where username='"+username+"'";
		System.out.printf(sql);
		ResultSet rs = statement.executeQuery(sql);
		
		if(rs.next())
		{
		}
		else
		{
			 rs.close();
			 statement.close();
	         conn.close();
			 File folder = new File("mail/"+username);
			 folder.mkdirs();
			 folder = new File("mail/"+username+"/sender");
			 folder.mkdirs();
			 folder = new File("mail/"+username+"/recver");
			 folder.mkdirs();
			 sql= "insert into user values('"+String.valueOf(FindUserIDMAX())+""+"','"+username+"')";
			 System.out.printf(sql);
			 Connect();
			 statement = conn.createStatement();
			 statement.executeUpdate(sql);
		}
		 rs.close();
		 statement.close();
        conn.close();
	}
	
	public int FindUserIDMAX() throws SQLException, ClassNotFoundException
	{
		int userID;
		Connect();
		statement = conn.createStatement();
		String sql = "select * from user order by userID desc";
		System.out.printf(sql);
		rs = statement.executeQuery(sql);
		
		if(rs.next())
		{
			 userID=rs.getInt("userID");
		}
		else
		{
			userID=0;
		}
		 rs.close();
		 statement.close();
        conn.close();
		return userID+1;
	}
	
	public void SaveFiletoMysql(String username,String filename,String filepath,String senddate,String subject,String from) throws ClassNotFoundException, SQLException
	{
		Connect();
		statement = conn.createStatement();
		String sql = "insert into recv values('"+username+"','"+filename+"','"+filepath+"','"+senddate+"','"+subject+"','"+from+"')";
		System.out.printf(sql);
		statement.executeUpdate(sql);
	  statement.close();
       conn.close();
	}
	
	public void GetRecvedMail(Vector row,Vector filepath,String username) throws SQLException, ClassNotFoundException
	{
		Connect();
		statement = conn.createStatement();
		String sql = "select * from recv where username='"+username+"' order by filename desc";
		rs = statement.executeQuery(sql);
		
		while(rs.next())
		{
            Vector cell = new Vector();
            cell.add(rs.getString("subject"));
            cell.add(rs.getString("from"));
            cell.add(rs.getString("senddate"));
            cell.add(new JButton("ÔÄ¶Á"));
            cell.add(new JButton("É¾³ý"));
            row.add(cell);
            filepath.add(rs.getString("filepath"));
		}
		 rs.close();
		 statement.close();
       conn.close();
	}
	
	public void DeleteRecvedMail(String filepath) throws ClassNotFoundException, SQLException
	{
		Connect();
		statement = conn.createStatement();
		String sql = "delete from recv where filepath='"+filepath+"'";
		statement.executeUpdate(sql);
		 statement.close();
	       conn.close();
	}
}
