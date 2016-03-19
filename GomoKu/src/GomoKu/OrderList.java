package GomoKu;

import java.util.ArrayList;

public class OrderList {
	ArrayList <String> list = new ArrayList<String>();
	int first = 1;
	int sum = 0;
	int[][] array = new int[15][15];
	public void changeFirst(int i){
		first = i;
	}
	public int getSum(){
		return sum;
	}
	public void addNewGo(String newGo){
		list.add(newGo);
		int row = newGo.charAt(0) - 'A';
		int line = newGo.charAt(1) - '1';
		if(list.size()%2 == 0)
			array[line][row] = 2;
		else
			array[line][row] = 1;
		sum++;
	}
	public void undo(){
		int row = list.get(sum - 1).charAt(0) - 'A';
		int line = list.get(sum - 1).charAt(1) - '1';
		array[line][row] = 0;
		list.remove(sum - 1);
		sum--;
		int row2 = list.get(sum - 1).charAt(0) - 'A';
		int line2 = list.get(sum - 1).charAt(1) - '1';
		array[line2][row2] = 0;
		list.remove(sum - 1);
		sum--;
	}
	public void reset(){
		list.clear();
		for(int i=0;i<15;i++)
			for(int j=0;j<15;j++)
				array[i][j] = 0;
	}
	public int check(String newGo){
		int length = list.size();
		for(int i=0; i < length ; i++){
			if(newGo.equals(list.get(i)))
				return -1;
		}
		return 0;
	}
	public int checkGomokuWin(){
		int winWay = 0;
		for(int i=0;i<15;i++){		
			for(int j=0;j<15;j++){
				if(array[i][j] != 0){
					if((i + 4 < 15) 
							&&(array[i+1][j] == array[i][j])
							&&(array[i+2][j] == array[i][j])
							&&(array[i+3][j] == array[i][j])
							&&(array[i+4][j] == array[i][j])
							){
						winWay = array[i][j];
						break;
					}
					if((j + 4 < 15)
							&&(array[i][j+1] == array[i][j])
							&&(array[i][j+2] == array[i][j])
							&&(array[i][j+3] == array[i][j])
							&&(array[i][j+4] == array[i][j])
							){
						winWay = array[i][j];
						break;
					}
					if((i + 4 < 15)
							&&(j + 4 < 15)
							&&(array[i+1][j+1] == array[i][j])
							&&(array[i+2][j+2] == array[i][j])
							&&(array[i+3][j+3] == array[i][j])
							&&(array[i+4][j+4] == array[i][j])
							){
						winWay = array[i][j];
						break;
					}
					if((i - 4 >= 0)
							&&(j + 4 < 15)
							&&(array[i-1][j+1] == array[i][j])
							&&(array[i-2][j+2] == array[i][j])
							&&(array[i-3][j+3] == array[i][j])
							&&(array[i-4][j+4] == array[i][j])
							){
						winWay = array[i][j];
						break;
					}
				}
			}
			if(winWay != 0)
				break;
		}
		return winWay;
	}

}
