package manner;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.SocketException;
import java.net.UnknownHostException;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

public class Register {
	
      public Register(String user,String pass,String repass,JFrame jf) throws UnknownHostException, IOException{
    	  String result;
    	  Socket socket = new Socket("lookout0405.cn", 7000);
    	  InputStream in = socket.getInputStream();
    	  OutputStream out = socket.getOutputStream();  
    	  //DataOutputStream os = new DataOutputStream(socket.getOutputStream());
    	  byte[] data= new byte[100];
    	  byte[] u,p,rp;
          int bytesRcvd;// Bytes received in last read 
          
              bytesRcvd = in.read(data,0,100);  
              if (bytesRcvd == -1) {  
                  throw new SocketException("Connection closed prematurely");  
              }  
          System.out.println("" + new String(data));      
        
    	  u=user.getBytes();
    	  out.write(u);
    	  bytesRcvd = in.read(data,0,100);
    	  System.out.println("" + new String(data));  
    	  
    	  p=pass.getBytes();
    	  out.write(p);
    	  bytesRcvd = in.read(data,0,100);
    	  System.out.println("" + new String(data)); 
    	  
    	  rp=repass.getBytes();
    	  out.write(rp);
    	  bytesRcvd = in.read(data,0,100);
    	  System.out.println("" + new String(data)); 
    	  
    	 bytesRcvd = in.read(data,0,100);
    	 result=new String(data).substring(0,3);
    	  System.out.println("" + result); 
    	  if(result.compareTo("100")==0)
    		  {
    		  System.out.println("用户名已存在"); 
    		  JOptionPane.showMessageDialog(jf,"用户名已存在");		  
    		  }
    	  else if(result.compareTo("101")==0)JOptionPane.showMessageDialog(jf,"两次密码输入不同");
    	  else if(result.compareTo("102")==0)JOptionPane.showMessageDialog(jf,"注册成功");
    	  
    	  in.close();
    	  out.close();
    	  socket.close();
      }
}
