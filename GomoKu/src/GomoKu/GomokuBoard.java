package GomoKu;

import java.util.ArrayList;

import org.eclipse.swt.SWT;
import org.eclipse.swt.graphics.Font;
import org.eclipse.swt.graphics.GC;
import org.eclipse.swt.graphics.Image;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.Shell;

public class GomokuBoard {
	Image imageBackground;
	GC gc;
	public void paint(Display display,Shell shell, ArrayList<String> array, int first){
		imageBackground = new Image(display,"images/img2.jpg");
		shell.setSize(800, 600);
		shell.open();
		gc = new GC(shell);
		gc.drawImage(imageBackground, 0, 0);
		////////
		{
			gc.setLineWidth(2);
			for(int i = 0; i <= 14; i++){
				gc.drawLine(40 + i*35, 40, 40 + i*35, 530);
				gc.drawLine(40, 40 + i*35, 530, 40 + i*35);
			}
			gc.setLineWidth(3);
			gc.drawRectangle(30, 30, 510, 510);
		}
		{
			Font font = new Font(display,"Arial",12,SWT.BOLD);
			gc.setFont(font);
			char ch = 'A';
			for(int i = 0; i <= 14; i++){
				gc.drawText(String.valueOf(ch), 35 + i*35, 10, true);
				ch++;
			}
			int integer = 1;
			for(int j = 0; j <= 14; j++){
				gc.drawText(String.valueOf(integer), 550, 30 + j*35, true);
				integer++;
			}
		}
		{
			gc.setBackground(display.getSystemColor(SWT.COLOR_BLACK));
			gc.fillOval(140, 140, 10, 10);
			gc.fillOval(420, 140, 10, 10);
			gc.fillOval(140, 420, 10, 10);
			gc.fillOval(420, 420, 10, 10);
			gc.fillOval(280, 280, 10, 10);
		}
		////////
		
		{
			int sum = array.size();
			int rownum = 0;
			int linenum = 0;
			for(int i = 0; i < sum;i++){
				String go = array.get(i);
				char row = go.charAt(0);
				char line = go.charAt(1);
				int length = go.length();
				rownum = row - 'A';
				if(length == 2)
					linenum = line - '1';
				else
					linenum = line - '1' + 11;
				if((i + first) % 2 == 1)
					gc.setBackground(display.getSystemColor(SWT.COLOR_BLACK));
				else
					gc.setBackground(display.getSystemColor(SWT.COLOR_WHITE));
				gc.fillOval(25 + rownum*35, 25 + linenum*35, 30, 30);
			}
			gc.setBackground(display.getSystemColor(SWT.COLOR_RED));
			gc.fillOval(35 + rownum*35, 35 + linenum*35, 10, 10);
		}
		gc.dispose();
		imageBackground.dispose();
		//////////////////////////////////
	}
	public void repaint(Display display,Shell shell){
		imageBackground = new Image(display,"images/img2.jpg");
		shell.setSize(800, 600);
		shell.open();
		gc = new GC(shell);
		gc.drawImage(imageBackground, 0, 0);
		////////
		{
			gc.setLineWidth(2);
			for(int i = 0; i <= 14; i++){
				gc.drawLine(40 + i*35, 40, 40 + i*35, 530);
				gc.drawLine(40, 40 + i*35, 530, 40 + i*35);
			}
			gc.setLineWidth(3);
			gc.drawRectangle(30, 30, 510, 510);
		}
		{
			Font font = new Font(display,"Arial",12,SWT.BOLD);
			gc.setFont(font);
			char ch = 'A';
			for(int i = 0; i <= 14; i++){
				gc.drawText(String.valueOf(ch), 35 + i*35, 10, true);
				ch++;
			}
			int integer = 1;
			for(int j = 0; j <= 14; j++){
				gc.drawText(String.valueOf(integer), 550, 30 + j*35, true);
				integer++;
			}
		}
		{
			gc.setBackground(display.getSystemColor(SWT.COLOR_BLACK));
			gc.fillOval(140, 140, 10, 10);
			gc.fillOval(420, 140, 10, 10);
			gc.fillOval(140, 420, 10, 10);
			gc.fillOval(420, 420, 10, 10);
			gc.fillOval(280, 280, 10, 10);
		}		
		////////
		gc.dispose();
		imageBackground.dispose();
		//////////////////////////////////
	}

}
