package com.example.demo.junit;

import static org.junit.Assert.*;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.junit.runner.JUnitCore;

import com.example.demo.entity.Board;
import com.example.demo.entity.Mines;

public class Test {

	@org.junit.Test
	public void test() {
		JUnitCore test=new JUnitCore();
		Board board = Board.getInstance();
		board.setSizeOfBoard(9);
		board.setBoardStatus(new char[9][9]);
		board.generateBoard();
		
		Mines mines = Mines.getInstance();
		mines.setNumberOfMines(10);
		mines.setAllMines(new HashMap<>());
		mines.generateMines(board.getSizeOfBoard());
		Integer key = null;
	    Integer value = null;
		
		for (Map.Entry<Integer,List<Integer>> entry : mines.getAllMines().entrySet()) {
		    key = entry.getKey();
		    value=entry.getValue().get(0);
		    break;
		}
		assertEquals(false,board.enterMove(key.intValue(),value.intValue()));
	}

}
