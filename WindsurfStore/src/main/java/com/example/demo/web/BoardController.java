package com.example.demo.web;

import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import com.example.demo.entity.Board;
import com.example.demo.entity.Sail;
import com.example.demo.repository.BoardRepository;
import com.example.demo.repository.SailRepository;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

import javax.websocket.server.PathParam;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.repository.CrudRepository;
//import org.springframework.http.HttpMethod;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;


@RestController
public class BoardController {

	@Autowired 
	private BoardRepository boardRepository;
	@Autowired
	private SailRepository sailRepository;
	
	@RequestMapping(value="/board", method=RequestMethod.POST)
	public ResponseEntity<Board> addBoard(@RequestBody Board board){
		boardRepository.save(board);
		return new ResponseEntity<>(HttpStatus.CREATED);
	}
	
	@RequestMapping(value="/boards", method=RequestMethod.GET) 
	public ResponseEntity<List<Board>> findAll(){
		List<Board> boards = new ArrayList<>();
		boardRepository.findAll().forEach(boards::add);
		for(Board a:boards)
			a.setSails(sailRepository.findByType(a.getType()));
		return new ResponseEntity<>(boards, HttpStatus.OK);
	}
	
	@RequestMapping(value="/board/{id}", method=RequestMethod.GET)
	public ResponseEntity<Board> findById(@PathVariable(value = "id") Long id){
		Optional <Board> boardOpt = boardRepository.findById(id);   
		if(boardOpt.isPresent()) {
			return new ResponseEntity<>(boardOpt.get(), HttpStatus.OK);
		}
		return new ResponseEntity<>(HttpStatus.NOT_FOUND);
	}
	
	@RequestMapping(value="/boardName/{name}", method=RequestMethod.GET)
	public ResponseEntity<List<Board>> findByName(@PathVariable(value = "name") String name){ 
		if(name == null || name.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.BAD_REQUEST);
		}
		List<Board> boards = boardRepository.findByName(name);
		if(boards.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.NOT_FOUND);
		}
		return new ResponseEntity<>(boards, HttpStatus.OK);
	}
	
	@RequestMapping(value="/boardType/{type}", method=RequestMethod.GET)
	public ResponseEntity<List<Board>> findByType(@PathVariable(value = "type") String type){ 
		if(type == null || type.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.BAD_REQUEST);
		}
		List<Board> boards = boardRepository.findByType(type);
		if(boards.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.NOT_FOUND);
		}
		return new ResponseEntity<>(boards, HttpStatus.OK);
	}
	
	@RequestMapping(value="/boardName/{name}/type/{type}", method=RequestMethod.GET)
	public ResponseEntity<List<Board>> findBooks(@PathVariable String name, @PathVariable String type){
		if(name == null || name.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.BAD_REQUEST);
		}
		List<Board> boards = boardRepository.findByNameAndType(name,type);
		if(boards.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.NOT_FOUND);
		}
		return new ResponseEntity<>(boards, HttpStatus.OK);
	}
	
	@RequestMapping(value="/boarD", method=RequestMethod.PUT)
	public ResponseEntity<Board> updateBook(@RequestBody Board board){ 
		if(board.getId() == null) {
			return new ResponseEntity<>(HttpStatus.BAD_REQUEST);
		}
		Optional<Board> boardOpt = boardRepository.findById(board.getId());
		if(!boardOpt.isPresent()) {
			return new ResponseEntity<>(HttpStatus.BAD_REQUEST);
		}
		Board updatedRecord = boardRepository.save(board);
		return new ResponseEntity<>(updatedRecord, HttpStatus.ACCEPTED);
	}
	
	@RequestMapping(value="/boarDName/{name}", method=RequestMethod.DELETE)
	public ResponseEntity<List<Board>> deleteByName(@PathVariable(value = "name") String name){ 
		if(name == null || name.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.BAD_REQUEST);
		}
		List<Board> boards = boardRepository.findByName(name);
		if(boards.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.NOT_FOUND);
		}
		boards.forEach(boardRepository::delete);
		return new ResponseEntity<>(HttpStatus.OK);

	}
	
	
	
}
