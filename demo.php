<?php
	require 'class.Address.inc';
	
	echo '<h2>Instanciamos la clase Address</h2>';
	$address = new Address();
	
	echo '<h2>Rellenamos sus propiedades</h2>';
	$address->street_address_1 = '555 Fake Street';
	$address->city_name = 'Townsville';
	$address->subdivision_name = 'State';
	$address->postal_code = '12345';
	$address->country_name = 'United States of America';
	
	// mostramos la matriz con las propiedades en forma de código para hacer debug
	echo '<code><pre>' . var_export($address, TRUE) . '</pre></code>';
	
	echo '<h2>Salida de la dirección con formato</h2>';
	echo $address->display();
	
	echo '<h2>Probamos __get y __set</h2>';
	// eliminamos el código postal antes definido, para poder comprobar si se lanza el LOOKUP en la db
	unset($address->postal_code);
	echo $address->display();
	
	echo '<h2>Creamos una dirección mediante la matriz</h2>';
	$address_2 = new Address(array(
			'street_address_1' => '123 Phony Ave',
			'city_name' => 'Vilageland',
			'subdivision_name' => 'Region',
			'postal_code' => '67890',
			'country_name' => 'Canada',
	));
	echo $address_2->display();
	
	echo '<h2>Dirección a cadena mediante __toString</h2>';
	echo $address_2;
?>