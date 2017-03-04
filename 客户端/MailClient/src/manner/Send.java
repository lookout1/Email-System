package manner;

import java.util.Properties;

import javax.mail.Address;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Session;
import javax.mail.Transport;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeMessage;

public class Send {
    public Send(String content,String subject,String to,String username) throws MessagingException{
		Properties props = new Properties();
		System.out.printf(content+subject+to+username);
		props.setProperty("mail.smtp.auth", "true");
		props.setProperty("mail.transport.protocol", "smtp");
		Session session = Session.getInstance(props);
		session.setDebug(true);
		Message msg = new MimeMessage(session);
		msg.setText(content);
		msg.setFrom(new InternetAddress(username+"@lookout0405.cn"));
		msg.setSubject(subject);
		
		Transport transport = session.getTransport();
		transport.connect("lookout0405.cn",25, username, "123456");
		transport.sendMessage(msg,
				new Address[]{new InternetAddress(to)});
		transport.close();
    }
}

