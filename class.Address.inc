<?php

    /**
     * Dirección física
     */
    class Address
    {
    	
    	// tipos de dirección mediante constantes
    	const ADDRESS_TYPE_RESIDENCE = 1;
    	const ADDRESS_TYPE_BUSINESS = 2;
    	const ADDRESS_TYPE_PARK = 3;
    	
    	// tipo de dirección usando las constantes antes añadidas
    	static public $valid_address_types = array(
    		self::ADDRESS_TYPE_RESIDENCE => 'Residence',
    		self::ADDRESS_TYPE_BUSINESS => 'Business',
    		self::ADDRESS_TYPE_PARK => 'Park',
    	);
    	
        // clave primaria para almacenar la dirección
        protected $_address_id;
        
        // tipo de id de la dirección
        protected $_address_type_id;
        
        // hora de creación y de actualización
        protected $_time_created;
        protected $_time_updated;
        
        // direcciones
        public $street_address_1;
        public $street_address_2;
        
        // ciudad
        public $city_name;
        
        // subdivision
        public $subdivision_name;
        
        // código postal
        protected $_postal_code;
        
        // país
        public $country_name;
        
        /**
         * Creamos un método constructor que se lanza al inicializar el objeto
         * El constructor tiene un parámetro en forma de matriz para insertar los valores de las ppiedades
         */
        function __construct($data = array()) {
        	$this->_time_created = time();
        	// comprobamos que efectivamente es una matriz
        	if (!is_array($data)) {
        		trigger_error('Unable to construct address with a ' . get_class($name)); // obtenemos el nombre de la clase
        	}
        	
        	// si hay algún valor, rellenamos los datos de la dirección
        	if (count($data) > 0) {
        		foreach ($data as $name => $value) {
        		// comprobamos si hay ppiedades protegidas y les añadimos el '_'
        			if(in_array($name, array(
        				'time_created',
        				'time_updated',
        			))) {
        			$name = '_' . $name;
        			}
        			$this->$name = $value; // le añadimos el valor a la ppiedad recorrida
        		}
        	}
        }
        
        /**
         * Usamos un método mágico __get para comprobar si el código postal está definido
         * Si no está definido, le damos el valor obtenido por _postal_code_guess
         */ 
        function __get($name) {
        	// comprobamos si está definido el CP, si no, lanzamos la función _postal_code_guess
        	if (!$this->_postal_code) {
        		$this->_postal_code = $this->_postal_code_guess();
        	}
        	
        	// tratamos de devolver una propiedad protegida por su nombre
        	$protected_property_name = '_' . $name;
        	// comprobamos si existe la propiedad pasada por argumento en la función
        	// si existe, la devolvemos
        	if (property_exists($this, $protected_property_name)) {
        		return $this->$protected_property_name;
        	}
        	// si no existe, lanzamos un error PHP
        	trigger_error('Undefined property via __get:' . $name);
        	return NULL;
        }
        
        function __set($name, $value) {
        	// añadimos una id válida de dirección
        	if ('address_type_id' == $name) {
        		$this->_setAddressTypeId($value);
        		return;
        	}
        	// permitimos insertar el valor de _postal_code
        	if ('postal_code' == $name) {
        		$this->$name = $value;
        		return;
        	}
        	// si no es el código postal, lanzamos un error
        	trigger_error('Undefined or unallow property via __set:' . $name);
        }
        
        /**
         * Usamos el método mágico __toString para dar salida en formato cadena
         * además lo colocamos en el constructor para obtener el resultado automático
         */
        function __toString() {
        	return $this->display();
        }
        
        /**
         * Creamos un método para averiguar el código postal si éste no está definido
         */
        protected function _postal_code_guess() {
        	return 'LOOKUP';
        }
        
        /**
         * Mostramos la dirección en HTML formateado
         * @return string
         */
        public function display() {
        	$output = '';
        	
        	// mostramos la dirección
        	$output .= $this->street_address_1;
        	if ($this->street_address_2) {
        		$output .= '<br/>' . $this->street_address_2;
        	}
        	
        	// ciudad y código postal
        	$output .= '<br/>';
        	$output .= $this->city_name . ', ' . $this->subdivision_name;
        	$output .= ' ' . $this->postal_code;
        	
        	// país
        	$output .= '<br/>';
        	$output .= $this->country_name;
        	return $output;
        }
        
        /**
         * Determinamos si un tipo de dirección es válida
         */
        static public function isValidAddressTypeId($address_type_id) {
        	// comprobamos si existe la clave dentro de la matriz de los tipos de dirección
        	return array_key_exists($address_type_id, self::$valid_address_types);
        }
        
        /**
         * Si es válida la id de dirección, se establece mediante set (en el magic method set de arriba)
         * @param integer $address_type_id
         */
        protected function _setAddressTypeId($address_type_id) {
        	if(self::isValidAddressTypeId($address_type_id)) {
        		$this->_address_type_id = $address_type_id;
        	}
        }

    }

?>
