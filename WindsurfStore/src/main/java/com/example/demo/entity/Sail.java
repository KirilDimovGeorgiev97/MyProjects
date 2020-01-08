package com.example.demo.entity;

import java.util.List;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToMany;
import javax.persistence.ManyToOne;


@Entity

public class Sail {
	
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	
	private Long id;
	private String name;
	private String type;
	private Float size;
	@ManyToMany(mappedBy ="sails")
	
	private List<Board> boards;
	
	public List<Board> getBoards() {
		return boards;
	}
	
	public void setBoards(List<Board> boards) {
		this.boards = boards;
	}
	
	public Long getId() {
		return id;
	}
	
	public void setId(Long id) {
		this.id = id;
	}
	
	public String getName() {
		return name;
	}
	
	public void setName(String name) {
		this.name = name;
	}
	
	public String getType() {
		return type;
	}
	
	public void setType(String type) {
		this.type = type;
	}
	
	public Float getSize() {
		return size;
	}
	
	public void setSize(Float size) {
		this.size = size;
	}
	
	
}
