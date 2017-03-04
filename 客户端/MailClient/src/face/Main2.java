package face;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.sql.SQLException;
import java.util.Vector;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.internet.MimeMessage;
import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import javax.swing.table.TableCellEditor;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableColumn;

import db.DB;

import manner.Recv;
import manner.Send;

public class Main2 extends JFrame{

	Vector filepath;
	String username;
	String password;
	Main2 m;
	JTabbedPane option;
	JPanel write;
	JScrollPane recv;
	JScrollPane send;
	JButton refresh;
    DB db=new DB();
	
	Main2(String username,String password) throws ClassNotFoundException, SQLException
	{
		m=this;
	    this.username=username;
	    this.password=password;
		
		option=new JTabbedPane();
		
		write=getWrite();
		option.addTab("写信", write);
		
		recv=getRecv();
		option.addTab("收件箱", recv);
		
		send=getSend();
		option.addTab("发件箱", send);
		
		refresh=new JButton("刷新");
		refresh.addActionListener(new Refresh());
		/*option.addChangeListener(new ChangeListener(){
			public void stateChanged(ChangeEvent e) {   
				if(option.getSelectedIndex()==0)write=getWrite();
				else if(option.getSelectedIndex()==1)
					try {
						new Recv(username,password);
					} catch (Exception e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}
				else if(option.getSelectedIndex()==2)send=getSend();
				}  });*/
		
		this.add(option,null);
		this.add(refresh,BorderLayout.NORTH);
		
    	this.setTitle("邮件客户端");
    	this.setBackground(Color.WHITE);
		this.setSize(500,500);
		this.setResizable(false);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);//一定要设置关闭
        this.setVisible(true);
        this.setLocation(500,200);
        
	}
	
//  public static void main(String[] args) throws ClassNotFoundException, SQLException {
//	m=new Main2("test","123456");
//	}
	
	JPanel getWrite()
	{
		JLabel rec=new JLabel("收信人               ");
		JLabel sub=new JLabel("主题                    ");
		JTextField to=new JTextField(35);
		JTextField subject=new JTextField(35);
		JTextArea content=new JTextArea(15,43);
		JButton send=new JButton("发送");
		send.addActionListener(new SendMail(content,subject,to));
		JPanel write=new JPanel();
		
		write.setLayout(new FlowLayout(0));
		
		write.add(rec,null);
		write.add(to,null);
		write.add(sub,null);
		write.add(subject,null);
		JScrollPane scroll = new JScrollPane(content);
		write.add(scroll,null);
		write.add(send,null);
			
		return write;
	}
	
	JScrollPane getRecv() throws ClassNotFoundException, SQLException
	{
		//JPanel Recv=new JPanel();
		//JScrollPane scroll = new JScrollPane(Recv);
	    DefaultTableModel tableModel = new DefaultTableModel();
        Vector row = new Vector();
        filepath=new Vector();
        db.GetRecvedMail(row,filepath,username);
	    String[] tableHeads = {"主题","发件人", "发送时间", "阅读","删除"};
        Vector tableHeadName = new Vector();        
        for (int i = 0; i < tableHeads.length; i++) {
            tableHeadName.add(tableHeads[i]);
        }   
        tableModel.setDataVector(row, tableHeadName);
        JTable table = new JTable(tableModel);
        TableColumn column = table.getColumnModel().getColumn(3);
        column.setCellRenderer(new MyRender(table));
        column.setCellEditor(new MyRender(table));
        column = table.getColumnModel().getColumn(4);
        column.setCellRenderer(new MyRender2(table));
        column.setCellEditor(new MyRender2(table));
        JScrollPane scroll = new JScrollPane(table);
	   // Recv.add(table);
		return scroll;
	}
	
	
	class MyRender extends AbstractCellEditor implements TableCellRenderer,ActionListener, TableCellEditor{
		private static final long serialVersionUID = 1L;
		private JButton button =null;
		JTable table;
		public MyRender(JTable table){
			button = new JButton("阅读");
			button.addActionListener(this);
			this.table=table;
		}
		public Object getCellEditorValue() {
			return null;
		}
		public Component getTableCellRendererComponent(JTable table, Object value,boolean isSelected, boolean hasFocus, int row, int column) {
			return button;
		}
		
		public Component getTableCellEditorComponent(JTable table, Object value,
				boolean isSelected, int row, int column) {
			return button;
		}
		
		@Override
		public void actionPerformed(ActionEvent e) {
			File file = new File(filepath.get(table.getSelectedRow()).toString());
	    	try {
				FileInputStream fileStream=new FileInputStream(file);
				Message message=new MimeMessage(null,fileStream);
				new MailContent(message);
				fileStream.close();
			} catch (MessagingException | IOException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			} 
	       }
		}

	class MyRender2 extends AbstractCellEditor implements TableCellRenderer,ActionListener, TableCellEditor{
		private static final long serialVersionUID = 1L;
		private JButton button =null;
		JTable table;
		public MyRender2(JTable table){
			button = new JButton("删除");
			button.addActionListener(this);
			this.table=table;
		}
		public Object getCellEditorValue() {
			return null;
		}
		public Component getTableCellRendererComponent(JTable table, Object value,boolean isSelected, boolean hasFocus, int row, int column) {
			return button;
		}
		
		public Component getTableCellEditorComponent(JTable table, Object value,
				boolean isSelected, int row, int column) {
			return button;
		}
		
		@Override
		public void actionPerformed(ActionEvent e) {
			File file = new File(filepath.get(table.getSelectedRow()).toString());
			file.delete();
			try {
				db.DeleteRecvedMail(filepath.get(table.getSelectedRow()).toString());
			} catch (ClassNotFoundException | SQLException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		    try {
				new Main2(username,password);
				 m.dispose();
			} catch (ClassNotFoundException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		}
	}
	JScrollPane getSend()
	{
		JPanel Send=new JPanel();
		JScrollPane scroll = new JScrollPane(Send);
		
		return scroll;
	}
	class Refresh implements ActionListener{
		public void actionPerformed(ActionEvent e)
		{
			try{
		    new Recv(username,password);
		    new Main2(username,password);
		    m.dispose();
			}
			catch(Exception ex){
			}
		}
	}
	class SendMail implements ActionListener{
		JTextField to;
		JTextField subject;
		JTextArea content;
		SendMail(JTextArea content,JTextField subject,JTextField to){
			this.to=to;
			this.subject=subject;
			this.content=content;
		}
		public void actionPerformed(ActionEvent e)
		{
			try{
		    new Send(content.getText(),subject.getText(),to.getText(),username);
		    new Main2(username,password);
		    m.dispose();
			}
			catch(Exception ex){
			}
		}
	}
}
	


