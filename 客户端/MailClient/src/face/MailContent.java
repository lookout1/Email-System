package face;

import java.awt.Color;
import java.io.IOException;

import javax.mail.Message;
import javax.mail.MessagingException;
import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class MailContent extends JFrame{
	JTextArea text;
	JScrollPane scroll;
	
	MailContent(Message message) throws IOException, MessagingException
	{
		text=new JTextArea();
		text.setText(""+message.getContent());
		text.setEditable(false);
		
		scroll=new JScrollPane(text);
		
		this.add(scroll);
		
    	this.setTitle("邮件客户端");
    	this.setBackground(Color.WHITE);
		this.setSize(500,500);
		this.setResizable(false);
        this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);//一定要设置关闭
        this.setVisible(true);
        this.setLocation(1000,200);
	}
}
