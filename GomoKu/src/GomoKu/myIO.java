package GomoKu;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;

public class myIO {
	private InputStreamReader read[];
	private BufferedReader bufread[];
	private OutputStreamWriter writer[];
	private BufferedWriter bufwriter[];
	public myIO(int MAXStreamnum)
	{
		read=new InputStreamReader[MAXStreamnum];
		bufread=new BufferedReader[MAXStreamnum];
		writer=new OutputStreamWriter[MAXStreamnum];
		bufwriter=new BufferedWriter[MAXStreamnum];
		int i;
		for(i=0;i<MAXStreamnum;i++)
		{
			read[i]=null;
			bufread[i]=null;
			writer[i]=null;
			bufwriter[i]=null;
		}
	}
	public void startRead(String filepath,String encodingString,int Readernum)
	{
		try {
			read[Readernum] = new InputStreamReader(new FileInputStream(filepath), encodingString);
			bufread[Readernum] = new BufferedReader(read[Readernum]);
		} catch (UnsupportedEncodingException e) {
			// TODO 自动生成的 catch 块
			e.printStackTrace();
		} catch (FileNotFoundException e) {
			// TODO 自动生成的 catch 块
			e.printStackTrace();
		}
		
	}
	public void endRead(int Readernum)
	{
		if(bufread!=null)
			try {
				bufread[Readernum].close();
				bufread[Readernum]=null;
			} catch (IOException e) {
				// TODO 自动生成的 catch 块
				e.printStackTrace();
			}
		if(read!=null)
			try {
				read[Readernum].close();
				read[Readernum]=null;
			} catch (IOException e) {
				// TODO 自动生成的 catch 块
				e.printStackTrace();
			}
	}
	public void startWrite(String filepath,String encodingString,int Writernum)
	{
		try {
			writer[Writernum]=new OutputStreamWriter(new FileOutputStream(filepath),encodingString);
			bufwriter[Writernum]=new BufferedWriter(writer[Writernum]);
		} catch (UnsupportedEncodingException e) {
			// TODO 自动生成的 catch 块
			e.printStackTrace();
		} catch (FileNotFoundException e) {
			// TODO 自动生成的 catch 块
			e.printStackTrace();
		}
	}
	public void endWrite(int Writernum)
	{
		try {
			if(bufwriter!=null)
			{
				bufwriter[Writernum].close();
				bufwriter[Writernum]=null;
			}
			if(writer!=null)
			{
				writer[Writernum].close();
				writer[Writernum]=null;
			}
			
		} catch (IOException e) {
			// TODO 自动生成的 catch 块
			e.printStackTrace();
		}
		
	}
	public String readOneSentence(int Readernum)
	{
		try {
			return bufread[Readernum].readLine();
		} catch (IOException e) {
			// TODO 自动生成的 catch 块
			System.out.println("文件未正确打开，读取出错");
			e.printStackTrace();
			return null;
		}
	}
	public void writeOneString(String s,int Writernum)
	{
		
		try {
			bufwriter[Writernum].write(s);
		} catch (IOException e) {
			// TODO 自动生成的 catch 块
			e.printStackTrace();
			System.out.println("写入string出错");
		}
	}
	public void writeStringBufferIntoTXT(StringBuffer buf,int Writernum)//将StringBuffer写入txt
	{
		
			try {
				bufwriter[Writernum].write(buf.toString());
			} catch (IOException e) {
				// TODO 自动生成的 catch 块
				e.printStackTrace();
			}
	}
	public static boolean isFileExist(String path)
	{
		File file=new File(path);
		return file.exists();
	}
	public int readint(int readernum)
	{
		int rst=-1;
		try {
			rst=bufread[readernum].read();
		} catch (IOException e) {
			// TODO 自动生成的 catch 块
			e.printStackTrace();
		}
		return rst;
	}
	public void writechars(char []a,int writernum)
 	{
 		try {
			bufwriter[writernum].write(a);
		} catch (IOException e) {
			// TODO 自动生成的 catch 块
			e.printStackTrace();
			System.out.println("Wrong in IOforHMM.writechars");
		}
 	}
}
