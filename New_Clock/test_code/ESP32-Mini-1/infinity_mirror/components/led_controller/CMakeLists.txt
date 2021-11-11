if(IDF_VERSION_MAJOR GREATER_EQUAL 4)
    idf_component_register(SRC_DIRS ./
        REQUIRES log driver
	REQUIRES esp32-neopixel
	REQUIRES protocol_examples_common
	REQUIRES nvs_flash
        INCLUDE_DIRS ./)
else()
    set(COMPONENT_SRCDIRS ./)
    set(COMPONENT_ADD_INCLUDEDIRS ./)
    set(COMPONENT_REQUIRES log driver)
    register_component()
endif()
