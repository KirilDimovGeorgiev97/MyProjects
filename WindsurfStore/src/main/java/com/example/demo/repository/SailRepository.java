package com.example.demo.repository;


import java.util.List;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;
import com.example.demo.entity.Sail;

@Repository
public interface SailRepository extends CrudRepository<Sail,Long>  {

	List<Sail> findByName(String name);
	List<Sail> findByType(String type);
	List<Sail> findByNameAndType(String name, String type);
	List<Sail> findByNameOrderByIdDesc(String name);

}
