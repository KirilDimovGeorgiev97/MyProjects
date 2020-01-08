package com.example.demo.web;

import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.DeleteMapping;
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
import javax.persistence.TransactionRequiredException;

import javax.websocket.server.PathParam;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.repository.CrudRepository;
//import org.springframework.http.HttpMethod;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;

@RestController
public class SailController {
	
	@Autowired 
	private SailRepository sailRepository;
	@Autowired
	private BoardRepository boardRepository;
	
	@RequestMapping(value="/sail", method=RequestMethod.POST)
	public ResponseEntity<Sail> addSail(@RequestBody Sail sail){
		sailRepository.save(sail);
		return new ResponseEntity<>(HttpStatus.CREATED);
	}
	
	@RequestMapping(value="/sails", method=RequestMethod.GET) 
	public ResponseEntity<List<Sail>> findAll(){
		List<Sail> sails = new ArrayList<>();
		sailRepository.findAll().forEach(sails::add);
		return new ResponseEntity<>(sails, HttpStatus.OK);
	}
	
	@RequestMapping(value="/sail/{id}", method=RequestMethod.GET)
	public ResponseEntity<Sail> findById(@PathVariable(value = "id") Long id){
		Optional <Sail> sailOpt = sailRepository.findById(id);   
		if(sailOpt.isPresent()) {
			return new ResponseEntity<>(sailOpt.get(), HttpStatus.OK);
		}
		return new ResponseEntity<>(HttpStatus.NOT_FOUND);
	}
	
	@RequestMapping(value="/sailName/{name}", method=RequestMethod.GET)
	public ResponseEntity<List<Sail>> findByName(@PathVariable(value = "name") String name){ 
		if(name == null || name.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.BAD_REQUEST);
		}
		List<Sail> sails = sailRepository.findByName(name);
		if(sails.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.NOT_FOUND);
		}
		return new ResponseEntity<>(sails, HttpStatus.OK);
	}
	
	@RequestMapping(value="/sailType/{type}", method=RequestMethod.GET)
	public ResponseEntity<List<Sail>> findByType(@PathVariable(value = "type") String type){ 
		if(type == null || type.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.BAD_REQUEST);
		}
		List<Sail> sails = sailRepository.findByType(type);
		if(sails.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.NOT_FOUND);
		}
		return new ResponseEntity<>(sails, HttpStatus.OK);
	}
	
	@RequestMapping(value="/sailName/{name}/type/{type}", method=RequestMethod.GET)
	public ResponseEntity<List<Sail>> findBooks(@PathVariable String name, @PathVariable String type){
		if(name == null || name.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.BAD_REQUEST);
		}
		List<Sail> sails = sailRepository.findByNameAndType(name,type);
		if(sails.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.NOT_FOUND);
		}
		return new ResponseEntity<>(sails, HttpStatus.OK);
	}
	
	@RequestMapping(value="/saiL", method=RequestMethod.PUT)
	public ResponseEntity<Sail> updateBook(@RequestBody Sail sail){ 
		if(sail.getId() == null) {
			return new ResponseEntity<>(HttpStatus.BAD_REQUEST);
		}
		Optional<Sail> sailOpt = sailRepository.findById(sail.getId());
		if(!sailOpt.isPresent()) {
			return new ResponseEntity<>(HttpStatus.BAD_REQUEST);
		}
		Sail updatedRecord = sailRepository.save(sail);
		return new ResponseEntity<>(updatedRecord, HttpStatus.ACCEPTED);
	}
	
	@DeleteMapping(value="/saiLName/{name}")
	public ResponseEntity<List<Sail>> deleteByName(@PathVariable(value = "name") String name){ 
		if(name == null || name.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.BAD_REQUEST);
		}
		List<Sail> sails = sailRepository.findByName(name);
		if(sails.isEmpty()) {
			return new ResponseEntity<>(HttpStatus.NOT_FOUND);
		}
		sails.forEach(sailRepository::delete);
		return new ResponseEntity<>(HttpStatus.OK);

	}
}
