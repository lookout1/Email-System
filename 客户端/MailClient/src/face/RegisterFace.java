package face;

import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.net.UnknownHostException;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JTextField;

import manner.Register;

public class RegisterFace extends JFrame implements ActionListener{
	JButton button;
	JLabel user;
	JLabel pass;
	JLabel repass;
	JTextField username;
	JTextField password;
	JTextField repassword;
	JFrame jf;
	
     RegisterFace(){
    	 jf=this;
    	 button=new JButton("ȷ��");
    	 button.addActionListener(this);
    	 user=new JLabel("              �û�����             ");
    	 pass=new JLabel("              ���룺               ");
    	 repass=new JLabel("                ȷ�����룺          ");
    	 username=new JTextField(25);
    	 password=new JTextField(25);
    	 repassword=new JTextField(25);
    	 
    	 this.setLayout(new FlowLayout());
    	 
    	 this.add(user);
    	 this.add(username);
    	 this.add(pass);
    	 this.add(password);
    	 this.add(repass);
    	 this.add(repassword);
    	 this.add(button);
    	 
     	this.setTitle("�ʼ��ͻ���");
     	this.setBackground(Color.WHITE);
 		this.setSize(500,500);
 		this.setResizable(false);
         this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);//һ��Ҫ���ùر�
         this.setVisible(true);
         this.setLocation(1000,200);
     }

	@Override
	public void actionPerformed(ActionEvent e) {
		String u=username.getText();
		String p=password.getText();
		String rp=repassword.getText();
		try {
			new Register(u,p,rp,jf);
		} catch (UnknownHostException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
	}
}
