package GomoKu;

import java.util.ArrayList;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;

public class GomoKuLoadShell {
	GomokuBoard board;
	Shell shell;
	ArrayList <String> list2 = new ArrayList<String>();
	int nowStep = 0;
	int sum;
	public void open(final ArrayList<String> list){
		final Display display = Display.getDefault();
		shell = new Shell();
		shell.setText("GomoKuLoad");
		board = new GomokuBoard();
		board.repaint(display, shell);
		sum = list.size();
		
		Button button_GoOn = new Button(shell,SWT.NONE);
		button_GoOn.setBounds(600, 100, 100, 25);
		button_GoOn.setText("GoOn ->");
		button_GoOn.addSelectionListener(new SelectionAdapter(){
			public void widgetSelected(SelectionEvent e){
				if(nowStep < sum){
//					System.out.println(list.get(nowStep));
					list2.add(list.get(nowStep));
					board.paint(display, shell, list2, 1);
					nowStep ++;
				}
			}
		});
		
		Button button_Prev = new Button(shell,SWT.NONE);
		button_Prev.setBounds(600, 200, 100, 25);
		button_Prev.setText("Prev <-");
		button_Prev.addSelectionListener(new SelectionAdapter(){
			public void widgetSelected(SelectionEvent e){
				if(nowStep > 0){
					list2.remove(nowStep-1);
					board.paint(display, shell, list2, 1);
					nowStep --;
				}
			}
		});
		while(!shell.isDisposed()){
			if(!display.readAndDispatch()){
				display.sleep();
			}
		}
	}
}
