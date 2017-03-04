package manner;

import java.io.File;
import java.io.FileOutputStream;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Properties;

import javax.mail.Folder;
import javax.mail.Message;
import javax.mail.Session;
import javax.mail.Store;
import javax.mail.internet.InternetAddress;

import db.DB;

public class Recv{
	public Recv(String username,String password) throws Exception
	{
		SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		
		   Properties props = new Properties();

		    String host = "lookout0405.cn";
		    String provider = "pop3";

		    Session session = Session.getInstance(props);
		    Store store = session.getStore(provider);
		    store.connect(host, username, password);

		    DB db=new DB();
		    db.FindUser(username);
		    
		    Folder inbox = store.getFolder("INBOX");
		    if (inbox == null) {
		      System.out.println("No INBOX");
		      System.exit(1);
		    }
		    inbox.open(Folder.READ_ONLY);

		    Message[] messages = inbox.getMessages();
		    for (int i = 0; i < messages.length; i++) {
//		      System.out.println("Message " + (i + 1));
//		      messages[i].writeTo(System.out);
		    	String filepath="";
		    	System.out.printf(messages[i].getSubject());
		    	System.out.printf(format.format(messages[i].getSentDate()));
		    	String from=messages[i].getHeader("From")[0];
		    	from=from.split("<")[1].split(">")[0];
		    	System.out.printf(from);
		    	filepath=filepath+"mail/"+username+"/recver/"+String.valueOf((new Date()).getTime());
		    	System.out.printf(filepath);
		    	File file = new File(filepath);
		    	FileOutputStream fileStream=new FileOutputStream(file);
		    	messages[i].writeTo(fileStream);
		    	fileStream.close();
		    	db.SaveFiletoMysql(username,String.valueOf((new Date()).getTime()),filepath,format.format(messages[i].getSentDate()),messages[i].getSubject(),from);
		    	
		    }
		    inbox.close(false);
		    store.close();
	}

}
