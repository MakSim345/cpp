A thread safe, simple and flexible C++ logging library (based on templates)

## Usage Example

```C++
	// set logging level (as default DEBUG3)
	Log::ReportingLevel() = Log::LevelFromString( "WARNING" );
	
	// initialize a log file
	LOG_FILE_INIT( "MyLog.log" );
	
	LOG_IS_OUTPUT_TIME( true );
	
	// writes message in the log file
	LOG_INFO << "Initialize the log file!";

	LOG_IS_OUTPUT_TIME( false );
	
	// int _l[] = { 4, 8, 15, 16, 23, 42 };
	LOG_DEBUG << "LOST numbers: "<<_l[0]<<_l[1]<<_l[2]<<_l[3]<<_l[4]<<_l[5]<<" end.\n";
	
	// after this, all next messages will be output to the console
	LOG_USE_STDERR;
	
	LOG_INFO << "end of the world in 10 minutes...\n" << "please press a button";
	
	// again writes message in the log file ...
	LOG_USE_FILE;
	
	LOG_ERROR << "now the end of the world\n";
```

## License

Public domain.