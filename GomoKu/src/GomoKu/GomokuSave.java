package GomoKu;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
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
public class GomokuSave {
	public void open(final ArrayList <String> list) throws Exception{
		final Display display = Display.getDefault();
		final Shell shell = new Shell();
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
		
		Button button_save = new Button(shell,SWT.NONE);
		button_save.setText("Save");
		button_save.setBounds(150, 150, 100, 25);
		
		button_save.addSelectionListener(new SelectionAdapter(){
			public void widgetSelected(SelectionEvent e){
				try{
			
					String savePath = text_path.getText();
					String fileName = text_filename.getText();
					FileWriter filewriter = new FileWriter(savePath + fileName + ".txt");
				
					String information = "";
					int length = list.size();
					for(int i=0 ; i<length; i++){
						information += list.get(i);
	//					System.out.println(list.get(i));
						information += "\n";
					}
					filewriter.write(information);	
					filewriter.flush();
					filewriter.close();
					MessageDialog.openInformation(shell, null, "Storage Success");
				
				}catch(Exception e2){
					e2.printStackTrace();
				}
				
			}
		});
		
		
		
		shell.layout();
	//	gc.dispose();
	//	imageBackground.dispose();
		while(!shell.isDisposed()){
			if(!display.readAndDispatch()){
				display.sleep();
			}
		}
	}

}
