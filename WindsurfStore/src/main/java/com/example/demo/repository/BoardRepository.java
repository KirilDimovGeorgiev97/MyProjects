package com.example.demo.repository;

import java.util.List;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;
import com.example.demo.entity.Board;




@Repository

public interface BoardRepository extends CrudRepository<Board,Long> {

	List<Board> findByName(String name);
	List<Board> findByType(String type);
	List<Board> findByNameAndType(String name, String type);
	List<Board> findByNameOrderByIdDesc(String name);

}
