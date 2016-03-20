package GomoKu;

import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.MouseAdapter;
import org.eclipse.swt.events.MouseEvent;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.graphics.GC;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;


@SuppressWarnings("unused")
public class GomoKuEntry {
	static GomokuBoard board;
	static OrderList newOrder;
	static AIforGobangGame ai;
	static Shell shell;
	public static void main(String args[]){
		final Display display = Display.getDefault();
		shell = new Shell();
		shell.setText("GomoKu");
		//////////////////////////////////////////////////

		board = new GomokuBoard();
		newOrder = new OrderList();
		
		board.repaint(display, shell);
		ai = new AIforGobangGame(-1, -1, "E:\\quanzhi.txt", "GBK",3);
		
		shell.addMouseListener(new MouseAdapter(){
			public void mouseDoubleClick(MouseEvent e){
				int x = e.x;
				int y = e.y;
				int row = (x - 23) / 35;
				int line = (y - 23) / 35;
				int check2 = 0;
				int ifBlackWin = 0;
				if((row > 14) || (row < 0))
					check2 = -1;
				if((line > 14) || (line < 0))
					check2 = -1;
				char rowchar = (char) (row + 'A');
				char linechar = (char) (line + '1');
				String go = String.valueOf(rowchar);
				go = go + linechar;
				int check = newOrder.check(go);
				if(check == -1){
					MessageDialog.openInformation(shell, null, "illegal set");
				}
				else if(check2 == -1){
					
				}
				else{
					newOrder.addNewGo(go);
					board.paint(display, shell, newOrder.list, newOrder.first);
					int winWay = newOrder.checkGomokuWin();
					String win;
					if(winWay == 1){
						win = "black win";
						MessageDialog.openInformation(shell, null, win);
						ai.judge_iswin(1);
						ai.TD_study();
						ifBlackWin = 1;
					}
					else if(winWay == 2){
						win = "white win";
						MessageDialog.openInformation(shell, null, win);
					}
					else
						;
					/////////////////////
					int[] array2 = new int[300];
					for(int i=0,k=0; i<15; i++)
						for(int j=0; j<15; j++){
							if(newOrder.array[i][j] == 2)
								array2[k++] = -1;
							else
								array2[k++] = newOrder.array[i][j];
						}
					Result rst=new Result();
					
					if(ifBlackWin == 0)
						ai.makecmd(array2 , rst);
					else
						;
					/////
					
					int line2 = rst.getx();
					int row2 = rst.gety();
					char line2char = (char) (line2 + '1');
					char row2char = (char) (row2 + 'A');
					String go2 = String.valueOf(row2char);
					go2 += line2char;
					int check3 = newOrder.check(go2);
					if(check3 == -1){
						MessageDialog.openInformation(shell, null, "illegal set");
					}
					
					if(ifBlackWin == 0){
						newOrder.addNewGo(go2);
						board.paint(display, shell, newOrder.list, newOrder.first);			
						winWay = newOrder.checkGomokuWin();
						if(winWay == 1){
							win = "black win";
							MessageDialog.openInformation(shell, null, win);
							ai.judge_iswin(1);
							ai.TD_study();
						}
						else if(winWay == 2){
							win = "white win";
							MessageDialog.openInformation(shell, null, win);
							ai.judge_iswin(-1);
							ai.TD_study();
						}
						else
							;
					}
					/////
					
				}
			}
		});
		
		Button button_reset = new Button(shell,SWT.NONE);
		button_reset.setBounds(600, 80, 100, 25);
		button_reset.setText("Reset(重新开始)");
		button_reset.addSelectionListener(new SelectionAdapter(){
			public void widgetSelected(SelectionEvent e){
				newOrder.reset();
				ai.init();
				board.repaint(display, shell);
			}
		});
		
		Button button_undo = new Button(shell,SWT.NONE);
		button_undo.setBounds(600, 160, 100, 25);
		button_undo.setText("Undo(悔棋)");
		button_undo.addSelectionListener(new SelectionAdapter(){
			public void widgetSelected(SelectionEvent e){
				//newOrder.undo();
				//board.paint(display, shell, newOrder.list, newOrder.first);
				String message="考虑到您先走已经占了极大的优势，我决定去掉悔棋功能。以后多小心吧，想好再下。";
				MessageDialog.openInformation(shell, null, message);
			}
		});
		
		Button button_save = new Button(shell,SWT.NONE);
		button_save.setBounds(600, 240, 100, 25);
		button_save.setText("Save(保存棋谱)");
		button_save.addSelectionListener(new SelectionAdapter(){
			public void widgetSelected(SelectionEvent e){
				GomokuSave save = new GomokuSave();
				try {
					save.open(newOrder.list);
				} catch (Exception e1) {
					e1.printStackTrace();
				}
			}
		});
		
		Button button_load = new Button(shell,SWT.NONE);
		button_load.setBounds(600, 320, 100, 25);
		button_load.setText("Load(载入棋谱)");
		button_load.addSelectionListener(new SelectionAdapter(){
			public void widgetSelected(SelectionEvent e){
				GomokuLoad load = new GomokuLoad();
				try {
					load.open();
					load.printf();
				} catch (Exception e1) {
					e1.printStackTrace();
				}
			}
		});
		
		Button button_learn = new Button(shell,SWT.NONE);
		button_learn.setBounds(600, 400, 100, 25);
		button_learn.setText("Learn(学习)");
		button_learn.addSelectionListener(new SelectionAdapter(){
			public void widgetSelected(SelectionEvent e){
				newOrder.reset();
				ai.saveWeight("E:\\quanzhi.txt");
				ai.init();
				board.repaint(display, shell);
				MessageDialog.openInformation(shell, null, "Learning Success");
			}
		});
		
		Button button_refresh = new Button(shell,SWT.NONE);
		button_refresh.setBounds(600, 480, 100, 25);
		button_refresh.setText("刷新界面");
		button_refresh.addSelectionListener(new SelectionAdapter(){
			public void widgetSelected(SelectionEvent e){
				board.paint(display, shell, newOrder.list, newOrder.first);	
			}
		});
		////////////////
		while(!shell.isDisposed()){
			if(!display.readAndDispatch()){
				display.sleep();
			}
		}
		
		
		
	}

}
