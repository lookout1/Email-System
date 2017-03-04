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
    	 button=new JButton("确定");
    	 button.addActionListener(this);
    	 user=new JLabel("              用户名：             ");
    	 pass=new JLabel("              密码：               ");
    	 repass=new JLabel("                确认密码：          ");
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
    	 
     	this.setTitle("邮件客户端");
     	this.setBackground(Color.WHITE);
 		this.setSize(500,500);
 		this.setResizable(false);
         this.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);//一定要设置关闭
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
