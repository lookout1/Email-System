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
        user=new JLabel("�û�");
        pass=new JLabel("����");
        title=new JLabel("�� �� �� �� ��");
        title.setFont(new Font("����",Font.BOLD,30));
        login=new JButton("��¼");
        login.addActionListener(new loginListen());
        register=new JButton("ע��");
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
        
    	this.setTitle("�ʼ��ͻ���");
    	this.setBackground(Color.WHITE);
		this.setSize(500,500);
		this.setResizable(false);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//һ��Ҫ���ùر�
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
				JOptionPane.showMessageDialog(m,"�û������������");
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
