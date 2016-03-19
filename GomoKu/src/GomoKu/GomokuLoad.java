package GomoKu;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.InputStreamReader;
import java.util.ArrayList;

import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.graphics.GC;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Text;

@SuppressWarnings("unused")
public class GomokuLoad {
	int sum = 0;
	ArrayList <String> list = new ArrayList<String>();
	public void open() throws Exception{
		final Display display = Display.getDefault();
		Shell shell = new Shell();
		String information = "";
		shell.setText("Save");
		shell.setSize(400, 300);
		shell.open();
		Image imageBackground = new Image(display,"images/img2.jpg");
		GC gc = new GC(shell);
		gc.drawImage(imageBackground, 0, 0);
		
		Font font = new Font(display,"Arial",12,SWT.BOLD);
		gc.setFont(font);
		gc.drawText("Path:", 50, 50, true);
		
		final Text text_path = new Text(shell,SWT.BORDER);
		text_path.setBounds(100, 50, 220, 25);
		text_path.setTextLimit(100);
		text_path.setText("E:\\");
		
		gc.drawText("FileName:", 50, 100, true);
		
		final Text text_filename = new Text(shell,SWT.BORDER);
		text_filename.setBounds(130, 100, 190, 25);
		text_filename.setTextLimit(100);
		
		Button button_load = new Button(shell,SWT.NONE);
		button_load.setText("Load");
		button_load.setBounds(150, 150, 100, 25);
		
		button_load.addSelectionListener(new SelectionAdapter(){
			public void widgetSelected(SelectionEvent e){
				try{
					String information = "";
					String loadPath = text_path.getText();
					String fileName = text_filename.getText();
					String encoding = "GBK";
					File file = new File(loadPath + fileName + ".txt");
					InputStreamReader read = new InputStreamReader(new FileInputStream(file),encoding);
					@SuppressWarnings("resource")
					BufferedReader bufferedReader = new BufferedReader(read);
					String lineOne = null;
					while((lineOne = bufferedReader.readLine()) != null){
						information += lineOne;
					}
					int length = information.length();
					for(int i=0; i<length ;){
						char ch;
						char ch2;
						char ch3;
						ch = information.charAt(i);
						ch2 = information.charAt(i+1);
						if(i + 2 >= length){
							String go = "" + ch + ch2;
							list.add(go);
	//						System.out.println(go + "+");
							sum++;
							break;
						}
						ch3 = information.charAt(i+2);
						if((ch3 >= '0') && (ch3 <= '9')){
							String go = "" + ch + ch2 + ch3;
							list.add(go);
	//						System.out.println(go + "++");
							sum++;
							i += 3;
						}
						else{
							String go = "" + ch + ch2;
							list.add(go);
	//						System.out.println(go + "+++");
							sum++;
							i += 2;
						}
					}
					
					
					
					/////////////////////////
					GomoKuLoadShell loadshell = new GomoKuLoadShell();
					loadshell.open(list);
					
					
					/////////////////////////
					
				}catch(Exception e2){
					e2.printStackTrace();
				}			
			}
		});	
		shell.layout();
	//	gc.dispose();
	//	imageBackground.dispose();
	
	}
	
	public void printf(){
		for(int i=0; i<sum; i++){
			System.out.println(list.get(i));
		}
	}

}
