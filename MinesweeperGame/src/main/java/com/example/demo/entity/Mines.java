package com.example.demo.entity;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Mines {
	
	
	private static Mines mines;
	public int numberOfMines;
	public Map<Integer, List<Integer>> allMines = new HashMap<>(); 
	
	
	private Mines() {
		super();
	}
	
	public static Mines getInstance() {
		if(mines==null)
			mines=new Mines();
		return mines;
	}
	
	public int getNumberOfMines() {
		return this.numberOfMines;
	}

	public void setNumberOfMines(int numberOfMines) {
		this.numberOfMines = numberOfMines;
	}

	public Map<Integer, List<Integer>> getAllMines() {
		return this.allMines;
	}

	public void setAllMines(Map<Integer, List<Integer>> allMines) {
		this.allMines = allMines;
	}

	public void displayMines() {
		this.allMines.forEach((k,v) ->{System.out.println(k+":"+v);});
	}
		
	public void generateMines(int max) {
		int c=0;
		do {
			for(int i = 0;i<this.numberOfMines*2;i++) {
				
				int a = (int) ((Math.random() * (max - 0)) + 0);
				int b = (int) ((Math.random() * (max - 0)) + 0);
				//System.out.println(a+" "+b);
				
				if(allMines.containsKey(Integer.valueOf(a))) 
					if(allMines.get(Integer.valueOf(a)).contains(Integer.valueOf(b)))
						continue;
					else {
						allMines.get(Integer.valueOf(a)).add(b);
						c++;
					}
				else {
					allMines.put(Integer.valueOf(a), new ArrayList<Integer>());
				    allMines.get(Integer.valueOf(a)).add(Integer.valueOf(b));
				    c++;
				}
				if(c>=this.numberOfMines) {
					System.out.println(c);
					//allMines.forEach((k,v) ->{System.out.println(k+":"+v);});
			    	break;
				}
			}
			
			if(c>=this.numberOfMines) {
				
				break;
			}
		    	
			System.out.println(c);
			
		}while(c<numberOfMines);
	}
	

}
