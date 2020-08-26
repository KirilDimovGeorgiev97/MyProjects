package com.example.demo.entity;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class Board {
	
	private static Board board=null;
	public int sizeOfBoard;
	public char [][]BoardStatus;
	
	private Board() {
		super();
	}
	
	public static Board getInstance() {
		if(board==null) 
			board=new Board();
		return board;
			
	}
	
	public int getSizeOfBoard() {
		return sizeOfBoard;
	}

	public void setSizeOfBoard(int sizeOfBoard) {
		this.sizeOfBoard = sizeOfBoard;
	}

	public char[][] getBoardStatus() {
		return BoardStatus;
	}

	public void setBoardStatus(char[][] boardStatus) {
		BoardStatus = boardStatus;
	}
	
	
	public int getRandomNumber(int min, int max) {
	    return (int) ((Math.random() * (max - min)) + min);
	}
	

	
	public void generateBoard() {
		for(int i=0;i<this.sizeOfBoard;i++) {
			for(int j=0;j<this.sizeOfBoard;j++) {
				this.BoardStatus[i][j]='-';
			}
		}
	}
	
	public boolean checkBoardEmpty() {
		
		Map<Integer,List<Integer>> allMines=Mines.getInstance().getAllMines();
		
		int count = 0;
		int count2 = 0;
		
		for(int i=0;i<this.sizeOfBoard;i++) {
			System.out.println(i+"  ");
			for(int j=0;j<this.sizeOfBoard;j++) {
				System.out.print(this.BoardStatus[i][j]);
				if(this.BoardStatus[i][j]==' ')  
					continue;
				else
					if(allMines.containsKey(Integer.valueOf(i)) && allMines.get(Integer.valueOf(i)).contains(Integer.valueOf(j)))
						count++;
			}
		}
		for (Map.Entry<Integer,List<Integer>> entry : allMines.entrySet()) {
		    count2+=entry.getValue().size();
		}
		if(count==count2)
			return true;
		else
			return false;
	}
	
	public void displayBoard2() {
		
		System.out.print("    ");
		for(int i=0; i<this.sizeOfBoard;i++) {
			if(i == this.sizeOfBoard-1) {
				System.out.println(i);
				break;
			}
			if(this.sizeOfBoard<=9)
				System.out.print(i+" ");
			else
				if(i<=9)
					System.out.print(i+"  ");
				else
					System.out.print(i+" ");
		}
		
		for(int i=0;i<this.sizeOfBoard;i++) {
			if(i<=9)
				System.out.print(i+"   ");
			else
				System.out.print(i+"  ");
			for(int j=0;j<this.sizeOfBoard;j++) {
				if(Mines.getInstance().getAllMines().containsKey(Integer.valueOf(i)) && Mines.getInstance().getAllMines().get(Integer.valueOf(i)).contains(Integer.valueOf(j)))
					this.BoardStatus[i][j]='*';
				if(this.sizeOfBoard<=9)
					System.out.print(this.BoardStatus[i][j] + " ");
				else 
					System.out.print(this.BoardStatus[i][j] + "  ");
			}
			System.out.println();
		}
	}
	
	public void displayBoard() {
		
		System.out.print("    ");
		for(int i=0; i<this.sizeOfBoard;i++) {
			if(i == this.sizeOfBoard-1) {
				System.out.println(i);
				break;
			}
			if(this.sizeOfBoard<=9)
				System.out.print(i+" ");
			else
				if(i<=9)
					System.out.print(i+"  ");
				else
					System.out.print(i+" ");
		}
		
		for(int i=0;i<this.sizeOfBoard;i++) {
			if(i<=9)
				System.out.print(i+"   ");
			else
				System.out.print(i+"  ");
			for(int j=0;j<this.sizeOfBoard;j++) {
				if(this.sizeOfBoard<=9)
					System.out.print(this.BoardStatus[i][j] + " ");
				else 
					System.out.print(this.BoardStatus[i][j] + "  ");
			}
			System.out.println();
		}
	}
	
	public boolean enterMove(int a, int b) {
		Map<Integer,List<Integer>> allMines=Mines.getInstance().getAllMines();
		
		int count=0;
		
		if(allMines.containsKey(Integer.valueOf(a)) && allMines.get(Integer.valueOf(a)).contains(Integer.valueOf(b)))
			return false;
		else{
			for(int i = -1;i<2;i++) {
				
				for(int j=-1;j<2;j++) {
					if(a+i==a && b+j==b)
						continue;
					System.out.print(a+i + " " + (b+j) + " ");
					if(allMines.containsKey(Integer.valueOf(a+i)) && allMines.get(Integer.valueOf(a+i)).contains(Integer.valueOf(b+j)))
						count++;
				}
				System.out.println();
			}
			System.out.println();
			if(count>0)
				this.BoardStatus[a][b] = Character.forDigit(count,10);
			else {
				this.BoardStatus[a][b] = ' ';
				for(int i = -1;i<2;i++) {
					for(int j=-1;j<2;j++) {
						if(a+i==a && b+j==b)
							continue;
						try {
							this.BoardStatus[a+i][b+j] = ' ';
						}catch(IndexOutOfBoundsException e) {

						}
					}
				}
			}
		}
		return true;
	}
	
}