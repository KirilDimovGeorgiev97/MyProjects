package com.example.demo;

import java.util.HashMap;
import java.util.Scanner;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import com.example.demo.entity.Board;
import com.example.demo.entity.Mines;

@SpringBootApplication
public class MinesweeperGameApplication {
	public static final String intro = "Enter the Difficulty level:";
	public static final String levelBeginner = "Press 0 for BEGINNER (9*9 Cells and 10 Mines)";
	public static final String levelIntermediate = "Press 1 for INTERMEDIATE (16*16 Cells and 40 Mines)";
	public static final String levelAdvanced = "Press 2 for ADVANCED (24*24 Cells and 99 mines)";
	public static final String currStatus = "Current Status of Board:";
	public static final String enter="Enter your move,(row,move) \n ->";
	public static final String lost="You lost!";
	public static final String win="You won!";
	
	public static int n;
	public static int numberOfMines;
	public static boolean checkGame = true;

	public static void main(String[] args) {
		SpringApplication.run(MinesweeperGameApplication.class, args);
		Scanner sc = new Scanner(System.in);
		
		System.out.println("intro");
		System.out.println(levelBeginner);
		System.out.println(levelIntermediate);
		System.out.println(levelAdvanced);
		
		
		int input = sc.nextInt();
		
		if(input==0) {
			n=9;
			numberOfMines=10;
		}else if(input==1) {
			n=16;
			numberOfMines=40;
		}else {
			n=24;
			numberOfMines=99;
		}
		Board board = Board.getInstance();
		board.setSizeOfBoard(n);
		board.setBoardStatus(new char[n][n]);
		board.generateBoard();
		
		Mines mines = Mines.getInstance();
		mines.setNumberOfMines(numberOfMines);
		mines.setAllMines(new HashMap<>());
		mines.generateMines(board.getSizeOfBoard());
		sc.nextLine();
		while(checkGame) {
			System.out.println(enter);
		
			
			board.displayBoard();
		

			String input2=sc.nextLine();
			
			int row = Integer.parseInt(input2.split("\\s+")[0]);
			int column = Integer.parseInt(input2.split("\\s+")[1]);
			
			checkGame=board.enterMove(row, column);
			if(!checkGame) {
				board.displayBoard2();
				System.out.println(lost);
				return ;
			}
			
			
			checkGame=board.checkBoardEmpty();
			System.out.println(board.checkBoardEmpty());
		}
		board.displayBoard2();
		System.out.println(win);
	}

}
