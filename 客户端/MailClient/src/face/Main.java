package face;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;
import javax.swing.border.Border;

import manner.Recv;

public class Main extends JFrame{

	static Main m;
	
	JTextField username;
	JPasswordField password;
	JLabel user;
	JLabel pass;
	JLabel title;
	JButton login;
	JButton register;
	
	
    Main(){
        
        username=new JTextField(10);
        password=new JPasswordField(10);
        user=new JLabel("用户");
        pass=new JLabel("密码");
        title=new JLabel("邮 件 客 户 端");
        title.setFont(new Font("宋体",Font.BOLD,30));
        login=new JButton("登录");
        login.addActionListener(new loginListen());
        register=new JButton("注册");
        register.addActionListener(new registerListen());
        
        JPanel top=new JPanel();
        top.setPreferredSize(new Dimension(100,100));
        top.add(title);
        
        JPanel userINF=new JPanel();
        userINF.setPreferredSize(new Dimension(100,100));
        userINF.setLayout(new FlowLayout());
        userINF.add(user);
        userINF.add(username);
        userINF.add(pass);
        userINF.add(password);
        
        JPanel bottom=new JPanel();
        bottom.setPreferredSize(new Dimension(100,100));
        bottom.add(login);
        bottom.add(register);
        
       this.add(userINF,BorderLayout.CENTER);
       this.add(top,BorderLayout.NORTH);
       this.add(bottom,BorderLayout.SOUTH);
        
    	this.setTitle("邮件客户端");
    	this.setBackground(Color.WHITE);
		this.setSize(500,500);
		this.setResizable(false);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//一定要设置关闭
        this.setVisible(true);
        this.setLocation(500,200);
    }
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		m=new Main();
	}
    
	class loginListen implements ActionListener{
		public void actionPerformed(ActionEvent e)
		{
			try{
		    new Recv(username.getText(),password.getText());
		    new Main2(username.getText(),password.getText());
		    m.dispose();
			}
			catch(Exception ex){
				JOptionPane.showMessageDialog(m,"用户名或密码错误");
			}
		}
	}
	
	class registerListen implements ActionListener{
		public void actionPerformed(ActionEvent e)
		{
		    new RegisterFace();
		}
	}
}
